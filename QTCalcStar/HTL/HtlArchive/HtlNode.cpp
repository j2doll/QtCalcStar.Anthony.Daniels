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
#include ".\HtlNode.h"

using namespace HTL;
#pragma warning(push)
#pragma warning (disable : 4996 ) /* sprintf, sscanf unsafe */
#pragma warning (disable : 4477 ) /* sprintf, sscanf deprecated warning */
#pragma warning (disable : 4478 ) /* sprintf, sscanf deprecated warning */
#pragma warning (disable : 4018 ) /* warning C4018: '<': signed/unsigned mismatch */

//PUBLIC CONSTRUCTORS & DESTRUCTOR/////////////////////////////
HtlNode::HtlNode(void)
{	
	m_objType = HTL_STRING;
	m_ptrParentNode = NULL;
	m_objIndex.Zero();
	return;
};
HtlNode::HtlNode(HtlNode * ptrParentNode)
{
	m_objType = HTL_STRING;
	if(ptrParentNode)
	{
		m_ptrParentNode = ptrParentNode;
		//Set_intLevel(ptrParentNode->Get_intLevel() + 1);
	}else{
		m_ptrParentNode = NULL;
		m_objIndex.Zero();
	}

	return;
};
HtlNode::HtlNode(HtlNode & rhs)
{
	//self assignment check
	if(this == &rhs)
		return;
	//perform the copy construction
	m_ptrParentNode = rhs.Get_ptrParentNode();
	m_objIndex = rhs.Get_objIndex();
	m_strName = rhs.Get_strName();
	m_strValue = rhs.Get_strValue();
	m_objType = rhs.Get_objType();
	return;
};
HtlNode::~HtlNode(void)
{
	m_ptrParentNode = NULL;
	m_strName.clear();
	m_strValue.clear();
};
//PUBLIC OPERATOR OVERLOADS
HtlNode & HtlNode::operator = (HtlNode & rhs)
{	
	//self assignment check
	if(this == &rhs)
		return *this;
	//do the copy assignment
	m_ptrParentNode = rhs.Get_ptrParentNode();
	m_objIndex = rhs.Get_objIndex();

	m_strName = rhs.Get_strName();
	m_strValue = rhs.Get_strValue();
	m_objType = rhs.Get_objType();
	return *this;
};


void HtlNode::Set_intRow(long lngRow){m_objIndex.m_lngX = lngRow;return;};
void HtlNode::Set_intColumn(long lngCol){m_objIndex.m_lngY = lngCol;return;};
void HtlNode::Set_intLevel(long lngLevel){m_objIndex.m_lngZ = lngLevel;return;};

long HtlNode::Get_intRow(void){return m_objIndex.m_lngX;};
long HtlNode::Get_intColumn(void){return m_objIndex.m_lngY;};
long HtlNode::Get_intLevel(void){return m_objIndex.m_lngZ;};





#pragma warning (disable : 4996 ) /* sprintf, sscanf unsafe warning */
//!Set and Get for Node Value
void HtlNode::Set_strValue(const std::string & strValue)
{
	m_strValue = strValue;
	EncodeSpecialChars(m_strValue);
	m_objType = HTL_STRING;
};

void HtlNode::Set_strValue(const char * ptrCharString)
{
	m_strValue = ptrCharString;
	EncodeSpecialChars(m_strValue);
	m_objType = HTL_STRING;
};

void HtlNode::Set_strValue(bool blnVal)
{
	if(blnVal)
	{
		m_strValue = '1';
	}else{
		m_strValue = '0';
	};
	m_objType = CPP_BOOL;
};

void HtlNode::Set_strValue(short shrtVal)
{
	try{
		char chrBuf[256];
		sprintf(chrBuf,"%d",shrtVal);
		m_strValue = chrBuf;
		m_objType = CPP_SHORT;
	}catch(...){
		return;
	}
};

