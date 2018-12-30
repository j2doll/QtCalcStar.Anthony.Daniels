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

#include <vector>
#include <string>
#include <map>
#include <algorithm>


#include ".\HtlJSONReader.h"
#include "..\HtlElement.h"
#include "..\HtlAttribute.h"
#include "..\HtlComment.h"
#include "..\HtlProcess.h"

using namespace HTL;

//PUBLIC CONSTRUCTORS & DESTRUCTOR/////////////////////////////
HtlJSONReader::HtlJSONReader(void)
{
	
	return;
};

HtlJSONReader::~HtlJSONReader(void)
{
	m_str.clear();
	
	return;
};

//Load the XML Element based on the current starting location of the index
int HtlJSONReader::LoadJSONElement(HtlElement * ptrElement, const std::string & strInput, HtlElementIndex & objCurrElementIndex)
{	
	/*
	//READELEMENT
	READOPENTAG (get open and close positions)-->Create Substring and feed it to a XMLReader
	Use the XMLReader to:
	read tag name
	read attribute list
	parse attribute list
	create and populate the attributes
	READCLOSETAG
	EXTRACT COMMENT (area between open tag and first sub element)
	For each Sub Element
	Get the Sub Element Starting Location
	LoadXMLTree with that index(recursive call with same original input string)	
	*/

	//READ the OPEN TAG
	int intTemp, intReturn;
	bool blnNullElement;
	std::string strTagName, strCloseTag;
	intReturn = 1;
	if(ptrElement == NULL)
	{
		//then nothing to do
		return 0;
	}
	//test try and access the element, if bad pointer quit out gracefully
	try{
		std::string strTemp = ptrElement->Get_strName();
	}catch(...){
		//BAD POINTER RETURN ERROR
		return -1;
	}

	m_intStringSize = strInput.size();
	if(m_intStringSize <= 0)
	{
		return 0;
	}
	//Otherwise safe to proceed


	//THESE FUNCTIONS MUST BE CALLED IN ORDER
	//LOAD THE OPEN TAG
	intTemp = LoadOpenTag(ptrElement,strInput,objCurrElementIndex,blnNullElement);
	if(intTemp < 0){intReturn = -1;};
	//LOAD THE ATTRIBUTES
	//THERE ARE NO ATTRIBUTES IN JSON
	//intTemp = LoadAttributes(ptrElement,strInput,objCurrElementIndex);
	if(intTemp < 0){intReturn = -1;};
	//IF ELEMENT IS NOT A NULL TERMINATED ELEMENT, THEN LOAD THE REST
	if(blnNullElement == false)
	{
		//LOAD THE VALUE FOR THE ELEMENT
      bool blnHasValue;
		intTemp = LoadValue(ptrElement,strInput,objCurrElementIndex, blnHasValue);
		if(intTemp < 0){intReturn = -1;};
		//LOAD ALL OF THE SUB ELEMENTS

      if (!blnHasValue)
      {  //then object element with sub nodes
         intTemp = LoadSubNodes(ptrElement, strInput, objCurrElementIndex);
         if (intTemp < 0) { intReturn = -1; };
      }

	}else{
		//then null element artificially set the end close tag beginning and end to the open tag end position
		objCurrElementIndex.m_intCloseTagStartPos = objCurrElementIndex.m_intOpenTagEndPos;
		objCurrElementIndex.m_intCloseTagEndPos = objCurrElementIndex.m_intOpenTagEndPos;
	}

	return intReturn;

};



