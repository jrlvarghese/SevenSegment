//Make useful file to handle shift register 74HC595
//#include <iostream>
//using namespace std;
#include "Arduino.h"
#include "shiftReg.h"
#include "HardwareSerial.h"
#define CC 1
#define CA 0
//Constructor --> if the pins are not defined while initiating it will be the default pins
shiftReg::shiftReg()
{
	_latchPin = 12;	//Connected to pin 12 of the ic (ST_CP)
	_clockPin = 8;	//to pin 11 of ic (SH_CP)
	_dataPin = 11;	//to pin 14 of ic (DATA pin)
	_srNum = 1;	//by default total number of sr is 1
	_mode = CC;	//sets to common cathode mode by default
	_bitOrder = MSBFIRST; //default bit order is MSBFIRST
}

//Destructor 
shiftReg::~shiftReg()
{
	//do nothing
}

//Function to set the pins. This will change the default pins
void shiftReg::setPins(uint8_t latchPin, uint8_t clockPin, uint8_t dataPin)
{
	//Pins are set hear
	_latchPin = latchPin;
	_clockPin = clockPin;
	_dataPin = dataPin;
	pinMode(_latchPin,OUTPUT);
	pinMode(_clockPin,OUTPUT);
	pinMode(_dataPin,OUTPUT);
}

/*Function to set total number of shift registers
srNum -- indicates total number of shift registers
mode -- define wether common cathode or anode
bitOrder -- MSBFIRST OR LSBFIRST*/
void shiftReg::setReg(uint8_t srNum, uint8_t bitOrder)
{
	_srNum = srNum;	//sets total number of shift registers
	_bitOrder = bitOrder;	//sets the bit order LSBFIRST OR MSBFIRST
}
/*Functions to set register mode wether common cathode or anode*/
void shiftReg::commonCathode()
{
	_mode = CC;
}
void shiftReg::commonAnode()
{
	_mode = CA;
}
/*Function to display integer number -->it takes any integer value and displays*/
void shiftReg::dispInt(int num)
{
	/*An array to store the values for the display. 
	Inorder to get CommAnode mode  255 - CommCathode*/
	int numArr[2][10] = {{252,96,218,242,102,182,190,224,254,246},//LSBFIRST CommCathode
							{63,6,91,79,102,109,125,7,127,111}};//MSBFIRST CommCathode*/
	if(_bitOrder == LSBFIRST)
	{
		if(_mode)//for common cathode mode 
			bitOut_LSBF(numArr[0][num]);
		else//for common anode mode
			bitOut_LSBF(255 - numArr[0][num]);
	}
	else if(_bitOrder == MSBFIRST)
	{
		if(_mode)//for common cathode 
			bitOut_MSBF(numArr[1][num]);
		else	//for common anode
			bitOut_MSBF(255 - numArr[1][num]);
	}
}

/*bitOut_LSBF outputs the bits in an order of LSBFIRST
takes input and convert to 8 bit binary. Then outputs bit by bit*/
void shiftReg::bitOut_LSBF(int val)
{
    uint8_t i;
	digitalWrite(_latchPin, LOW);
    for(i=0; i<8; i++)
	{
		digitalWrite(_dataPin, !!(val & (1 << i)));
        digitalWrite(_clockPin, HIGH);
        digitalWrite(_clockPin, LOW);        
    }
	digitalWrite(_latchPin, HIGH);
}

void shiftReg::bitOut_MSBF(int val)
{
    uint8_t i;
	digitalWrite(_latchPin, LOW);
    for(i=0; i<8; i++)
	{
		digitalWrite(_dataPin, !!(val & (1 << (7 - i))));
        digitalWrite(_clockPin, HIGH);
        digitalWrite(_clockPin, LOW);        
    }
	digitalWrite(_latchPin, HIGH);
}
/*Chaser which can move one bit from one end to another.
Will make the bits move from one end to another and again start from the begining
Takes input as total number of channels depending on the number of channels required*/
void shiftReg::chaser(int channels, int speed)
{
	uint8_t val = 1;
	for(uint8_t i = 0; i<channels; i++) 
	{
		digitalWrite(_latchPin, LOW);
		for(uint8_t j=0; j<(8*_srNum); j++)
		{
			//cout<<!!(val&(1<<j))<<setw(7);
			if(_bitOrder == LSBFIRST)
			{
				digitalWrite(_dataPin, !!((val<<i)&(1<<j)));
				digitalWrite(_clockPin, HIGH);
				digitalWrite(_clockPin, LOW);
			}
			else
			{
				digitalWrite(_dataPin, !!((val<<i) & (1 << (channels - j))));
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
