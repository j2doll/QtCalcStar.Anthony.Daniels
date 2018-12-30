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

#pragma warning (disable : 4996 ) /* deprecated itoa, ltoa */

#include ".\StlStringAlgorithms.h"
#include ".\HtlStringAlgorithms.h"
#include "..\modHtlMath.h"
#include "..\modHtlContainer.h"

namespace HTL{

	namespace HtlStringAlg{
		//string name equality testing function
		bool IsStringEqual(const std::string & strA, const std::string & strB)
		{
			try
			{
				size_t i, intLHS, intRHS, intLen;
				intLHS = strA.size();
				intRHS = strB.size();
				if (intLHS != intRHS) { return false; };//different number of characters
				intLen = min(intLHS, intRHS);
				for (i = 0; i < intLen; i++)
				{
					if (strA[i] != strB[i]) { return false; };
				};
				//made it all the way through found a match
				return true;
			}
			catch (...)
			{
				std::string errMsg;
				errMsg = "HtlStringAlgorithms IsStringEqual Error thrown";
				throw std::exception(errMsg.c_str());
			}
		};

		//commonly used string functions
		//Tokenizes or splits a string based on a delimiter 
		void StringTokenize(std::string& strA, std::vector<std::string> & tokens, char delimiter)
		{
			try
			{
				size_t intWordBegin, intWordEnd, intWordLen;
				size_t i, intLen;
				std::string strWord;
				std::string strTemp;

				intLen = strA.size();
				//safety check
				if (intLen <= 0) { return; };
				intWordBegin = 0;

				for (i = 0; i < intLen; i++)
				{
					if (strA[i] == delimiter)
					{
						//word end triggered
						intWordEnd = i;

						intWordLen = intWordEnd - intWordBegin;
						//special case
						if (intWordLen <= 0)
						{//zero length word skip it
							intWordBegin = i;
						}
						else {
							//get the substring of the word
							strWord = strA.substr(intWordBegin, intWordLen);
							strTemp = strWord;
							tokens.push_back(strTemp);
							intWordBegin = i + 1;
						};//end word check
					};//end delimiter found
				};//end for loop through strA
				//last word if there was any delimeters
				if (intWordBegin > 0)
				{
					//then at least one split, add the last word manually
					intWordLen = intLen - intWordBegin;
					strWord = strA.substr(intWordBegin, intWordLen);
					strTemp = strWord;
					tokens.push_back(strTemp);
				};
				return;
			}
			catch (...)
			{
				std::string errMsg;
				errMsg = "HtlStringAlgorithms StringTokenize Error thrown";
				throw std::exception(errMsg.c_str());
			}
		};

		//!Finds the first occurance of the character
		int IndexOf(std::string & strA, char c, int from, bool blnCaseSensitive)
		{
			try
			{
				size_t intFirst;
				size_t i, intLen;

				intLen = strA.size();
				//safety check
				if (intLen <= 0) { return -1; };
				intFirst = -1;//error code for not found

				for (i = 0; i < intLen; i++)
				{
					if (strA[i] == c)
					{
						//character match
						intFirst = i;
						return intFirst;
					}
					else if (!blnCaseSensitive) {

						if (GetUpper(strA[i]) == GetUpper(c))
						{
							//character match Non-CaseSensistive
							intFirst = i;
							return intFirst;
						};

					};//end delimiter found
				};//end for loop through strA
				return intFirst;
			}
			catch (...)
			{
				std::string errMsg;
				errMsg = "HtlStringAlgorithms IndexOf Error thrown";
				throw std::exception(errMsg.c_str());
			}
		};
		//!Finds the last occurance of the character
		int LastIndexOf(std::string & strA, char c, int from, bool blnCaseSensitive)
		{
			try
			{
				size_t intLast;
				size_t i, intLen;

				intLen = strA.size();
				//safety check
				if (intLen <= 0) { return -1; };
				intLast = -1;//error code for not found

				for (i = 0; i < intLen; i++)
				{
					if (strA[i] == c)
					{
						//character match
						intLast = i;
					}
					else if (!blnCaseSensitive) {

						if (GetUpper(strA[i]) == GetUpper(c))
						{
							//character match Non-CaseSensistive
							intLast = i;
						};
					};//end delimiter found
				};//end for loop through strA
				return intLast;
			}
			catch (...)
			{
				std::string errMsg;
				errMsg = "HtlStringAlgorithms LastIndexOf Error thrown";
				throw std::exception(errMsg.c_str());
			}
		};

