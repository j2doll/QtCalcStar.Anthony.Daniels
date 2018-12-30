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

#include ".\HtlString.h"
using namespace std;

namespace HTL{

	ChrNode HtlString::m_objSharedNull;

	static size_t charLength(const char* chrIn) {
		size_t i;
		for (i = 0; !(chrIn[i] == CHR_NULL); ++i){/*loop until null char*/};   
		return i;
	}
	static size_t charLength(const unsigned char* chrIn) {
		size_t i;
		for (i = 0; !(chrIn[i] == CHR_NULL); ++i){/*loop until null char*/};   
		return i;
	}


	//!HTL String Constructors
	HtlString::HtlString(void)
		: m_chrNull('\0')
	{
		//set to NULL STRING
		m_ptrData = &m_objSharedNull;
		m_objSharedNull.m_arrChar[0] = '\0';
		m_objSharedNull.m_intAlloc = 0;
		m_objSharedNull.m_intSize = 0;
	};

	HtlString::HtlString(const char * unicode, int size)
		: m_chrNull('\0')
	{
      try
      {
         //This constructor takes the incoming text and
         //appends it to the current string
         if ((!unicode) || (size <= 0)) {
            //no characters, nothing to do...
            //return gracefully
            m_ptrData = &m_objSharedNull;
            m_objSharedNull.m_arrChar[0] = '\0';
            return;
         }
         else {
            //reserve the memory
            m_ptrData = (ChrNode*)qMemAlloc(sizeof(ChrNode) + size * sizeof(char));
            //set the container sizes
            m_ptrData->m_intSize = size;
            m_ptrData->m_intAlloc = size;
            //perform the memory copying of the incoming string
            memcpy(m_ptrData->m_arrChar, unicode, size * sizeof(char));
            //set the NULL terminator for the string
            m_ptrData->m_arrChar[size] = '\0';
            return;
         };

      }
      catch (...)
      {
         std::string errMsg;
         errMsg = "HtlString Constructor Error thrown";
         throw std::exception(errMsg.c_str());
      }
	};

	HtlString::HtlString(char c)
		: m_chrNull('\0')
	{
      try
      {
         //This constructor takes the incoming text and
         //appends it to the current string
         //reserve the memory
         m_ptrData = (ChrNode*)qMemAlloc(sizeof(ChrNode) + 1 * sizeof(char));
         //set the container sizes
         m_ptrData->m_intSize = 1;
         m_ptrData->m_intAlloc = 1;
         //perform the memory copying of the incoming string
         //memcpy(m_ptrData->m_arrChar, c, 1 * sizeof(char));
         //set the NULL terminator for the string
         m_ptrData->m_arrChar[0] = c;
         m_ptrData->m_arrChar[1] = '\0';
         return;
      }
      catch (...)
      {
         std::string errMsg;
         errMsg = "HtlString Constructor Error thrown";
         throw std::exception(errMsg.c_str());
      }
	};

	HtlString::HtlString(const std::string & strInput)
		: m_chrNull('\0')
	{
		//call the unicode constructor
		HtlString(strInput.c_str(),strInput.size());
	};

	HtlString::HtlString(const HtlString & strInput)
		: m_chrNull('\0')
	{
		//call the unicode constructor
		HtlString(strInput.unicode(),strInput.size());
	};

	//!HTL String Destructors
	HtlString::~HtlString()
	{
		//clear the string and all of its memory
		this->clear();
		//set to NULL STRING
		m_ptrData = &m_objSharedNull;
		m_objSharedNull.m_arrChar[0] = '\0';
		m_objSharedNull.m_intAlloc = 0;
		m_objSharedNull.m_intSize = 0;
	};

