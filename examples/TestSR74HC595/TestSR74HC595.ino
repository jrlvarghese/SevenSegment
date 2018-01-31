#include "SevenSegment.h"
SevenSegment sr;
//String jeril = "Jeril";
String letters = "abcdefghijklmnopqrstuvwxyz\n";
char *ptr = &letters[0];
void setup() {
  // put your setup code here, to run once:
  sr.commonCathode(); //initiates the shift register in common cathode mode
  sr.setPins(12,8,11);

}

void loop() {
  // put your main code here, to run repeatedly:
  /*for(int i=0; i<10; i++)
  {
    int spd = 50 * i;
    sr.setReg(1, MSBFIRST);
    sr.chaser(6, spd);
    // sr.setReg(1, LSBFIRST);
    //sr.chaser(7, spd);
  }
  for(int i=0; i<10; i++)
  {
    sr.setReg(1, MSBFIRST);
    sr.dispInt(i);
    delay(400);
  }
  for(int i=0; i<10; i++)
  {
    sr.setReg(1, LSBFIRST);
    sr.dispInt(i);
    delay(400);
  }
  for(int i=0; i<6; i++)
  {
    sr.dispChar(ptr+i);
    delay(500);
  }*/
  sr.setBITOrder(LSBFIRST);
  sr.dispChar('j');
  delay(500);
  sr.setBITOrder(MSBFIRST);
  sr.dispChar('i');
  delay(500);
}
/*
//74HC595
//You should now be able to see the 7-segment display cycle from 0 to F
//Email:support@sunfounder.com
//Website:www.sunfounder.com
//2015.5.7

const int latchPin = 12;//Pin connected to ST_CP of 74HC595
const int clockPin = 8;//Pin connected to SH_CP of 74HC595 
const int dataPin = 11; //Pin connected to DS of 74HC595 
//display 0,1,2,3,4,5,6,7,8,9,A,b,C,d,E,F
int datArray[16] = {252, 96, 218, 242, 102, 182, 190, 224, 254, 246, 238, 62, 156, 122, 158, 142};

void setup ()
{
  //set pins to output
  pinMode(latchPin,OUTPUT);
  pinMode(clockPin,OUTPUT);
  pinMode(dataPin,OUTPUT);
}
void loop()
{
  //loop from 0 to 256
  for(int num = 0; num < 16; num++)
  {
    digitalWrite(latchPin,LOW); //ground latchPin and hold low for as long as you are transmitting
    shiftOut(dataPin,clockPin,LSBFIRST,datArray[num]);
    //return the latch pin high to signal chip that it 
    //no longer needs to listen for information
    digitalWrite(latchPin,HIGH); //pull the latchPin to save the data
    delay(1000); //wait for a second
  }
}*/