//Load the Tag to the Element Name
int HtlJSONReader::LoadOpenTag(HtlElement * ptrElement, const std::string & strInput, HtlElementIndex & objCurrElementIndex, bool & blnNullElementReturn)
{

	size_t intCursor, intPosTag, intOpenPos, intClosePos;
	std::string strTagName;
	HtlArchNodeType enumNodeType = NODE;
	blnNullElementReturn = false;
	//find the open Tag
	intCursor = objCurrElementIndex.m_intOpenTagStartPos;
	while(intCursor < strInput.size())
	{
		intOpenPos = FindNextChar(strInput,intCursor,'\"');
		if( (intOpenPos < strInput.size())&&
			(intOpenPos >= 0) )
		{//then valid open tag. check special cases first
			//check for comment

				enumNodeType = ELEMENT;
				objCurrElementIndex.m_intOpenTagStartPos = intOpenPos;
				//process as normal element opening tag with attributes
				//find the close tag position
				intClosePos = FindNextChar(strInput,intOpenPos+1,'\"');
				if((intClosePos < strInput.size())&&
					(intClosePos > 0) )
				{//then valid close tag position

					objCurrElementIndex.m_intOpenTagEndPos = intClosePos;
					//check to see if NULL ELEMENT
               int colonIdx = FindNextNWSChar(strInput, intClosePos+1);
               if (strInput[colonIdx] == ':')
               {
                  int nullBeginIdx = FindNextNWSChar(strInput, colonIdx+1);
                  if (strInput[nullBeginIdx] == '{')
                  {
                     int nullEndIdx = FindNextNWSChar(strInput, nullBeginIdx+1);
                     if (strInput[nullEndIdx] == '}')
                     {
                        blnNullElementReturn = true;
                        //then NULL NODE
                     }
                  }
               }
               else {
                  blnNullElementReturn = false;
               }


					//use the close bracket to calculate the length, dependent on whether or not it is null terminal
				   objCurrElementIndex.m_intTagLength = ((intClosePos - 1) - (intOpenPos));

				//extract the tag sub string
				strTagName = strInput.substr(objCurrElementIndex.m_intOpenTagStartPos + 1, objCurrElementIndex.m_intTagLength);
				//Set the tag name for this element
				ptrElement->Set_strName(strTagName);
				return 1;
			}else{
				intCursor = ++intOpenPos;
			};

		}else{
			//no tags found
			return -1;
		};
	};//end while loop through the string

	return 0;

};

//Load the Tag to the Element Name
int HtlJSONReader::LoadCloseTag(HtlElement * ptrElement, const std::string & strInput, HtlElementIndex & objCurrElementIndex)
{
   bool blnStartFound = false;
   int intStartOpenBlock;
   int intLevel = 0;
   int intOpenTagEnd = objCurrElementIndex.m_intOpenTagEndPos+1;
   int colonIdx = FindNextNWSChar(strInput, intOpenTagEnd);
   if (strInput[colonIdx] == ':')
   {
      intStartOpenBlock = FindNextNWSChar(strInput, colonIdx+1);
      if (strInput[intStartOpenBlock] == '{')
      {
         blnStartFound = true;
      }
   }

   if (!blnStartFound) { return -1; };//error checking
   if(!(intStartOpenBlock + 1 < strInput.size())) { return -1; };//error checking

   //now loop through the string to find the same level close bracket
   int strLength = strInput.size();
   for (int m = intStartOpenBlock + 1;m < strLength; m++)
   {
      if ((strInput[m] == '}') && (intLevel == 0))
      {
         //then matching bracket found
         objCurrElementIndex.m_intCloseTagStartPos = m;
         objCurrElementIndex.m_intCloseTagEndPos = m;
         return 1;
      }

      //otherwise need to increment or decrement
      if (strInput[m] == '{')
      {
         intLevel++;
      };

      if (strInput[m] == '}')
      {
         intLevel--;
      };

      //safety checks
      if (intLevel < 0)
      {
         //unbalanced JSON
         return -1;
      }

   };

   //made it to the end of the string
   objCurrElementIndex.m_intCloseTagStartPos = strLength - 1;
   objCurrElementIndex.m_intCloseTagEndPos = strLength - 1;
   return -1;
};


