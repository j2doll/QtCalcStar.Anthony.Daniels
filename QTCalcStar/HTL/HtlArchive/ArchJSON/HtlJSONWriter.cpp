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

#include ".\HtlJSONWriter.h"
#include "..\HtlElement.h"
#include "..\HtlAttribute.h"
#include "..\HtlComment.h"
#include "..\HtlProcess.h"

namespace HTL
{

	//PUBLIC CONSTRUCTORS & DESTRUCTOR/////////////////////////////
	HtlJSONWriter::HtlJSONWriter(void)
	{
		m_intNumIndentSpaces = 3;
		return;
	};

	HtlJSONWriter::~HtlJSONWriter(void)
	{
		m_str.clear();
	};


	//Set pointer to the element
	void HtlJSONWriter::Set_ptrElement(HtlElement * ptrElement)
	{
		if(ptrElement)
		{
			m_ptrElement = ptrElement;
		}else{
			m_ptrElement = NULL;
		};
	};
	//Get the pointer to the element
	HtlElement * HtlJSONWriter::Get_ptrElement(void)
	{
		return m_ptrElement;
	};

	//!Sets the number of indent spaces per level
	void HtlJSONWriter::Set_intNumIndentSpaces(unsigned int intNumIndentSpaces)
	{
		if(intNumIndentSpaces > 10)
		{
			//maximum of 10 space indent
			m_intNumIndentSpaces = 10;
		}else{
			m_intNumIndentSpaces = intNumIndentSpaces;
		};
		return;
	};
	//!Gets the number of indent spaces per level
	unsigned int HtlJSONWriter::Get_intNumIndentSpaces(void)
	{
		return m_intNumIndentSpaces;
	};

	//!Save the XML Element based with or without formatting
	int HtlJSONWriter::SaveJSONElement(HtlElement * ptrElement, std::string & strOutput, int elemIndex, int elemTotal, bool blnWithFormatting)
	{	
		/*
		//SAVE ELEMENT
		START THE OPENTAG
		SERIALIZE THE ATTRIBUTES INTO THE OPEN TAG
		CLOSE THE OPEN TAG
		WRITE THE VALUE
		WRITE THE COMMENTS
		WRITE THE PROCESSES
		WRITE THE SUB ELEMENTS
		WRITE THE CLOSE TAG
		*/
		int i,intNumAttributes,intNumComments,intNumProcesses,intNumSubElements;
		int intTemp, intReturn;
		bool blnNullNode = false;
		bool blnRootNode = false;
		bool blnInline = false;
		intReturn = 1;
		blnRootNode = ptrElement->IsRootNode();
		blnNullNode = ptrElement->IsNullNode();
		intNumAttributes = ptrElement->CountAttributes();
		intNumComments = ptrElement->CountComments();
		intNumProcesses = ptrElement->CountProcesses();
		intNumSubElements = ptrElement->CountSubElements();
		if((intNumComments <= 0)&&(intNumProcesses <= 0)&&(intNumSubElements <= 0))
		{
			//then treat as an inline HtlElement
			blnInline = true;
		};


		//START THE OPENTAG///////////////////////////////////////////////
		intTemp = WriteOpenTag(ptrElement,strOutput,blnWithFormatting);
		if(intTemp < 0){intReturn = -1;};

		if(blnNullNode)
		{
			return 1;
		};

		if(blnInline)
		{
			//then treat as an inline XML Element
			intTemp = WriteValueInline(ptrElement,strOutput,false);
			if(intTemp < 0){intReturn = -1;};
			//write the close tag inline
         if (elemIndex < elemTotal - 1)
         {
            intTemp = WriteSeperator(ptrElement, strOutput, false);
            if (intTemp < 0) { intReturn = -1; };
         }
			return intReturn;
		}else{

			//WRITE THE SUB ELEMENTS/////////////////////////////////////////////
			if(intNumSubElements > 0)
			{
            //write a carriage return if necessary for formatting
            if (blnWithFormatting) { strOutput += '\n'; };
            //write the open tag indent
            if (blnWithFormatting) { WriteIndent(strOutput, ptrElement->Get_intLevel()); };
            strOutput += "{\n";

				//write a carriage return if necessary for formatting
				for(i = 0; i < intNumSubElements;i++)
				{
					intTemp = SaveJSONElement(ptrElement->GetSubElement(i),strOutput, i, intNumSubElements, blnWithFormatting);
					if(intTemp < 0){intReturn = -1;};

				};

            //write a carriage return if necessary for formatting
            if (blnWithFormatting) { strOutput += '\n'; };
            //write the open tag indent
            if (blnWithFormatting) { WriteIndent(strOutput, ptrElement->Get_intLevel()); };
            strOutput += "}\n";

			};

			//WRITE THE CLOSE TAG 
         if (elemIndex < elemTotal - 1)
         {
            //write the open tag indent
            if (blnWithFormatting) { WriteIndent(strOutput, ptrElement->Get_intLevel()); };
            intTemp = WriteSeperator(ptrElement, strOutput, blnWithFormatting);
            if (intTemp < 0) { intReturn = -1; };
         }

			return intReturn;
		};//end simple inline element check
		return intReturn;
	};

	void HtlJSONWriter::WriteIndent(std::string & strOutput, unsigned int intLevel)
	{
		unsigned int i, j;
		for(i = 0; i < intLevel;i++)
		{
			for(j = 0; j < m_intNumIndentSpaces; j++)
			{
				strOutput.append(" ");
			};
		};
		return;
	};


