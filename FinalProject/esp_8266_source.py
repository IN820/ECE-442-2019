# -*- coding: utf-8 -*-
import dht
import json
import network
import time
import machine
from ubinascii import hexlify
from machine import Pin, unique_id, Signal, PWM
from machine import ADC, Pin
from umqtt.robust import MQTTClient

# 连接的GPIO口
pin_dht = 5
pin_per = 4
pin_light = 0
pin_door = 12
pin_switch1 = 13
pin_switch2 = 14
PIN_BUZZER = 15
PIN_LIGHT = 16
INVERT = False


# 读取配置文件
with open('config.json') as f:
    CONFIG = json.loads(f.read())
    print("Load Config: {b}".format(b=CONFIG))

# MQTT主题 - light
DEVICE_NAMEled = 'SimepleLight_' + hexlify(unique_id()).decode()

BASE_TOPICled = 'hachina/sensor/' + DEVICE_NAMEled
AVAILABILITY_TOPICled = BASE_TOPICled + "/availability"
STATE_TOPICled = BASE_TOPICled + "/state"
COMMAND_TOPICled = BASE_TOPICled + "/command"

# MQTT主题 - 温度
DEVICE_NAME = 'TemperatureSensor_' + hexlify(unique_id()).decode()

BASE_TOPIC = 'hachina/sensor/' + DEVICE_NAME
AVAILABILITY_TOPIC = BASE_TOPIC + "/availability"
STATE_TOPIC = BASE_TOPIC + "/state"

# MQTT主题 - 湿度
DEVICE_NAMEhum = 'HumiditySensor_' + hexlify(unique_id()).decode()

BASE_TOPIChum = 'hachina/sensor/' + DEVICE_NAMEhum
AVAILABILITY_TOPIChum = BASE_TOPIChum + "/availability"
STATE_TOPIChum = BASE_TOPIChum + "/state"

# MQTT主题 - 人体
DEVICE_NAMEper = 'PeopleSensor_' + hexlify(unique_id()).decode()

BASE_TOPICper = 'hachina/sensor/' + DEVICE_NAMEper
AVAILABILITY_TOPICper = BASE_TOPICper + "/availability"
STATE_TOPICper = BASE_TOPICper + "/state"

# MQTT - light_sensor
DEVICE_NAMElig = 'LightSensor_' + hexlify(unique_id()).decode()

BASE_TOPIClig = 'hachina/sensor/' + DEVICE_NAMElig
AVAILABILITY_TOPIClig = BASE_TOPIClig + "/availability"
STATE_TOPIClig = BASE_TOPIClig + "/state"

# MQTT主题 - 门磁
DEVICE_NAMEd = 'DoorSensor_' + hexlify(unique_id()).decode()

BASE_TOPICd = 'hachina/sensor/' + DEVICE_NAMEd
AVAILABILITY_TOPICd = BASE_TOPICd + "/availability"
STATE_TOPICd = BASE_TOPICd + "/state"


# MQTT自动配置
DISCOVERY_CONFIG_TOPICled = 'homeassistant/light/' + DEVICE_NAMEled + '/config'
DISCOVERY_CONFIG_DATA_SCHEMAled = """
{"name": "%s",
"command_topic": "%s",
"state_topic": "%s",
"availability_topic": "%s"
}
"""
DISCOVERY_CONFIG_DATAled = DISCOVERY_CONFIG_DATA_SCHEMAled % (DEVICE_NAMEled,
                                                        COMMAND_TOPICled,
                                                        STATE_TOPICled,
                                                        AVAILABILITY_TOPICled
                                                        )

# MQTT自动配置 - 温度
DISCOVERY_CONFIG_TOPIC = 'homeassistant/sensor/' + DEVICE_NAME + '/config'
DISCOVERY_CONFIG_DATA_SCHEMA = """
{"name": "%s",
"state_topic": "%s",
"availability_topic": "%s",
"device_class": "illuminance",
"unit_of_measurement": "℃"
}
"""
DISCOVERY_CONFIG_DATA = DISCOVERY_CONFIG_DATA_SCHEMA % (DEVICE_NAME,
                                                        STATE_TOPIC,
                                                        AVAILABILITY_TOPIC
                                                        )
# MQTT自动配置 - 湿度
DISCOVERY_CONFIG_TOPIChum = 'homeassistant/sensor/' + DEVICE_NAMEhum + '/config'
DISCOVERY_CONFIG_DATA_SCHEMAhum = """
{"name": "%s",
"state_topic": "%s",
"availability_topic": "%s",
"device_class": "illuminance",
"unit_of_measurement": "RH"
}
"""
DISCOVERY_CONFIG_DATAhum = DISCOVERY_CONFIG_DATA_SCHEMAhum % (DEVICE_NAMEhum,
                                                        STATE_TOPIChum,
                                                        AVAILABILITY_TOPIChum
                                                        )

