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

#ifndef STL_STRING_ALGORITHMS_H
#define STL_STRING_ALGORITHMS_H

#include "..\modHtlLibRefs.h"
#include <string>
#include <vector>
using namespace std;

namespace HTL{

	namespace HtlStringAlg{
		//string name equality testing function
		HTL_DLLAPI	bool IsStringEqual(const std::string & strA, const std::string & strB);

		//commonly used string functions
		//Tokenizes or splits a string based on a delimiter 
		HTL_DLLAPI void StringTokenize(std::string& strA, std::vector<std::string> & tokens, char delimiter = ' ');

		//!Finds the first occurance of the character
		HTL_DLLAPI int IndexOf(std::string & strA, char c, int from = 0, bool blnCaseSensitive = false);
		//!Finds the last occurance of the character
		HTL_DLLAPI int LastIndexOf(std::string & strA, char c, int from = 0, bool blnCaseSensitive = false);

		//!Checks to see if strA contains character
		HTL_DLLAPI bool Contains(std::string & strA, char c, bool blnCaseSensitive = false);
		//!Checks to see if strA contains sub string
		HTL_DLLAPI bool Contains(std::string & strA, const std::string &s, bool blnCaseSensitive = false);

		//!Checks to see if strA contains sub string
		HTL_DLLAPI bool StartsWith(std::string & strA, const std::string &s, bool blnCaseSensitive = false);
		//!Checks to see if strA contains sub string
		HTL_DLLAPI bool EndsWith(std::string & strA, const std::string &s, bool blnCaseSensitive = false);


		//!Convert the string to lower case
		HTL_DLLAPI void ToLower(std::string & strA);

		//!Convert the string to upper case
		HTL_DLLAPI void ToUpper(std::string & strA);


		//!Remove from strA the section starting at i with length len
		HTL_DLLAPI bool Remove(std::string & strA, int i, int len);
		//!Remove from strA the character c with or without case sensitivity
		HTL_DLLAPI bool Remove(std::string & strA, char c, bool blnCaseSensitive = false);
		//!Remove from strA the substring strA with or without case sensitivity
		HTL_DLLAPI bool Remove(std::string & strA, const std::string &s, bool blnCaseSensitive = false);

		//!Replaces each occurance of chrOld with the chrNew
		HTL_DLLAPI bool Replace(std::string & strA, char chrOld, char chrNew, bool blnCaseSensitive = false);
		//!Replaces each occurance of the strOld with the strNew
		HTL_DLLAPI bool Replace(std::string & strA, std::string & strOld, std::string &  strNew, bool blnCaseSensitive = false);



		//!Set the string to the Number inputed
		HTL_DLLAPI void SetNumber(std::string & strA,short varVal, int base=10);
		HTL_DLLAPI void SetNumber(std::string & strA,ushort varVal, int base=10);
		HTL_DLLAPI void SetNumber(std::string & strA,int varVal, int base=10);
		HTL_DLLAPI void SetNumber(std::string & strA,uint varVal, int base=10);
		HTL_DLLAPI void SetNumber(std::string & strA,long varVal, int base=10);
		HTL_DLLAPI void SetNumber(std::string & strA,ulong varVal, int base=10);
		//HTL_DLLAPI void SetNumber(std::string & strA,qlonglong, int base=10);
		//HTL_DLLAPI void SetNumber(std::string & strA,qulonglong, int base=10);
		HTL_DLLAPI void SetNumber(std::string & strA,float varVal, int prec=6);
		HTL_DLLAPI void SetNumber(std::string & strA,double varVal, int prec=6);

	};//end namespace std::stringAlg

};//end namespace HTL

#endif