	//HTL String Operator Overloads
	//Assignment Operators
	HtlString & HtlString::operator=(char c)
	{
      try
      {
         //safety check
         if (!m_ptrData) { return *this; };

         //clear existing characters
         clear();
         //assign the new character
         //reserve the memory
         m_ptrData = (ChrNode*)qMemAlloc(sizeof(ChrNode) + 1 * sizeof(char));
         //set the container sizes
         m_ptrData->m_intSize = 1;
         m_ptrData->m_intAlloc = 1;
         //perform the memory copying of the incoming string
         //memcpy(m_ptrData->m_arrChar, c, 1 * sizeof(char));
         //set the NULL terminator for the string
         m_ptrData->m_arrChar[0] = c;
         m_ptrData->m_arrChar[1] = '\0';
         return *this;
      }
      catch (...)
      {
         std::string errMsg;
         errMsg = "HtlString Constructor Error thrown";
         throw std::exception(errMsg.c_str());
      }
	};

	HtlString & HtlString::operator=(const char * ptrRHS)
	{
      try
      {
         //safety check
         if (!m_ptrData) { return *this; };

         size_t intSize;
         //clear the existing string
         clear();

         intSize = strlen(ptrRHS);
         //This constructor takes the incoming text and
         //appends it to the current string
         if ((!ptrRHS) || (intSize <= 0)) {
            //no characters, nothing to do...
            //return gracefully
            m_ptrData = &m_objSharedNull;
            m_objSharedNull.m_arrChar[0] = '\0';
            return *this;
         }
         else {
            //reserve the memory
            m_ptrData = (ChrNode*)qMemAlloc(sizeof(ChrNode) + intSize * sizeof(char));
            //set the container sizes
            m_ptrData->m_intSize = intSize;
            m_ptrData->m_intAlloc = intSize;
            //perform the memory copying of the incoming string
            memcpy(m_ptrData->m_arrChar, ptrRHS, intSize * sizeof(char));
            //set the NULL terminator for the string
            m_ptrData->m_arrChar[intSize] = '\0';
            return *this;
         };

         return *this;
      }
      catch (...)
      {
         std::string errMsg;
         errMsg = "HtlString Assignment Operator Error thrown";
         throw std::exception(errMsg.c_str());
      }
	};

	HtlString & HtlString::operator=(const unsigned char * ptrRHS)
	{
      try
      {
         //safety check
         if (!m_ptrData) { return *this; };

         size_t intSize;
         //clear the existing string
         clear();

         intSize = charLength(ptrRHS);
         //This constructor takes the incoming text and
         //appends it to the current string
         if ((!ptrRHS) || (intSize <= 0)) {
            //no characters, nothing to do...
            //return gracefully
            m_ptrData = &m_objSharedNull;
            m_objSharedNull.m_arrChar[0] = '\0';
            return *this;
         }
         else {
            //reserve the memory
            m_ptrData = (ChrNode*)qMemAlloc(sizeof(ChrNode) + intSize * sizeof(char));
            //set the container sizes
            m_ptrData->m_intSize = intSize;
            m_ptrData->m_intAlloc = intSize;
            //perform the memory copying of the incoming string
            memcpy(m_ptrData->m_arrChar, ptrRHS, intSize * sizeof(char));
            //set the NULL terminator for the string
            m_ptrData->m_arrChar[intSize] = '\0';
            return *this;
         };

         return *this;

      }
      catch (...)
      {
         std::string errMsg;
         errMsg = "HtlString Assignment Operator Error thrown";
         throw std::exception(errMsg.c_str());
      }
   };

	HtlString & HtlString::operator=(const std::string & ptrRHS)
	{
		//safety check
		if(!m_ptrData){return *this;};

		return operator=(ptrRHS.c_str());
	};

	HtlString & HtlString::operator=(const HtlString & ptrRHS)
	{
		//safety check
		if(!m_ptrData){return *this;};

		return operator=(ptrRHS.unicode());
	};
	//Compound Add Assignment Operator // A += B
	HtlString & HtlString::operator += (char c)
	{
		//safety check
		if(!m_ptrData){return *this;};

		return append(c);
	};

