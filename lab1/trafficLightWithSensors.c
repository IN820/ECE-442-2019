Code for Intersection traffic light design with sensors
const int buttonPin1 = 2; // the number of the pushbutton pin
const int buttonPin2 = 1;
const int redPin_ns = 13; // the number of the LED pin
const int yelPin_ns = 12;
const int grePin_ns = 11;
const int redPin_ew = 10; // the number of the LED pin
const int yelPin_ew = 9;
const int grePin_ew = 8;
int i = 0;
void setup() {
pinMode(buttonPin1, INPUT);
pinMode(buttonPin2, INPUT);
pinMode(redPin_ns, OUTPUT);
pinMode(yelPin_ns, OUTPUT);
pinMode(grePin_ns, OUTPUT);
pinMode(redPin_ew, OUTPUT);
pinMode(yelPin_ew, OUTPUT);
pinMode(grePin_ew, OUTPUT);
digitalWrite(redPin_ns, LOW);
digitalWrite(yelPin_ns, LOW);
digitalWrite(grePin_ns, HIGH);
digitalWrite(redPin_ew, HIGH);
digitalWrite(yelPin_ew, LOW);
digitalWrite(grePin_ew, LOW);
}
void loop() {
int reading1 = digitalRead(buttonPin1);
int reading2 = digitalRead(buttonPin2);
if (reading1 == LOW && reading2 == LOW) {
digitalWrite(redPin_ns, LOW);
digitalWrite(yelPin_ns, LOW);
digitalWrite(grePin_ns, HIGH);
digitalWrite(redPin_ew, HIGH);
digitalWrite(yelPin_ew, LOW);
digitalWrite(grePin_ew, LOW);
}
else
{
if (reading1 == HIGH || reading2 == HIGH) {
i = i +1;
delay(1000);//1000ms*10
}
else
i = 0;
if (i == 10)
{
i = 0;
digitalWrite(grePin_ns, LOW);
digitalWrite(yelPin_ns, HIGH);
delay(1000);
digitalWrite(yelPin_ns, LOW);
digitalWrite(redPin_ns, HIGH);
delay(1000);
digitalWrite(redPin_ew, LOW);
digitalWrite(grePin_ew, HIGH);
delay(5000);
digitalWrite(grePin_ew, LOW);
digitalWrite(yelPin_ew, HIGH);
delay(1000);
digitalWrite(yelPin_ew, LOW);
digitalWrite(redPin_ew, HIGH);
delay(1000);
}
}
}
