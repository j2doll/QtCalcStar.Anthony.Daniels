/*
**	This file is part of the Hpc Template Library (Htl or HTL).
**  It is based on a merger of QT, STL, and SigSlots along with development of new classes.
**  License information is in the HtlLicense.h file
**	This software was merged and developed by:
**	
**  Anthony Daniels
**	QT, STL, SigSlots
**
**  HTL is free software: you can redistribute it and/or modify
**  it under the terms of the GNU Lesser General Public License as published by
**  the Free Software Foundation, either version 3 of the License, or
**  (at your option) any later version.
**
**  The United States of America Department of Defense has unlimited 
**	usage, redistribution, and modification rights to HtlStar.
**
**  HTL is distributed in the hope that it will be useful,
**  but WITHOUT ANY WARRANTY; without even the implied warranty of
**  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
**  GNU Lesser General Public License for more details.
**
**  You should have received a copy of the GNU Lesser General Public License
**  along with HTL.  If not, see <http://www.gnu.org/licenses/>.
*/
#pragma once
#pragma warning(push)
#pragma warning (disable : 4005 ) /* macro redefinition */
#define HTL_DLLEXPORT
#pragma warning(pop)


#include ".\HtlGUID128.h"
#include "..\HtlString\HtlString.h"
#include "..\modHtlRandNumGen.h"
//STL streaming functions needed sscanf, sprintf
#include <iostream>

using namespace std;
#pragma warning(push)
#pragma warning (disable : 4996 ) /* sprintf, sscanf unsafe */
#pragma warning (disable : 4477 ) /* sprintf, sscanf deprecated warning */
#pragma warning (disable : 4778 ) /* sprintf, sscanf deprecated warning */
#pragma warning (disable : 4018 ) /* warning C4018: '<': signed/unsigned mismatch */

namespace HTL
{

	HtlGUID128::HtlGUID128()
	{
		setNull();
	};
	//This constructor is kept for Windows compatibility
	//HtlGUID128 native is symmetric storage
	//Microsoft Windows format for GUIDs is  c5057190-a286-4427-b172-2fc56a92423f in hex string
	HtlGUID128::HtlGUID128 ( uint l, ushort w1, ushort w2, uchar b1, uchar b2, uchar b3, uchar b4, uchar b5, uchar b6, uchar b7, uchar b8 )
	{
		try{
			char chrBuff[20];
			sprintf(chrBuff,"%08x",l);//convert it to hexidecimal characters
			sscanf(chrBuff,"%02x%02x%02x%02x",
				&(m_uchrData[0]),
				&(m_uchrData[1]),
				&(m_uchrData[2]),
				&(m_uchrData[3]) );
			sprintf(chrBuff,"%04x",w1);//convert it to hexidecimal characters
			sscanf(chrBuff,"%02x%02x%",
				&(m_uchrData[4]),
				&(m_uchrData[5]) );
			sprintf(chrBuff,"%04x",w2);//convert it to hexidecimal characters
			sscanf(chrBuff,"%02x%02x%",
				&(m_uchrData[6]),
				&(m_uchrData[7]) );

			m_uchrData[8] = b1;
			m_uchrData[9] = b2;
			m_uchrData[10] = b3;
			m_uchrData[11] = b4;
			m_uchrData[12] = b5;
			m_uchrData[13] = b6;
			m_uchrData[14] = b7;
			m_uchrData[15] = b8;
		}catch(...){

		};
		return;
	};
	//This is HtlGUID native format with symmetric strings  c5057190-a2864427-b1722fc5-6a92423f
	HtlGUID128::HtlGUID128 ( uint w0, uint w1, uint w2, uint w3)
	{
		try{
			char chrBuff[20];
			sprintf(chrBuff,"%08x",w0);//convert it to hexidecimal characters
			sscanf(chrBuff,"%02x%02x%02x%02x",
				&(m_uchrData[0]),
				&(m_uchrData[1]),
				&(m_uchrData[2]),
				&(m_uchrData[3]) );
			sprintf(chrBuff,"%08x",w1);//convert it to hexidecimal characters
			sscanf(chrBuff,"%02x%02x%02x%02x",
				&(m_uchrData[4]),
				&(m_uchrData[5]),
				&(m_uchrData[6]),
				&(m_uchrData[7]) );
			sprintf(chrBuff,"%08x",w2);//convert it to hexidecimal characters
			sscanf(chrBuff,"%02x%02x%02x%02x",
				&(m_uchrData[8]),
				&(m_uchrData[9]),
				&(m_uchrData[10]),
				&(m_uchrData[11]) );
			sprintf(chrBuff,"%08x",w3);//convert it to hexidecimal characters
			sscanf(chrBuff,"%02x%02x%02x%02x",
				&(m_uchrData[12]),
				&(m_uchrData[13]),
				&(m_uchrData[14]),
				&(m_uchrData[15]) );
		}catch(...){

		};
		return;
	};

