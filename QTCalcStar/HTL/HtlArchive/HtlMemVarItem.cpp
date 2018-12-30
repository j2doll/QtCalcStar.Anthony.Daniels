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

#include ".\HtlElement.h"
#include ".\HtlMemVarItem.h"

using namespace HTL;

//Functions for setting XML Type Info Attributes
HtlElement* HTL::GetOrMakeElement(HtlElement * ptrCurrNode,const std::string & strMemVarName)
{
	HtlElement* ptrNewNode = ptrCurrNode->GetSubElement(strMemVarName);
	if(!ptrNewNode)
	{
		//doesn't exist make a new one
		ptrNewNode = ptrCurrNode->AddSubElement();
		ptrNewNode->Set_strName(strMemVarName);
	}
	//return desired node pointer
	return ptrNewNode;
};


int HTL::SetAttribTypeInfo(HtlElement * ptrCurrNode,std::string & strType, std::string & strBaseType)
{
	HtlAttribute * ptrCurrAttrib = NULL;

	//Reset the type information
	ptrCurrAttrib = ptrCurrNode->GetAttribute(HTL_strTYPE);
	if(ptrCurrAttrib)
	{
		ptrCurrAttrib->Set_strValue(strType);
	}else{
		//need to create it first
		ptrCurrAttrib = ptrCurrNode->AddAttribute();
		if(ptrCurrAttrib)
		{
			ptrCurrAttrib->Set_strName(HTL_strTYPE);
			ptrCurrAttrib->Set_strValue(strType);
		};
	};
	//reset base type information
	ptrCurrAttrib = ptrCurrNode->GetAttribute(HTL_strBASETYPE);
	if(ptrCurrAttrib)
	{
		ptrCurrAttrib->Set_strValue(strBaseType);
	}else{
		//need to create it first
		ptrCurrAttrib = ptrCurrNode->AddAttribute();
		if(ptrCurrAttrib)
		{
			ptrCurrAttrib->Set_strName(HTL_strBASETYPE);
			ptrCurrAttrib->Set_strValue(strBaseType);
		};
	};
	return 1;
};

int HTL::SetAttribTypeInfo(HtlElement * ptrCurrNode,std::string & strType, std::string & strBaseType,std::string & strSubObjType, std::string & strSubObjBaseType,std::string & strIntNumDim)
{
	HtlAttribute * ptrCurrAttrib = NULL;

	//Reset the type information
	ptrCurrAttrib = ptrCurrNode->GetAttribute(HTL_strTYPE);
	if(ptrCurrAttrib)
	{
		ptrCurrAttrib->Set_strValue(strType);
	}else{
		//need to create it first
		ptrCurrAttrib = ptrCurrNode->AddAttribute();
		if(ptrCurrAttrib)
		{
			ptrCurrAttrib->Set_strName(HTL_strTYPE);
			ptrCurrAttrib->Set_strValue(strType);
		};
	};
	//reset base type information
	ptrCurrAttrib = ptrCurrNode->GetAttribute(HTL_strBASETYPE);
	if(ptrCurrAttrib)
	{
		ptrCurrAttrib->Set_strValue(strBaseType);
	}else{
		//need to create it first
		ptrCurrAttrib = ptrCurrNode->AddAttribute();
		if(ptrCurrAttrib)
		{
			ptrCurrAttrib->Set_strName(HTL_strBASETYPE);
			ptrCurrAttrib->Set_strValue(strBaseType);
		};
	};
	//reset sub object type information
	ptrCurrAttrib = ptrCurrNode->GetAttribute(HTL_strSUBOBJTYPE);
	if(ptrCurrAttrib)
	{
		ptrCurrAttrib->Set_strValue(strSubObjType);
	}else{
		//need to create it first
		ptrCurrAttrib = ptrCurrNode->AddAttribute();
		if(ptrCurrAttrib)
		{
			ptrCurrAttrib->Set_strName(HTL_strSUBOBJTYPE);
			ptrCurrAttrib->Set_strValue(strSubObjType);
		};
	};
	//reset sub object base type information
	ptrCurrAttrib = ptrCurrNode->GetAttribute(HTL_strSUBOBJBASETYPE);
	if(ptrCurrAttrib)
	{
		ptrCurrAttrib->Set_strValue(strSubObjBaseType);
	}else{
		//need to create it first
		ptrCurrAttrib = ptrCurrNode->AddAttribute();
		if(ptrCurrAttrib)
		{
			ptrCurrAttrib->Set_strName(HTL_strSUBOBJBASETYPE);
			ptrCurrAttrib->Set_strValue(strSubObjBaseType);
		};
	};
	//reset intNumDimension information
	ptrCurrAttrib = ptrCurrNode->GetAttribute(HTL_strINTNUMDIM);
	if(ptrCurrAttrib)
	{
		ptrCurrAttrib->Set_strValue(strIntNumDim);
	}else{
		//need to create it first
		ptrCurrAttrib = ptrCurrNode->AddAttribute();
		if(ptrCurrAttrib)
		{
			ptrCurrAttrib->Set_strName(HTL_strINTNUMDIM);
			ptrCurrAttrib->Set_strValue(strIntNumDim);
		};
	};
	return 1;
};