		//!Checks to see if strA contains character
		bool Contains(std::string & strA, char c, bool blnCaseSensitive)
		{
			try
			{
				bool blnMatchFound;
				size_t intLast;
				size_t i, intLen;

				intLen = strA.size();
				//safety check
				if (intLen <= 0) { return false; };
				intLast = -1;//error code for not found
				blnMatchFound = false;
				for (i = 0; i < intLen; i++)
				{
					if (strA[i] == c)
					{
						//character match
						intLast = i;
						blnMatchFound = true;
					}
					else if (!blnCaseSensitive) {

						if (GetUpper(strA[i]) == GetUpper(c))
						{
							//character match Non-CaseSensistive
							intLast = i;
							blnMatchFound = true;
						};
					};//end delimiter found
				};//end for loop through strA
				return blnMatchFound;
			}
			catch (...)
			{
				std::string errMsg;
				errMsg = "HtlStringAlgorithms Contains Error thrown";
				throw std::exception(errMsg.c_str());
			}
		};
		//!Checks to see if strA contains sub string
		bool Contains(std::string & strA, const std::string &s, bool blnCaseSensitive)
		{
			try
			{
				bool blnMatchFound;
				size_t intLast;
				size_t i, j, intLenS, intLenA;
				std::string strWord;

				//safety check			
				intLenS = s.size();
				if (intLenS <= 0) { return false; };
				//safety check
				intLenA = strA.size();
				if (intLenA <= 0) { return false; };
				//initialize
				intLast = -1;//error code for not found
				blnMatchFound = false;
				for (i = 0; i < intLenA; i++)
				{
					if (strA[i] == s[0])
					{
						blnMatchFound = true;
						//character match for start
						for (j = 0; j < intLenS; j++)
						{
							if (strA[i + j] != s[j])
							{
								//then not a match, keep going
								blnMatchFound = false;
							};
						};
						//if blnMatchFound == true, then it will quit out
						if (blnMatchFound) { return true; };

					}
					else if (!blnCaseSensitive) {

						blnMatchFound = true;
						//character match for start
						for (j = 0; j < intLenS; j++)
						{
							if (GetUpper(strA[(i + j)]) != GetUpper(s[j]))
							{
								//then not a match, keep going
								blnMatchFound = false;
							};
						};
						//if blnMatchFound == true, then it will quit out
						if (blnMatchFound) { return true; };
					};//end delimiter found
				};//end for loop

				return false;
			}
			catch (...)
			{
				std::string errMsg;
				errMsg = "HtlStringAlgorithms Contains Error thrown";
				throw std::exception(errMsg.c_str());
			}
		};

