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
		void bitOut(uint8_t val);	//Outputs the bits at the datapin
		void dispInt(int val);	//displays the integer values
		void chaser(uint8_t channels);	//channels is the number of channels
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
	/*An array to store the values for the display. 
	Inorder to get CommAnode mode  255 - CommCathode*/
	uint8_t numArr[2][10] = {{252,96,218,242,102,182,190,224,254,246},//MSBFIRST CommCathode
							{64,6,81,79,102,109,125,7,127,111}};//LSBFIRST CommCathode
	if(_bitOrder == MSBFIRST)
	{
		if(_mode == c)//for common cathode mode 
			bitOut_MSBF(numArr[0][num]);
		else//for common anode mode
			bitOut_MSBF(255 - numArr[0][num]);
	}
	else if(_bitOrder == LSBFIRST)
	{
		if(_mode == c)//for common cathode 
			bitOut_LSBF(numArr[1][num]);
		else	//for common anode
			bitOut_LSBF(255 - numArr[1][num]);
	}
}

/*Shiftout function which is customised without declaring the pins and bit order*/
void shiftReg::bitOut_LSBF(uint8_t val)
{
    uint8_t i;

    for(i=0; i<8; i++)
	{
		digitalWrite(_dataPin, !!(val & (1 << i)));
        digitalWrite(_clockPin, HIGH);
        digitalWrite(_clockPin, LOW);        
    }
}

void shiftReg::bitOut_MSBF(uint8_t val)
{
    uint8_t i;

    for(i=0; i<8; i++)
	{
		digitalWrite(_dataPin, !!(val & (1 << (7 - i))));
        digitalWrite(_clockPin, HIGH);
        digitalWrite(_clockPin, LOW);        
    }
}
/*Chaser which can move one bit from one end to another.
Will make the bits move from one end to another and again start from the begining*/
void shiftReg::chaser(uint8_t channels)
{
	uint8_t val = 0;
	for(uint8_t i = 0; i<channels; i++) 
	{
		val = (1<<i);
		for(uint8_t j=0; j<channels; j++)
		{
			//cout<<!!(val&(1<<j))<<setw(7);
			if(_bitOrder == LSBFIRST)
			{
				digitalWrite(_dataPin, !!(val&(1<<j)));
			}
			else
			{
				digtalWrite(_dataPin, !!(val & (1 << (channels - j))));
			}
		}
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