int HTL::SetAttribSubTypeInfo(HtlElement * ptrCurrNode, std::string & strSubObjType, std::string & strSubObjBaseType,std::string & strIntNumDim)
{
	HtlAttribute * ptrCurrAttrib = NULL;


	//reset sub object type information
	ptrCurrAttrib = ptrCurrNode->GetAttribute(HTL_strSUBOBJTYPE);
	if(ptrCurrAttrib)
	{
		ptrCurrAttrib->Set_strValue(strSubObjType);
	}else{
		//need to create it first
		ptrCurrAttrib = ptrCurrNode->AddAttribute();
		if(ptrCurrAttrib)
		{
			ptrCurrAttrib->Set_strName(HTL_strSUBOBJTYPE);
			ptrCurrAttrib->Set_strValue(strSubObjType);
		};
	};
	//reset sub object base type information
	ptrCurrAttrib = ptrCurrNode->GetAttribute(HTL_strSUBOBJBASETYPE);
	if(ptrCurrAttrib)
	{
		ptrCurrAttrib->Set_strValue(strSubObjBaseType);
	}else{
		//need to create it first
		ptrCurrAttrib = ptrCurrNode->AddAttribute();
		if(ptrCurrAttrib)
		{
			ptrCurrAttrib->Set_strName(HTL_strSUBOBJBASETYPE);
			ptrCurrAttrib->Set_strValue(strSubObjBaseType);
		};
	};
	//reset intNumDimension information
	ptrCurrAttrib = ptrCurrNode->GetAttribute(HTL_strINTNUMDIM);
	if(ptrCurrAttrib)
	{
		ptrCurrAttrib->Set_strValue(strIntNumDim);
	}else{
		//need to create it first
		ptrCurrAttrib = ptrCurrNode->AddAttribute();
		if(ptrCurrAttrib)
		{
			ptrCurrAttrib->Set_strName(HTL_strINTNUMDIM);
			ptrCurrAttrib->Set_strValue(strIntNumDim);
		};
	};
	return 1;
};


int HTL::SetAttribType(HtlElement * ptrCurrNode,std::string & strType)
{
	HtlAttribute * ptrCurrAttrib = NULL;

	//Reset the type information
	ptrCurrAttrib = ptrCurrNode->GetAttribute(HTL_strTYPE);
	if(ptrCurrAttrib)
	{
		ptrCurrAttrib->Set_strValue(strType);
	}else{
		//need to create it first
		ptrCurrAttrib = ptrCurrNode->AddAttribute();
		if(ptrCurrAttrib)
		{
			ptrCurrAttrib->Set_strName(HTL_strTYPE);
			ptrCurrAttrib->Set_strValue(strType);
		};
	};
	return 1;
};