//Load the Attributes into the Element
int	HtlJSONReader::LoadValue(HtlElement * ptrElement, const std::string & strInput, HtlElementIndex & objCurrElementIndex, bool & blnHasValue)
{
	//makes the assumption that the open tag has been established.
	//take the tag string minus open and close characters
	//Parse the attributes into a name,value pair vector stripping the "" or '' around the value and the = sign
	//Cycle through the pair vector to create the attributes
   blnHasValue = false;
	std::string strValTemp;
	HtlAttribute * ptrCurrAttrib = NULL;
	JSONNameValuePair objNVPTemp;
	std::vector<JSONNameValuePair> arrObjAttribNVPs;
   bool GoodOpenValue = false;
   int colonIdx = FindNextChar(strInput, objCurrElementIndex.m_intOpenTagEndPos, ':');
   if (colonIdx < 0) { return 1; }//then sub element node, no value

   int valueStartIdx = FindNextNWSMatch(strInput, colonIdx + 1, '{', GoodOpenValue);
   if (GoodOpenValue) 
   {
      objCurrElementIndex.m_intSubElementStartPos = valueStartIdx;
      blnHasValue = false;
      return 1; 
   }

   valueStartIdx = FindNextNWSMatch(strInput, colonIdx + 1, '\"', GoodOpenValue);
   if (valueStartIdx < 0) { return -1; }

   int valueEndIdx = FindNextChar(strInput, valueStartIdx + 1, '\"');
   if (valueEndIdx < 0) { return -1; }
   blnHasValue = true;

   int lengthIdx = (valueEndIdx - valueStartIdx - 1);
   if (lengthIdx < 0) { return -1; }

   strValTemp = strInput.substr(valueStartIdx + 1, lengthIdx);
   ptrElement->Set_strValue(strValTemp);
   objCurrElementIndex.m_intSubElementStartPos = valueEndIdx + 1;
   objCurrElementIndex.m_intCloseTagStartPos = valueEndIdx + 1;
   objCurrElementIndex.m_intCloseTagEndPos = valueEndIdx + 1;
   return 1;
};

//Load the Attributes into the Element
int	HtlJSONReader::LoadSubNodes(HtlElement * ptrElement, const std::string & strInput, HtlElementIndex & objCurrElementIndex)
{
	//makes the assumption that the open tag has been established.
	//take the tag string minus open and close characters
	//Parse the attributes into a name,value pair vector stripping the "" or '' around the value and the = sign
	//Cycle through the pair vector to create the attributes
	int intTemp, iRet;
	std::string strValTemp;
	size_t intCursor, intOpenTag, lngStringSize;
	bool blnIsComment, blnIsProcess, blnIsElement, blnCloseTagFound;
    blnCloseTagFound = false;
	blnIsComment = false;
	blnIsProcess = false;
	blnIsElement = false;

	lngStringSize = strInput.size();
	intCursor = objCurrElementIndex.m_intOpenTagEndPos + 1;

   iRet = LoadCloseTag(ptrElement, strInput, objCurrElementIndex);
   if (iRet < 0)
   {
      return -1;//error finding close tag
   }


   while ((!blnCloseTagFound) && (intCursor < lngStringSize))
   {
      //Set node type to generic node
      HtlArchNodeType enumCurrNodeType = NODE;
      //find next open tag
      intOpenTag = FindNextTagStart(strInput, intCursor, blnCloseTagFound);

      if (intOpenTag < objCurrElementIndex.m_intCloseTagStartPos)
      {
         //treat it as a sub element
         enumCurrNodeType = ELEMENT;
         HtlElementIndex objSubElementIndex;
         objSubElementIndex.m_intOpenTagStartPos = intOpenTag;
         //CODE TO LOAD THE SUB-ELEMENT NODE/////
         //TO BE ADDED///////
         intTemp = LoadSubElement(ptrElement, strInput, objSubElementIndex);
         if (intTemp < 0)
         {//then loading process failed
            ++intCursor;
         }
         else {
            intCursor = objSubElementIndex.m_intCloseTagEndPos;
            if (intCursor < objSubElementIndex.m_intOpenTagStartPos)
            {
               // then illegal close tag, could be null element,
               //set to end of open tag
               intCursor = objSubElementIndex.m_intOpenTagEndPos;
            };
         };
         ++intCursor;
      }
      else
      {
         blnCloseTagFound = true;
      }
	};//end while loop through
	return 1;
};