		//!Checks to see if strA contains sub string
		bool StartsWith(std::string & strA, const std::string &s, bool blnCaseSensitive)
		{
			try
			{
				bool blnMatchFound;
				size_t intLast;
				size_t i, j, intLenS, intLenA;
				std::string strWord;

				//safety check			
				intLenS = s.size();
				if (intLenS <= 0) { return false; };
				//safety check
				intLenA = strA.size();
				if (intLenA <= 0) { return false; };
				//initialize
				intLast = -1;//error code for not found
				blnMatchFound = false;
				i = 0;//set index to beginning of word

				if (blnCaseSensitive)
				{
					blnMatchFound = true;
					if (strA[0] == s[0])
					{
						//character match for start
						for (j = 0; j < intLenS; j++)
						{
							if (strA[i + j] != s[j])
							{
								//then not a match, keep going
								blnMatchFound = false;
							};
						};
					}
					else {
						blnMatchFound = false;
					};
					//if blnMatchFound == true, then it will quit out
					if (blnMatchFound) { return true; };
				}
				else {

					blnMatchFound = true;
					if (GetUpper(strA[0]) == GetUpper(s[0]))
					{
						//character match for start
						for (j = 0; j < intLenS; j++)
						{
							if (GetUpper(strA[(i + j)]) != GetUpper(s[j]))
							{
								//then not a match, keep going
								blnMatchFound = false;
							};
						};
					}
					else {
						blnMatchFound = false;
					};
					//if blnMatchFound == true, then it will quit out
					if (blnMatchFound) { return true; };
				};
				return false;
			}
			catch (...)
			{
				std::string errMsg;
				errMsg = "HtlStringAlgorithms StartsWith Error thrown";
				throw std::exception(errMsg.c_str());
			}
		};
		//!Checks to see if strA contains sub string
		bool EndsWith(std::string & strA, const std::string &s, bool blnCaseSensitive)
		{
			try
			{
				bool blnMatchFound;
				size_t intLast;
				size_t i, j, intLenS, intLenA;
				std::string strWord;

				//safety check zero length	
				intLenS = s.size();
				if (intLenS <= 0) { return false; };
				//safety check zero length
				intLenA = strA.size();
				if (intLenA <= 0) { return false; };
				//safety check ending longer than word
				if (intLenS > intLenA) { return false; };
				//initialize
				intLast = -1;//error code for not found
				blnMatchFound = false;
				i = intLenA - intLenS;//set index to beginning of word
				//safety check illegal index
				if (i < 0) { return false; };

				if (blnCaseSensitive)
				{
					blnMatchFound = true;
					if (strA[i] == s[0])
					{
						//character match for start
						for (j = 0; j < intLenS; j++)
						{
							if (strA[i + j] != s[j])
							{
								//then not a match, keep going
								blnMatchFound = false;
							};
						};
					}
					else {
						blnMatchFound = false;
					};
					//if blnMatchFound == true, then it will quit out
					if (blnMatchFound) { return true; };
				}
				else {

					blnMatchFound = true;
					if (GetUpper(strA[i]) == GetUpper(s[0]))
					{
						//character match for start
						for (j = 0; j < intLenS; j++)
						{
							if (GetUpper(strA[(i + j)]) != GetUpper(s[j]))
							{
								//then not a match, keep going
								blnMatchFound = false;
							};
						};
					}
					else {
						blnMatchFound = false;
					};
					//if blnMatchFound == true, then it will quit out
					if (blnMatchFound) { return true; };
				};
				return false;
			}
			catch (...)
			{
				std::string errMsg;
				errMsg = "HtlStringAlgorithms EndsWith Error thrown";
				throw std::exception(errMsg.c_str());
			}
		};

		//!Convert the string to lower case
		void ToLower(std::string & strA)
		{
			try
			{
				size_t i, intLen;
				intLen = strA.size();
				if (intLen <= 0) { return; };
				for (i = 0; i < intLen; i++)
				{
					ToLower(strA[i]);
				};
				return;
			}
			catch (...)
			{
				std::string errMsg;
				errMsg = "HtlStringAlgorithms ToLower Error thrown";
				throw std::exception(errMsg.c_str());
			}
		};

		//!Convert the string to upper case
		void ToUpper(std::string & strA)
		{
			try
			{
				size_t i, intLen;
				intLen = strA.size();
				if (intLen <= 0) { return; };
				for (i = 0; i < intLen; i++)
				{
					ToUpper(strA[i]);
				};
				return;
			}
			catch (...)
			{
				std::string errMsg;
				errMsg = "HtlStringAlgorithms ToUpper Error thrown";
				throw std::exception(errMsg.c_str());
			}
		};

