//Setting up TN901 Temperature Sensor
//This temperature sensor uses infrared to detect motion (diff of environment and target teperature)
//This sensor is initially used to detect motion, but finally replaced with ultrasonic motion sensor

#include "TN901.h"
 
#include <stdio.h>
#include <string.h>
#include <inttypes.h>
#include "Arduino.h"       

void TN901::Init(int TN_Data,int TN_Clk,int TN_ACK)
{
  //define pin
  _dataPin=TN_Data;
  _clkPin=TN_Clk;
  _ackPin=TN_ACK;
 
  pinMode(_clkPin, INPUT);
  pinMode(_ackPin, OUTPUT);
  digitalWrite(_ackPin,HIGH);
}
//////////////////////////////////////
void TN901::Read()
{
  digitalWrite(_ackPin,LOW);
  ReadData(TN901_OTADDRESS);//Target temp ends with 0x4c    
  if((Data[0]==TN901_OTADDRESS)&&
     (Data[4]==TN901_ENDADDRESS))//every frame ends with 0x0d    
  {   
    GetData_OT();  
  } 
 
  delay(1); //time ineterval, up delay if needed***
 
  digitalWrite(_ackPin,LOW); 
  ReadData(TN901_ETADDRESS);//environment temp ends with 0x66      
 
  if((Data[0]==TN901_ETADDRESS)&&
     (Data[4]==TN901_ENDADDRESS))//every frame ends with 0x0d    
  {   
    GetData_ET();
  }
}

//Read Data
void TN901::ReadData(char flag)
{
  char i,j,k;
  byte BitState = 0;          //send 7 frame at a time
  for(k=0;k<7;k++)
  {
    for(j=0;j<5;j++)        //5 bit in a frame
    {
      for(i=0;i<8;i++)
      {
        int temp= digitalRead(_clkPin);
        while(temp)
        {
          temp = digitalRead(_clkPin);
        } 
        temp= digitalRead(_clkPin);
        BitState= digitalRead(_dataPin);
        Data[j]= Data[j]<<1;
        Data[j]= Data[j]|BitState;
 
        while(!temp)
        {
          temp = digitalRead(_clkPin);
        }
      }
    }
   if(Data[0]==flag)  k=8;
  }
 
  digitalWrite(_ackPin,HIGH);
} 
///////////////////////////////////////
  //Get temperature
void TN901::GetData_ET()   
{      
  ET=(Data[1]<<8)|Data[2];   
  ET = int(((float)ET/16 - 273.15)*100);      
}   
void TN901::GetData_OT()   
{   
  OT=(Data[1]<<8)|Data[2];   
  OT = int(((float)OT/16 - 273.15)*100);      
}