	HtlGUID128::HtlGUID128 ( const char* ptrRHS )
	{
		//ASSUMES NATIVE FORMAT
		try{
			if(!ptrRHS){return;};//safety check
			sscanf(ptrRHS,"%02x%02x%02x%02x-%02x%02x%02x%02x-%02x%02x%02x%02x-%02x%02x%02x%02x",
				&(m_uchrData[0]), &(m_uchrData[1]),	&(m_uchrData[2]), &(m_uchrData[3]),
				&(m_uchrData[4]), &(m_uchrData[5]),	&(m_uchrData[6]), &(m_uchrData[7]),
				&(m_uchrData[8]), &(m_uchrData[9]),	&(m_uchrData[10]), &(m_uchrData[11]),
				&(m_uchrData[12]), &(m_uchrData[13]), &(m_uchrData[14]), &(m_uchrData[15]) );
		}catch(...){

		}
		return;
	};
	HtlGUID128::HtlGUID128 ( const HtlString & strRHS )
	{
		HtlGUID128(strRHS.unicode());
		return;
	};
	HtlGUID128::HtlGUID128 ( const HtlGUID128 & ptrRHS )
	{
		for(int i = 0; i < 16; i++)
		{
			m_uchrData[i] = ptrRHS[i];
		};
	};
	HtlGUID128::~HtlGUID128()
	{
		setNull();	
	};

	//!Serialization TO string formats
	HtlString HtlGUID128::toString (void) const
	{
		char charBuf[256];
		sprintf(charBuf,"%02X%02X%02X%02X-%02X%02X%02X%02X-%02X%02X%02X%02X-%02X%02X%02X%02X",
			(m_uchrData[0]), (m_uchrData[1]), (m_uchrData[2]), (m_uchrData[3]),
			(m_uchrData[4]), (m_uchrData[5]), (m_uchrData[6]), (m_uchrData[7]),
			(m_uchrData[8]), (m_uchrData[9]), (m_uchrData[10]),	(m_uchrData[11]),
			(m_uchrData[12]), (m_uchrData[13]),	(m_uchrData[14]),(m_uchrData[15]) );

		HtlString strOut = charBuf;
		return strOut;	
	};

	std::string HtlGUID128::toStdString (void) const
	{
		char charBuf[256];
		sprintf(charBuf,"%02X%02X%02X%02X-%02X%02X%02X%02X-%02X%02X%02X%02X-%02X%02X%02X%02X",
			(m_uchrData[0]), (m_uchrData[1]), (m_uchrData[2]), (m_uchrData[3]),
			(m_uchrData[4]), (m_uchrData[5]), (m_uchrData[6]), (m_uchrData[7]),
			(m_uchrData[8]), (m_uchrData[9]), (m_uchrData[10]),	(m_uchrData[11]),
			(m_uchrData[12]), (m_uchrData[13]),	(m_uchrData[14]),(m_uchrData[15]) );

		std::string strOut = charBuf;
		return strOut;
	};

	const char* HtlGUID128::toCharString(void)
	{
		sprintf(m_strData,"%02X%02X%02X%02X-%02X%02X%02X%02X-%02X%02X%02X%02X-%02X%02X%02X%02X",
			(m_uchrData[0]), (m_uchrData[1]), (m_uchrData[2]), (m_uchrData[3]),
			(m_uchrData[4]), (m_uchrData[5]), (m_uchrData[6]), (m_uchrData[7]),
			(m_uchrData[8]), (m_uchrData[9]), (m_uchrData[10]),	(m_uchrData[11]),
			(m_uchrData[12]), (m_uchrData[13]),	(m_uchrData[14]),(m_uchrData[15]) );

		return &m_strData[0];
	};

