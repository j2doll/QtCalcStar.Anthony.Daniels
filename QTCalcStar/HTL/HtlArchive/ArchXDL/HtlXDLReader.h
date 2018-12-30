/*
**	This file is part of the XMLStar.
**	This software was developed by:
**	
**  Anthony Daniels, Mi Yan
**	The University of Michigan
**	Department of Naval Architecture & Marine Engineering
**	Department of Computer Science
**
**  XMLStar is free software: you can redistribute it and/or modify
**  it under the terms of the GNU Lesser General Public License as published by
**  the Free Software Foundation, either version 3 of the License, or
**  (at your option) any later version.
**
**  The United States of America Department of Defense has unlimited 
**	usage, redistribution, and modification rights to XMLStar.
**
**  XMLStar is distributed in the hope that it will be useful,
**  but WITHOUT ANY WARRANTY; without even the implied warranty of
**  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
**  GNU Lesser General Public License for more details.
**
**  You should have received a copy of the GNU Lesser General Public License
**  along with XMLStar.  If not, see <http://www.gnu.org/licenses/>.
*/

#pragma once
#ifndef HTL_XDLREADER_H
#define HTL_XDLREADER_H

#include "..\..\modHtlGlobal.h"

using namespace std;
namespace HTL{

	typedef std::pair<std::string,std::string> XMLNameValuePair;


	class HtlElement;
	class HtlAttribute;
	class HtlComment;
	class HtlProcess;

	class HTL_DLLAPI HtlXDLReader
	{
	public:

		//!PUBLIC CONSTRUCTORS & DESTRUCTOR/////////////////////////////
		HtlXDLReader(void);
		virtual ~HtlXDLReader(void);
		//!PUBLIC OPERATOR OVERLOADS

		//XML SERIALIZATION AND DE-SERIALIZATION METHODS///////////
		//!Expand the XDL string value of the element
		virtual int LoadXDLTree(HtlElement * ptrCurrTop, const std::string & strInput, HtlElementIndex & objCurrElementIndex);
		virtual int LoadXDLTree(HtlElement * ptrCurrTop, std::istream & strStreamInput);
		virtual int LoadXDLTree(HtlElement * ptrCurrTop, std::ifstream & strStreamInput);

		//!Load the XDL Element based on the current starting location of the index
		int LoadXDLElement(HtlElement * ptrElement, const std::string & strInput, HtlElementIndex & objCurrElementIndex);

	protected:
		//!Load the Tag to the Element Name
		int LoadOpenTag(HtlElement * ptrElement, const std::string & strInput, HtlElementIndex & objCurrElementIndex, bool & blnNullElementReturn);
		//!Load the Tag to the Element Name
		int LoadCloseTag(HtlElement * ptrElement, const std::string & strInput, HtlElementIndex & objCurrElementIndex);
		//!Load the Attributes into the Element
		int	LoadAttributes(HtlElement * ptrElement, const std::string & strInput, HtlElementIndex & objCurrElementIndex);
		//!Load the Value into the Element
		int	LoadValue(HtlElement * ptrElement, const std::string & strInput, HtlElementIndex & objCurrElementIndex);

		//!Load the Comments, Processes, and Sub Elements
		int	LoadSubNodes(HtlElement * ptrElement, const std::string & strInput, HtlElementIndex & objCurrElementIndex);
		//!Load a Sub Element
		int	LoadSubElement(HtlElement * ptrElement, const std::string & strInput, HtlElementIndex & objCurrElementIndex);

		//!Load the Comments into the Element
		int	LoadComment(HtlElement * ptrElement, const std::string & strInput, HtlElementIndex & objCurrElementIndex);

		//!Load the Comments into the Element
		int	LoadProcess(HtlElement * ptrElement, const std::string & strInput, HtlElementIndex & objCurrElementIndex);
		//!Load the Tag to the Element Name
		int LoadProcessOpenTag(HtlElement * ptrElement, const std::string & strInput, HtlElementIndex & objCurrElementIndex);
		//!Load the Attributes into the Element
		int	LoadProcessAttributes(HtlElement * ptrElement, const std::string & strInput, HtlElementIndex & objCurrElementIndex);
		//!Load the Value into the Element
		int	LoadProcessValue(HtlElement * ptrElement, const std::string & strInput, HtlElementIndex & objCurrElementIndex);
		
		//!Find Next < character indicating a start tag
		long FindNextTagStart(const std::string & strInput,size_t intStartPos, bool & blnCloseTag);
		//!Find Next Non-White Space Legal Character
		long FindNextNWSLChar(const std::string & strInput,size_t intStartPos); 
		//!Find Next Non-White Space Character
		long FindNextNWSChar(const std::string & strInput,size_t intStartPos);
		//!Find Next White Space Character
		long FindNextWSChar(const std::string & strInput,size_t intStartPos);
		//!Find Next Quotation " or '
		long FindNextQuote(const std::string & strInput,size_t intStartPos);
		//!Find Next Character
		long FindNextChar(const std::string & strInput,size_t intStartPos, char chrFind);

		bool IsNodeComment(const std::string & strInput,size_t intStartPos);
		bool IsNodeProcess(const std::string & strInput,size_t intStartPos);
		bool IsNodeElement(const std::string & strInput,size_t intStartPos);

	private:

	HtlComment * m_ptrCurrComment;
	HtlProcess * m_ptrCurrProcess;
	std::string m_str;
	size_t m_intStringSize;
	};//end XMLWriter class definition

};//end namespace XMLStar
#endif