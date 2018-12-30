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


#ifndef HTL_STRING_ALGORITHMS_H
#define HTL_STRING_ALGORITHMS_H

#include ".\HtlString.h"



namespace HTL{

	namespace HtlStringAlg{
		//string name equality testing function
		HTL_DLLAPI	bool IsStringEqual(const HtlString & strA, const HtlString & strB);

		//commonly used string functions
		//Tokenizes or splits a string based on a delimiter 
		HTL_DLLAPI void StringTokenize(HtlString& strA, std::vector<std::string> & tokens, char delimiter = ' ');

		//!Finds the first occurance of the character
		HTL_DLLAPI int IndexOf(HtlString & strA, char c, int from = 0, bool blnCaseSensitive = false);
		//!Finds the last occurance of the character
		HTL_DLLAPI int LastIndexOf(HtlString & strA, char c, int from = 0, bool blnCaseSensitive = false);

		//!Checks to see if strA contains character
		HTL_DLLAPI bool Contains(HtlString & strA, char c, bool blnCaseSensitive = false);
		//!Checks to see if strA contains sub string
		HTL_DLLAPI bool Contains(HtlString & strA, const HtlString &s, bool blnCaseSensitive = false);

		//!Checks to see if strA contains sub string
		HTL_DLLAPI bool StartsWith(HtlString & strA, const HtlString &s, bool blnCaseSensitive = false);
		//!Checks to see if strA contains sub string
		HTL_DLLAPI bool EndsWith(HtlString & strA, const HtlString &s, bool blnCaseSensitive = false);

		//!Convert the character to lower case
		HTL_DLLAPI void ToLower(char & chrA);
		//!Convert the string to lower case
		HTL_DLLAPI void ToLower(HtlString & strA);
		//!Get the character to lower case
		HTL_DLLAPI char GetLower(char chrA);

		//!Convert the character to upper case
		HTL_DLLAPI void ToUpper(char & chrA);
		//!Convert the string to upper case
		HTL_DLLAPI void ToUpper(HtlString & strA);
		//!Get the character to upper case
		HTL_DLLAPI char GetUpper(char chrA);

		//!Remove from strA the section starting at i with length len
		HTL_DLLAPI bool Remove(HtlString & strA, int i, int len);
		//!Remove from strA the character c with or without case sensitivity
		HTL_DLLAPI bool Remove(HtlString & strA, char c, bool blnCaseSensitive = false);
		//!Remove from strA the substring strA with or without case sensitivity
		HTL_DLLAPI bool Remove(HtlString & strA, const HtlString &s, bool blnCaseSensitive = false);

		//!Replaces each occurance of chrOld with the chrNew
		HTL_DLLAPI bool Replace(HtlString & strA, char chrOld, char chrNew, bool blnCaseSensitive = false);
		//!Replaces each occurance of the strOld with the strNew
		HTL_DLLAPI bool Replace(HtlString & strA, HtlString & strOld, HtlString &  strNew, bool blnCaseSensitive = false);



		//!Set the string to the Number inputed
		HTL_DLLAPI void SetNumber(HtlString & strA,short varVal, int base=10);
		HTL_DLLAPI void SetNumber(HtlString & strA,ushort varVal, int base=10);
		HTL_DLLAPI void SetNumber(HtlString & strA,int varVal, int base=10);
		HTL_DLLAPI void SetNumber(HtlString & strA,uint varVal, int base=10);
		HTL_DLLAPI void SetNumber(HtlString & strA,long varVal, int base=10);
		HTL_DLLAPI void SetNumber(HtlString & strA,ulong varVal, int base=10);
		//HTL_DLLAPI void SetNumber(HtlString & strA,qlonglong, int base=10);
		//HTL_DLLAPI void SetNumber(HtlString & strA,qulonglong, int base=10);
		HTL_DLLAPI void SetNumber(HtlString & strA,float varVal, int prec=6);
		HTL_DLLAPI void SetNumber(HtlString & strA,double varVal, int prec=6);



		//!Character Functions
		//!Is Null Character
		HTL_DLLAPI bool IsNull(char c);
		//!Is Punctuation Character
		HTL_DLLAPI bool IsPunct(char c);
		//!Is White Space Character
		HTL_DLLAPI bool IsWhiteSpace(char c);
		//Is an Alpha (Letter) Character
		HTL_DLLAPI bool IsAlpha(char c);
		//!Is a Numeric Character
		HTL_DLLAPI bool IsNumeric(char c);
		//!Is an Alpha or Numeric Character
		HTL_DLLAPI bool IsAlphaNumeric(char c);
		//!Is a Mark Character
		HTL_DLLAPI bool IsMark(char c);
		//!Is a Printable Character
		HTL_DLLAPI bool IsPrint(char c);

		//!Is a lower case character
		HTL_DLLAPI bool IsLower(char c);
		//!Is an upper case character
		HTL_DLLAPI bool IsUpper(char c);

	};//end namespace HtlStringAlg
};//end namespace HTL
#endif