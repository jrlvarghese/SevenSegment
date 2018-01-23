//Make useful file to handle shift register 74HC595
#include <iostream>
using namespace std;
//void setPins(uint8_t x, uint8_t y, uint8_t z);
class shiftReg
{
	//Declare the pins
	private:
		uint8_t _latchPin;
		uint8_t _clockPin;
		uint8_t _dataPin;
		uint8_t _srNum; //variable for total number of shift registers in use
		uint8_t _mode;
		uint8_t _bitOrder;
		
	public:
		shiftReg();	//default constructor
		void setPins(uint8_t latchPin, uint8_t clockPin, uint8_t dataPin);
		void setReg(uint8_t srNum, uint8_t mode, uint8_t bitOrder);
		~shiftReg();	//default destructor for the class
};
//Constructor --> if the pins are not defined while initiating it will be the default pins
shiftReg::shiftReg()
{
	_latchPin = 12;	//Connected to pin 12 of the ic (ST_CP)
	_clockPin = 8;	//to pin 11 of ic (SH_CP)
	_dataPin = 11;	//to pin 14 of ic (DATA pin)
	_srNum = 1;	//by default total number of sr is 1
	_mode = c;	//sets to common cathode mode by default
	_bitOrder = MSBFIRST; //default bit order is MSBFIRST
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
void shiftReg::setReg(uint8_t srNum, uint8_t mode, uint8_t bitOrder)
{
	_srNum = srNum;	//sets total number of shift registers
	_mode = mode	//sets wether common cathode (c) or anode mode (a)
	_bitOrder = bitOrder;	//sets the bit order LSBFIRST OR MSBFIRST
}

//Function to display integer number -->
//it takes any integer value and displays
void shiftReg::dispInt(int num)
{
	
}

/*Chaser which can move one bit from one end to another.
Will make the bits move from one end to another and again viceversa*/
void shiftReg::chaser(uint8_t channels)
{
	
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