	//!Serialization FROM string formats
	bool HtlGUID128::fromString(HtlString & ptrRHS)
	{
		try{
			char chrBuf[128];
			int p0, p1, p2, p3, p4, p5, p6, p7, p8, p9, p10, p11, p12, p13, p14, p15;
			strcpy(chrBuf, ptrRHS.unicode());
			sscanf_s(chrBuf,"%02X%02X%02X%02X-%02X%02X%02X%02X-%02X%02X%02X%02X-%02X%02X%02X%02X",
				&p0, &p1, &p2, &p3, &p4, &p5, &p6, &p7, &p8, &p9, &p10, &p11, &p12, &p13, &p14, &p15);

			(m_uchrData[0]) = unsigned char(p0);
			(m_uchrData[1]) = unsigned char(p1);
			(m_uchrData[2]) = unsigned char(p2);
			(m_uchrData[3]) = unsigned char(p3);
			(m_uchrData[4]) = unsigned char(p4);
			(m_uchrData[5]) = unsigned char(p5);
			(m_uchrData[6]) = unsigned char(p6);
			(m_uchrData[7]) = unsigned char(p7);
			(m_uchrData[8]) = unsigned char(p8);
			(m_uchrData[9]) = unsigned char(p9);
			(m_uchrData[10]) = unsigned char(p10);
			(m_uchrData[11]) = unsigned char(p11);
			(m_uchrData[12]) = unsigned char(p12);
			(m_uchrData[13]) = unsigned char(p13);
			(m_uchrData[14]) = unsigned char(p14);
			(m_uchrData[15]) = unsigned char(p15);

			return true;
		}catch(...){
			return false;
		};	

	};

	bool HtlGUID128::fromStdString( std::string & ptrRHS)
	{
		try{
			char chrBuf[128];
			int p0, p1, p2, p3, p4, p5, p6, p7, p8, p9, p10, p11, p12, p13, p14, p15;
			strcpy(chrBuf, ptrRHS.c_str());
			sscanf_s(chrBuf,"%02X%02X%02X%02X-%02X%02X%02X%02X-%02X%02X%02X%02X-%02X%02X%02X%02X",
				&p0, &p1, &p2, &p3, &p4, &p5, &p6, &p7, &p8, &p9, &p10, &p11, &p12, &p13, &p14, &p15);

			(m_uchrData[0]) = unsigned char(p0);
			(m_uchrData[1]) = unsigned char(p1);
			(m_uchrData[2]) = unsigned char(p2);
			(m_uchrData[3]) = unsigned char(p3);
			(m_uchrData[4]) = unsigned char(p4);
			(m_uchrData[5]) = unsigned char(p5);
			(m_uchrData[6]) = unsigned char(p6);
			(m_uchrData[7]) = unsigned char(p7);
			(m_uchrData[8]) = unsigned char(p8);
			(m_uchrData[9]) = unsigned char(p9);
			(m_uchrData[10]) = unsigned char(p10);
			(m_uchrData[11]) = unsigned char(p11);
			(m_uchrData[12]) = unsigned char(p12);
			(m_uchrData[13]) = unsigned char(p13);
			(m_uchrData[14]) = unsigned char(p14);
			(m_uchrData[15]) = unsigned char(p15);

			return true;
		}catch(...){
			return false;
		};

	};

	bool HtlGUID128::fromCharString(const char* ptrRHS)
	{
		try{
			if(!ptrRHS){return false;};//safety code
			char chrBuf[128];
			int p0, p1, p2, p3, p4, p5, p6, p7, p8, p9, p10, p11, p12, p13, p14, p15;
			strcpy(chrBuf, ptrRHS);
			sscanf_s(chrBuf,"%02X%02X%02X%02X-%02X%02X%02X%02X-%02X%02X%02X%02X-%02X%02X%02X%02X",
				&p0, &p1, &p2, &p3, &p4, &p5, &p6, &p7, &p8, &p9, &p10, &p11, &p12, &p13, &p14, &p15);

			(m_uchrData[0]) = unsigned char(p0);
			(m_uchrData[1]) = unsigned char(p1);
			(m_uchrData[2]) = unsigned char(p2);
			(m_uchrData[3]) = unsigned char(p3);
			(m_uchrData[4]) = unsigned char(p4);
			(m_uchrData[5]) = unsigned char(p5);
			(m_uchrData[6]) = unsigned char(p6);
			(m_uchrData[7]) = unsigned char(p7);
			(m_uchrData[8]) = unsigned char(p8);
			(m_uchrData[9]) = unsigned char(p9);
			(m_uchrData[10]) = unsigned char(p10);
			(m_uchrData[11]) = unsigned char(p11);
			(m_uchrData[12]) = unsigned char(p12);
			(m_uchrData[13]) = unsigned char(p13);
			(m_uchrData[14]) = unsigned char(p14);
			(m_uchrData[15]) = unsigned char(p15);

			return true;
		}catch(...){
			return false;
		};	

	};

