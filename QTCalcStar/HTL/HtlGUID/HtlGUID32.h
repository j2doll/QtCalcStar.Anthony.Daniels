/*
	The High Performance Template Library is a Licensed as LGPL.
	It is intended to provide a base object architecture, with
	Serialization, thread control, etc.  
	It is based on a merger of QT, BOOST, STL, and SigSlots.
	This Library is LGPL.
	License information is in the HtlLicense.h file
	October 2012
*/

#pragma once

#ifndef HTL_GUID128_H
#define HTL_GUID128_H

#include "..\modHtlLibRefs.h"
#include <string>
using namespace std;

namespace HTL{
	

	//!HtlGUID128 is a 128 bit Global Unique Identifier  (16 chars)
	/*!
		HtlString is a character container class for holding strings. 
		It is based off of the QT and MFC GUID classes.  The goal of this class is to provide the 
		basic container for Global Unique Identifiers.
		HtlGUID native format with symmetric strings  c5057190-a2864427-b1722fc5-6a92423f in hex string.
	*/

	class HTL_DLLAPI HtlGUID32{


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
		const char* toCharString(void) const;

		//!Serialization FROM string formats
		void fromString(HtlString & ptrRHS);
		void fromStdString( std::string & ptrRHS);
		void fromCharString(const char* ptrRHS);

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

	private:
		//!GLOBAL UNIQUE IDENTIFIER CHARACTER DATA
		char m_ucharData[16];
		//!Static method for generating a global unique identifier
		static void CreateGUID(void);
	};//END NAMESPACE HTL

#endif