void HtlNode::Set_strValue(unsigned short ushrtVal)
{
	try{
		char chrBuf[256];
		sprintf(chrBuf,"%u",ushrtVal);
		m_strValue = chrBuf;
		m_objType = CPP_USHORT;
	}catch(...){
		return;
	}
};

void HtlNode::Set_strValue(int intVal)
{
	try{
		char chrBuf[256];
		sprintf(chrBuf,"%d",intVal);
		m_strValue = chrBuf;
		m_objType = CPP_INT;
	}catch(...){
		return;
	}
};

void HtlNode::Set_strValue(unsigned int uint)
{
	try{
		char chrBuf[256];
		sprintf(chrBuf,"%u",uint);
		m_strValue = chrBuf;
		m_objType = CPP_UINT;
	}catch(...){
		return;
	}
};

void HtlNode::Set_strValue(long lngVal)
{
	try{
		char chrBuf[256];
		sprintf(chrBuf,"%ld",lngVal);
		m_strValue = chrBuf;
		m_objType = CPP_LONG;
	}catch(...){
		return;
	}
};

void HtlNode::Set_strValue(unsigned long ulngVal)
{
	try{
		char chrBuf[256];
		sprintf(chrBuf,"%lu",ulngVal);
		m_strValue = chrBuf;
		m_objType = CPP_ULONG;
	}catch(...){
		return;
	}
};

void HtlNode::Set_strValue(float sngVal)
{
	try{
		char chrBuf[256];
		sprintf(chrBuf,"%f",sngVal);
		m_strValue = chrBuf;
		m_objType = CPP_FLOAT;
	}catch(...){
		return;
	}
};

void HtlNode::Set_strValue(double dblVal)
{
	try{
		char chrBuf[256];
		sprintf(chrBuf,"%lf",dblVal);
		m_strValue = chrBuf;
		m_objType = CPP_DOUBLE;
	}catch(...){
		return;
	}
};

void HtlNode::Set_strValue(char chrVal)
{
	try{
		char chrBuf[256];
		sprintf(chrBuf,"%s",chrVal);
		m_strValue = chrBuf;
		EncodeSpecialChars(m_strValue);
		m_objType = CPP_CHAR;
	}catch(...){
		return;
	}
};

void HtlNode::Set_strValue(unsigned char uchrVal)
{
	try{
		char chrBuf[256];
		sprintf(chrBuf,"%s",uchrVal);
		m_strValue = chrBuf;
		EncodeSpecialChars(m_strValue);
		m_objType = CPP_UCHAR;
	}catch(...){
		return;
	}
};


std::string HtlNode::Get_strValue(void)
{
	return m_strValue;
};

void HtlNode::Get_strValue(bool & blnValReturn)
{
	if((m_objType == CPP_BOOL)||(m_objType == HTL_STRING))
	{
		if(m_strValue == "1")
		{
			//return true
			blnValReturn = true;
		}else{
			//return false
			blnValReturn = false;
		};
	}else{
		//not a boolean attribute type
		//return default value
		blnValReturn = false;
	};
	return;
};

void HtlNode::Get_strValue(short & shrtValReturn)
{		
	short shrtTemp;
	const char * chrBuffer;
	if((m_objType == CPP_SHORT)||(m_objType == HTL_STRING))
	{
		chrBuffer = m_strValue.c_str();
		sscanf(m_strValue.c_str(),"%hd",&shrtTemp);
		shrtValReturn = shrtTemp;
	}else{
		//not a boolean attribute type
		//return default value
		shrtValReturn = 0;
	};
	return;
};

void HtlNode::Get_strValue(unsigned short & ushrtValReturn)
{		
	unsigned short ushrtTemp;
	const char * chrBuffer;
	if((m_objType == CPP_USHORT)||(m_objType == HTL_STRING))
	{
		chrBuffer = m_strValue.c_str();
		sscanf(chrBuffer,"%hu",&ushrtTemp);
		ushrtValReturn = ushrtTemp;
	}else{
		//not a boolean attribute type
		//return default value
		ushrtValReturn = 0;
	};
	return;
};