//!Load the Sub Element into the Element
int	HtlJSONReader::LoadSubElement(HtlElement * ptrElement, const std::string & strInput, HtlElementIndex & objCurrElementIndex)
{
	//NOTE, THIS METHOD CAUSES A RECURSIVE LOOP WITHIN THE XML TREE STRUCTURE BUILDING.
	//IF CIRCULAR LOGIC IS PRESENT IN THE XML FILE, THIS WILL CAUSE AN INFINITE LOOP.
	//HOWEVER, XML DOCS ARE TREE STRUCTURES SO THIS SHOULDN'T BE A PROBLEM
	//THIS ALGORITHM CREATES A DEPTH FIRST SEARCH APPROACH TO BUILDING THE XML TREE.
	int intTemp, intReturn;
	//set return optimistic
	intReturn = 1;
	HtlElement * ptrNewSubElement = ptrElement->AddSubElement();
	if(ptrNewSubElement)
	{//then valid sub element creation, call that elements Loading function.
		intTemp = LoadJSONElement(ptrNewSubElement, strInput,objCurrElementIndex);
		if(intTemp < 0){intReturn = -1;};
	}
	return intReturn;
};
//!Find Next < character indicating a start tag
long HtlJSONReader::FindNextTagStart(const std::string & strInput,size_t intStartPos, bool & blnCloseTag)
{
	size_t intCursor, lngStringSize;
	//skip through primary white space and illegal characters
	lngStringSize = strInput.size();
	intCursor = intStartPos;
	while(intCursor < lngStringSize)
	{
		if( strInput[intCursor] == '\"')
		{
			//check to see if we are dealing with a close tag instead
			if((intCursor + 1) < strInput.size())
			{//then safe to check one ahead
				if(strInput[intCursor + 1] == '/')
				{
					blnCloseTag = true;
				}else{
					blnCloseTag = false;
				};
			}else{
				//nothing left, cant be a close tag
				blnCloseTag = false;	
			};
			//then next tag start found
			return intCursor;
		}else{
			//increment the counter
			intCursor++;
		};
	};
	//no white space found return illegal index
	blnCloseTag = false;
	return -1;	
};


//!Find Next Non-White Space Legal Character
long HtlJSONReader::FindNextNWSLChar(const std::string & strInput,size_t intStartPos)
{
	long intCursor, lngStringSize;
	//skip through primary white space and illegal characters
	lngStringSize = strInput.size();
	intCursor = intStartPos;
	while(intCursor < lngStringSize)
	{
		if( ((int)(strInput[intCursor]) > 32)&&
			(strInput[intCursor] != '?')&&
			(strInput[intCursor] != '\\')&&
			(strInput[intCursor] != '/')&&
			(strInput[intCursor] != '!')&&
			(strInput[intCursor] != '<')&&
			(strInput[intCursor] != '>') )
		{
			//32 or less is the white space characters of ASCII
			//then non-white space legal character found
			return intCursor;
		}else{
			//increment the counter
			intCursor++;
		};
	};
	//no white space found return illegal index
	return -1;	
};
//!Find Next Non-White Space Character
long HtlJSONReader::FindNextNWSChar(const std::string & strInput,size_t intStartPos)
{
	long intCursor, lngStringSize;
	//skip through primary white space and illegal characters
	lngStringSize = strInput.size();
	intCursor = intStartPos;
	while(intCursor < lngStringSize)
	{
		if( int(strInput[intCursor]) > 32)
		{
			//32 or less is the white space characters of ASCII
			//then non-white space legal character found
			return intCursor;
		}else{
			//increment the counter
			intCursor++;
		};
	};
	//no white space found return illegal index
	return -1;	
};

long HtlJSONReader::FindNextNWSMatch(const std::string & strInput, size_t intStartPos, char chr, bool & blnMatch)
{
   long intCursor, lngStringSize;
   //skip through primary white space and illegal characters
   lngStringSize = strInput.size();
   intCursor = intStartPos;
   while (intCursor < lngStringSize)
   {
      if (int(strInput[intCursor]) > 32)
      {
         //32 or less is the white space characters of ASCII
         //then non-white space legal character found

         if (strInput[intCursor] == chr)
         {
            blnMatch = true;
         }
         else {
            blnMatch = false;
         }
         return intCursor;
      }
      else {
         //increment the counter
         intCursor++;
      };
   };
   //no white space found return illegal index
   return -1;
};
//!Find Next White Space Character
long HtlJSONReader::FindNextWSChar(const std::string & strInput,size_t intStartPos)
{
	long intCursor,lngStringSize;
	//cycle until white space found
	lngStringSize = strInput.size();
	intCursor = intStartPos;
		
	while(intCursor < lngStringSize)
	{
		if( (int)(strInput[intCursor]) <= 32)
		{
			//32 or less is the white space characters of ASCII
			//then whitespace found
			return intCursor;
		}else{
			//not whitespace increment counter
			intCursor++;
		};
	};
	//no white space found return illegal index
	return -1;
};