	HtlString & HtlString::operator += (const char * ptrRHS)
	{
		//safety check
		if(!m_ptrData){return *this;};

		return append(ptrRHS);
	};

	HtlString & HtlString::operator += (const std::string & ptrRHS)
	{
		//safety check
		if(!m_ptrData){return *this;};

		return append(ptrRHS);
	};

	HtlString & HtlString::operator += (const HtlString & ptrRHS)
	{
		//safety check
		if(!m_ptrData){return *this;};

		return append(ptrRHS);
	};

	//Streaming Assignment Operators
	HtlString & HtlString::operator <<= (char c)
	{
		//safety check
		if(!m_ptrData){return *this;};

		return append(c);
	};

	HtlString & HtlString::operator <<= (char * ptrRHS)
	{
		//safety check
		if(!m_ptrData){return *this;};

		return append(ptrRHS);
	};

	HtlString & HtlString::operator <<= (const std::string & ptrRHS)
	{
		//safety check
		if(!m_ptrData){return *this;};

		return append(ptrRHS);
	};

	HtlString & HtlString::operator <<= (const HtlString & ptrRHS)
	{
		//safety check
		if(!m_ptrData){return *this;};

		return append(ptrRHS);
	};

	HtlString & HtlString::operator << (char c)
	{
		//safety check
		if(!m_ptrData){return *this;};

		return append(c);
	};

	HtlString & HtlString::operator << (const char * ptrRHS)
	{
		//safety check
		if(!m_ptrData){return *this;};

		return append(ptrRHS);
	};

	HtlString & HtlString::operator << (const std::string & ptrRHS)
	{
		//safety check
		if(!m_ptrData){return *this;};

		return append(ptrRHS);
	};

	HtlString & HtlString::operator << (const HtlString & ptrRHS)
	{
		//safety check
		if(!m_ptrData){return *this;};

		return append(ptrRHS);
	};


	//Boolean Logic Operators (HtlString only)
	//std::string operators are for conversion into native format only
	bool HtlString::operator == (const char* ptrRHS) const
	{
		size_t i, intLenLHS, intLenRHS;

		if(!m_ptrData){return false;};

		intLenLHS = m_ptrData->m_intSize;
		intLenRHS = strlen(ptrRHS);
		if(intLenLHS != intLenRHS){return false;};

		for(i = 0 ; i < intLenLHS ; i++)
		{
			//compare character by character
			if( m_ptrData->m_arrChar[i]!= ptrRHS[i])
			{
				return false;
			};	
		};
		//made it all the way through, then a match
		return true;
	};

	bool HtlString::operator != (const char* ptrRHS) const
	{
		size_t i, intLenLHS, intLenRHS;

		if(!m_ptrData){return true;};

		intLenLHS = m_ptrData->m_intSize;
		intLenRHS = strlen(ptrRHS);
		if(intLenLHS != intLenRHS){return true;};

		for(i = 0 ; i < intLenLHS ; i++)
		{
			//compare character by character
			if( m_ptrData->m_arrChar[i]!= ptrRHS[i])
			{
				return true;
			};	
		};
		//made it all the way through, then a match
		return false;
	};

	bool HtlString::operator < (const char* ptrRHS) const
	{
		size_t i, intLenLHS, intLenRHS;

		if(!m_ptrData){return true;};

		intLenLHS = m_ptrData->m_intSize;
		intLenRHS = strlen(ptrRHS);
		//check Less Than by length first, then compare by characters
		if(intLenLHS < intLenRHS){return true;};
		//then intLenLHS >= intLenRHS
		for(i = 0 ; i < intLenRHS ; i++)
		{
			//compare character by character by negation
			if( m_ptrData->m_arrChar[i] > ptrRHS[i])
			{
				return false;
			};	
		};
		//made it all the way through, then a match
		return true;
	};