int HTL::SetAttribBaseType(HtlElement * ptrCurrNode,std::string & strBaseType)
{
	HtlAttribute * ptrCurrAttrib = NULL;

	//reset base type information
	ptrCurrAttrib = ptrCurrNode->GetAttribute(HTL_strBASETYPE);
	if(ptrCurrAttrib)
	{
		ptrCurrAttrib->Set_strValue(strBaseType);
	}else{
		//need to create it first
		ptrCurrAttrib = ptrCurrNode->AddAttribute();
		if(ptrCurrAttrib)
		{
			ptrCurrAttrib->Set_strName(HTL_strBASETYPE);
			ptrCurrAttrib->Set_strValue(strBaseType);
		};
	};
	return 1;
};

int HTL::SetAttribSubType(HtlElement * ptrCurrNode,std::string & strSubObjType)
{
	HtlAttribute * ptrCurrAttrib = NULL;

	//reset sub object type information
	ptrCurrAttrib = ptrCurrNode->GetAttribute(HTL_strSUBOBJTYPE);
	if(ptrCurrAttrib)
	{
		ptrCurrAttrib->Set_strValue(strSubObjType);
	}else{
		//need to create it first
		ptrCurrAttrib = ptrCurrNode->AddAttribute();
		if(ptrCurrAttrib)
		{
			ptrCurrAttrib->Set_strName(HTL_strSUBOBJTYPE);
			ptrCurrAttrib->Set_strValue(strSubObjType);
		};
	};
	return 1;
};

int HTL::SetAttribSubBaseType(HtlElement * ptrCurrNode,std::string & strSubObjBaseType)
{
	HtlAttribute * ptrCurrAttrib = NULL;

	//reset sub object base type information
	ptrCurrAttrib = ptrCurrNode->GetAttribute(HTL_strSUBOBJBASETYPE);
	if(ptrCurrAttrib)
	{
		ptrCurrAttrib->Set_strValue(strSubObjBaseType);
	}else{
		//need to create it first
		ptrCurrAttrib = ptrCurrNode->AddAttribute();
		if(ptrCurrAttrib)
		{
			ptrCurrAttrib->Set_strName(HTL_strSUBOBJBASETYPE);
			ptrCurrAttrib->Set_strValue(strSubObjBaseType);
		};
	};
	return 1;
};

int HTL::SetAttribIntNumDim(HtlElement * ptrCurrNode,std::string & strIntNumDim)
{
	HtlAttribute * ptrCurrAttrib = NULL;

	//reset intNumDimension information
	ptrCurrAttrib = ptrCurrNode->GetAttribute(HTL_strINTNUMDIM);
	if(ptrCurrAttrib)
	{
		ptrCurrAttrib->Set_strValue(strIntNumDim);
	}else{
		//need to create it first
		ptrCurrAttrib = ptrCurrNode->AddAttribute();
		if(ptrCurrAttrib)
		{
			ptrCurrAttrib->Set_strName(HTL_strINTNUMDIM);
			ptrCurrAttrib->Set_strValue(strIntNumDim);
		};
	};
	return 1;
};

//HTL SET DEFAULT VALUE//////////////////////////////////////////////////
template<>
int HTL::SetDefaultVal<bool>(bool & objItem){ objItem = false; return 1;};

template<>
int HTL::SetDefaultVal<char>(char & objItem){ objItem = '\0'; return 1;};

template<>
int HTL::SetDefaultVal<unsigned char>(unsigned char & objItem){ objItem = '\0'; return 1;};

template<>
int HTL::SetDefaultVal<short>(short & objItem){ objItem = 0; return 1;};

template<>
int HTL::SetDefaultVal<unsigned short>(unsigned short & objItem){ objItem = 0; return 1;};

template<>
int HTL::SetDefaultVal<int>(int & objItem){ objItem = 0; return 1;};

template<>
int HTL::SetDefaultVal<unsigned int>(unsigned int & objItem){ objItem = 0; return 1;};

template<>
int HTL::SetDefaultVal<long>(long & objItem){ objItem = 0; return 1;};

template<>
int HTL::SetDefaultVal<unsigned long>(unsigned long & objItem){ objItem = 0; return 1;};

template<>
int HTL::SetDefaultVal<float>(float & objItem){ objItem = 0.0f; return 1;};

template<>
int HTL::SetDefaultVal<double>(double & objItem){ objItem = 0.0f; return 1;};