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

#ifndef HTL_GUID256_H
#define HTL_GUID256_H

#include "..\modHtlLibRefs.h"
#include <string>
using namespace std;

namespace HTL{
	
	class HtlString;
	class HtlGUID128;
	class HtlRandNumDist;
	typedef HtlRandNumDist HtlUniform;

	//!HtlGUID256 is a 256 bit Global Unique Identifier  (32 chars)
	/*!
		HtlString is a character container class for holding strings. 
		It is based off of the QT and MFC GUID classes.  The goal of this class is to provide the 
		basic container for Global Unique Identifiers.
		HtlGUID native format with symmetric strings  
		c5057190-a2864427-b1722fc5-6a92423f-c5057190-a2864427-b1722fc5-6a92423f  in hex string.
	*/

	class HTL_DLLAPI HtlGUID256{


	public:

		HtlGUID256 ();
		//This constructor is kept for Windows compatibility
		//HtlGUID128 native is symmetric storage
		//Microsoft Windows format for GUIDs is  c5057190-a286-4427-b172-2fc56a92423f in hex string
		//128 bit GUID becomes c5057190-a2864427-b1722fc5-6a92423f-00000000-00000000-00000000-00000000
		//with zero padding in the later 128 bits
		HtlGUID256 ( uint l, ushort w1, ushort w2, uchar b1, uchar b2, uchar b3, uchar b4, uchar b5, uchar b6, uchar b7, uchar b8 );
		//This is HtlGUID native format with symmetric strings c5057190-a2864427-b1722fc5-6a92423f-c5057190-a2864427-b1722fc5-6a92423f
		HtlGUID256 ( uint w0, uint w1, uint w2, uint w3,uint w4, uint w5, uint w6, uint w7);
		HtlGUID256 ( const char* ptrRHS );
		HtlGUID256 ( const HtlString & strRHS );
		HtlGUID256 ( const HtlGUID128 & ptrRHS );
		HtlGUID256 ( const HtlGUID256 & ptrRHS );
		virtual ~HtlGUID256 ();

		//!Serialization TO string formats
		HtlString	toString (void) const;
		std::string toStdString (void) const;
		const char* toCharString(void);

		//!Serialization FROM string formats
		bool fromString(HtlString & ptrRHS);
		bool fromStdString( std::string & ptrRHS);
		bool fromCharString(const char* ptrRHS);
		//!Sets the GUID to the NULL ID 00000000-00000000-00000000-00000000-00000000-00000000-00000000-00000000
		void setNull(void);
		bool isNull(void);
		void newID(void){createGUID256();};
		//!Assignment Operator Overloads
		HtlGUID256 &	operator= ( const GUID & ptrRHS );
		HtlGUID256 &	operator= ( const HtlGUID128 & ptrRHS );
		HtlGUID256 &	operator= ( const HtlGUID256 & ptrRHS );

		//!Boolean Logic Operator Overloads
		bool operator == (const HtlGUID256 & ptrRHS );
		bool operator != (const HtlGUID256 & ptrRHS );
		bool operator < (const HtlGUID256 & ptrRHS );
		bool operator > (const HtlGUID256 & ptrRHS );
		bool operator <= (const HtlGUID256 & ptrRHS );
		bool operator >= (const HtlGUID256 & ptrRHS );

		const uchar & at(size_t i) const;
		uchar & at(size_t i);

		const uchar & operator[](size_t i) const;
		uchar & operator[](size_t i);
		//GUID format checking
		bool isValidWinGUID(const char * strInput);
		bool isValidHtlGUID(const char * strInput);

	private:
		//!GLOBAL UNIQUE IDENTIFIER CHARACTER DATA
		uchar m_uchrData[32];
		uchar m_chrNull;
		//!string buffer for string version of the GUID
		char m_strData[256];
		//!method for generating a global unique identifier
		void createGUID256(void);

		static HTL::HtlUniform * GetRNG(void);
	};//end class HtlGUID256
};//END NAMESPACE HTL

#endif