	bool HtlString::operator > (const char* ptrRHS) const
	{
		size_t i, intLenLHS, intLenRHS;

		if(!m_ptrData){return true;};

		intLenLHS = m_ptrData->m_intSize;
		intLenRHS = strlen(ptrRHS);
		//check Less Than by length first, then compare by characters
		if(intLenLHS > intLenRHS){return true;};
		//then intLenLHS <= intLenRHS
		for(i = 0 ; i < intLenLHS ; i++)
		{
			//compare character by character by negation
			if( m_ptrData->m_arrChar[i] < ptrRHS[i])
			{
				return false;
			};	
		};
		//made it all the way through, then a match
		return true;
	};

	bool HtlString::operator <= (const char* ptrRHS) const
	{
		size_t i, intLenLHS, intLenRHS;

		if(!m_ptrData){return true;};

		intLenLHS = m_ptrData->m_intSize;
		intLenRHS = strlen(ptrRHS);
		//check Less Than by length first, then compare by characters
		if(intLenLHS <= intLenRHS){return true;};
		//then intLenLHS >= intLenRHS
		for(i = 0 ; i < intLenRHS ; i++)
		{
			//compare character by character by negation
			if( m_ptrData->m_arrChar[i] > ptrRHS[i])
			{
				return false;
			};	
		};
		//made it all the way through, then a match
		return true;
	};

	bool HtlString::operator >= (const char* ptrRHS) const
	{
		size_t i, intLenLHS, intLenRHS;

		if(!m_ptrData){return true;};

		intLenLHS = m_ptrData->m_intSize;
		intLenRHS = strlen(ptrRHS);
		//check Less Than by length first, then compare by characters
		if(intLenLHS >= intLenRHS){return true;};
		//then intLenLHS <= intLenRHS
		for(i = 0 ; i < intLenLHS ; i++)
		{
			//compare character by character by negation
			if( m_ptrData->m_arrChar[i] < ptrRHS[i])
			{
				return false;
			};	
		};
		//made it all the way through, then a match
		return true;
	};


	bool HtlString::operator == (const HtlString & ptrRHS) const
	{
		return operator == (ptrRHS.unicode());
	};

	bool HtlString::operator != (const HtlString & ptrRHS) const
	{
		return operator != (ptrRHS.unicode());
	};

	bool HtlString::operator < (const HtlString & ptrRHS) const
	{
		return operator < (ptrRHS.unicode());
	};

	bool HtlString::operator > (const HtlString & ptrRHS) const
	{
		return operator > (ptrRHS.unicode());
	};

	bool HtlString::operator <= (const HtlString & ptrRHS) const
	{
		return operator <= (ptrRHS.unicode());
	};

	bool HtlString::operator >= (const HtlString & ptrRHS) const
	{
		return operator <= (ptrRHS.unicode());
	};

	//!HTL String Resizing Functions
	void HtlString::reserve(size_t intSize)
	{
		//safety checks
		if(!m_ptrData){return;};
		size_t intOldSize, intNewSize;
		intOldSize = m_ptrData->m_intSize;
		intNewSize = sizeof(ChrNode)+((intSize)*sizeof(char));

		//This constructor takes the incoming text and
		//appends it to the current string
		if(intSize <= 0)
		{
			//no characters, nothing to do...
			//return gracefully
			m_ptrData = &m_objSharedNull;
			m_objSharedNull.m_arrChar[0] = '\0';
			return;
		}else{
			if(m_ptrData != &m_objSharedNull)
			{
				//then not shared null, already exists
				if(intNewSize < intOldSize)
				{
					//then shrink 
					this->shrink( (intOldSize - intNewSize) );

				}else{
					//then grow 
					this->grow( (intNewSize - intOldSize) );
				};
			}else{
				//shared null, just make it
				//reserve the memory
				m_ptrData = (ChrNode*) qMemAlloc(sizeof(ChrNode)+intNewSize*sizeof(char));
				//set the container sizes
				m_ptrData->m_intSize = intNewSize;
				m_ptrData->m_intAlloc = intNewSize;
			};
			return;		
		};
		return;
	};