//!Find Next Quotation " or '
long HtlJSONReader::FindNextQuote(const std::string & strInput,size_t intStartPos)
{
	long intCursor, lngStringSize;
	//cycle until white space found
	lngStringSize = strInput.size();
	intCursor = intStartPos;
	while(intCursor < lngStringSize)
	{
		if((strInput[intCursor] == '\'')||(strInput[intCursor] == '\"'))
		{//then search character
			return intCursor;
		}else{
			//not search character
			intCursor++;
		};
	};
	//no white space found return illegal index
	return -1;
};

//!Find Next White Space Character
long HtlJSONReader::FindNextChar(const std::string & strInput,size_t intStartPos, char chrFind)
{

	long intCursor, lngStringSize;
	//cycle until white space found
	lngStringSize = strInput.size();
	intCursor = intStartPos;
	while(intCursor < lngStringSize)
	{
		if(strInput[intCursor] == chrFind)
		{//then search character
			return intCursor;
		}else{
			//not search character
			intCursor++;
		};
	};
	//no white space found return illegal index
	return -1;
};


//XML SERIALIZATION AND DE-SERIALIZATION METHODS///////////
//!Expand the XML string value of the element
int HtlJSONReader::LoadJSONTree(HtlElement * ptrCurrTop,const std::string & strInput, HtlElementIndex & objCurrElementIndex)
{
	//find the starting index for the element
	int intReturn;
	//now that we found the starting position, hand it off to the XMLReader
	//Clear();
	intReturn = LoadJSONElement(ptrCurrTop, strInput, objCurrElementIndex);
	return intReturn;
};

int HtlJSONReader::LoadJSONTree(HtlElement * ptrCurrTop, std::istream & strStreamInput)
{
	int intTemp, intReturn;
	std::string strFileInput;
	intReturn = 1;
	//LOAD THE FILE STREAM INTO A STRING THEN LOAD THE XML
	if(!strStreamInput)
	{
		cout << "While opening a file an error is encountered" << endl;
	}else{
		//cout << "File is successfully opened" << endl;
	}

	std::stringstream buffer;
	buffer << strStreamInput.rdbuf();
	strFileInput = buffer.str(); 

	HtlElementIndex objCurrElementIndex;
	intTemp = LoadJSONTree(ptrCurrTop,strFileInput,objCurrElementIndex);
	if(intTemp < 0){intReturn = -1;};

	return intReturn;
};
int HtlJSONReader::LoadJSONTree(HtlElement * ptrCurrTop, std::ifstream & strStreamInput)
{
	int intTemp, intReturn;
	std::string strFileInput;
	intReturn = 1;
	//LOAD THE FILE STREAM INTO A STRING THEN LOAD THE XML
	if(!strStreamInput)
	{
		cout << "While opening a file an error is encountered" << endl;
	}else{
		//cout << "File is successfully opened" << endl;
	}

	std::stringstream buffer;
	buffer << strStreamInput.rdbuf();
	strFileInput = buffer.str(); 

	HtlElementIndex objCurrElementIndex;
	intTemp = LoadJSONTree(ptrCurrTop, strFileInput,objCurrElementIndex);
	if(intTemp < 0){intReturn = -1;};

	return intReturn;
};

//!Update the indexes
//int HtlJSONReader::UpdateIndexes(void)
//{
//	int i, intNumAttributes,j,intNumSubElements;
//	intNumAttributes = m_arrPtrAttributes.size();
//	if(m_blnRootNode)
//	{
//		Set_intLevel(0);
//	}
//	for(i = 0; i < intNumAttributes; i++)
//	{
//		m_arrPtrAttributes.at(i)->Set_intLevel(Get_intLevel());
//		m_arrPtrAttributes.at(i)->Set_intRow(i);
//	};
//	intNumSubElements = m_arrPtrSubElements.size();
//	for(j = 0; j < intNumSubElements;j++)
//	{
//		m_arrPtrSubElements.at(j)->Set_intLevel(Get_intLevel() + 1);
//		m_arrPtrSubElements.at(j)->Set_intRow(j);
//		m_arrPtrSubElements.at(j)->UpdateIndexes();
//	};
//	return 1;
//};
