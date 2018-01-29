#include "Arduino.h"
#include "SevenSegment.h"
#include "HardwareSerial.h"

/*Default constructor for the SevenSegment class*/
SevenSegment::SevenSegment()
{
	//nothing to specify
}

/*Function to display integer number -->it takes any integer value and displays*/
void SevenSegment::dispInt(int num)
{
	/*An array to store the values for the display. 
	Inorder to get CommAnode mode  255 - CommCathode*/
	uint8_t numArr[2][10] = {{252,96,218,242,102,182,190,224,254,246},//LSBFIRST CommCathode
							{63,6,91,79,102,109,125,7,127,111}};//MSBFIRST CommCathode*/
	uint8_t digit = 1;//sets the value of digit to either of these values
	//Check how many digits are present
	if(num<10)
		digit = 1;
	else if(num<100)
		digit = 2;
	else if(num<1000)
		digit = 3;
	else if(num<10000)
		digit = 4;
	else if(num<100000)
		digit = 5;
	digitalWrite(_latchPin, LOW);	//Pull the latchpin to low for the bits to be write
	switch(digit)
	{
		case 1:
			if(_bitOrder == LSBFIRST)
			{
				bitOut_LSBF(numArr[0][num]);//Takes the value from the above mentioned array
			}
			else if(_bitOrder == MSBFIRST)
			{
				bitOut_MSBF(numArr[1][num]);
			}
			break;
		case 2:
			if(_bitOrder == LSBFIRST)
			{
				bitOut_LSBF(numArr[0][num/10]);//First digit
				bitOut_LSBF(numArr[0][num%10]);//Second digit
			}
			else
			{
				bitOut_MSBF(numArr[1][num/10]);	//First digit
				bitOut_MSBF(numArr[1][num%10]);	//Second digit
			}
		case 3:
			if(_bitOrder == LSBFIRST)
			{
				bitOut_LSBF(numArr[0][num/100]);	//First digit
				num /=10;
				bitOut_LSBF(numArr[0][num/10]);		//Second digit
				bitOut_LSBF(numArr[0][num%10]);		//Third digit
			}else
			{
				bitOut_LSBF(numArr[1][num/100]);	//First digit
				num /=10;
				bitOut_LSBF(numArr[1][num/10]);		//Second digit
				bitOut_LSBF(numArr[1][num%10]);		//Third digit
			}
	}
	digitalWrite(_latchPin, HIGH);//Enable the latchPin once all the numbers have been wrote
	
}
/*Function to display strings. Takes in pointer to the array of character
Input string must contain an end of line character '\n'
Please ensure that the input string is in small letters*/
void SevenSegment::dispString(char *ptr)
{
	//Array to numerically represent characters from A to Z. 
	//First row contains values for LSBFIRST and second row contains values for MSBFIRST
	//Letters that cannot be displayed in 7 segment are k, m, q, w, x, z
	//These letters are replaced with 0 
	//							   a, b,  c, d,  e,  f, g,  h,  i,  j, k, l, m,n, o, p, q,r, s,  t  u,  v,w,x, y, z
	uint8_t charNumArr[2][26] = {{238,62,156,122,158,142,188,110,12,120,0,28,0,42,58,206,0,14,182,30,124,0,0,0,118,0},
							  {119,124,57,94,121,113,61,118,48,30,0,56,0,84,92,115,0,112,109,120,62,0,0,0,110,0}}; 
	digitalWrite(_latchPin, HIGH);	//make latchPin low so that the bits are transfered
	for(uint8_t i=0; i<100; i++)
	{
		if(*(ptr + i)=='\n')	//once the char reaches end of line exit the loop
			break;
		if(_bitOrder == LSBFIRST)
		{
			if(*(ptr+i)>=97)	//If the given input is small letter
				bitOut_LSBF(charNumArr[0][*(ptr+i)-97]);	//output is fed from LSBFIRST array
			else	//If the given input is capital letter
				bitOut_LSBF(charNumArr[0][*(ptr+i)-65])
		}
		else
		{
			if(*(ptr+i)>=97)	//if given input is small letter
				bitOut_MSBF(charNumArr[1][*(ptr+i)-97]);	//From MSBFIRST array
			else	//If given input is capital letter
				bitOut_MSBF(charNumArr[1][*(ptr+i)-65]);
		}
	}
	digitalWrite(_latchPin, LOW);	//pullup latchpin to high inorder to ouptut the bits
	
}

/*Function to display characters. Input will be a character*/
void SevenSegment::dispChar(uint8_t input)
{
	//Array to numerically represent characters from A to Z. 
	//First row contains values for LSBFIRST and second row contains values for MSBFIRST
	//Letters that cannot be displayed in 7 segment are k, m, q, w, x, z
	//These letters are replaced with 0 
	//							   a, b,  c, d,  e,  f, g,  h,  i,  j, k, l, m,n, o, p, q,r, s,  t  u,  v,w,x, y, z
	uint8_t charNumArr[2][26] = {{238,62,156,122,158,142,188,110,12,120,0,28,0,42,58,206,0,14,182,30,124,0,0,0,118,0},
							  {119,124,57,94,121,113,61,118,48,30,0,56,0,84,92,115,0,112,109,120,62,0,0,0,110,0}}; 
	digitalWrite(_latchPin, LOW);	//keep latchpin low until the bits are passed
	if(_bitOrder == LSBFIRST)
			bitOut_LSBF(charNumArr[0][input-97]);	//output is fed from LSBFIRST array
		else
			bitOut_MSBF(charNumArr[1][input-97]);	//From MSBFIRST array
	digitalWrite(_latchPin, HIGH);	//Make latchpin to high to output
	
}