	void HtlString::resize(size_t intSize)
	{
		//safety checks
		if(!m_ptrData){return;};

		size_t intOldSize, intNewSize;
		m_ptrData = NULL;
		intOldSize = m_ptrData->m_intSize;
		intNewSize = sizeof(ChrNode)+((intSize)*sizeof(char));
		//This constructor takes the incoming text and
		//appends it to the current string
		if( intSize <= 0)
		{
			//no characters, nothing to do...
			//return gracefully
			m_ptrData = &m_objSharedNull;
			m_objSharedNull.m_arrChar[0] = '\0';
			return;
		}else{
			//reserve the memory
			//qMemReAllocAligned(void *oldptr, size_t newsize, size_t oldsize, size_t alignment)
			m_ptrData = (ChrNode*) qMemReAlloc(m_ptrData, intNewSize);

			//set the container sizes
			m_ptrData->m_intSize = intSize;
			m_ptrData->m_intAlloc = m_ptrData->m_intSize;

			//set the NULL terminator for the string
			m_ptrData->m_arrChar[intNewSize] = '\0';
			return;		
		};

		return;
	};

	void HtlString::rightTrim(size_t intNumChar)
	{
		//reallocate aligned with the trim shift
		//safety checks
		if(!m_ptrData){return;};

		//safe to proceed
		if( intNumChar >= m_ptrData->m_intSize)
		{
			//trim too large, right trimming entire string.
			clear();
		}else{
			//valid right trim
			//shrink the string
			shrink(intNumChar);
		};
		return;
	};
	void HtlString::leftTrim(size_t intNumChar)
	{
		//reallocate aligned with the trim shift
		//safety checks
		if(!m_ptrData){return;};

		//safe to proceed
		if( intNumChar >= m_ptrData->m_intSize)
		{
			//trim too large, left trimming entire string.
			clear();
		}else{
			//valid left trim
			char* chrBuf;
			chrBuf = (char*)qMemAlloc(m_ptrData->m_intSize);
			size_t i, intNewSize;
			intNewSize = m_ptrData->m_intSize - intNumChar;
			for(i = 0 ; i < m_ptrData->m_intSize ; i++)
			{
				//copy to temp buffer
				chrBuf[i] = m_ptrData->m_arrChar[i];
			};
			//shrink the string
			shrink(intNumChar);
			//copy back
			for(i = 0 ; i < intNewSize ; i++)
			{
				//copy to temp buffer
				m_ptrData->m_arrChar[i]=chrBuf[i + intNumChar];
			};
			m_ptrData->m_arrChar[intNewSize] = '\0';

			//free the temporary character buffer
			qMemFree(chrBuf);

		};//end if valid left trim

		return;
	};
	void HtlString::fill(char c)
	{
		//safety checks
		if(!m_ptrData){return;};

		size_t i;

		for(i = 0 ; i < m_ptrData->m_intSize ; i++)
		{
			//copy to temp buffer
			m_ptrData->m_arrChar[i] = c;
		};
		return;
	};

	void HtlString::clear()
	{
	
		if((m_ptrData) && (m_ptrData != &m_objSharedNull))
		{
			fill('\0');
			qMemFree(m_ptrData);
			m_ptrData = &m_objSharedNull;
		};
		return;
	};