void HtlNode::Get_strValue(int & intValReturn)
{		
	int intTemp;
	const char * chrBuffer;
	if((m_objType == CPP_INT)||(m_objType == HTL_STRING))
	{
		chrBuffer = m_strValue.c_str();
		sscanf(chrBuffer,"%d",&intTemp);
		intValReturn = intTemp;
	}else{
		//not a boolean attribute type
		//return default value
		intValReturn = 0;
	};
	return;
};

void HtlNode::Get_strValue(unsigned int & uintValReturn)
{		
	unsigned int uintTemp;
	const char * chrBuffer;
	if((m_objType == CPP_UINT)||(m_objType == HTL_STRING))
	{
		chrBuffer = m_strValue.c_str();
		sscanf(chrBuffer,"%u",&uintTemp);
		uintValReturn = uintTemp;
	}else{
		//not a boolean attribute type
		//return default value
		uintValReturn = 0;
	};
	return;
};

void HtlNode::Get_strValue(long & lngValReturn)
{		
	long lngTemp;
	const char * chrBuffer;
	if((m_objType == CPP_LONG)||(m_objType == HTL_STRING))
	{
		chrBuffer = m_strValue.c_str();
		sscanf(chrBuffer,"%ld",&lngTemp);
		lngValReturn = lngTemp;
	}else{
		//not a boolean attribute type
		//return default value
		lngValReturn = 0;
	};
	return;
};

void HtlNode::Get_strValue(unsigned long & ulngValReturn)
{
	unsigned long ulngTemp;
	const char * chrBuffer;
	if((m_objType == CPP_ULONG)||(m_objType == HTL_STRING))
	{
		chrBuffer = m_strValue.c_str();
		sscanf(chrBuffer,"%lu",&ulngTemp);
		ulngValReturn = ulngTemp;
	}else{
		//not a boolean attribute type
		//return default value
		ulngValReturn = 0;
	};
	return;
};

void HtlNode::Get_strValue(float & sngValReturn)
{
	float sngTemp;
	const char * chrBuffer;
	if((m_objType == CPP_FLOAT)||(m_objType == HTL_STRING))
	{

		chrBuffer = m_strValue.c_str();
		sscanf(chrBuffer,"%f",&sngTemp);
		sngValReturn = sngTemp;
	}else{
		//not a boolean attribute type
		//return default value
		sngValReturn = 0.0f;
	};
	return;
};

void HtlNode::Get_strValue(double & dblValReturn)
{
	double dblTemp;
	const char * chrBuffer;
	if((m_objType == CPP_DOUBLE)||(m_objType == HTL_STRING))
	{
		chrBuffer = m_strValue.c_str();
		sscanf(chrBuffer,"%lf",&dblTemp);
		dblValReturn = dblTemp;
	}else{
		//not a boolean attribute type
		//return default value
		dblValReturn = 0.0f;
	};
	return;
};

void HtlNode::Get_strValue(char & chrValReturn)
{	
	char chrTemp;
	const char * chrBuffer;
	if((m_objType == CPP_CHAR)||(m_objType == HTL_STRING))
	{
		std::string strTemp = m_strValue;
		DecodeSpecialChars(strTemp);

		chrBuffer = m_strValue.c_str();
		sscanf(chrBuffer,"%c",&chrTemp);
		chrValReturn = chrTemp;
	}else{
		//not a boolean attribute type
		//return default value
		chrValReturn = NULL;
	};
	return;
};

void HtlNode::Get_strValue(unsigned char & uchrValReturn)
{	
	unsigned char uchrTemp;
	const char * chrBuffer;
	if((m_objType == CPP_UCHAR)||(m_objType == HTL_STRING))
	{		
		std::string strTemp = m_strValue;
		DecodeSpecialChars(strTemp);

		chrBuffer = m_strValue.c_str();
		sscanf(chrBuffer,"%c",&uchrTemp);
		uchrValReturn = uchrTemp;
	}else{
		//not a boolean attribute type
		//return default value
		uchrValReturn = NULL;
	};
	return;
};