	//write the open tag including all attributes
	int HtlJSONWriter::WriteOpenTag(HtlElement * ptrElement, std::string & strOutput, bool blnWithFormatting)
	{
		int intNumAttributes;
		bool blnNullNode = false;
		bool blnRootNode = false;
		blnRootNode = ptrElement->IsRootNode();
		blnNullNode = ptrElement->IsNullNode();
		intNumAttributes = ptrElement->CountAttributes();

		//if not the root node add a carriage return before starting the tag
		if((blnRootNode == false)&&(blnWithFormatting)){strOutput += '\n';};
		//write the open tag indent
		if(blnWithFormatting){WriteIndent(strOutput,ptrElement->Get_intLevel());};
		//write the open tag
		strOutput += '\"';
		strOutput += ptrElement->Get_strName();
      strOutput += "\": ";
		//append the attributes
		//THERE ARE NO ATTRIBUTES IN JSON
		//SKIPPING ATTRIBUTE WRITING

		if(blnNullNode){strOutput += "{}";};
		//write the end open tag
		
		return 1;
	};

   //write the value for the element
   int HtlJSONWriter::WriteValueInline(HtlElement * ptrElement, std::string & strOutput, bool blnWithFormatting)
   {
      std::string strTemp, strDecodedValue;
      strTemp = ptrElement->Get_strValue();
      bool blnIsAllWhiteSpace = IsAllWhiteSpace(strTemp);
      if ((blnIsAllWhiteSpace == false) && (strTemp.size() > 0))
      {
         //write a carriage return if necessary for formatting
         if (blnWithFormatting) { strOutput += '\n'; };
         //write the open tag indent
         if (blnWithFormatting) { WriteIndent(strOutput, ptrElement->Get_intLevel()); };
         strOutput += '\"';
         strOutput += ptrElement->Get_strValue();
         strOutput += '\"';
      }
      else if (strTemp.size() <= 0)
      {
         strOutput += '\"';
         strOutput += '\"';
      };


      return 1;
   };

	//write the value for the element
	int HtlJSONWriter::WriteValue(HtlElement * ptrElement, std::string & strOutput, bool blnWithFormatting)
	{
		std::string strTemp, strDecodedValue;
		strTemp = ptrElement->Get_strValue();
		bool blnIsAllWhiteSpace = IsAllWhiteSpace(strTemp);
		if( (blnIsAllWhiteSpace == false) && (strTemp.size() > 0) )
		{
			//write a carriage return if necessary for formatting
			if(blnWithFormatting){strOutput += '\n';};
			//write the open tag indent
			if(blnWithFormatting){WriteIndent(strOutput,ptrElement->Get_intLevel());};
         strOutput += '\"';
			strOutput +=  ptrElement->Get_strValue();
         strOutput += '\"';
		};
		return 1;
	};

	//write the node close tag
	int HtlJSONWriter::WriteSeperator(HtlElement * ptrElement, std::string & strOutput, bool blnWithFormatting)
	{
      //write the open tag
      strOutput += ",";
      return 1;
	};

	//!checks to see if the string is all whitespace
	bool HtlJSONWriter::IsAllWhiteSpace(const std::string & strInput)
	{
		bool blnNotWhiteSpace = false;
		size_t i, intNumChars;
		intNumChars = strInput.size();
		if(intNumChars > 0)
		{
			for(i = 0; i < intNumChars; i++)
			{
				if( (int)(strInput[i]) > 32)
				{
					//32 or less is the white space characters of ASCII
					return false;
				};
			};
			//made it all the way through with white space characters only
			return true;
		}else{
			//nothing in string, return as if whitespace
			return true;
		};
	}; 




//!Update the indexes
int HtlJSONWriter::UpdateIndexes(HtlElement * ptrCurrTop)
{
	int i, intNumAttributes,j,intNumSubElements;
	intNumAttributes = ptrCurrTop->CountAttributes();

	ptrCurrTop->Set_intLevel(0);

	for(i = 0; i < intNumAttributes; i++)
	{
		ptrCurrTop->GetAttribute(i)->Set_intLevel(ptrCurrTop->Get_intLevel());
		ptrCurrTop->GetAttribute(i)->Set_intRow(i);
	};
	intNumSubElements = ptrCurrTop->CountSubElements();
	for(j = 0; j < intNumSubElements;j++)
	{
		ptrCurrTop->GetSubElement(j)->Set_intLevel(ptrCurrTop->Get_intLevel() + 1);
		ptrCurrTop->GetSubElement(j)->Set_intRow(j);
		ptrCurrTop->GetSubElement(j)->UpdateIndexes();
	};
	return 1;
};

int HtlJSONWriter::SaveJSONTree(HtlElement * ptrCurrTop,std::string & strOutput,bool blnWithFormatting)
{
	int intReturn = 0;
	//hand it off to the XMLWriter
	this->UpdateIndexes(ptrCurrTop);
   strOutput += "{\n";
   intReturn = this->SaveJSONElement(ptrCurrTop, strOutput, 0, 1, blnWithFormatting);
   strOutput += "\n}";
	return intReturn;
};

int HtlJSONWriter::SaveJSONTree(HtlElement * ptrCurrTop, std::ostream & strStreamOut,bool blnWithFormatting)
{
	int intReturn = 0;
	//hand it off to the XMLWriter
	std::string strFileOutPut;

	intReturn = SaveJSONTree(ptrCurrTop, strFileOutPut, blnWithFormatting);
	strStreamOut << strFileOutPut;
	return NULL;
};

int HtlJSONWriter::SaveJSONTree(HtlElement * ptrCurrTop, std::ofstream & strStreamOut,bool blnWithFormatting)
{
	int intReturn = 0;
	//hand it off to the XMLWriter
	std::string strFileOutPut;

	intReturn = SaveJSONTree(ptrCurrTop, strFileOutPut, blnWithFormatting);
	strStreamOut << strFileOutPut;
	return NULL;
};



};//end namespace HTL