	void HtlString::grow(size_t intSize)
	{
		//safety checks
		if(!m_ptrData){return;};

		size_t intOldSize, intNewSize, intCurrEnd, intNewEnd;
		intCurrEnd = m_ptrData->m_intSize;
		intOldSize = sizeof(ChrNode)+((m_ptrData->m_intSize)*sizeof(char));
		intNewSize = intOldSize + intSize;//ADD TO THE EXISTING
		//This constructor takes the incoming text and
		//appends it to the current string
		if(intOldSize <= 0)
		{
			//no characters, nothing to do...
			//return gracefully
			m_ptrData = &m_objSharedNull;
			m_objSharedNull.m_arrChar[0] = '\0';
			return;
		}else{
			//reserve the memory
			//qMemReAllocAligned(void *oldptr, size_t newsize, size_t oldsize, size_t alignment)
			m_ptrData = (ChrNode*) qMemReAlloc(m_ptrData, intNewSize);

			//set the container sizes
			m_ptrData->m_intSize = intCurrEnd + intSize;
			m_ptrData->m_intAlloc = m_ptrData->m_intSize;

			//set the NULL terminator for the string
			m_ptrData->m_arrChar[intCurrEnd] = ' ';
			intNewEnd = intCurrEnd + intSize;
			m_ptrData->m_arrChar[intNewEnd] = '\0';
			return;		
		};

		return;
	};

	void HtlString::shrink(size_t intSize)
	{
		//safety checks
		if(!m_ptrData){return;};

		size_t intOldSize, intNewSize, intCurrString, intNewEnd;
		intCurrString = m_ptrData->m_intSize;
		//safety check. If requested shrink is greater than current size, alloc a zero size string
		if( intSize > intCurrString)
		{
			intNewSize = sizeof(ChrNode);
			m_ptrData = (ChrNode*) qMemReAlloc(m_ptrData, intNewSize);
			return;
		};
		//otherwise perform shrink

		intOldSize = sizeof(ChrNode)+((m_ptrData->m_intSize)*sizeof(char));
		intNewSize = intOldSize - intSize;//SUBTRACT FROM EXISTING 
		intNewEnd = intCurrString - intSize;
		//This constructor takes the incoming text and
		//appends it to the current string
		if( (!m_ptrData)||(intOldSize <= 0)) {
			//no characters, nothing to do...
			//return gracefully
			m_ptrData = &m_objSharedNull;
			m_objSharedNull.m_arrChar[0] = '\0';
			return;
		}else {
			//reserve the memory
			//qMemReAllocAligned(void *oldptr, size_t newsize, size_t oldsize, size_t alignment)
			m_ptrData = (ChrNode*) qMemReAlloc(m_ptrData, intNewSize);

			//set the container sizes
			m_ptrData->m_intSize = intNewEnd;
			m_ptrData->m_intAlloc = m_ptrData->m_intSize;

			m_ptrData->m_arrChar[intNewEnd] = '\0';
			return;		
		};

		return;
	};

	void HtlString::realloc()
	{

	};

	//!HTL String Append and Prepend Functions
	HtlString & HtlString::append(char c)
   {
      try
      {
         //safety checks
         if (!m_ptrData) { return *this; };
         if (m_ptrData == &m_objSharedNull)
         {
            operator=(c);
            return *this;
         };
         //safe to append character
         grow(1);
         //append the character
         m_ptrData->m_arrChar[(m_ptrData->m_intSize - 1)] = c;
         return *this;
      }
      catch (...)
      {
         std::string errMsg;
         errMsg = "HtlString Append Error thrown";
         throw std::exception(errMsg.c_str());
      }
   };
	HtlString & HtlString::append(const char* ptrRHS)
	{
      try 
      {
         //safety checks
         if (!m_ptrData) { return *this; };
         if (m_ptrData == &m_objSharedNull)
         {
            operator=(ptrRHS);
            return *this;
         };
         //otherwise append to existing string
         size_t intOldSize = m_ptrData->m_intSize;
         size_t intStrSize = strlen(ptrRHS);
         //safe to append character
         grow(intStrSize);
         //append the character
         //perform the memory copying of the incoming string
         char * ptrLoc = &m_ptrData->m_arrChar[intOldSize];
         memcpy(ptrLoc, ptrRHS, intStrSize * sizeof(char));
         return *this;
      }
      catch (...)
      {
         std::string errMsg;
         errMsg = "HtlString Append Error thrown";
         throw std::exception(errMsg.c_str());
      }
	};
	HtlString & HtlString::append(const std::string & ptrRHS)
	{	
		//safety checks
		if(!m_ptrData){return *this;};

		append(ptrRHS.c_str());
		return *this;
	};
	HtlString & HtlString::append(const HtlString & ptrRHS)
	{
		//safety checks
		if(!m_ptrData){return *this;};

		append(ptrRHS.unicode());
		return *this;
	};