# MQTT自动配置 - 人体
DISCOVERY_CONFIG_TOPICper= 'homeassistant/sensor/' + DEVICE_NAMEper + '/config'
DISCOVERY_CONFIG_DATA_SCHEMAper = """
{"name": "%s",
"state_topic": "%s",
"availability_topic": "%s",
"device_class": "illuminance"
}
"""
DISCOVERY_CONFIG_DATAper = DISCOVERY_CONFIG_DATA_SCHEMAper % (DEVICE_NAMEper,
                                                        STATE_TOPICper,
                                                        AVAILABILITY_TOPICper
                                                        )

# MQTT auto setup - motion
DISCOVERY_CONFIG_TOPIClig= 'homeassistant/sensor/' + DEVICE_NAMElig + '/config'
DISCOVERY_CONFIG_DATA_SCHEMAlig = """
{"name": "%s",
"state_topic": "%s",
"availability_topic": "%s",
"device_class": "illuminance"
}
"""
DISCOVERY_CONFIG_DATAlig = DISCOVERY_CONFIG_DATA_SCHEMAlig % (DEVICE_NAMElig,
                                                        STATE_TOPIClig,
                                                        AVAILABILITY_TOPIClig
                                                        )

# MQTT自动配置 - 门磁
DISCOVERY_CONFIG_TOPICd= 'homeassistant/sensor/' + DEVICE_NAMEd + '/config'
DISCOVERY_CONFIG_DATA_SCHEMAd = """
{"name": "%s",
"state_topic": "%s",
"availability_topic": "%s",
"device_class": "illuminance"
}
"""
DISCOVERY_CONFIG_DATAd = DISCOVERY_CONFIG_DATA_SCHEMAd % (DEVICE_NAMEd,
                                                        STATE_TOPICd,
                                                        AVAILABILITY_TOPICd
                                                        )
def mqtt_cb(topic, msg):

    global mqtt, light

    print("the line is read")
    print((topic, msg))
    if topic==COMMAND_TOPICled.encode():
        if msg == b"ON":
            light.on()
        elif msg == b"OFF":
            light.off()
            
        mqtt.publish( STATE_TOPICled,
                      b"ON" if light.value() else b"OFF",
                      retain=True )
            

def init():
    global mqtt, dht_sensor, per_sensor, light_sensor, door_sensor, light,buzzer, switch1, switch2
    #LED
    light = Signal(Pin(PIN_LIGHT, Pin.OUT), invert=INVERT)
    #buzzer
    buzzer = PWM(Pin(PIN_BUZZER),freq = 440)
    # dht11
    dht_sensor = dht.DHT11(machine.Pin(pin_dht))
    # light sensor
    light_sensor = machine.ADC(pin_light)
    # 门磁开关
    door_sensor = Pin(pin_door, Pin.IN, Pin.PULL_UP)    # 门磁 close：1 ，open：0
    # 人体传感器
    per_sensor = Pin(pin_per, Pin.IN, Pin.PULL_UP)       #人体红外 1：有人， 0：无人
    # switch
    switch1 = Pin(pin_switch1, Pin.IN, Pin.PULL_UP)
    switch2 = Pin(pin_switch2, Pin.IN, Pin.PULL_UP)

    # wifi init
    ap_if = network.WLAN(network.AP_IF)
    sta_if = network.WLAN(network.STA_IF)
    ap_if.active(False)
    sta_if.active(True)
    sta_if.connect(CONFIG.get("wifi_ssid"),
                   CONFIG.get("wifi_password")
                   )
    time.sleep(10)
    if sta_if.isconnected():
        print("WIFI connected")
    else:
        print("Can't connect to WIFI")
        return False

    # MQTT init
    mqtt = MQTTClient(client_id=DEVICE_NAME,
                      server=CONFIG.get("mqtt_server"),
                      port=CONFIG.get("mqtt_port"),
                      user=CONFIG.get("mqtt_user"),
                      password=CONFIG.get("mqtt_password"),
                      keepalive=60)
    mqtt.set_last_will(AVAILABILITY_TOPICled, b"offline", retain=True)
    mqtt.set_last_will(AVAILABILITY_TOPIC, b"offline", retain=True)
    mqtt.set_last_will(AVAILABILITY_TOPIChum, b"offline", retain=True)
    mqtt.set_last_will(AVAILABILITY_TOPICper, b"offline", retain=True)
    mqtt.set_last_will(AVAILABILITY_TOPIClig, b"offline", retain=True)
    mqtt.set_last_will(AVAILABILITY_TOPICd, b"offline", retain=True)
    try:
        mqtt.connect()
        print("MQTT connected")
        mqtt.publish(DISCOVERY_CONFIG_TOPICled, DISCOVERY_CONFIG_DATAled.encode(), retain=True)
        mqtt.publish(DISCOVERY_CONFIG_TOPIC, DISCOVERY_CONFIG_DATA.encode(), retain=True)
        mqtt.publish(DISCOVERY_CONFIG_TOPIChum, DISCOVERY_CONFIG_DATAhum.encode(), retain=True)
        mqtt.publish(DISCOVERY_CONFIG_TOPICper, DISCOVERY_CONFIG_DATAper.encode(), retain=True)
        mqtt.publish(DISCOVERY_CONFIG_TOPIClig, DISCOVERY_CONFIG_DATAlig.encode(), retain=True)
        mqtt.publish(DISCOVERY_CONFIG_TOPICd, DISCOVERY_CONFIG_DATAd.encode(), retain=True)
        mqtt.publish(AVAILABILITY_TOPICled, b"online", retain=True)
        mqtt.publish(AVAILABILITY_TOPIC, b"online", retain=True)
        mqtt.publish(AVAILABILITY_TOPIChum, b"online", retain=True)
        mqtt.publish(AVAILABILITY_TOPICper, b"online", retain=True)
        mqtt.publish(AVAILABILITY_TOPIClig, b"online", retain=True)
        mqtt.publish(AVAILABILITY_TOPICd, b"online", retain=True)
    except OSError as e:
        print("Can't connect to MQTT Broker: %r" % e)
        return False

    return True


