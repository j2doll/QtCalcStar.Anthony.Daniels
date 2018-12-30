#include ".\GtBasicMath.h"
#include <stdio.h>
#include <stdlib.h>
#include <string>


#define GtPI 3.1415926

using namespace std;

int gRound(double value){
	//Add 0.5 to the double and convert to int performs
	//a zero decimal place rounding.
	if(value > 0.0)
	{
		return (int)(value + 0.5);
	}else{
		return (int)(value - 0.5);
	}
};

double gRound(double value, unsigned int numdecimals){
	long lngTemp, lngDecShift;
	double dblTemp;

	//Shift the Decimal Places by the number desired and
	//then round that value to an integer. Then shift the decimals
	//back to the original position and return the double.
	lngDecShift = (long)pow(10.0, static_cast<int>(numdecimals));
	if(value > 0.0){
		lngTemp = (long)((value * lngDecShift) + 0.5);
		dblTemp = ((double)lngTemp / (double)lngDecShift);
		return dblTemp;
	}else{
		lngTemp = (long)((value * lngDecShift) - 0.5);
		dblTemp = ((double)lngTemp / (double)lngDecShift);
		return dblTemp;
	};
};

double gTrunc(double value, unsigned int numdecimals){
	long lngTemp;
	//Shift the Decimal Places by the number desired and
	//then truncate that value to an integer. Then shift the decimals
	//back to the original position and return the double.
	if(numdecimals < 1){
		return floor(value);
	}else{
		lngTemp = (long)floor(value * (numdecimals *10));
		return (lngTemp/(numdecimals*10));
	};
};

double gFactorial(int intX)
{
	double dblFact;
	int intCursor;
	if (intX < 0) { return 0.0f; };
	intCursor = intX;
	dblFact = 1.0f;
	while (intCursor >= 1)
	{
		dblFact = dblFact*intCursor;
		intCursor--;
	};
	return dblFact;
};
//
double floor(double value, unsigned int numdecimals)
{
	long lngTemp, lngDecShift;
	double dblTemp;

	//Shift the Decimal Places by the number desired and
	//then round that value to an integer. Then shift the decimals
	//back to the original position and return the double.
	lngDecShift = (long)pow(10.0, static_cast<int>(numdecimals));
	if(value > 0.0){
		lngTemp = (long)((value * lngDecShift));
		dblTemp = ((double)lngTemp / (double)lngDecShift);
		return dblTemp;
	}else{
		lngTemp = (long)((value * lngDecShift));
		dblTemp = ((double)lngTemp / (double)lngDecShift);
		return dblTemp;
	};
};
double ceil(double value, unsigned int numdecimals)
{
	long lngTemp, lngDecShift;
	double dblTemp;
	//THIS NEEDS TO BE MODIFIED
	//Shift the Decimal Places by the number desired and
	//then round that value to an integer. Then shift the decimals
	//back to the original position and return the double.
	lngDecShift = (long)pow(10.0, static_cast<int>(numdecimals));
	if(value > 0.0){
		lngTemp = (long)((value * lngDecShift));
		dblTemp = ((double)lngTemp / (double)lngDecShift);
		return dblTemp;
	}else{
		lngTemp = (long)((value * lngDecShift));
		dblTemp = ((double)lngTemp / (double)lngDecShift);
		return dblTemp;
	};
};

char * itoa(char * buf, int intValue)
{
	sprintf_s(buf, 256, "%d",intValue);
	return buf;
};

char * uitoa(char * buf, unsigned int uintValue)
{
	sprintf_s(buf, 256, "%u",uintValue);
	return buf;
};

char* ltoa(char * buf, long lngValue)
{
	sprintf_s(buf, 256, "%d",lngValue);
	return buf;
};

char * ultoa(char * buf, unsigned long ulngValue)
{
	sprintf_s(buf, 256, "%u",ulngValue);
	return buf;
};

char * ftoa(char * buf, float sngValue)
{
	sprintf_s(buf, 256, "%3.6f",sngValue);
	return buf;
};

char * dtoa(char * buf, double dblValue)
{
	sprintf_s(buf, 256, "%3.12f",dblValue);
	return buf;
};

char * ftoa(char * buf, float sngValue, unsigned int numdecimals)
{	char chrDec[50];
	std::string strFormat = "%6.";
	strFormat += itoa(chrDec, numdecimals);
	strFormat += "f";
	sprintf_s(buf, 256, strFormat.c_str(), sngValue);
	return buf;
};

char * dtoa(char * buf, double dblValue, unsigned int numdecimals)
{
	char chrDec[50];
	std::string strFormat = "%6.";
	strFormat += itoa(chrDec, numdecimals);
	strFormat += "f";
	sprintf_s(buf, 256, strFormat.c_str(),dblValue);
	return buf;
};

char * deg2rad(double deg, double& rad)
{
	static char buf[50];
	//std::string strFormat = "%6.3f";
	rad = deg * (GtPI / 180.0f);
	sprintf_s(buf, 256, "%6.6f",rad);
	return buf;	
};
char * rad2deg(double deg, double& rad)
{
	static char buf[50];
	//std::string strFormat = "%6.3f";
	deg = rad * (180.0f/ GtPI);
	sprintf_s(buf, 256, "%6.3f",deg);
	return buf;	
};


float linterp(float x1, float x, float x2, float y1, float y2)
{
	return (((x - x1)*(y2 - y1)) / (x2 - x1) + y1);
}