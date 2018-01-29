#ifndef shiftReg_h
#define sfiftReg_h
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
		void setReg(uint8_t srNum, uint8_t bitOrder);
		void commonCathode();
		void commonAnode();	//sets the register ouputs for a common anode display
		void bitOut_MSBF(uint8_t val);	//Outputs the bits at the datapin
		void bitOut_LSBF(uint8_t val);
		void dispInt(int val);	//displays the integer values
		void dispString(char *ptr);	//displays strings: string should end with '\n'
		void dispChar(uint8_t input);	//displays characters from a to z
		void chaser(int channels, int speed);	//channels is the number of channels
		~shiftReg();	//default destructor for the class
};
#endif