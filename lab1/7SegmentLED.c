const int pin1A = 8; //These are all identifying the binary inputs of
const int pin2A = 9; //the 4511 Seven Segment Decoder
const int pin3A = 10;
const int pin4A = 11;
const int pin1B = 2; //These are all identifying the binary inputs of
const int pin2B = 3; //the 4511 Seven Segment Decoder
const int pin3B = 4;
const int pin4B = 5;
void setup()
{
pinMode(pin1A, OUTPUT);
pinMode(pin2A, OUTPUT);
pinMode(pin3A, OUTPUT);
pinMode(pin4A, OUTPUT);
pinMode(pin1B, OUTPUT);
pinMode(pin2B, OUTPUT);
pinMode(pin3B, OUTPUT);
pinMode(pin4B, OUTPUT);
}
void loop()
{
digitalWrite(pin1B, B0); //Write "0" to the display
digitalWrite(pin2B, B0);
digitalWrite(pin3B, B0);
digitalWrite(pin4B, B0);
sequenceA();
digitalWrite(pin1B, B1); //Write "1" to the display
digitalWrite(pin2B, B0);
digitalWrite(pin3B, B0);
digitalWrite(pin4B, B0);
sequenceA();
digitalWrite(pin1B, B0); //Write "2" to the display
digitalWrite(pin2B, B1);
digitalWrite(pin3B, B0);
digitalWrite(pin4B, B0);
sequenceA();
digitalWrite(pin1B, B1); //Write "3" to the display
digitalWrite(pin2B, B1);
digitalWrite(pin3B, B0);
digitalWrite(pin4B, B0);
sequenceA();
digitalWrite(pin1B, B0); //Write "4" to the display
digitalWrite(pin2B, B0);
digitalWrite(pin3B, B1);
digitalWrite(pin4B, B0);
sequenceA();
digitalWrite(pin1B, B1); //Write "5" to the display
digitalWrite(pin2B, B0);
digitalWrite(pin3B, B1);
digitalWrite(pin4B, B0);
sequenceA();
digitalWrite(pin1B, B0); //Write "6" to the display
digitalWrite(pin2B, B1);
digitalWrite(pin3B, B1);
digitalWrite(pin4B, B0);
sequenceA();
digitalWrite(pin1B, B1); //Write "7" to the display
digitalWrite(pin2B, B1);
digitalWrite(pin3B, B1);
digitalWrite(pin4B, B0);
sequenceA();
digitalWrite(pin1B, B0); //Write "8" to the display
digitalWrite(pin2B, B0);
digitalWrite(pin3B, B0);
digitalWrite(pin4B, B1);
sequenceA();
digitalWrite(pin1B, B1); //Write "9" to the display
digitalWrite(pin2B, B0);
digitalWrite(pin3B, B0);
digitalWrite(pin4B, B1);
sequenceA();
}
void sequenceA()
{
digitalWrite(pin1A, B0); //Write "0" to the display
digitalWrite(pin2A, B0);
digitalWrite(pin3A, B0);
digitalWrite(pin4A, B0);
delay(1000);
digitalWrite(pin1A, B1); //Write "1" to the display
digitalWrite(pin2A, B0);
digitalWrite(pin3A, B0);
digitalWrite(pin4A, B0);
delay(1000); //Wait for of a second (or else the numbers would be a blur)
digitalWrite(pin1A, B0); //Write "2" to the display
digitalWrite(pin2A, B1);
digitalWrite(pin3A, B0);
digitalWrite(pin4A, B0);
delay(1000); //Wait for of a second
digitalWrite(pin1A, B1); //Write "3" to the display
digitalWrite(pin2A, B1);
digitalWrite(pin3A, B0);
digitalWrite(pin4A, B0);
delay(1000); //Wait for of a second
digitalWrite(pin1A, B0); //Write "4" to the display
digitalWrite(pin2A, B0);
digitalWrite(pin3A, B1);
digitalWrite(pin4A, B0);
delay(1000); //Wait for of a second
digitalWrite(pin1A, B1); //Write "5" to the display
digitalWrite(pin2A, B0);
digitalWrite(pin3A, B1);
digitalWrite(pin4A, B0);
delay(1000); //Wait for of a second
digitalWrite(pin1A, B0); //Write "6" to the display
digitalWrite(pin2A, B1);
digitalWrite(pin3A, B1);
digitalWrite(pin4A, B0);
delay(1000); //Wait for of a second
digitalWrite(pin1A, B1); //Write "7" to the display
digitalWrite(pin2A, B1);
digitalWrite(pin3A, B1);
digitalWrite(pin4A, B0);
delay(1000); //Wait for of a second
digitalWrite(pin1A, B0); //Write "8" to the display
digitalWrite(pin2A, B0);
digitalWrite(pin3A, B0);
digitalWrite(pin4A, B1);
delay(1000); //Wait for of a second
digitalWrite(pin1A, B1); //Write "9" to the display
digitalWrite(pin2A, B0);
digitalWrite(pin3A, B0);
digitalWrite(pin4A, B1);
delay(1000); //Wait for of a second
}
