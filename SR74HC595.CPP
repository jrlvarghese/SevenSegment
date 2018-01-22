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
		
	public:
		shiftReg();
		void setPins(uint8_t latchPin, uint8_t clockPin, uint8_t dataPin);
	/*const int latchPin = 12;	//Pin connected to ST_CP of 74HC595 pin 12
	const int clockPin = 8;	//Pin connected to SH_CP of 74HC595 pin 11
	const int dataPin = 11;	//Pin connected to DS of 74HC595 pin 14*/
};
//Constructor
shiftReg::shiftReg()
{
	_latchPin = 12;
	_clockPin = 8;
	_dataPin = 11;
}
//Function to set the pins. This will change the default pins
void shiftReg::setPins(uint8_t latchPin, uint8_t clockPin, uint8_t dataPin)
{
	//Pins are set hear
	_latchPin = latchPin;
	_clockPin = clockPin;
	_dataPin = dataPin;
	return;	
}
