#include <SoftwareSerial.h>
#define sensor_pin A0 //define pin of the sensor
SoftwareSerial mySerial(2, 4); // RX, TX
void setup() {
// Open serial communications and wait for port to open: Serial.begin(115200);
mySerial.begin(115200);
while (!Serial) {
; // wait for serial port to connect. Needed for native USB port only
}
pinMode(sensor_pin, INPUT); //set up sensor pin(A0)
Serial.println("Start Communication");
}
void loop()
{ // run over and over if(Serial.available())
{mySerial.write(Serial.read()); }
if(mySerial.available())
{ Serial.write(mySerial.read()); }
int raw_data_sensor = analogRead(A0); //read raw data
float sensor_value = (float)raw_sensor_value*500;
float sensor_value_celsius = sensor_value / 1024; //calculate Celsius
float sensor_Fah = 32 + (sensor_value_celsius * 9)/5; //calculate F.
char sensor_temp[10];
dtostrf(sensor_Fah, 2, 2, sensor_temp); //formatting
char str_output[10];
sprintf(str_output, "%sF", sensor_temp); //print
Serial.write(str_output);
mySerial.write(sensor_Fah); //send data using BT
Serial.println(" Bluetooth transmission complete"); //print end of each transmission
Delay(1000); //delay 1s
}
Code implemented for Raspberry Pi board
import bluetooth # needed for bluetooth communication
import thingspeak # needed for thingspeak
bluetooth_addr = "00:14:03:05:5A:C8" # The address from the HC-05 sensor (MAC address)
bluetooth_port = 1 # Channel 1 for RFCOMM(need no change)
bluetoothSocket = bluetooth.BluetoothSocket (bluetooth.RFCOMM)
bluetoothSocket.connect((bluetooth_addr,bluetooth_port))
#thingspeak information
channel_id = 802625 # channel ID from your Thingspeak channel
key = G9SLIL2VZ9B46PQ0 #'S_WRITE_API_KEY # obtain from Thingspeak (API key)
url = 'https://api.thinkspeak.com/update' # default URL to update Thingspeak (need no change)
ts = thingspeak.Channel(channel_id, key, url)
while 1:
try:
received_data = bluetoothSocket.recv(1024)
temperature = int.from_bytes(received_data,byteorder='big')
print("Current Temperature: %d" % temperature)
thingspeak_field1 = {"field1": temperature}
ts.update(thingspeak_field1) # update thingspeak
except KeyboardInterrupt:
print("keyboard interrupt detected")
break
bluetoothSocket.close()
