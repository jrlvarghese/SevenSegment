//Make useful file to handle shift register 74HC595
#include <iostream>
using namespace std;
//void setPins(uint8_t x, uint8_t y, uint8_t z);
class shiftReg
{
	//Declare the pins
	private:
		int _latchPin;
		int _clockPin;
		int _dataPin;
		int _srNum; //variable for total number of shift registers in use
		
	public:
		shiftReg();	//default constructor
		void setPins(uint8_t latchPin, uint8_t clockPin, uint8_t dataPin);
		void setRegNum(uint8_t srNum);
		~shiftReg();	//default destructor for the class
};
//Constructor --> if the pins are not defined while initiating it will be the default pins
shiftReg::shiftReg()
{
	_latchPin = 12;	//Connected to pin 12 of the ic (ST_CP)
	_clockPin = 8;	//to pin 11 of ic (SH_CP)
	_dataPin = 11;	//to pin 14 of ic (DATA pin)
	_srNum = 1;	//by default total number of sr is 1
}

//Function to set the pins. This will change the default pins
void shiftReg::setPins(uint8_t latchPin, uint8_t clockPin, uint8_t dataPin)
{
	//Pins are set hear
	_latchPin = latchPin;
	_clockPin = clockPin;
	_dataPin = dataPin;
}
//Function to set total number of shift registers
void shiftReg::setRegNum(uint8_t srNum)
{
	_srNum = srNum;	
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