	//!Sets the GUID to the NULL ID 00000000-00000000-00000000-00000000
	void HtlGUID128::setNull(void)
	{
		for(int i = 0; i < 16; i++)
		{
			m_uchrData[i] = NULL;
		};
	};

	bool HtlGUID128::isNull(void)
	{
		bool blnNull = true;
		for(int i = 0; i < 16; i++)
		{
			if(m_uchrData[i] != NULL)
			{
				blnNull = false;
			};
		};
		return blnNull;
	};

	//!Assignment Operator Overloads
	HtlGUID128 & HtlGUID128::operator= ( const GUID & ptrRHS )
	{
		//Windows GUID format check c5057190-a286-4427-b172-2fc56a92423f
		char chrBuff[20];
		sprintf(chrBuff,"%08x",ptrRHS.Data1);//convert it to hexidecimal characters
		sscanf(chrBuff,"%02x%02x%02x%02x",
			&(m_uchrData[0]),
			&(m_uchrData[1]),
			&(m_uchrData[2]),
			&(m_uchrData[3]) );
		sprintf(chrBuff,"%04x",ptrRHS.Data2);//convert it to hexidecimal characters
		sscanf(chrBuff,"%02x%02x",
			&(m_uchrData[4]),
			&(m_uchrData[5]) );
		sprintf(chrBuff,"%04x",ptrRHS.Data3);//convert it to hexidecimal characters
		sscanf(chrBuff,"%02x%02x",
			&(m_uchrData[6]),
			&(m_uchrData[7]) );
		sprintf(chrBuff,"%012x",ptrRHS.Data4);//convert it to hexidecimal characters
		sscanf(chrBuff,"%02x%02x%02x%02x%02x%02x",
			&(m_uchrData[8]),
			&(m_uchrData[9]),
			&(m_uchrData[10]),
			&(m_uchrData[11]),
			&(m_uchrData[12]),
			&(m_uchrData[13]),
			&(m_uchrData[14]),
			&(m_uchrData[15]) );
		return *this;
	};

	HtlGUID128 &	HtlGUID128::operator= ( const HtlGUID128 & ptrRHS )
	{
		for(int i = 0; i < 16; i++)
		{
			m_uchrData[i] = ptrRHS[i];
		};
		return *this;
	};

	//!Boolean Logic Operator Overloads
	bool HtlGUID128::operator == (const HtlGUID128 & ptrRHS )
	{
		for(int i = 0; i < 16; i++)
		{
			if(m_uchrData[i] != ptrRHS[i]){return false;};
		};
		//made it all the way through
		return true;
	};

	bool HtlGUID128::operator != (const HtlGUID128 & ptrRHS )
	{
		for(int i = 0; i < 16; i++)
		{
			if(m_uchrData[i] != ptrRHS[i]){return true;};
		};
		//made it all the way through
		return false;
	};

	bool HtlGUID128::operator < (const HtlGUID128 & ptrRHS )
	{
		for(int i = 0; i < 16; i++)
		{
			if(m_uchrData[i] < ptrRHS[i])
			{
				return true;
			}else if(m_uchrData[i] > ptrRHS[i]){
				return false;
			}
			//otherwise equal, continue to next character
		};
		//made it all the way through, must be equal
		return false;
	};

	bool HtlGUID128::operator > (const HtlGUID128 & ptrRHS )
	{
		for(int i = 0; i < 16; i++)
		{
			if(m_uchrData[i] > ptrRHS[i])
			{
				return true;
			}else if(m_uchrData[i] < ptrRHS[i]){
				return false;
			}
			//otherwise equal, continue to next character
		};
		//made it all the way through, must be equal
		return false;
	};

	bool HtlGUID128::operator <= (const HtlGUID128 & ptrRHS )
	{
		for(int i = 0; i < 16; i++)
		{
			if(m_uchrData[i] < ptrRHS[i])
			{
				return true;
			}else if(m_uchrData[i] > ptrRHS[i]){
				return false;
			}
			//otherwise equal, continue to next character
		};
		//made it all the way through, must be equal
		return true;
	};

	bool HtlGUID128::operator >= (const HtlGUID128 & ptrRHS )
	{
		for(int i = 0; i < 16; i++)
		{
			if(m_uchrData[i] > ptrRHS[i])
			{
				return true;
			}else if(m_uchrData[i] < ptrRHS[i]){
				return false;
			}
			//otherwise equal, continue to next character
		};
		//made it all the way through, must be equal
		return true;
	};