   HtlString & HtlString::prepend(char c)
   {
      try
      {
         //safety checks
         if (!m_ptrData) { return *this; };
         if (m_ptrData == &m_objSharedNull)
         {
            operator=(c);
            return *this;
         };
         //safe to proceed
         //duplicate to buffer

         size_t intOldSize = m_ptrData->m_intSize;
         char * chrBuf = NULL;
         chrBuf = (char*)qMemAlloc(intOldSize);

         memcpy(chrBuf, m_ptrData->m_arrChar, intOldSize * sizeof(char));
         //valid left trim

         size_t intNewSize;
         intNewSize = m_ptrData->m_intSize + 1;
         grow(1);
         //prepend and copy back string
         m_ptrData->m_arrChar[0] = c;
         //append old string
         char * ptrLoc = &m_ptrData->m_arrChar[1];
         memcpy(ptrLoc, chrBuf, intOldSize * sizeof(char));

         //free memory from temporary character buffer
         qMemFree(chrBuf);
         chrBuf = NULL;

         return *this;
      }
      catch (...)
      {
         std::string errMsg;
         errMsg = "HtlString Prepend Error thrown";
         throw std::exception(errMsg.c_str());
      }
   };
	HtlString & HtlString::prepend(const char* ptrRHS)
	{
      try
      {
         //safety checks
         if (!m_ptrData) { return *this; };
         if (m_ptrData == &m_objSharedNull)
         {
            operator=(ptrRHS);
            return *this;
         };
         //safe to proceed
         //duplicate to buffer
         size_t intStrLen = strlen(ptrRHS);
         size_t intOldSize = m_ptrData->m_intSize;
         char * chrBuf = NULL;
         chrBuf = (char*)qMemAlloc(intOldSize * sizeof(char));

         memcpy(chrBuf, m_ptrData->m_arrChar, intOldSize * sizeof(char));

         //valid prepend grow the string to accomodate
         grow(intStrLen);

         //prepend and copy back string
         char* ptrLoc1 = &m_ptrData->m_arrChar[0];
         memcpy(ptrLoc1, ptrRHS, intStrLen * sizeof(char));
         //append old string
         char* ptrLoc2 = &m_ptrData->m_arrChar[intStrLen];
         memcpy(ptrLoc2, chrBuf, intOldSize * sizeof(char));
         //clean up memory
         qMemFree(chrBuf);
         chrBuf = NULL;

         return *this;
      }
      catch (...)
      {
         std::string errMsg;
         errMsg = "HtlString Prepend Error thrown";
         throw std::exception(errMsg.c_str());
      }
   };
	HtlString & HtlString::prepend(const std::string & ptrRHS)
	{
		//safety checks
		if(!m_ptrData){return *this;};

		prepend(ptrRHS.c_str());
		return *this;
	};
	HtlString & HtlString::prepend(const HtlString & ptrRHS)
	{		
		//safety checks
		if(!m_ptrData){return *this;};

		prepend(ptrRHS.unicode());
		return *this;
	};
	//!HTL Container Accessors
	const char & HtlString::at(size_t i) const
	{
      try
      {
         if (!m_ptrData) { return m_chrNull; };
         if (i < m_ptrData->m_intSize)
         {
            return m_ptrData->m_arrChar[i];
         }
         else {
            //invalid index return NULL
            return m_chrNull;
         };
         return m_chrNull;
      }
      catch (...)
      {
         std::string errMsg;
         errMsg = "HtlString At Error thrown";
         throw std::exception(errMsg.c_str());
      }
	};
	char & HtlString::at(size_t i)
	{
      try
      {
         if (!m_ptrData) { return m_chrNull; };
         if (i < m_ptrData->m_intSize)
         {
            return m_ptrData->m_arrChar[i];
         }
         else {
            //invalid index return NULL
            return m_chrNull;
         };
         return m_chrNull;
      }
      catch (...)
      {
         std::string errMsg;
         errMsg = "HtlString At Error thrown";
         throw std::exception(errMsg.c_str());
      }
   };
   const char & HtlString::operator[](size_t i) const
   {
      try
      {
         if (!m_ptrData) { return m_chrNull; };
         if (i < m_ptrData->m_intSize)
         {
            return m_ptrData->m_arrChar[i];
         }
         else {
            //invalid index return NULL
            return m_chrNull;
         };
         return m_chrNull;
      }
      catch (...)
      {
         std::string errMsg;
         errMsg = "HtlString At Error thrown";
         throw std::exception(errMsg.c_str());
      }
	};
	char & HtlString::operator[](size_t i)
	{
      try
      {
         if (!m_ptrData) { return m_chrNull; };
         if (i < m_ptrData->m_intSize)
         {
            return m_ptrData->m_arrChar[i];
         }
         else {
            //invalid index return NULL
            return m_chrNull;
         };
         return m_chrNull;
      }
      catch (...)
      {
         std::string errMsg;
         errMsg = "HtlString At Error thrown";
         throw std::exception(errMsg.c_str());
      }
	};
	//!Sub String Accessors

