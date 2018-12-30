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

#ifndef HTL_STRING_H
#define HTL_STRING_H

#include "..\modHtlLibRefs.h"
#include "..\modHtlGlobal.h"
#include <string>
using namespace std;

namespace HTL{
	

	//!HtlString is a character container class for holding strings
	/*!
		HtlString is a character container class for holding strings. 
		It is based off of the QT and STL string classes.  The goal of this class is to provide the 
		basic container manipulation.  All string Algorithms are held as functions external to the class
		definition to keep the code footprint size down.  The string Algorithms are in HtlStringAlgorithms.h.
	*/
	#define CHR_NULL '\0'
	//!This is the struct that manages the actual character data
	struct HTL_DLLAPI ChrNode
	{

		ChrNode(void)
		{
			//set to NULL STRING
			m_intAlloc = 0;
			m_intSize = 0;
			m_arrChar[0] = '\0';
		};


		//!Size of the CArray character
		size_t m_intSize;
		//!Size of the CArray character
		size_t m_intAlloc;
		//!pointer to the head character
		//IMPORTANT that this is last item to be declared BECAUSE C character array runs after this
		char m_arrChar[1];
	};



	class HTL_DLLAPI HtlString{


public:
	//!HTL String Constructors
	HtlString(void);
    HtlString(const char *unicode, int size);
    HtlString(char c);
	HtlString(const std::string & strInput);
    HtlString(const HtlString & strInput);
	//!HTL String Destructors
	~HtlString();

	//HTL String Operator Overloads
	//!Assignment Operators
	HtlString & operator=(char c);
	HtlString & operator=(const char * ptrRHS);
	HtlString & operator=(const unsigned char * ptrRHS);
	HtlString & operator=(const std::string & ptrRHS);
	HtlString & operator=(const HtlString & ptrRHS);
	//!Compound Add Assignment Operator // A += B
	HtlString & HtlString::operator += (char c); 
	HtlString & HtlString::operator += (const char * ptrRHS); 
	HtlString & HtlString::operator += (const std::string & ptrRHS); 
	HtlString & HtlString::operator += (const HtlString & ptrRHS);
	//!Streaming Assignment Operators
	HtlString & operator <<= (char c);
	HtlString & operator <<= (char * ptrRHS);
	HtlString & operator <<= (const std::string & ptrRHS);
	HtlString & operator <<= (const HtlString & ptrRHS);

	HtlString & operator << (char c);
	HtlString & operator << (const char * ptrRHS);
	HtlString & operator << (const std::string & ptrRHS);
	HtlString & operator << (const HtlString & ptrRHS);


	//!Boolean Logic Operators (HtlString only)
	//std::string operators are for conversion into native format only
	bool operator == (const char* ptrRHS) const;
	bool operator != (const char* ptrRHS) const;
	bool operator < (const char* ptrRHS) const;
	bool operator > (const char* ptrRHS) const;
	bool operator <= (const char* ptrRHS) const;
	bool operator >= (const char* ptrRHS) const;

	bool operator == (const HtlString & ptrRHS) const;
	bool operator != (const HtlString & ptrRHS) const;
	bool operator < (const HtlString & ptrRHS) const;
	bool operator > (const HtlString & ptrRHS) const;
	bool operator <= (const HtlString & ptrRHS) const;
	bool operator >= (const HtlString & ptrRHS) const;

	//!HTL String Resizing Functions
	//!This reserves the memory for a string of intSize length, this calls the clean slate memalloc
    void reserve(size_t intSize);
	//!This resizes the memory for a string of intSize length, this calls the clean slate memReAlloc
    void resize(size_t intSize);
	//!This performs a left trim operation on the string 
    void leftTrim(size_t intNumChar);
	//!This performs a right trim operation on the string
	void rightTrim(size_t intNumChar);
	//!This performs a right trim operation on the string
	void truncate(int pos){resize(pos);};



	//!This performs a fill operation on the string of character c
    void fill(char c);
	//!This clears the current string contents and frees the memory
    void clear();
	//!ReAllocates the memory of the string and its contents
	void realloc();


	//!HTL String Append Functions
	HtlString & append(char c);
	HtlString & append(const char* ptrRHS);
	HtlString & append(const std::string & ptrRHS);
	HtlString & append(const HtlString & ptrRHS);
	//!HTL String Prepend Functions
	HtlString & prepend(char c);
	HtlString & prepend(const char* ptrRHS);
	HtlString & prepend(const std::string & ptrRHS);
	HtlString & prepend(const HtlString & ptrRHS);
	//!HTL Container Accessors
	const char & at(size_t i) const;
	char & at(size_t i);

	const char & operator[](size_t i) const;
	char & operator[](size_t i);

	//!Sub String Accessors
	void subString(HtlString & ptrString, size_t intStart, size_t intLength);

	//!HTL Container Analyzers
	//!Returns the size of the string
    size_t size(void) const;
		//!Returns the size of the string
    size_t count(void) const;
	//!Returns the size of the string forces a full recount
    void recount(void);
	//!Returns true if the string is empty
    bool isEmpty(void) const;
	//!Returns the current capacity of the string allocated memory
    size_t capacity(void) const;

	//!HTL String direct character array accessors
	inline const char *unicode(void) const
	{
		//return the pointer to the first character
		return &m_ptrData->m_arrChar[0];
	};
	//!HTL String direct character array accessors
	inline const char *charString(void) const
	{
		//return the pointer to the first character
		return &m_ptrData->m_arrChar[0];
	};
	//!HTL String direct character array accessors
	inline const ChrNode *data(void) 
	{
		return m_ptrData;
	};


	private:

	//!THIS IS THE POINTER TO THE ACTUAL CHARACTER DATA THAT IS BEING MANAGED
	ChrNode * m_ptrData;
	//!shared null character
	static ChrNode m_objSharedNull;
	//!null character constant
	char m_chrNull;
	//!This grows the string by int characters
	void grow(size_t intSize);
	//!This shrinks the string by int characters, or completely if intSize > intCurrentSize
	void shrink(size_t intSize);


	};//end HtlString Class Definition

};//end HTL namespace

#endif