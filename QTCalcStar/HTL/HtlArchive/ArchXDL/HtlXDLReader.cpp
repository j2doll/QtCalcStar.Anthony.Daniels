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


#include ".\HtlXDLReader.h"
#include "..\HtlElement.h"
#include "..\HtlAttribute.h"
#include "..\HtlComment.h"
#include "..\HtlProcess.h"

using namespace HTL;


#pragma warning(push)
#pragma warning (disable : 4018 ) /* warning C4018: '<': signed/unsigned mismatch */

//PUBLIC CONSTRUCTORS & DESTRUCTOR/////////////////////////////
HtlXDLReader::HtlXDLReader(void)
{
	
	return;
};

HtlXDLReader::~HtlXDLReader(void)
{
	m_str.clear();
	
	return;
};

//Load the XML Element based on the current starting location of the index
int HtlXDLReader::LoadXDLElement(HtlElement * ptrElement, const std::string & strInput, HtlElementIndex & objCurrElementIndex)
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
      //DON'T THROW EXCEPTION HERE BECAUSE WANT TO KEEP GOING
      //AND READ AS MUCH OF THE FILE AS POSSIBLE
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
	//THERE ARE NO ATTRIBUTES IN XDL
	//intTemp = LoadAttributes(ptrElement,strInput,objCurrElementIndex);
	if(intTemp < 0){intReturn = -1;};
	//IF ELEMENT IS NOT A NULL TERMINATED ELEMENT, THEN LOAD THE REST
	if(blnNullElement == false)
	{
		//LOAD THE VALUE FOR THE ELEMENT
		intTemp = LoadValue(ptrElement,strInput,objCurrElementIndex);
		if(intTemp < 0){intReturn = -1;};
		//LOAD ALL OF THE SUB ELEMENTS
		intTemp = LoadSubNodes(ptrElement,strInput,objCurrElementIndex);
		if(intTemp < 0){intReturn = -1;};
	}else{
		//then null element artificially set the end close tag beginning and end to the open tag end position
		objCurrElementIndex.m_intCloseTagStartPos = objCurrElementIndex.m_intOpenTagEndPos;
		objCurrElementIndex.m_intCloseTagEndPos = objCurrElementIndex.m_intOpenTagEndPos;
	}

	return intReturn;

};