		//!Remove from strA the section starting at i with length len
		bool Remove(std::string & strA, int i, int len)
		{
			try
			{
				std::string strTemp, strEnd;
				size_t intTailLen;
				//safety check
				if (strA.size() <= 0) { return false; };
				//
				intTailLen = strA.size() - (i + len);
				//extract front
				strTemp = strA.substr(0, i);
				//extract tail
				strEnd = strA.substr((i + len), intTailLen);
				//write removed string
				strA = strTemp;
				strA.append(strEnd);
				return true;
			}
			catch (...)
			{
				std::string errMsg;
				errMsg = "HtlStringAlgorithms Remove Error thrown";
				throw std::exception(errMsg.c_str());
			}
		};
		//!Remove from strA the character c with or without case sensitivity
		bool Remove(std::string & strA, char c, bool blnCaseSensitive)
		{
			try
			{
				bool blnMatchFound = false;
				std::string strTemp;
				size_t i, intLen;
				if (strA.size() <= 0) { return false; };
				intLen = strA.size();

				for (i = 0; i < intLen; i++)
				{
					if (blnCaseSensitive)
					{
						if (strA[i] != c)
						{
							//not match, add it to the string
							strTemp += (strA[i]);
						}
						else {
							//match, dont copy it
							blnMatchFound = true;
						};
					}
					else {
						if (GetUpper(strA[i]) != GetUpper(c))
						{
							//not match, add it to the string
							strTemp += (strA[i]);
						}
						else {
							//match, dont copy it
							blnMatchFound = true;
						};
					};//end case sensitive switch
				};//end loop through characters
				//copy new string over old one
				strA = strTemp;
				return blnMatchFound;
			}
			catch (...)
			{
				std::string errMsg;
				errMsg = "HtlStringAlgorithms Remove Error thrown";
				throw std::exception(errMsg.c_str());
			}
		};
		//!Remove from strA the substring strA with or without case sensitivity
		bool Remove(std::string & strA, const std::string &s, bool blnCaseSensitive)
		{
			try
			{
				bool blnMatchFound, blnMatchInstance;
				size_t intLastStart;
				size_t intCursor, j, intLenS, intLenA;
				std::string strWord, strTemp;

				//safety check			
				intLenS = s.size();
				if (intLenS <= 0) { return false; };
				//safety check
				intLenA = strA.size();
				if (intLenA <= 0) { return false; };
				//initialize
				intLastStart = 0;//error code for not found
				blnMatchFound = false;
				blnMatchInstance = false;
				intCursor = 0;
				while (intCursor < intLenA)
				{
					if (GetUpper(strA[intCursor]) == GetUpper(s[0]))
					{
						if (blnCaseSensitive)
						{
							blnMatchFound = true;
							//character match for start
							for (j = 0; j < intLenS; j++)
							{
								if (strA[intCursor + j] != s[j])
								{
									//then not a match, keep going
									blnMatchFound = false;
								};
							};
							//if blnMatchFound == true, then it will quit out
							if (blnMatchFound)
							{
								blnMatchInstance = true;
								intCursor = (intCursor + j);
							};

						}
						else {
							//not case sensistive use uppercase matching
							blnMatchFound = true;
							//character match for start
							for (j = 0; j < intLenS; j++)
							{
								if (GetUpper(strA[(intCursor + j)]) != GetUpper(s[j]))
								{
									//then not a match, keep going
									blnMatchFound = false;
								};
							};
							//if blnMatchFound == true, then it will quit out
							if (blnMatchFound)
							{
								blnMatchInstance = true;
								intCursor = (intCursor + j);
							};
						};//end delimiter found
					}
					else {
						//not match, append and advance cursor
						strTemp += strA[intCursor];
						intCursor++;
					};//end character match
				};//end while loop through string

				if (blnMatchInstance)
				{
					//the at least one match, copy construction string
					strA = strTemp;
				};
				return blnMatchFound;
			}
			catch (...)
			{
				std::string errMsg;
				errMsg = "HtlStringAlgorithms Remove Error thrown";
				throw std::exception(errMsg.c_str());
			}
		};

