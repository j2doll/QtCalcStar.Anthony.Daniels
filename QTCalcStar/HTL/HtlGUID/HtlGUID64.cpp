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


#include ".\HtlGUID64.h"
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

	HtlGUID64::HtlGUID64()
	{
		setNull();
	};

	//This is HtlGUID native format with symmetric strings  c5057190-a2864427-b1722fc5-6a92423f
	HtlGUID64::HtlGUID64 ( uint w0, uint w1)
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
		}catch(...){

		};
		return;
	};

	HtlGUID64::HtlGUID64 ( const char* ptrRHS )
	{
		//ASSUMES NATIVE FORMAT
		try{
			setNull();
			if(!ptrRHS){return;};//safety code
			sscanf(ptrRHS,"%02x%02x%02x%02x-%02x%02x%02x%02x",
				&(m_uchrData[0]), &(m_uchrData[1]),	&(m_uchrData[2]), &(m_uchrData[3]),
				&(m_uchrData[4]), &(m_uchrData[5]),	&(m_uchrData[6]), &(m_uchrData[7]) );
		}catch(...){

		}
		return;
	};
	HtlGUID64::HtlGUID64 ( const HtlString & strRHS )
	{
		HtlGUID64(strRHS.unicode());
		return;
	};
	HtlGUID64::HtlGUID64 ( const HtlGUID64 & ptrRHS )
	{
		for(int i = 0; i < 8; i++)
		{
			m_uchrData[i] = ptrRHS[i];
		};
	};
	HtlGUID64::~HtlGUID64()
	{
		setNull();	
	};

	//!Serialization TO string formats
	HtlString HtlGUID64::toString (void) const
	{
		char charBuf[256];
		sprintf(charBuf,"%02X%02X%02X%02X-%02X%02X%02X%02X",
			(m_uchrData[0]), (m_uchrData[1]), (m_uchrData[2]), (m_uchrData[3]),
			(m_uchrData[4]), (m_uchrData[5]), (m_uchrData[6]), (m_uchrData[7]) );

		HtlString strOut = charBuf;
		return strOut;	
	};

	std::string HtlGUID64::toStdString (void) const
	{
		char charBuf[256];
		sprintf(charBuf,"%02X%02X%02X%02X-%02X%02X%02X%02X",
			(m_uchrData[0]), (m_uchrData[1]), (m_uchrData[2]), (m_uchrData[3]),
			(m_uchrData[4]), (m_uchrData[5]), (m_uchrData[6]), (m_uchrData[7]));

		std::string strOut = charBuf;
		return strOut;
	};

	const char* HtlGUID64::toCharString(void)
	{
		sprintf(m_strData,"%02X%02X%02X%02X-%02X%02X%02X%02X",
			(m_uchrData[0]), (m_uchrData[1]), (m_uchrData[2]), (m_uchrData[3]),
			(m_uchrData[4]), (m_uchrData[5]), (m_uchrData[6]), (m_uchrData[7]) );

		return &m_strData[0];
	};

	//!Serialization FROM string formats
	bool HtlGUID64::fromString(HtlString & ptrRHS)
	{
		try{
			char chrBuf[128];
			int p0, p1, p2, p3, p4, p5, p6, p7;
			strcpy(chrBuf, ptrRHS.unicode());
			sscanf_s(chrBuf,"%02X%02X%02X%02X-%02X%02X%02X%02X",
				&p0, &p1, &p2, &p3, &p4, &p5, &p6, &p7);

			(m_uchrData[0]) = unsigned char(p0);
			(m_uchrData[1]) = unsigned char(p1);
			(m_uchrData[2]) = unsigned char(p2);
			(m_uchrData[3]) = unsigned char(p3);
			(m_uchrData[4]) = unsigned char(p4);
			(m_uchrData[5]) = unsigned char(p5);
			(m_uchrData[6]) = unsigned char(p6);
			(m_uchrData[7]) = unsigned char(p7);


			return true;
		}catch(...){
			return false;
		};	

	};

	bool HtlGUID64::fromStdString( std::string & ptrRHS)
	{
		try{
			char chrBuf[128];
			int p0, p1, p2, p3, p4, p5, p6, p7;
			strcpy(chrBuf, ptrRHS.c_str());
			sscanf_s(chrBuf,"%02X%02X%02X%02X-%02X%02X%02X%02X",
				&p0, &p1, &p2, &p3, &p4, &p5, &p6, &p7);

			(m_uchrData[0]) = unsigned char(p0);
			(m_uchrData[1]) = unsigned char(p1);
			(m_uchrData[2]) = unsigned char(p2);
			(m_uchrData[3]) = unsigned char(p3);
			(m_uchrData[4]) = unsigned char(p4);
			(m_uchrData[5]) = unsigned char(p5);
			(m_uchrData[6]) = unsigned char(p6);
			(m_uchrData[7]) = unsigned char(p7);


			return true;
		}catch(...){
			return false;
		};

	};

	bool HtlGUID64::fromCharString(const char* ptrRHS)
	{
		try{
			if(!ptrRHS){return false;};//safety code
			char chrBuf[128];
			int p0, p1, p2, p3, p4, p5, p6, p7;
			strcpy(chrBuf, ptrRHS);
			sscanf_s(chrBuf,"%02X%02X%02X%02X-%02X%02X%02X%02X",
				&p0, &p1, &p2, &p3, &p4, &p5, &p6, &p7);

			(m_uchrData[0]) = unsigned char(p0);
			(m_uchrData[1]) = unsigned char(p1);
			(m_uchrData[2]) = unsigned char(p2);
			(m_uchrData[3]) = unsigned char(p3);
			(m_uchrData[4]) = unsigned char(p4);
			(m_uchrData[5]) = unsigned char(p5);
			(m_uchrData[6]) = unsigned char(p6);
			(m_uchrData[7]) = unsigned char(p7);


			return true;
		}catch(...){
			return false;
		};	

	};

	//!Sets the GUID to the NULL ID 00000000-00000000-00000000-00000000
	void HtlGUID64::setNull(void)
	{
		for(int i = 0; i < 8; i++)
		{
			m_uchrData[i] = NULL;
		};
	};

	bool HtlGUID64::isNull(void)
	{
		bool blnNull = true;
		for(int i = 0; i < 8; i++)
		{
			if(m_uchrData[i] != NULL)
			{
				blnNull = false;
			};
		};
		return blnNull;
	};

	//!Assignment Operator Overloads
	HtlGUID64 & HtlGUID64::operator= ( const GUID & ptrRHS )
	{
		//Windows GUID format check c5057190-a286-4427
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
	
		return *this;
	};

	HtlGUID64 &	HtlGUID64::operator= ( const HtlGUID64 & ptrRHS )
	{
		for(int i = 0; i < 16; i++)
		{
			m_uchrData[i] = ptrRHS[i];
		};
		return *this;
	};

	//!Boolean Logic Operator Overloads
	bool HtlGUID64::operator == (const HtlGUID64 & ptrRHS )
	{
		for(int i = 0; i < 16; i++)
		{
			if(m_uchrData[i] != ptrRHS[i]){return false;};
		};
		//made it all the way through
		return true;
	};

	bool HtlGUID64::operator != (const HtlGUID64 & ptrRHS )
	{
		for(int i = 0; i < 16; i++)
		{
			if(m_uchrData[i] != ptrRHS[i]){return true;};
		};
		//made it all the way through
		return false;
	};

	bool HtlGUID64::operator < (const HtlGUID64 & ptrRHS )
	{
		for(int i = 0; i < 16; i++)
		{
			if(m_uchrData[i] > ptrRHS[i]){return false;};
		};
		//made it all the way through
		return true;
	};

	bool HtlGUID64::operator > (const HtlGUID64 & ptrRHS )
	{
		for(int i = 0; i < 16; i++)
		{
			if(m_uchrData[i] < ptrRHS[i]){return false;};
		};
		//made it all the way through
		return true;
	};

	bool HtlGUID64::operator <= (const HtlGUID64 & ptrRHS )
	{
		for(int i = 0; i < 16; i++)
		{
			if(m_uchrData[i] > ptrRHS[i]){return false;};
		};
		//made it all the way through
		return true;
	};

	bool HtlGUID64::operator >= (const HtlGUID64 & ptrRHS )
	{
		for(int i = 0; i < 16; i++)
		{
			if(m_uchrData[i] < ptrRHS[i]){return false;};
		};
		//made it all the way through
		return true;
	};

	//!HTL Container Accessors
	const uchar & HtlGUID64::at(size_t i) const
	{

		if((i >= 0) && (i < 8))
		{
			return m_uchrData[i];
		}else{
			//invalid index return NULL
			return m_chrNull;
		};
		return m_chrNull;
	};
	uchar & HtlGUID64::at(size_t i)
	{

		if((i >= 0) && (i < 8))
		{
			return m_uchrData[i];
		}else{
			//invalid index return NULL
			return m_chrNull;
		};
		return m_chrNull;
	};
	const uchar & HtlGUID64::operator[](size_t i) const
	{
		if((i >= 0) && (i < 8))
		{
			return m_uchrData[i];
		}else{
			//invalid index return NULL
			return m_chrNull;
		};
		return m_chrNull;
	};
	uchar & HtlGUID64::operator[](size_t i)
	{
		if((i >= 0) && (i < 8))
		{
			return m_uchrData[i];
		}else{
			//invalid index return NULL
			return m_chrNull;
		};
		return m_chrNull;
	};

	//Windows GUID format check c5057190-a2864427
	bool HtlGUID64::isValidHtlGUID(const char * strInput)
	{
		if(!strInput){return false;};//safety code
		int i, intNumChars;
		intNumChars = strlen(strInput);
		if(intNumChars != 17)
		{//then wrong length GUID is 17 hex and 1 '-'
			return false;
		};
		//check the hyphen locations
		for(i = 0; i < intNumChars;i++)
		{
			if(i == 8)
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
	void HtlGUID64::createGUID64(void)
	{;
		for(int i = 0; i < 8; i++)
		{
			m_uchrData[i] = GetRNG()->intNextAB(0,255);
		};
	};

	HTL::HtlUniform * HtlGUID64::GetRNG(void)
	{
		static HTL::HtlUniform m_objRNG;
		return &m_objRNG;
	}

};//end HTL namespace