def start():
    global mqtt, light_sensor, per_sensor, dht_sensor, door_sensor, light,buzzer, switch1, switch2

    while init() == False:
        time.sleep(10)
    while True:
        dht_sensor.measure()
        luxtem = dht_sensor.temperature()
        luxhum = dht_sensor.humidity()
        people = per_sensor.value()
        doors = door_sensor.value()

        # report to mqtt - temperature/humidity
        mqtt.publish(STATE_TOPIC, str(luxtem).encode(), retain=True)
        mqtt.publish(STATE_TOPIChum, str(luxhum).encode(), retain=True)

        if switch1.value() == 1 and switch2.value() == 1:
            print("auto mode: in home")
            
            val = light_sensor.read()
            val = (1024 - val)/10
            print(val)
            
            if val > 50:
                light.off()
                mqtt.publish( STATE_TOPICled, b"OFF", retain=True )
            else:
                if people == 1:
                    mqtt.publish(STATE_TOPICper, 'on', retain=True)
                    print("People Detected")
                    light.on()
                    mqtt.publish( STATE_TOPICled, b"ON", retain=True)
                    time.sleep(1)
                else:
                    mqtt.publish(STATE_TOPICper, 'off', retain=True)
                    light.off()
                    mqtt.publish( STATE_TOPICled, b"OFF", retain=True )
            
            # 向mqtt传值 - light sensor
            mqtt.publish(STATE_TOPIClig, str(val).encode(), retain=True)
            
            if people == 1:
                mqtt.publish(STATE_TOPICper, 'on', retain=True)
                print("People Detected")
            else:
                mqtt.publish(STATE_TOPICper, 'off', retain=True)

            time.sleep(2)
        if switch1.value() == 1 and switch2.value() == 0:
            print("manual mode: on")
            light.on()
            mqtt.publish( STATE_TOPICled, b"ON", retain=True )
            time.sleep(2)
        if switch1.value() == 0 and switch2.value() ==0:
            print("manual mode: off") 
            light.off()
            mqtt.publish( STATE_TOPICled, b"OFF", retain=True )
            time.sleep(2)
        if switch1.value() == 0 and switch2.value() == 1:
            working = True
            print("auto mode: out home")

            if doors == 0:
                mqtt.publish(STATE_TOPICd, 'open', retain=True)
                print("Door is open")
                #light.on()
                buzzer.duty(256)
                time.sleep(1)
                buzzer.deinit()
                time.sleep(1)
                buzzer.duty(256)
                time.sleep(1)
                buzzer.deinit()
                time.sleep(1)
            else:
                mqtt.publish(STATE_TOPICd, 'close', retain=True)
                print("monitoring")
                #light.off()
                working = False
                time.sleep(5)        
            





