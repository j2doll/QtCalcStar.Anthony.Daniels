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

#include ".\HtlDocument.h"

using namespace HTL;

//PUBLIC CONSTRUCTORS & DESTRUCTOR/////////////////////////////
HtlDocument::HtlDocument(void)
: HtlElement()
{
	//HtlNode Initialization/////////////
	Set_objNodeType(DOCUMENT);
	//HtlElement Initialization//////////
	//NONE
	//HtlDocuement Initialization////////
	//!Htl Document Prolog Properties included in output
	m_blnIncludePrologue = true;
	//!Htl Prolog string version number for the 
	m_strVersion = "1.0";
	//!Htl Prolog string encoding format for the 
	m_strEncoding = "UTF-8";
	//!Htl Prolog standalone mode
	m_strStandalone = "yes";
	//!Htl Document Type Format Tag included in output
	m_blnIncludeDocType = true;
	//!Htl Document Type Format Tag 
	m_strDocType.clear();

	return;
};
HtlDocument::HtlDocument(HtlNode * ptrParentNode)
: HtlElement(ptrParentNode)
{
	//HtlNode Initialization/////////////
	Set_objNodeType(DOCUMENT);
	//HtlElement Initialization//////////
	//NONE
	//HtlDocuement Initialization////////
	//!Htl Document Prolog Properties included in output
	m_blnIncludePrologue = true;
	//!Htl Prolog string version number for the 
	m_strVersion = "1.0";
	//!Htl Prolog string encoding format for the 
	m_strEncoding = "UTF-8";
	//!Htl Prolog standalone mode
	m_strStandalone = "yes";
	//!Htl Document Type Format Tag included in output
	m_blnIncludeDocType = true;
	//!Htl Document Type Format Tag 
	m_strDocType.clear();
	return;
};
HtlDocument::HtlDocument(HtlDocument & rhs)
{
	//self assignment check
	if(this == &rhs)
		return;
	//HtlNode Copy Construction

	//HtlAttribute Copy Construction

	return;
};
HtlDocument::~HtlDocument(void)
{

};
//PUBLIC OPERATOR OVERLOADS
HtlDocument & HtlDocument::operator = (HtlDocument & rhs)
{	
	//self assignment check
	if(this == &rhs)
		return *this;
	//HtlNode Assignment Operation

	//HtlAttribute Assignment Operation


	return *this;
};


//Set and Get for Include Prologue
void HtlDocument::Set_blnIncludePrologue(bool blnIncludePrologue)
{
	m_blnIncludePrologue = blnIncludePrologue;
};

bool HtlDocument::Get_blnIncludePrologue(void) const
{
	return m_blnIncludePrologue;
};

//Set and Get for Document Htl Version Number
void HtlDocument::Set_strVersion(std::string strVersion)
{
	m_strVersion = strVersion;
};

std::string HtlDocument::Get_strVersion(void) const
{
	return m_strVersion;
};

//Set and Get for Document Encoding 
void HtlDocument::Set_strEncoding(std::string strEncoding)
{
	m_strEncoding = strEncoding;
};

std::string HtlDocument::Get_strEncoding(void) const
{
	return m_strEncoding;
};

//Set and Get for Include Standalone
void HtlDocument::Set_blnStandalone(bool blnStandalone)
{
	if(blnStandalone)
	{
		m_strStandalone = "yes";
	}else{
		m_strStandalone = "no";
	};
	return;
};

bool HtlDocument::Get_blnStandalone(void) const
{
	if(m_strStandalone == "yes")
	{
		return true;
	}else{
		return false;
	};
};

//Set and Get for Include Document Type Statement
void HtlDocument::Set_blnIncludeDocType(bool m_blnIncludeDocType)
{
	m_blnIncludeDocType = m_blnIncludeDocType;
};

bool HtlDocument::Get_blnIncludeDocType(void) const
{
	return m_blnIncludeDocType;
};

//Set and Get for Document Type Statement 
void HtlDocument::Set_strDocType(std::string strDocType)
{
	m_strDocType = strDocType;
};

std::string HtlDocument::Get_strDocType(void) const
{
	return m_strDocType;
};


//Htl SERIALIZATION AND DE-SERIALIZATION METHODS///////////
//!Expand the Htl string value of the element
int HtlDocument::LoadHtlTree(std::string & strInput)
{
	return NULL;
};

int HtlDocument::LoadHtlTree(std::istream & strStreamInput)
{
	return NULL;
};

int HtlDocument::LoadHtlTree(std::ifstream & strStreamInput)
{
	return NULL;
};

int HtlDocument::SaveHtlTree(std::string & strOutput,bool blnWithFormatting)
{
	return NULL;
};

int HtlDocument::SaveHtlTree(std::ostream & strStreamOut,bool blnWithFormatting)
{
	return NULL;
};

int HtlDocument::SaveHtlTree(std::ofstream & strStreamOut,bool blnWithFormatting)
{
	return NULL;
};

//std::string HtlDocument::Get_strValue(bool blnWithFormatting)
//{
//	std::string strOutput;
//	return strOutput;
//};
