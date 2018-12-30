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

#ifndef HTL_GUID128_H
#define HTL_GUID128_H

#include "..\modHtlLibRefs.h"

#include "Guiddef.h" //Windows GUID
#include <string>
using namespace std;

namespace HTL{


	class HtlString;
	class HtlRandNumDist;
	typedef HtlRandNumDist HtlUniform;

	//!HtlGUID128 is a 128 bit Global Unique Identifier  (16 chars)
	/*!
	HtlString is a character container class for holding strings. 
	It is based off of the QT and MFC GUID classes.  The goal of this class is to provide the 
	basic container for Global Unique Identifiers.
	HtlGUID native format with symmetric strings  c5057190-a2864427-b1722fc5-6a92423f in hex string.
	*/

	class HTL_DLLAPI HtlGUID128{

	public:

		HtlGUID128 ();
		//This constructor is kept for Windows compatibility
		//HtlGUID128 native is symmetric storage
		//Microsoft Windows format for GUIDs is  c5057190-a286-4427-b172-2fc56a92423f in hex string
		HtlGUID128 ( uint l, ushort w1, ushort w2, uchar b1, uchar b2, uchar b3, uchar b4, uchar b5, uchar b6, uchar b7, uchar b8 );
		//This is HtlGUID native format with symmetric strings  c5057190-a2864427-b1722fc5-6a92423f
		HtlGUID128 ( uint w0, uint w1, uint w2, uint w3);
		HtlGUID128 ( const char* ptrRHS );
		HtlGUID128 ( const HtlString & strRHS );
		HtlGUID128 ( const HtlGUID128 & ptrRHS );
		virtual ~HtlGUID128 ();

		//!Serialization TO string formats
		HtlString	toString (void) const;
		std::string toStdString (void) const;
		const char* toCharString(void);

		//!Serialization FROM string formats
		bool fromString(HtlString & ptrRHS);
		bool fromStdString( std::string & ptrRHS);
		bool fromCharString(const char* ptrRHS);

		//!Sets the GUID to the NULL ID 00000000-00000000-00000000-00000000
		void setNull(void);
		bool isNull(void);
		void newID(void){createGUID128();};
		//!Assignment Operator Overloads
		HtlGUID128 &	operator= ( const GUID & ptrRHS );
		HtlGUID128 &	operator= ( const HtlGUID128 & ptrRHS );

		//!Boolean Logic Operator Overloads
		bool operator == (const HtlGUID128 & ptrRHS );
		bool operator != (const HtlGUID128 & ptrRHS );
		bool operator < (const HtlGUID128 & ptrRHS );
		bool operator > (const HtlGUID128 & ptrRHS );
		bool operator <= (const HtlGUID128 & ptrRHS );
		bool operator >= (const HtlGUID128 & ptrRHS );
		//These are for Microsoft Windows Format Compatibility
		bool operator == (const GUID & ptrRHS );
		bool operator != (const GUID & ptrRHS );
		bool operator < (const GUID & ptrRHS );
		bool operator > (const GUID & ptrRHS );
		bool operator <= (const GUID & ptrRHS );
		bool operator >= (const GUID & ptrRHS );

		const uchar & at(size_t i) const;
		uchar & at(size_t i);

		const uchar & operator[](size_t i) const;
		uchar & operator[](size_t i);
		//GUID format checking
		bool isValidWinGUID(const char * strInput);
		bool isValidHtlGUID(const char * strInput);

	private:
		//!GLOBAL UNIQUE IDENTIFIER CHARACTER DATA
		uchar m_uchrData[16];
		//!constant NULL character for returns
		uchar m_chrNull;
		//!string buffer for string version of the GUID
		char m_strData[256];
		//!Static method for generating a global unique identifier
		void createGUID128(void);

		static HTL::HtlUniform * GetRNG(void);


	};//end class HtlGUID128
};//END NAMESPACE HTL

#endif