void HtlNode::Get_strValue(std::string & strValReturn)
{	
	strValReturn = m_strValue;
};

void HtlNode::Get_strValueDecode(std::string & strValReturn)
{
	strValReturn = m_strValue;
	DecodeSpecialChars(strValReturn);
};



//!Encoding special characters to Htl compatible format
void HtlNode::EncodeSpecialChars(std::string & strToEncode)
{	
	size_t intPos;
	if(strToEncode.size() <= 0)
	{
		return;
	};
	//CHECK FOR '&' CHARACTER IN STRING///////////////////////
	intPos = 0;
	while(intPos < strToEncode.size())
	{
		intPos = strToEncode.find('&',intPos);
		if((intPos >= 0) && (intPos < strToEncode.size()) )
		{
			bool blnAlreadyEncoded = false;
			//check to see if already encoded
			if(strToEncode.substr(intPos,5) == "&amp;"){blnAlreadyEncoded = true;};
			if(strToEncode.substr(intPos,4) == "&lt;"){blnAlreadyEncoded = true;};
			if(strToEncode.substr(intPos,4) == "&gt;"){blnAlreadyEncoded = true;};
			if(strToEncode.substr(intPos,6) == "&quot;"){blnAlreadyEncoded = true;};
			if(strToEncode.substr(intPos,6) == "&apos;"){blnAlreadyEncoded = true;};
			if(strToEncode.substr(intPos,4) == "&eq;"){blnAlreadyEncoded = true;};

			if(!blnAlreadyEncoded)
			{
				//then match found, AND NOT ENCODED make the substitution
				strToEncode.replace(intPos,1,"&amp;");
			};
			//increment so don't double count
			++intPos;

		}else{
			//not found set to end of string to kick out of while loop
			intPos = strToEncode.size() + 1;
		};
	};

	//CHECK FOR '<' CHARACTER IN STRING///////////////////////
	intPos = 0;
	while(intPos < strToEncode.size())
	{
		intPos = strToEncode.find('<');
		if((intPos >= 0) && (intPos < strToEncode.size()) )
		{
			//then match found, make the substitution
			strToEncode.replace(intPos,1,"&lt;");
			//increment so don't double count
			++intPos;
		}else{
			//not found set to end of string to kick out of while loop
			intPos = strToEncode.size() + 1;
		};
	}
	//CHECK FOR '>' CHARACTER IN STRING///////////////////////
	intPos = 0;
	while(intPos < strToEncode.size())
	{
		intPos = strToEncode.find('>');
		if((intPos >= 0) && (intPos < strToEncode.size()) )
		{
			//then match found, make the substitution
			strToEncode.replace(intPos,1,"&gt;");
			//increment so don't double count
			++intPos;
		}else{
			//not found set to end of string to kick out of while loop
			intPos = strToEncode.size() + 1;
		};
	};
	//CHECK FOR '"' CHARACTER IN STRING///////////////////////
	intPos = 0;
	while(intPos < strToEncode.size())
	{
		intPos = strToEncode.find('\"');
		if((intPos >= 0) && (intPos < strToEncode.size()) )
		{
			//then match found, make the substitution
			strToEncode.replace(intPos,1,"&quot;");
			//increment so don't double count
			++intPos;
		}else{
			//not found set to end of string to kick out of while loop
			intPos = strToEncode.size() + 1;
		};
	};
	//CHECK FOR ''' CHARACTER IN STRING///////////////////////
	intPos = 0;
	while(intPos < strToEncode.size())
	{
		intPos = strToEncode.find('\'',intPos);
		if((intPos >= 0) && (intPos < strToEncode.size()) )
		{
			//then match found, make the substitution
			strToEncode.replace(intPos,1,"&apos;");
			//increment so don't double count
			++intPos;
		}else{
			//not found set to end of string to kick out of while loop
			intPos = strToEncode.size() + 1;
		};
	};

	//CHECK FOR '=' CHARACTER IN STRING///////////////////////
	intPos = 0;
	while(intPos < strToEncode.size())
	{
		intPos = strToEncode.find('=',intPos);
		if((intPos >= 0) && (intPos < strToEncode.size()) )
		{
			//then match found, make the substitution
			strToEncode.replace(intPos,1,"&eq;");
			//increment so don't double count
			++intPos;
		}else{
			//not found set to end of string to kick out of while loop
			intPos = strToEncode.size() + 1;
		};
	};
	return;
};
//!Decode special characters from Htl compatible format;
void HtlNode::DecodeSpecialChars(std::string & strToDecode)
{
	size_t intPos;
	if(strToDecode.size() <= 0)
	{
		return;
	};
	//CHECK FOR '<' CHARACTER IN STRING///////////////////////
	intPos = 0;
	while(intPos < strToDecode.size())
	{
		intPos = strToDecode.find("&lt;",intPos);
		if((intPos >= 0) && (intPos < strToDecode.size()) )
		{
			//then match found, make the substitution
			strToDecode.replace(intPos,4,"<");//char(60) is <
		}else{
			//not found set to end of string to kick out of while loop
			intPos = strToDecode.size() + 1;
		};
	}
	//CHECK FOR '>' CHARACTER IN STRING///////////////////////
	intPos = 0;
	while(intPos < strToDecode.size())
	{
		intPos = strToDecode.find("&gt;",intPos);
		if((intPos >= 0) && (intPos < strToDecode.size()) )
		{
			//then match found, make the substitution
			strToDecode.replace(intPos,4,">");//char(62) is >
		}else{
			//not found set to end of string to kick out of while loop
			intPos = strToDecode.size() + 1;
		};
	};
	//CHECK FOR '"' CHARACTER IN STRING///////////////////////
	intPos = 0;
	while(intPos < strToDecode.size())
	{
		intPos = strToDecode.find("&quot;",intPos);
		if((intPos >= 0) && (intPos < strToDecode.size()) )
		{
			//then match found, make the substitution
			strToDecode.replace(intPos,6,"\"");//char(38) is "
		}else{
			//not found set to end of string to kick out of while loop
			intPos = strToDecode.size() + 1;
		};
	};
	//CHECK FOR ''' CHARACTER IN STRING///////////////////////
	intPos = 0;
	while(intPos < strToDecode.size())
	{
		intPos = strToDecode.find("&apos;",intPos);
		if((intPos >= 0) && (intPos < strToDecode.size()) )
		{
			//then match found, make the substitution
			strToDecode.replace(intPos,6,"\'");//char(39) is '
		}else{
			//not found set to end of string to kick out of while loop
			intPos = strToDecode.size() + 1;
		};
	};
	//CHECK FOR '&' CHARACTER IN STRING///////////////////////
	intPos = 0;
	while(intPos < strToDecode.size())
	{
		intPos = strToDecode.find("&amp;",intPos);
		if((intPos >= 0) && (intPos < strToDecode.size()) )
		{
			//then match found, make the substitution
			strToDecode.replace(intPos,5,"&");//char(38) is &
		}else{
			//not found set to end of string to kick out of while loop
			intPos = strToDecode.size() + 1;
		};
	};
	//CHECK FOR '=' CHARACTER IN STRING///////////////////////
	intPos = 0;
	while(intPos < strToDecode.size())
	{
		intPos = strToDecode.find("&eq;",intPos);
		if((intPos >= 0) && (intPos < strToDecode.size()) )
		{
			//then match found, make the substitution
			strToDecode.replace(intPos,4,"=");//char(38) is =
		}else{
			//not found set to end of string to kick out of while loop
			intPos = strToDecode.size() + 1;
		};
	};
	return;
};