//Load the Tag to the Element Name
int HtlXDLReader::LoadOpenTag(HtlElement * ptrElement, const std::string & strInput, HtlElementIndex & objCurrElementIndex, bool & blnNullElementReturn)
{
	int intTemp;
	size_t intCursor, intPosTag, intOpenPos, intClosePos;
	std::string strTagName;
	HtlArchNodeType enumNodeType = NODE;
	blnNullElementReturn = false;
	//find the open Tag
	intCursor = objCurrElementIndex.m_intOpenTagStartPos;
	while(intCursor < strInput.size())
	{
		intOpenPos = FindNextChar(strInput,intCursor,'<');
		if( (intOpenPos < strInput.size())&&
			(intOpenPos >= 0) )
		{//then valid open tag. check special cases first
			//check for comment
			if(IsNodeComment(strInput,intOpenPos))
			{
				enumNodeType = COMMENT;
				HtlElementIndex objCommentIndex;
				objCommentIndex.m_intOpenTagStartPos =intOpenPos; 
				intTemp = LoadComment(ptrElement,strInput,objCommentIndex);
				if(intTemp < 0)
				{//then error
					intCursor = intOpenPos;
				}else{
					intCursor = objCommentIndex.m_intOpenTagEndPos;
				}
			}else if(IsNodeProcess(strInput,intOpenPos)){
				enumNodeType = PROCESS;
				HtlElementIndex objProcessIndex;
				objProcessIndex.m_intOpenTagStartPos =intOpenPos; 
				intTemp = LoadProcess(ptrElement,strInput,objProcessIndex);
				if(intTemp < 0)
				{//then error
					intCursor = intOpenPos;
				}else{
					intCursor = objProcessIndex.m_intOpenTagEndPos;
				}
			}else if(IsNodeElement(strInput,intOpenPos)){
				enumNodeType = ELEMENT;
				objCurrElementIndex.m_intOpenTagStartPos = intOpenPos;
				//process as normal element opening tag with attributes
				//find the close tag position
				intClosePos = FindNextChar(strInput,intOpenPos,'>');
				if((intClosePos < strInput.size())&&
					(intClosePos > 0) )
				{//then valid close tag position

					objCurrElementIndex.m_intOpenTagEndPos = intClosePos;
					//check to see if NULL ELEMENT
					if(strInput[intClosePos-1] == '/')
					{
						blnNullElementReturn = true;
					}else{
						blnNullElementReturn = false;
					}
				}else{
					//no close tag position found
					return -1;
				};
				//extract the tag name and set it

				intPosTag = FindNextWSChar(strInput,intOpenPos);
				if((intPosTag < intClosePos) && (intPosTag >= 0))
				{	//then tag end position is inside the close bracket >
					//use the white space location to calculate the tag length
					objCurrElementIndex.m_intTagLength = ((intPosTag - 1) - (intOpenPos));
				}else{
					//then no space found inside close bracket
					//use the close bracket to calculate the length, dependent on whether or not it is null terminal
					if(blnNullElementReturn)
					{
						objCurrElementIndex.m_intTagLength = ((intClosePos - 2) - (intOpenPos));
					}else{
						objCurrElementIndex.m_intTagLength = ((intClosePos - 1) - (intOpenPos));
					}
				};
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
int HtlXDLReader::LoadCloseTag(HtlElement * ptrElement, const std::string & strInput, HtlElementIndex & objCurrElementIndex)
{
	return -1;
};

//Load the Attributes into the Element
int	HtlXDLReader::LoadAttributes(HtlElement * ptrElement, const std::string & strInput, HtlElementIndex & objCurrElementIndex)
{
	//makes the assumption that the open tag has been established.
	//take the tag string minus open and close characters
	//Parse the attributes into a name,value pair vector stripping the "" or '' around the value and the = sign
	//Cycle through the pair vector to create the attributes
	std::string strOpenTag;
	long intCursor, intNameBegin, intNameEnd, intEqualLoc, intOpenQuote, intCloseQuote;
	size_t i, intNumAttribs;
	HtlAttribute * ptrCurrAttrib = NULL;
	XMLNameValuePair objNVPTemp;
	std::vector<XMLNameValuePair> arrObjAttribNVPs;
	//start at the tag end position
	intCursor = objCurrElementIndex.m_intOpenTagStartPos + objCurrElementIndex.m_intTagLength ;
	while(intCursor < objCurrElementIndex.m_intOpenTagEndPos)
	{

		//now we have reached the beginning of something to read, assume attribute name = "value"
		intNameBegin = FindNextNWSLChar(strInput,intCursor + 1);
		if( (intNameBegin >= 0)&&
			(intNameBegin < objCurrElementIndex.m_intOpenTagEndPos)&&
			(intNameBegin < strInput.size()) )
		{//then valid, continue extracting name
			//locate the equal separator
			intEqualLoc = FindNextChar(strInput,intNameBegin,'=');
			if(intEqualLoc < 0)
			{//return error
				return -1;
			}

			intNameEnd = FindNextWSChar(strInput,intNameBegin);
			if(intNameEnd < 0)
			{//return error
				return -1;
			}
			if(intNameEnd > intEqualLoc)
			{
				//then no white space present in name, set it to the equal sign
				intNameEnd = intEqualLoc - 1;
			}
			//extract the name
			objNVPTemp.first = strInput.substr(intNameBegin,(intNameEnd - intNameBegin + 1));

			intOpenQuote = FindNextQuote(strInput,intEqualLoc);
			if(intOpenQuote < 0)
			{//return error
				return -1;
			}
			if(intOpenQuote+1 >= strInput.size())
			{	//then at end of string
				return 0;
			}
			intCloseQuote = FindNextQuote(strInput,intOpenQuote+1);
			if(intCloseQuote < 0)
			{//return error
				return -1;
			}
			if((intCloseQuote - 1) >= (intOpenQuote + 1) )
			{//then valid value string indexes, extract the string value for the attribute
				objNVPTemp.second = strInput.substr((intOpenQuote + 1),((intCloseQuote -1) - (intOpenQuote)));
				arrObjAttribNVPs.push_back(objNVPTemp);
				intCursor = intCloseQuote;
			}else if((intCloseQuote - intOpenQuote - 1) == 0){
				//then null value attribute still make the attribute pair
				arrObjAttribNVPs.push_back(objNVPTemp);
				intCursor = intCloseQuote;
			}else{
				intCursor = intCloseQuote;
			}
		}else{
			//end of search region nothing left
		}
		//increment the cursor
		++intCursor;
	}
	//done parsing create the attributes
	intNumAttribs = arrObjAttribNVPs.size();
	for(i = 0; i < intNumAttribs;i++)
	{
		ptrCurrAttrib = ptrElement->AddAttribute();
		if(ptrCurrAttrib)
		{
			ptrCurrAttrib->Set_strName(arrObjAttribNVPs.at(i).first);
			ptrCurrAttrib->Set_strValue(arrObjAttribNVPs.at(i).second);
		};
	};//end for loop through attributes
	//successfully loaded the attributes for the object
	return 1;
};


//Load the Attributes into the Element
int	HtlXDLReader::LoadValue(HtlElement * ptrElement, const std::string & strInput, HtlElementIndex & objCurrElementIndex)
{
	//makes the assumption that the open tag has been established.
	//take the tag string minus open and close characters
	//Parse the attributes into a name,value pair vector stripping the "" or '' around the value and the = sign
	//Cycle through the pair vector to create the attributes
	std::string strValTemp;
	size_t intCursor,intOpenTag;
	HtlAttribute * ptrCurrAttrib = NULL;
	XMLNameValuePair objNVPTemp;
	std::vector<XMLNameValuePair> arrObjAttribNVPs;

	//start at the tag end position
	intCursor = objCurrElementIndex.m_intOpenTagEndPos;
	intOpenTag = FindNextChar(strInput,intCursor,'<');

	if((intOpenTag) > (objCurrElementIndex.m_intOpenTagEndPos + 1))
	{
		strValTemp = strInput.substr((objCurrElementIndex.m_intOpenTagEndPos + 1), ((intOpenTag -1 ) - (objCurrElementIndex.m_intOpenTagEndPos)) );
		ptrElement->Set_strValue(strValTemp);
		return 1;
	}else{
		//never found a value return null
		return 0; 
	};
};

//Load the Attributes into the Element
int	HtlXDLReader::LoadSubNodes(HtlElement * ptrElement, const std::string & strInput, HtlElementIndex & objCurrElementIndex)
{
	//makes the assumption that the open tag has been established.
	//take the tag string minus open and close characters
	//Parse the attributes into a name,value pair vector stripping the "" or '' around the value and the = sign
	//Cycle through the pair vector to create the attributes
	int intTemp;
	std::string strValTemp;
	size_t intCursor, intOpenTag, lngStringSize;
	bool blnIsComment, blnIsProcess, blnIsElement, blnCloseTagFound;
    blnCloseTagFound = false;
	blnIsComment = false;
	blnIsProcess = false;
	blnIsElement = false;

	lngStringSize = strInput.size();
	intCursor = objCurrElementIndex.m_intOpenTagEndPos;

	while((!blnCloseTagFound)&&(intCursor < lngStringSize))
	{
		//Set node type to generic node
		HtlArchNodeType enumCurrNodeType = NODE;
		//find next open tag
		intOpenTag = FindNextTagStart(strInput,intCursor,blnCloseTagFound);

		if(blnCloseTagFound == false)
		{//then check to see what type of tag this is.
			//check to see if it is a comment
			blnIsComment = IsNodeComment(strInput,intOpenTag);
			if(blnIsComment)
			{
				enumCurrNodeType = COMMENT;
				HtlElementIndex objCommentIndex;
				objCommentIndex.m_intOpenTagStartPos = intOpenTag;
				//CODE TO LOAD THE COMMENT NODE/////
				//TO BE ADDED///////
				intTemp = LoadComment(ptrElement,strInput,objCommentIndex);
				if(intTemp < 0)
				{//then loading comment failed
					++intCursor;
				}else{
					intCursor = objCommentIndex.m_intOpenTagEndPos;
				};
			};//end comment check
			//check to see if it is a process and if the node type is not set yet
			blnIsProcess = IsNodeProcess(strInput,intOpenTag);
			if((blnIsProcess)&&(enumCurrNodeType == NODE))
			{//then safe to check as a process
				enumCurrNodeType = PROCESS;
				HtlElementIndex objProcessIndex;
				objProcessIndex.m_intOpenTagStartPos = intOpenTag;
				//CODE TO LOAD THE PROCESS NODE/////
				//TO BE ADDED///////
				intTemp = LoadProcess(ptrElement,strInput,objProcessIndex);
				if(intTemp < 0)
				{//then loading process failed
					++intCursor;
				}else{
					intCursor = objProcessIndex.m_intOpenTagEndPos;
				};
			};//end process check
			//treat it as a sub element
			blnIsElement = IsNodeElement(strInput,intOpenTag);
			if((blnIsElement)&&(enumCurrNodeType == NODE))
			{
				enumCurrNodeType = ELEMENT;
				HtlElementIndex objSubElementIndex;
				objSubElementIndex.m_intOpenTagStartPos = intOpenTag;
				//CODE TO LOAD THE SUB-ELEMENT NODE/////
				//TO BE ADDED///////
				intTemp = LoadSubElement(ptrElement,strInput,objSubElementIndex);
				if(intTemp < 0)
				{//then loading process failed
					++intCursor;
				}else{
					intCursor = objSubElementIndex.m_intCloseTagEndPos;
					if(intCursor < objSubElementIndex.m_intOpenTagStartPos)
					{	
						// then illegal close tag, could be null element,
						//set to end of open tag
						intCursor = objSubElementIndex.m_intOpenTagEndPos;
					};
				};
			};//end sub element
			//safety advance code
			if( (blnIsComment == false) && (blnIsProcess == false) && (blnIsElement == false) )
			{//nothing found advance cursor so don't get stuck in infinite loop
				++intCursor;
			};
		}else{
			//close tag found, set the cursor to the current location and continue forward
			objCurrElementIndex.m_intCloseTagStartPos = intOpenTag;
			objCurrElementIndex.m_intCloseTagEndPos = FindNextChar(strInput,intOpenTag,'>');
			if(objCurrElementIndex.m_intCloseTagEndPos < 0)
			{//illegal index, character not found
				objCurrElementIndex.m_intCloseTagEndPos = (strInput.size() - 1);
			};
			return 1;
		};//end close tag check
	};//end while loop through
	return 1;
};

//!Load the Sub Element into the Element
int	HtlXDLReader::LoadSubElement(HtlElement * ptrElement, const std::string & strInput, HtlElementIndex & objCurrElementIndex)
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
		intTemp = LoadXDLElement(ptrNewSubElement, strInput,objCurrElementIndex);
		if(intTemp < 0){intReturn = -1;};
	}
	return intReturn;
};
//!Load the Comment into the Element
int	HtlXDLReader::LoadComment(HtlElement * ptrElement, const std::string & strInput, HtlElementIndex & objCurrElementIndex)
{
	std::string strValTemp;
	int intReturn = 1;
	size_t intStartPos, intEndPos;
	intStartPos = objCurrElementIndex.m_intOpenTagStartPos;
	if((intStartPos + 3) < strInput.size())
	{//then safe to check as a comment
		if((strInput[intStartPos] == '<')&&
			(strInput[intStartPos+1] == '!')&&
			(strInput[intStartPos+2] == '-')&&
			(strInput[intStartPos+3] == '-'))
		{//then comment node
			intReturn = 1;
		}else{
			return 0;
		}//end check
	};//end safety check
	//scan for the close tag
	intEndPos = FindNextChar(strInput,intStartPos,'>');
	if((intEndPos > 0) && (intEndPos > intStartPos) && (intEndPos - 2 > 0) )
	{
		//check the trailing dashes
		if( (strInput[intEndPos] == '>')&&
			(strInput[intEndPos-1] == '-')&&
			(strInput[intEndPos-2] == '-') )
		{	//then valid end open tag for comment.
			objCurrElementIndex.m_intOpenTagEndPos = intEndPos;
			intReturn = 1;
		}else{
			//invalid close comment, abort comment read
			return -1;
		}
	}else{
		return -1;
	}//end valid end tag check
	if(intReturn > 0)
	{//then OK to grab the inbetween value string
		if((intStartPos + 4) < (intEndPos - 3))
		{
			HtlComment* ptrNewComment = ptrElement->AddComment();
			strValTemp = strInput.substr((intStartPos + 4), ((intEndPos - 3) - (intStartPos + 3)) );
			if(ptrNewComment)
			{
				ptrNewComment->Set_strValue(strValTemp);
				return 1;
			}else{
				return 0;
			}//end valid new comment check
		}else{
			return -1;
		}//end valid tags check

	}//end intReturn check
	return intReturn;
};
//!Load the Process into the Element
int	HtlXDLReader::LoadProcess(HtlElement * ptrElement, const std::string & strInput, HtlElementIndex & objCurrElementIndex)
{
	std::string strValTemp;
	int intReturn = 1;
	size_t intStartPos, intEndPos;
	intStartPos = objCurrElementIndex.m_intOpenTagStartPos;
	if((intStartPos + 1) < strInput.size())
	{//then safe to check as a comment
		if((strInput[intStartPos] == '<')&&
			(strInput[intStartPos+1] == '?') )
		{//then comment node
			intReturn = 1;
		}else{
			return 0;
		}//end check
	};//end safety check
	//scan for the close tag
	intEndPos = FindNextChar(strInput,intStartPos,'>');
	if((intEndPos > 0) && (intEndPos > intStartPos) && (intEndPos - 1 > 0) )
	{
		//check the trailing dashes
		if( (strInput[intEndPos] == '>')&&
			(strInput[intEndPos-1] == '?') )
		{	//then valid end open tag for comment.
			objCurrElementIndex.m_intOpenTagEndPos = intEndPos;
			intReturn = 1;
		}else{
			//invalid close comment, abort comment read
			return -1;
		}
	}else{
		return -1;
	}//end valid end tag check
	if(intReturn > 0)
	{//then OK to grab the inbetween value string
		if((intStartPos + 2) < (intEndPos - 2))
		{
			m_ptrCurrProcess = ptrElement->AddProcess();
			intReturn = LoadProcessOpenTag(ptrElement,strInput,objCurrElementIndex);
			intReturn = LoadProcessAttributes(ptrElement,strInput,objCurrElementIndex);
			intReturn = LoadProcessValue(ptrElement,strInput,objCurrElementIndex);
		}else{
			return -1;
		}//end valid tags check

	}//end intReturn check
	return intReturn;
};

//!Load the Tag to the Process Target Name
int HtlXDLReader::LoadProcessOpenTag(HtlElement * ptrElement, const std::string & strInput, HtlElementIndex & objCurrElementIndex)
{
	int intReturn;
	size_t intCursor, intPosTag, intStartPos, intEndPos;
	std::string strTagName;
	HtlArchNodeType enumNodeType = NODE;
	//find the open Tag
	intCursor = objCurrElementIndex.m_intOpenTagStartPos;
	while(intCursor < strInput.size())
	{
		intStartPos = FindNextChar(strInput,intCursor,'<');
		if( ((intStartPos + 1) < strInput.size())&& (intStartPos >= 0) ) 
		{//then safe to check as a comment
			if((strInput[intStartPos] == '<')&&
				(strInput[intStartPos+1] == '?') )
			{//then comment node
				intReturn = 1;
			}else{
				return 0;
			}//end check
		};//end safety check
		//scan for the close tag
		intEndPos = FindNextChar(strInput,intStartPos,'>');
		if((intEndPos > 0) && (intEndPos > intStartPos) && (intEndPos - 1 > 0) )
		{
			//check the trailing dashes
			if( (strInput[intEndPos] == '>')&&
				(strInput[intEndPos-1] == '?') )
			{	//then valid end open tag for comment.
				objCurrElementIndex.m_intOpenTagEndPos = intEndPos;
				intReturn = 1;
			}else{
				//invalid close comment, abort comment read
				return -1;
			}
		}else{
			return -1;
		}//end valid end tag check

		//extract the tag name and set it

		intPosTag = FindNextWSChar(strInput,intStartPos);
		if((intPosTag < intEndPos) && (intPosTag >= 0))
		{	//then tag end position is inside the close bracket >
			//use the white space location to calculate the tag length
			objCurrElementIndex.m_intTagLength = ((intPosTag - 1) - (intStartPos+1));
		}else{
			//then no space found inside close bracket
			//use the close bracket to calculate the length, dependent on whether or not it is null terminal
			objCurrElementIndex.m_intTagLength = ((intEndPos - 2) - (intStartPos+1));

		};
		//extract the tag sub string
		strTagName = strInput.substr(objCurrElementIndex.m_intOpenTagStartPos + 2, objCurrElementIndex.m_intTagLength);
		//Set the tag name for this element
		m_ptrCurrProcess->Set_strName(strTagName);
		return 1;
	};//end while loop through the string

	return 0;


};
//!Load the Attributes into the Process
int	HtlXDLReader::LoadProcessAttributes(HtlElement * ptrElement,const std::string & strInput, HtlElementIndex & objCurrElementIndex)
{
	//makes the assumption that the open tag has been established.
	//take the tag string minus open and close characters
	//Parse the attributes into a name,value pair vector stripping the "" or '' around the value and the = sign
	//Cycle through the pair vector to create the attributes
	std::string strOpenTag;
	long intCursor, intNameBegin, intNameEnd, intEqualLoc, intOpenQuote, intCloseQuote;
	size_t i, intNumAttribs;
	HtlAttribute * ptrCurrAttrib = NULL;
	XMLNameValuePair objNVPTemp;
	std::vector<XMLNameValuePair> arrObjAttribNVPs;
	//start at the tag end position
	intCursor = objCurrElementIndex.m_intOpenTagStartPos + 1 + objCurrElementIndex.m_intTagLength ;
	while(intCursor < objCurrElementIndex.m_intOpenTagEndPos)
	{

		//now we have reached the beginning of something to read, assume attribute name = "value"
		intNameBegin = FindNextNWSLChar(strInput,intCursor + 1);
		if( (intNameBegin >= 0)&&
			(intNameBegin < objCurrElementIndex.m_intOpenTagEndPos)&&
			(intNameBegin < strInput.size()) )
		{//then valid, continue extracting name
			//locate the equal separator
			intEqualLoc = FindNextChar(strInput,intNameBegin,'=');
			if(intEqualLoc < 0)
			{//return error
				return -1;
			}

			intNameEnd = FindNextWSChar(strInput,intNameBegin);
			if(intNameEnd < 0)
			{//return error
				return -1;
			}
			if(intNameEnd > intEqualLoc)
			{
				//then no white space present in name, set it to the equal sign
				intNameEnd = intEqualLoc - 1;
			}
			//extract the name
			objNVPTemp.first = strInput.substr(intNameBegin,(intNameEnd - intNameBegin)+1);

			intOpenQuote = FindNextQuote(strInput,intEqualLoc);
			if(intOpenQuote < 0)
			{//return error
				return -1;
			}
			if(intOpenQuote+1 >= strInput.size())
			{	//then at end of string
				return 0;
			}
			intCloseQuote = FindNextQuote(strInput,intOpenQuote+1);
			if(intCloseQuote < 0)
			{//return error
				return -1;
			}
			if((intCloseQuote - 1) >= (intOpenQuote + 1) )
			{//then valid value string indexes, extract the string value for the attribute
				objNVPTemp.second = strInput.substr((intOpenQuote + 1),((intCloseQuote -1) - (intOpenQuote)));
				arrObjAttribNVPs.push_back(objNVPTemp);
				intCursor = intCloseQuote;
			}else if((intCloseQuote - intOpenQuote - 1) == 0){
				//then null value attribute still make the attribute pair
				arrObjAttribNVPs.push_back(objNVPTemp);
				intCursor = intCloseQuote;
			}else{
				intCursor = intCloseQuote;
			}
		}else{
			//end of search region nothing left
		}
		//increment the cursor
		intCursor++;
	}
	//done parsing create the attributes
	intNumAttribs = arrObjAttribNVPs.size();
	for(i = 0; i < intNumAttribs;i++)
	{
		ptrCurrAttrib = m_ptrCurrProcess->AddAttribute();
		if(ptrCurrAttrib)
		{
			ptrCurrAttrib->Set_strName(arrObjAttribNVPs.at(i).first);
			ptrCurrAttrib->Set_strValue(arrObjAttribNVPs.at(i).second);
		};
	};//end for loop through attributes
	//successfully loaded the attributes for the object
	return 1;
};
//!Load the Value into the Element
int	HtlXDLReader::LoadProcessValue(HtlElement * ptrElement,const std::string & strInput, HtlElementIndex & objCurrElementIndex)
{

	return 0;
};

//!Find Next < character indicating a start tag
long HtlXDLReader::FindNextTagStart(const std::string & strInput,size_t intStartPos, bool & blnCloseTag)
{
	size_t intCursor, lngStringSize;
	//skip through primary white space and illegal characters
	lngStringSize = strInput.size();
	intCursor = intStartPos;
	while(intCursor < lngStringSize)
	{
		if( strInput[intCursor] == '<')
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
long HtlXDLReader::FindNextNWSLChar(const std::string & strInput,size_t intStartPos)
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
long HtlXDLReader::FindNextNWSChar(const std::string & strInput,size_t intStartPos)
{
	long intCursor, lngStringSize;
	//skip through primary white space and illegal characters
	lngStringSize = strInput.size();
	intCursor = intStartPos;
	while(intCursor < lngStringSize)
	{
		if( int(strInput[intCursor]) >= 32)
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
//!Find Next White Space Character
long HtlXDLReader::FindNextWSChar(const std::string & strInput,size_t intStartPos)
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
long HtlXDLReader::FindNextQuote(const std::string & strInput,size_t intStartPos)
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
long HtlXDLReader::FindNextChar(const std::string & strInput,size_t intStartPos, char chrFind)
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

bool HtlXDLReader::IsNodeComment(const std::string & strInput,size_t intStartPos)
{
	if((intStartPos + 3) < strInput.size())
	{//then safe to check as a comment
		if((strInput[intStartPos] == '<')&&
			(strInput[intStartPos+1] == '!')&&
			(strInput[intStartPos+2] == '-')&&
			(strInput[intStartPos+3] == '-'))
		{//then comment node
			return true;
		}else{
			return false;
		}//end check
	};//end safety check
	return false;
};

bool HtlXDLReader::IsNodeProcess(const std::string & strInput,size_t intStartPos)
{
	if((intStartPos + 1) < strInput.size())
	{//then safe to check as a process
		if((strInput[intStartPos] == '<')&&
			(strInput[intStartPos+1] == '?'))
		{//then process node
			return true;
		}else{
			return false;
		};
	};//end process check
	return false;
};

bool HtlXDLReader::IsNodeElement(const std::string & strInput,size_t intStartPos)
{
	if((intStartPos + 1) < strInput.size())
	{//then safe to check as a process
		if( (strInput[intStartPos] == '<')&&
			(strInput[intStartPos+1] != '?')&&
			(strInput[intStartPos+1] != '!')&&
			(strInput[intStartPos+1] != '\\')&&
			(strInput[intStartPos+1] != '/')&&			
			(strInput[intStartPos+1] != '<')&&
			(strInput[intStartPos+1] != '>') )			
		{
			//then is a valid element
			return true;
		}else{
			//not a valid element
			return false;
		};
	};//end safety check
	return false;
};



//XML SERIALIZATION AND DE-SERIALIZATION METHODS///////////
//!Expand the XML string value of the element
int HtlXDLReader::LoadXDLTree(HtlElement * ptrCurrTop,const std::string & strInput, HtlElementIndex & objCurrElementIndex)
{
	//find the starting index for the element
	int intReturn;
	//now that we found the starting position, hand it off to the XMLReader
	//Clear();
	intReturn = LoadXDLElement(ptrCurrTop, strInput, objCurrElementIndex);
	return intReturn;
};

int HtlXDLReader::LoadXDLTree(HtlElement * ptrCurrTop, std::istream & strStreamInput)
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
	intTemp = LoadXDLTree(ptrCurrTop,strFileInput,objCurrElementIndex);
	if(intTemp < 0){intReturn = -1;};

	return intReturn;
};
int HtlXDLReader::LoadXDLTree(HtlElement * ptrCurrTop, std::ifstream & strStreamInput)
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
	intTemp = LoadXDLTree(ptrCurrTop, strFileInput,objCurrElementIndex);
	if(intTemp < 0){intReturn = -1;};

	return intReturn;
};

//!Update the indexes
//int HtlXDLReader::UpdateIndexes(void)
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
