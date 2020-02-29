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
