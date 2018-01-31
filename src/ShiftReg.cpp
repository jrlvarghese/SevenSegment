//Make useful file to handle shift register 74HC595
//#include <iostream>
//using namespace std;
#include "Arduino.h"
#include "ShiftReg.h"
#include "HardwareSerial.h"
#define CC 1	//set the default value for common cathode mode as 1
#define CA 0	//also set the default value for common anode mode as 0
//Constructor --> if the pins are not defined while initiating it will be the default pins
ShiftReg::ShiftReg()
{
	_latchPin = 12;	//Connected to pin 12 of the ic (ST_CP)
	_clockPin = 8;	//to pin 11 of ic (SH_CP)
	_dataPin = 11;	//to pin 14 of ic (DATA pin)
	_srNum = 1;	//by default total number of sr is 1
	_mode = CC;	//sets to common cathode mode by default
	_bitOrder = MSBFIRST; //default bit order is MSBFIRST
}

//Destructor 
ShiftReg::~ShiftReg()
{
	//do nothing
}
//Function to set the pins. This will change the default pins
void ShiftReg::setPins(uint8_t latchPin, uint8_t clockPin, uint8_t dataPin)
{
	//Pins are set hear
	_latchPin = latchPin;
	_clockPin = clockPin;
	_dataPin = dataPin;
	pinMode(_latchPin,OUTPUT);
	pinMode(_clockPin,OUTPUT);
	pinMode(_dataPin,OUTPUT);
}

/*Function to set total number of registers by default it is one*/
void ShiftReg::setTotalRegisters(uint8_t srNum)
{
	_srNum = srNum;	//sets total number of shift registers
}

/*Functions to set register mode wether common cathode or anode*/
void ShiftReg::commonCathode()
{
	_mode = CC;
}
void ShiftReg::commonAnode()
{
	_mode = CA;
}

/*Function to set total number of shift registers
srNum -- indicates total number of shift registers
mode -- define wether common cathode or anode
bitOrder -- MSBFIRST OR LSBFIRST*/
void ShiftReg::setBITOrder(uint8_t bitOrder)
{
	_bitOrder = bitOrder;	//sets the bit order LSBFIRST OR MSBFIRST
}

/*bitOut_LSBF outputs the bits in an order of LSBFIRST
takes input and convert to 8 bit binary. Then outputs bit by bit*/
void ShiftReg::bitOut_LSBF(uint8_t val)
{
    uint8_t i;
    for(i=0; i<8; i++)
	{
		if(_mode)
			digitalWrite(_dataPin, !!(val & (1 << i)));
		else
			digitalWrite(_dataPin, !(val & (1 << i)));			
        digitalWrite(_clockPin, HIGH);
        digitalWrite(_clockPin, LOW);        
    }
}

void ShiftReg::bitOut_MSBF(uint8_t val)
{
    uint8_t i;
    for(i=0; i<8; i++)
	{
		if(_mode)
			digitalWrite(_dataPin, !!(val & (1 << (7 - i))));
		else
			digitalWrite(_dataPin, !(val & (1 << (7 - i))));
        digitalWrite(_clockPin, HIGH);
        digitalWrite(_clockPin, LOW);        
    }
}
/*Chaser which can move one bit from one end to another.
Will make the bits move from one end to another and again start from the begining
Takes input as total number of channels depending on the number of channels required*/
void ShiftReg::chaser(int channels, int speed)
{
	uint8_t val = 1;
	uint8_t totalBit = 8*_srNum;//Total bit is calculated based on the total number of shift registers
	for(uint8_t i = 0; i<channels; i++) 
	{
		digitalWrite(_latchPin, LOW);
		for(uint8_t j=0; j<totalBit; j++)
		{
			//cout<<!!(val&(1<<j))<<setw(7);
			if(_bitOrder == LSBFIRST)
			{
				if(_mode)
					digitalWrite(_dataPin, !!((val<<i)&(1<<(j%8))));
				else
					digitalWrite(_dataPin, !((val<<i)&(1<<(j%8))));
				
				digitalWrite(_clockPin, HIGH);
				digitalWrite(_clockPin, LOW);
			}
			else
			{
				if(_mode)
					digitalWrite(_dataPin, !!((val<<i) & (1<<(((totalBit-1)-j)%8))));
				else
					digitalWrite(_dataPin, !((val<<i) & (1<<(((totalBit-1)- j)%8))));
				digitalWrite(_clockPin, HIGH);
				digitalWrite(_clockPin, LOW);
			}
		}
		digitalWrite(_latchPin, HIGH);
		delay(speed);
	}	
}

/*
------------------------- END OF THE PROGRAM ----------------------------------------
//This is similar to default function in arduino:
//Please note default function name is shiftout
void shiftOut(uint8_t dataPin, uint8_t clockPin, uint8_t bitOrder, uint8_t val)
{
    uint8_t i;

    for (i = 0; i < 8; i++)  {
        if (bitOrder == LSBFIRST)
            digitalWrite(dataPin, !!(val & (1 << i)));
        else    
            digitalWrite(dataPin, !!(val & (1 << (7 - i))));

        digitalWrite(clockPin, HIGH);
        digitalWrite(clockPin, LOW);        
    }
}
*/
