//

char command[100]={NULL};//接收数据的字符串
void setup(){ Serial.begin(9600); // Seri haberleşmeyi kullanacağımızı bildirdik } 
void loop(){
 while (Serial.available()<=0)
  {delay(500);}//如果串口无数据则等待>>秒
while (Serial.available()>0)
  {
  int b=0;
  
  for(int i=0;i<100;i++){command[i]=NULL;}
  while (Serial.available()>0)
  {
    command[b]=(Serial.read());//接收串口数据，每次只能接收一个字符串
    b=b+1;
    if(Serial.available()<=0){b=0;}
    delay(2)
}
