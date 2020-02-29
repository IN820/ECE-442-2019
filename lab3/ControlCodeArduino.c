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