	void HtlString::subString(HtlString & ptrString, size_t intStart, size_t intLength)
	{	
      try
      {
         //safety check
         std::string strTemp;
         if (!m_ptrData) { return; };

         size_t i;
         ptrString.clear();
         ptrString.reserve(intLength);
         for (i = 0; i < intLength; i++)
         {
            ptrString.at(i) = m_ptrData->m_arrChar[(intStart + i)];
         };
         ptrString.at(i) = '\0';
         strTemp = ptrString.unicode();

         return;
      }
      catch (...)
      {
         std::string errMsg;
         errMsg = "HtlString Substring Error thrown";
         throw std::exception(errMsg.c_str());
      }
	};
	//!HTL Container Analyzers
	//!Returns the length of the string minus the null terminator (\0)
	size_t HtlString::size(void) const
	{
		if(!m_ptrData){return 0;};
		return m_ptrData->m_intSize;
	};
	//!Returns the length of the string minus the null terminator (\0)
	size_t HtlString::count(void) const
	{
		if(!m_ptrData){return 0;};
		return m_ptrData->m_intSize;
	};
	//!Forces a recount of the length of the string minus the null terminator (\0)
	void HtlString::recount(void)
	{
      try
      {
         //safety check
         if (!m_ptrData) { return; };

         size_t i = 0;
         bool blnNullReached = false;

         while (!blnNullReached)
         {

            if (m_ptrData->m_arrChar[i] == '\0')
            {
               blnNullReached = true;
            }
            else {
               //increment counter
               ++i;
            };
         };
         if (i > 0)
         {
            m_ptrData->m_intSize = i;
            m_ptrData->m_intAlloc = i;
         };
         return;
      }
      catch (...)
      {
         std::string errMsg;
         errMsg = "HtlString Recount Error thrown";
         throw std::exception(errMsg.c_str());
      }
	};

	bool HtlString::isEmpty(void) const
	{
		//safety check
		if(!m_ptrData){return true;};

		if(m_ptrData->m_intSize <= 0)
		{return true;}else{return false;};

		return true;
	};
	//
	size_t HtlString::capacity(void) const
	{//
		//safety check
		if(!m_ptrData){return 0;};

		return m_ptrData->m_intAlloc;

	};

};//end namespace HTL