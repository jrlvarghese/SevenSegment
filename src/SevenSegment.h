/*Header file for the seven segment class*/
#ifndef SevenSegment_h
#define SevenSegment_h
#include <ShiftReg.h>
class SevenSegment: public ShiftReg
{
	public:
		SevenSegment();	//Default constructor
		void dispInt(int num);
		void dispChar(uint8_t in);
		void dispString(char *ptr);
};
#endif