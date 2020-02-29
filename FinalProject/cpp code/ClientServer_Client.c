//// This code along with the the ClientServer_host.cpp are used to do a one-way connection between PC and Arduino Board
// Eventually a Arduino to Raspberry Pi connection are used in this project, but this code are tested fully functional
// Important** Use this code on arduino board


char command[100]={NULL}; 
void setup(){ Serial.begin(9600); 
void loop(){
 while (Serial.available()<=0)
  {delay(500);}//check for input every 0.5s
while (Serial.available()>0)
  {
  int b=0;
  
  for(int i=0;i<100;i++){command[i]=NULL;}
  while (Serial.available()>0)
  {
    command[b]=(Serial.read()); //read input
    b=b+1;
    if(Serial.available()<=0){b=0;}
    delay(2)
}