		//!Replaces each occurance of chrOld with the chrNew
		bool Replace(std::string & strA, char chrOld, char chrNew, bool blnCaseSensitive)
		{
			try
			{
				bool blnMatchFound = false;
				std::string strTemp;
				size_t i, intLen;
				if (strA.size() <= 0) { return false; };
				intLen = strA.size();

				for (i = 0; i < intLen; i++)
				{
					if (blnCaseSensitive)
					{
						if (strA[i] == chrOld)
						{
							strA[i] = chrNew;
							blnMatchFound = true;
						};
					}
					else {
						if (GetUpper(strA[i]) == GetUpper(chrOld))
						{
							strA[i] = chrNew;
							blnMatchFound = true;
						}
					};//end case sensitive switch
				};//end loop through characters
				//copy new string over old one
				return blnMatchFound;
			}
			catch (...)
			{
				std::string errMsg;
				errMsg = "HtlStringAlgorithms Replace Error thrown";
				throw std::exception(errMsg.c_str());
			}
		};
		//!Replaces each occurance of the strOld with the strNew
		bool Replace(std::string & strA, std::string & strOld, std::string &  strNew, bool blnCaseSensitive)
		{
			try
			{
				bool blnMatchFound, blnMatchInstance;
				size_t intLastStart;
				size_t intCursor, j, intLenS, intLenA;
				std::string strWord, strTemp;

				//safety check			
				intLenS = strOld.size();
				if (intLenS <= 0) { return false; };
				//safety check
				intLenA = strA.size();
				if (intLenA <= 0) { return false; };
				//initialize
				intLastStart = 0;//error code for not found
				blnMatchFound = false;
				blnMatchInstance = false;
				intCursor = 0;
				while (intCursor < intLenA)
				{
					if (GetUpper(strA[intCursor]) == GetUpper(strOld[0]))
					{
						if (blnCaseSensitive)
						{
							blnMatchFound = true;
							//character match for start
							for (j = 0; j < intLenS; j++)
							{
								if (strA[intCursor + j] != strOld[j])
								{
									//then not a match, keep going
									blnMatchFound = false;
								};
							};
							//if blnMatchFound == true, then it will quit out
							if (blnMatchFound)
							{
								blnMatchInstance = true;
								strTemp.append(strNew);
								intCursor = (intCursor + j);
							};

						}
						else {
							//not case sensistive use uppercase matching
							blnMatchFound = true;
							//character match for start
							for (j = 0; j < intLenS; j++)
							{
								if (GetUpper(strA[(intCursor + j)]) != GetUpper(strOld[j]))
								{
									//then not a match, keep going
									blnMatchFound = false;
								};
							};
							//if blnMatchFound == true, then it will quit out
							if (blnMatchFound)
							{
								blnMatchInstance = true;
								strTemp.append(strNew);
								intCursor = (intCursor + j);
							};
						};//end delimiter found
					}
					else {
						//not match, append and advance cursor
						strTemp += strA[intCursor];
						intCursor++;
					};//end character match
				};//end while loop through string

				if (blnMatchInstance)
				{
					//the at least one match, copy construction string
					strA = strTemp;
				};
				return blnMatchFound;
			}
			catch (...)
			{
				std::string errMsg;
				errMsg = "HtlStringAlgorithms Remove Error thrown";
				throw std::exception(errMsg.c_str());
			}
		};



		//!Set the string to the Number inputed
		void SetNumber(std::string & strA,short varVal, int base)
		{
			char chrBuf[128];
			char* ptrBuf = &chrBuf[0];
			itoa(int(varVal),ptrBuf,base);
			strA = chrBuf;
			return;	
		};
		void SetNumber(std::string & strA,ushort varVal, int base)
		{
			char chrBuf[128];
			char* ptrBuf = &chrBuf[0];
			itoa(int(varVal),ptrBuf,base);
			strA = chrBuf;
			return;	
		};
		void SetNumber(std::string & strA,int varVal, int base)
		{
			char chrBuf[128];
			char* ptrBuf = &chrBuf[0];
			itoa(int(varVal),ptrBuf,base);
			strA = chrBuf;
			return;	
		};
		void SetNumber(std::string & strA,uint varVal, int base)
		{
			char chrBuf[128];
			char* ptrBuf = &chrBuf[0];
			itoa(int(varVal),ptrBuf,base);
			strA = chrBuf;
			return;		
		};
		void SetNumber(std::string & strA,long varVal, int base)
		{
			char chrBuf[128];
			char* ptrBuf = &chrBuf[0];
			ltoa(long(varVal),ptrBuf,base);
			strA = chrBuf;
			return;	
		};
		void SetNumber(std::string & strA,ulong varVal, int base)
		{
			char chrBuf[128];
			char* ptrBuf = &chrBuf[0];
			ltoa(long(varVal),ptrBuf,base);
			strA = chrBuf;
			return;	
		};
		//void SetNumber(std::string & strA,qlonglong, int base)
		//{
		//	return false;	
		//};
		//void SetNumber(std::string & strA,qulonglong, int base)
		//{
		//	return false;	
		//};
		void SetNumber(std::string & strA,float varVal, char f, int prec)
		{
			char chrBuf[128];
			char chrDec[10];
			char* ptrDec = &chrDec[0];
			std::string strFormat = "%6.";
			itoa(prec,ptrDec, 10);
			strFormat += chrDec;
			strFormat += "f";
			sprintf_s(chrBuf, 256, strFormat.c_str(), varVal);

			strA = chrBuf;
			return;
		};
		void SetNumber(std::string & strA,double varVal, char f, int prec)
		{
			char chrBuf[128];
			char chrDec[10];
			char* ptrDec = &chrDec[0];
			std::string strFormat = "%6.";
			itoa(prec,ptrDec, 10);
			strFormat += chrDec;
			strFormat += "lf";
			sprintf_s(chrBuf, 256, strFormat.c_str(), varVal);

			strA = chrBuf;
			return;		
		};


	};//end namespace std::stringAlg
};//end namespace HTL