	//These are for Microsoft Windows Format Compatibility
	bool HtlGUID128::operator == (const GUID & ptrRHS )
	{
		HtlGUID128 objTemp;
		objTemp = ptrRHS;
		return operator==(objTemp);
	};

	bool HtlGUID128::operator != (const GUID & ptrRHS )
	{
		HtlGUID128 objTemp;
		objTemp = ptrRHS;
		return operator!=(objTemp);
	};

	bool HtlGUID128::operator < (const GUID & ptrRHS )
	{
		HtlGUID128 objTemp;
		objTemp = ptrRHS;
		return operator<(objTemp);
	};

	bool HtlGUID128::operator > (const GUID & ptrRHS )
	{
		HtlGUID128 objTemp;
		objTemp	= ptrRHS;
		return operator>(objTemp);
	};

	bool HtlGUID128::operator <= (const GUID & ptrRHS )
	{
		HtlGUID128 objTemp;
		objTemp = ptrRHS;
		return operator<=(objTemp);
	};

	bool HtlGUID128::operator >= (const GUID & ptrRHS )
	{
		HtlGUID128 objTemp;
		objTemp = ptrRHS;
		return operator==(objTemp);
	};


	//!HTL Container Accessors
	const uchar & HtlGUID128::at(size_t i) const
	{

		if((i >= 0) && (i < 16))
		{
			return m_uchrData[i];
		}else{
			//invalid index return NULL
			return m_chrNull;
		};
		return m_chrNull;
	};
	uchar & HtlGUID128::at(size_t i)
	{

		if((i >= 0) && (i < 16))
		{
			return m_uchrData[i];
		}else{
			//invalid index return NULL
			return m_chrNull;
		};
		return m_chrNull;
	};
	const uchar & HtlGUID128::operator[](size_t i) const
	{
		if((i >= 0) && (i < 16))
		{
			return m_uchrData[i];
		}else{
			//invalid index return NULL
			return m_chrNull;
		};
		return m_chrNull;
	};
	uchar & HtlGUID128::operator[](size_t i)
	{
		if((i >= 0) && (i < 16))
		{
			return m_uchrData[i];
		}else{
			//invalid index return NULL
			return m_chrNull;
		};
		return m_chrNull;
	};

	//Windows GUID format check c5057190-a286-4427-b172-2fc56a92423f
	bool HtlGUID128::isValidWinGUID(const char * strInput)
	{
		if(!strInput){return false;};//safety code
		int i, intNumChars;
		intNumChars = strlen(strInput);
		if(intNumChars != 36)
		{//then wrong length GUID is 32 hex and 4 '-'
			return false;
		};
		//check the hyphen locations
		for(i = 0; i < intNumChars;i++)
		{
			if((i == 8) || (i == 13) || (i == 18) || (i == 23))
			{
				//then expect a hyphen
				if(strInput[i] != '-')
				{
					return false;
				};
			}else{
				//otherwise expect a hex
				if(isxdigit(strInput[i]) == 0)
				{
					//then not a hexidecimal digit
					return false;
				};
			};
		};
		//made it all the way through without kicking out false, must be a valid GUID
		return true;
	};

	//Windows GUID format check c5057190-a2864427-b1722fc5-6a92423f
	bool HtlGUID128::isValidHtlGUID(const char * strInput)
	{
		if(!strInput){return false;};//safety code
		int i, intNumChars;
		intNumChars = strlen(strInput);
		if(intNumChars != 36)
		{//then wrong length GUID is 32 hex and 4 '-'
			return false;
		};
		//check the hyphen locations
		for(i = 0; i < intNumChars;i++)
		{
			if((i == 8) || (i == 17) || (i == 26))
			{
				//then expect a hyphen
				if(strInput[i] != '-')
				{
					return false;
				};
			}else{
				//otherwise expect a hex
				if(isxdigit(strInput[i]) == 0)
				{
					//then not a hexidecimal digit
					return false;
				};
			};
		};
		//made it all the way through without kicking out false, must be a valid GUID
		return true;
	};

	//!Method for generating a global unique identifier
	void HtlGUID128::createGUID128(void)
	{;
		for(int i = 0; i < 16; i++)
		{
			m_uchrData[i] = GetRNG()->intNextAB(0,255);
		};
	};

	HTL::HtlUniform * HtlGUID128::GetRNG(void)
	{
		static HTL::HtlUniform m_objRNG;
		return &m_objRNG;
	}

};//end HTL namespace