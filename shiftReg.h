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
		void setReg(uint8_t srNum, uint8_t mode, uint8_t bitOrder);
		void bitOut_MSBF(int val);	//Outputs the bits at the datapin
		void bitOut_LSBF(int val);
		void dispInt(int val);	//displays the integer values
		void chaser(int channels);	//channels is the number of channels
		~shiftReg();	//default destructor for the class
};
#endif