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



#include "..\HtlString\HtlString.h"
#include "..\modHtlRandNumGen.h"
#include ".\HtlGUID128.h"
#include ".\HtlGUID256.h"


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


	HtlGUID256::HtlGUID256()
	{
		setNull();
	};
	//This constructor is kept for Windows compatibility
	//HtlGUID128 native is symmetric storage
	//Microsoft Windows format for GUIDs is  c5057190-a286-4427-b172-2fc56a92423f in hex string
	//128 bit GUID becomes c5057190-a2864427-b1722fc5-6a92423f-00000000-00000000-00000000-00000000
	//with zero padding in the later 128 bits
	HtlGUID256::HtlGUID256 ( uint l, ushort w1, ushort w2, uchar b1, uchar b2, uchar b3, uchar b4, uchar b5, uchar b6, uchar b7, uchar b8 )
	{
		try{
			char chrBuff[20];
			setNull();

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
			
			for(int i = 16; i < 32; i++)
			{
				m_uchrData[i] = '0';
			};
		}catch(...){

		};
		return;
	};
	//This is HtlGUID native format with symmetric strings  c5057190-a2864427-b1722fc5-6a92423f-c5057190-a2864427-b1722fc5-6a92423f
	HtlGUID256::HtlGUID256 ( uint w0, uint w1, uint w2, uint w3,uint w4, uint w5, uint w6, uint w7)
	{
		try{
			char chrBuff[20];
			setNull();

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
			sprintf(chrBuff,"%08x",w4);//convert it to hexidecimal characters
			sscanf(chrBuff,"%02x%02x%02x%02x",
				&(m_uchrData[16]),
				&(m_uchrData[17]),
				&(m_uchrData[18]),
				&(m_uchrData[19]) );
			sprintf(chrBuff,"%08x",w5);//convert it to hexidecimal characters
			sscanf(chrBuff,"%02x%02x%02x%02x",
				&(m_uchrData[20]),
				&(m_uchrData[21]),
				&(m_uchrData[22]),
				&(m_uchrData[23]) );
			sprintf(chrBuff,"%08x",w6);//convert it to hexidecimal characters
			sscanf(chrBuff,"%02x%02x%02x%02x",
				&(m_uchrData[24]),
				&(m_uchrData[25]),
				&(m_uchrData[26]),
				&(m_uchrData[27]) );
			sprintf(chrBuff,"%08x",w7);//convert it to hexidecimal characters
			sscanf(chrBuff,"%02x%02x%02x%02x",
				&(m_uchrData[28]),
				&(m_uchrData[29]),
				&(m_uchrData[30]),
				&(m_uchrData[31]) );

		}catch(...){

		};
		return;
	};

	HtlGUID256::HtlGUID256 ( const char* ptrRHS )
	{
		//ASSUMES NATIVE FORMAT
		try{
			setNull();
			if(!ptrRHS){return;};//safety code
			sscanf(ptrRHS,"%02x%02x%02x%02x-%02x%02x%02x%02x-%02x%02x%02x%02x-%02x%02x%02x%02x-%02x%02x%02x%02x-%02x%02x%02x%02x-%02x%02x%02x%02x-%02x%02x%02x%02x",
				&(m_uchrData[0]), &(m_uchrData[1]),	&(m_uchrData[2]), &(m_uchrData[3]),
				&(m_uchrData[4]), &(m_uchrData[5]),	&(m_uchrData[6]), &(m_uchrData[7]),
				&(m_uchrData[8]), &(m_uchrData[9]),	&(m_uchrData[10]), &(m_uchrData[11]),
				&(m_uchrData[12]), &(m_uchrData[13]), &(m_uchrData[14]), &(m_uchrData[15]),
				&(m_uchrData[16]), &(m_uchrData[17]), &(m_uchrData[18]), &(m_uchrData[19]),
				&(m_uchrData[20]), &(m_uchrData[21]), &(m_uchrData[22]), &(m_uchrData[23]),
				&(m_uchrData[24]), &(m_uchrData[25]), &(m_uchrData[26]), &(m_uchrData[27]),
				&(m_uchrData[28]), &(m_uchrData[29]), &(m_uchrData[30]), &(m_uchrData[31]) );
		}catch(...){

		}
		return;
	};
	HtlGUID256::HtlGUID256 ( const HtlString & strRHS )
	{
		m_chrNull = '0';

		HtlGUID256(strRHS.unicode());
		return;
	};
		
	HtlGUID256::HtlGUID256 ( const HtlGUID128 & ptrRHS )
	{
		setNull();
		for(int i = 0; i < 16; i++)
		{
			m_uchrData[i] = ptrRHS[i];
		};
	};

	HtlGUID256::HtlGUID256 ( const HtlGUID256 & ptrRHS )
	{
		for(int i = 0; i < 32; i++)
		{
			m_uchrData[i] = ptrRHS[i];
		};
	};
	HtlGUID256::~HtlGUID256()
	{
		setNull();	
	};

	//!Serialization TO string formats
	HtlString HtlGUID256::toString (void) const
	{
		char charBuf[256];
		sprintf(charBuf,"%02X%02X%02X%02X-%02X%02X%02X%02X-%02X%02X%02X%02X-%02X%02X%02X%02X-%02X%02X%02X%02X-%02X%02X%02X%02X-%02X%02X%02X%02X-%02X%02X%02X%02X",
			(m_uchrData[0]), (m_uchrData[1]), (m_uchrData[2]), (m_uchrData[3]),
			(m_uchrData[4]), (m_uchrData[5]), (m_uchrData[6]), (m_uchrData[7]),
			(m_uchrData[8]), (m_uchrData[9]), (m_uchrData[10]),	(m_uchrData[11]),
			(m_uchrData[12]), (m_uchrData[13]),	(m_uchrData[14]),(m_uchrData[15]),
			(m_uchrData[16]), (m_uchrData[17]), (m_uchrData[18]), (m_uchrData[19]),
			(m_uchrData[20]), (m_uchrData[21]), (m_uchrData[22]), (m_uchrData[23]),
			(m_uchrData[24]), (m_uchrData[25]), (m_uchrData[26]), (m_uchrData[27]),
			(m_uchrData[28]), (m_uchrData[29]),	(m_uchrData[30]), (m_uchrData[31]) );
		HtlString strOut = charBuf;
		return strOut;	
	};

	std::string HtlGUID256::toStdString (void) const
	{
		char charBuf[256];
		sprintf(charBuf,"%02X%02X%02X%02X-%02X%02X%02X%02X-%02X%02X%02X%02X-%02X%02X%02X%02X-%02X%02X%02X%02X-%02X%02X%02X%02X-%02X%02X%02X%02X-%02X%02X%02X%02X",
			(m_uchrData[0]), (m_uchrData[1]), (m_uchrData[2]), (m_uchrData[3]),
			(m_uchrData[4]), (m_uchrData[5]), (m_uchrData[6]), (m_uchrData[7]),
			(m_uchrData[8]), (m_uchrData[9]), (m_uchrData[10]),	(m_uchrData[11]),
			(m_uchrData[12]), (m_uchrData[13]),	(m_uchrData[14]),(m_uchrData[15]),
			(m_uchrData[16]), (m_uchrData[17]), (m_uchrData[18]), (m_uchrData[19]),
			(m_uchrData[20]), (m_uchrData[21]), (m_uchrData[22]), (m_uchrData[23]),
			(m_uchrData[24]), (m_uchrData[25]), (m_uchrData[26]), (m_uchrData[27]),
			(m_uchrData[28]), (m_uchrData[29]),	(m_uchrData[30]), (m_uchrData[31]) );

		std::string strOut = charBuf;
		return strOut;
	};

	const char* HtlGUID256::toCharString(void)
	{
		sprintf(m_strData,"%02X%02X%02X%02X-%02X%02X%02X%02X-%02X%02X%02X%02X-%02X%02X%02X%02X-%02X%02X%02X%02X-%02X%02X%02X%02X-%02X%02X%02X%02X-%02X%02X%02X%02X",
			(m_uchrData[0]), (m_uchrData[1]), (m_uchrData[2]), (m_uchrData[3]),
			(m_uchrData[4]), (m_uchrData[5]), (m_uchrData[6]), (m_uchrData[7]),
			(m_uchrData[8]), (m_uchrData[9]), (m_uchrData[10]),	(m_uchrData[11]),
			(m_uchrData[12]), (m_uchrData[13]),	(m_uchrData[14]),(m_uchrData[15]),
			(m_uchrData[16]), (m_uchrData[17]), (m_uchrData[18]), (m_uchrData[19]),
			(m_uchrData[20]), (m_uchrData[21]), (m_uchrData[22]), (m_uchrData[23]),
			(m_uchrData[24]), (m_uchrData[25]), (m_uchrData[26]), (m_uchrData[27]),
			(m_uchrData[28]), (m_uchrData[29]),	(m_uchrData[30]), (m_uchrData[31]) );

		return &m_strData[0];
	};

	//!Serialization FROM string formats
	bool HtlGUID256::fromString(HtlString & ptrRHS)
	{
		try{
			char chrBuf[256];
			int p0, p1, p2, p3, p4, p5, p6, p7, p8, p9, p10, p11, p12, p13, p14, p15;
			int p16, p17, p18, p19, p20, p21, p22, p23, p24, p25, p26, p27, p28, p29, p30, p31;
			strcpy(chrBuf, ptrRHS.unicode());
			sscanf_s(chrBuf,"%02X%02X%02X%02X-%02X%02X%02X%02X-%02X%02X%02X%02X-%02X%02X%02X%02X-%02X%02X%02X%02X-%02X%02X%02X%02X-%02X%02X%02X%02X-%02X%02X%02X%02X",
				&p0, &p1, &p2, &p3, &p4, &p5, &p6, &p7, &p8, &p9, &p10, &p11, &p12, &p13, &p14, &p15,
				&p16, &p17, &p18, &p19, &p20, &p21, &p22, &p23, &p24, &p25, &p26, &p27, &p28, &p29, &p30, &p31);

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
			(m_uchrData[16]) = unsigned char(p16);
			(m_uchrData[17]) = unsigned char(p17);
			(m_uchrData[18]) = unsigned char(p18);
			(m_uchrData[19]) = unsigned char(p19);
			(m_uchrData[20]) = unsigned char(p20);
			(m_uchrData[21]) = unsigned char(p21);
			(m_uchrData[22]) = unsigned char(p22);
			(m_uchrData[23]) = unsigned char(p23);
			(m_uchrData[24]) = unsigned char(p24);
			(m_uchrData[25]) = unsigned char(p25);
			(m_uchrData[26]) = unsigned char(p26);
			(m_uchrData[27]) = unsigned char(p27);
			(m_uchrData[28]) = unsigned char(p28);
			(m_uchrData[29]) = unsigned char(p29);
			(m_uchrData[30]) = unsigned char(p30);
			(m_uchrData[31]) = unsigned char(p31);
			return true;
		}catch(...){
			return false;
		};	

	};

	bool HtlGUID256::fromStdString( std::string & ptrRHS)
	{
		try{
		char chrBuf[256];
			int p0, p1, p2, p3, p4, p5, p6, p7, p8, p9, p10, p11, p12, p13, p14, p15;
			int p16, p17, p18, p19, p20, p21, p22, p23, p24, p25, p26, p27, p28, p29, p30, p31;
			strcpy(chrBuf, ptrRHS.c_str());
			sscanf_s(chrBuf,"%02X%02X%02X%02X-%02X%02X%02X%02X-%02X%02X%02X%02X-%02X%02X%02X%02X-%02X%02X%02X%02X-%02X%02X%02X%02X-%02X%02X%02X%02X-%02X%02X%02X%02X",
				&p0, &p1, &p2, &p3, &p4, &p5, &p6, &p7, &p8, &p9, &p10, &p11, &p12, &p13, &p14, &p15,
				&p16, &p17, &p18, &p19, &p20, &p21, &p22, &p23, &p24, &p25, &p26, &p27, &p28, &p29, &p30, &p31);

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
			(m_uchrData[16]) = unsigned char(p16);
			(m_uchrData[17]) = unsigned char(p17);
			(m_uchrData[18]) = unsigned char(p18);
			(m_uchrData[19]) = unsigned char(p19);
			(m_uchrData[20]) = unsigned char(p20);
			(m_uchrData[21]) = unsigned char(p21);
			(m_uchrData[22]) = unsigned char(p22);
			(m_uchrData[23]) = unsigned char(p23);
			(m_uchrData[24]) = unsigned char(p24);
			(m_uchrData[25]) = unsigned char(p25);
			(m_uchrData[26]) = unsigned char(p26);
			(m_uchrData[27]) = unsigned char(p27);
			(m_uchrData[28]) = unsigned char(p28);
			(m_uchrData[29]) = unsigned char(p29);
			(m_uchrData[30]) = unsigned char(p30);
			(m_uchrData[31]) = unsigned char(p31);
			return true;
		}catch(...){
			return false;
		};

	};

	bool HtlGUID256::fromCharString(const char* ptrRHS)
	{
		try{
			if(!ptrRHS){return false;};//safety code
			char chrBuf[256];
			int p0, p1, p2, p3, p4, p5, p6, p7, p8, p9, p10, p11, p12, p13, p14, p15;
			int p16, p17, p18, p19, p20, p21, p22, p23, p24, p25, p26, p27, p28, p29, p30, p31;
			strcpy(chrBuf, ptrRHS);
			sscanf_s(chrBuf,"%02X%02X%02X%02X-%02X%02X%02X%02X-%02X%02X%02X%02X-%02X%02X%02X%02X-%02X%02X%02X%02X-%02X%02X%02X%02X-%02X%02X%02X%02X-%02X%02X%02X%02X",
				&p0, &p1, &p2, &p3, &p4, &p5, &p6, &p7, &p8, &p9, &p10, &p11, &p12, &p13, &p14, &p15,
				&p16, &p17, &p18, &p19, &p20, &p21, &p22, &p23, &p24, &p25, &p26, &p27, &p28, &p29, &p30, &p31);

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
			(m_uchrData[16]) = unsigned char(p16);
			(m_uchrData[17]) = unsigned char(p17);
			(m_uchrData[18]) = unsigned char(p18);
			(m_uchrData[19]) = unsigned char(p19);
			(m_uchrData[20]) = unsigned char(p20);
			(m_uchrData[21]) = unsigned char(p21);
			(m_uchrData[22]) = unsigned char(p22);
			(m_uchrData[23]) = unsigned char(p23);
			(m_uchrData[24]) = unsigned char(p24);
			(m_uchrData[25]) = unsigned char(p25);
			(m_uchrData[26]) = unsigned char(p26);
			(m_uchrData[27]) = unsigned char(p27);
			(m_uchrData[28]) = unsigned char(p28);
			(m_uchrData[29]) = unsigned char(p29);
			(m_uchrData[30]) = unsigned char(p30);
			(m_uchrData[31]) = unsigned char(p31);
			return true;
		}catch(...){
			return false;
		};	

	};

	//!Sets the GUID to the NULL ID 00000000-00000000-00000000-00000000
	void HtlGUID256::setNull(void)
	{
		m_chrNull = '0';
		for(int i = 0; i < 32; i++)
		{
			m_uchrData[i] = NULL;
		};
	};

	bool HtlGUID256::isNull(void)
	{
		bool blnNull = true;
		for(int i = 0; i < 32; i++)
		{
			if(m_uchrData[i] != NULL)
			{
				blnNull = false;
			};
		};
		return blnNull;
	};

	//!Assignment Operator Overloads
	HtlGUID256 & HtlGUID256::operator= ( const GUID & ptrRHS )
	{
		//Windows GUID format check c5057190-a286-4427-b172-2fc56a92423f
		setNull();//zero pad the tail of the GUID
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

	HtlGUID256 &	HtlGUID256::operator= ( const HtlGUID256 & ptrRHS )
	{
		for(int i = 0; i < 32; i++)
		{
			m_uchrData[i] = ptrRHS[i];
		};
		return *this;
	};

	//!Boolean Logic Operator Overloads
	bool HtlGUID256::operator == (const HtlGUID256 & ptrRHS )
	{
		for(int i = 0; i < 32; i++)
		{
			if(m_uchrData[i] != ptrRHS[i]){return false;};
		};
		//made it all the way through
		return true;
	};

	bool HtlGUID256::operator != (const HtlGUID256 & ptrRHS )
	{
		for(int i = 0; i < 32; i++)
		{
			if(m_uchrData[i] != ptrRHS[i]){return true;};
		};
		//made it all the way through
		return false;
	};

	bool HtlGUID256::operator < (const HtlGUID256 & ptrRHS )
	{
		for(int i = 0; i < 32; i++)
		{
			if(m_uchrData[i] > ptrRHS[i]){return false;};
		};
		//made it all the way through
		return true;
	};

	bool HtlGUID256::operator > (const HtlGUID256 & ptrRHS )
	{
		for(int i = 0; i < 32; i++)
		{
			if(m_uchrData[i] < ptrRHS[i]){return false;};
		};
		//made it all the way through
		return true;
	};

	bool HtlGUID256::operator <= (const HtlGUID256 & ptrRHS )
	{
		for(int i = 0; i < 32; i++)
		{
			if(m_uchrData[i] > ptrRHS[i]){return false;};
		};
		//made it all the way through
		return true;
	};

	bool HtlGUID256::operator >= (const HtlGUID256 & ptrRHS )
	{
		for(int i = 0; i < 32; i++)
		{
			if(m_uchrData[i] < ptrRHS[i]){return false;};
		};
		//made it all the way through
		return true;
	};

	//!HTL Container Accessors
	const uchar & HtlGUID256::at(size_t i) const
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
	uchar & HtlGUID256::at(size_t i)
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
	const uchar & HtlGUID256::operator[](size_t i) const
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
	uchar & HtlGUID256::operator[](size_t i)
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
	bool HtlGUID256::isValidWinGUID(const char * strInput)
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
	bool HtlGUID256::isValidHtlGUID(const char * strInput)
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
	void HtlGUID256::createGUID256(void)
	{;
		for(int i = 0; i < 32; i++)
		{
			m_uchrData[i] = GetRNG()->intNextAB(0,255);
		};
	};

	HTL::HtlUniform * HtlGUID256::GetRNG(void)
	{
		static HTL::HtlUniform m_objRNG;
		return &m_objRNG;
	}


};//end HTL namespace