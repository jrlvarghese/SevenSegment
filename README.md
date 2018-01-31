THIS A ARDUINO LIBRARY FOR CONTROLLING SEVENSEGMENT DISPLAY


Contains two classes
1. ShiftReg
2. SevenSegment

ShiftReg initites a shift register connection with arduino. Pins are connected in the following manner.
latchpin of 74HC595 to pin 11 of arduino
clock pin 			to pin 8 of arduino
data pin 			to pin 12 of arduino

Shift register class contains following functions:
		void setPins(uint8_t latchPin, uint8_t clockPin, uint8_t dataPin); //SETS THE PINS
		void setBITOrder(uint8_t bitOrder);		//SETS THE BIT ORDER
		void setTotalRegisters(uint8_t srNum);	//Sets the total number of shift registers used
		void commonCathode();
		void commonAnode();	//sets the register ouputs for a common anode display
		void bitOut_MSBF(uint8_t val);	//Outputs the bits at the datapin
		void bitOut_LSBF(uint8_t val);	//Ouputs the bits at the data pin
		
		void chaser(int channels, int speed);	//channels is the number of channels
			speed is actually delay time. If the speed is more it actually delays the interval (slows down chaser)
			

SevenSegment is another class in this library
	Functions in this library includes all those functions in ShiftReg class and also following functions
	
	void dispInt(int num);
		Displays any integer values. Upto 5 digits. You should connect adequate number of shift register and 
		seven segment diplay for this.
	
	void dispChar(uint8_t in);
		Displays character from A to Z of which few characters cannot be displayed in a sevensegment display.
		
	void dispString(char *ptr);