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

#include ".\HtlBase.h"
#include "..\modHtlArchive.h"

namespace HTL
{
	//!Default Constructor
	HtlBase::HtlBase() : m_objType(HtlUnknownType)
	{
		m_objType = HTL::HTL_BASE;
	};
	//!Default Constructor
	HtlBase::HtlBase(const HtlBase& rhs)
	{
		m_objType = HTL::HTL_BASE;
	};
	//!Virtual Destructor
	HtlBase::~HtlBase(void)
	{
		m_strType.clear();
		m_objType = HtlUnknownType;
	};

	//PUBLIC OPERATOR OVERLOADS
	HtlBase & HtlBase::operator = (const HtlBase & rhs){ return (*this); };
	//collection of fields
	//static version of HtlBase::m_blnSafeCallEnabled;
	//bool HtlBase::m_blnSafeCallEnabled = false;

	//Virtual Inheritance Serialization Engines
	//SERIALIZATION ACCESSOR MACRO///////////////////////////////////////
	int HtlBase::Save(HTL::HtlElement * ptrCurrNode, std::string strMemVarName, bool blnWithSubObjects)
	{

		int intReturn = 0;
		//SAFETY CHECK //put at top of all Serialize Methods
		if(!ptrCurrNode){return 0;};
		//CALL PARENT CLASS Serialize()
		/*...*/
		//SET Self information
		ptrCurrNode->Set_strName(strMemVarName);
		std::string strBaseType;
		HTL::enumToString<HtlObjectType>(m_objType,strBaseType);
		HTL::SetAttribTypeInfo(ptrCurrNode,m_strType, strBaseType);
		//strSTDBaseType.clear();
		//strBaseType.clear();
		//Standard Member Variables
      intReturn &= SetHtlMemVar<std::string, STL_STRING>(ptrCurrNode, "m_strType", m_strType, false);
		intReturn &= SetHtlMemVar<HtlObjectType,HTL_ENUM>(ptrCurrNode,"m_objType",m_objType, false);
		//Sub Object Member Variables
		if(blnWithSubObjects)
		{
			/*...*/
		};

		return intReturn;


	};

	int HtlBase::Load(HTL::HtlElement * ptrCurrNode, std::string strMemVarName)
	{

		int intReturn = 0;
		//SAFETY CHECK //put at top of all Serialize Methods
		if(!ptrCurrNode){return 0;};
		//CALL PARENT CLASS Serialize()
		/*...*/
		//Standard Member Variables
      intReturn &= GetHtlMemVar<std::string, STL_STRING>(ptrCurrNode, "m_strType", m_strType);
		intReturn &= GetHtlMemVar<HtlObjectType,HTL_ENUM>(ptrCurrNode,"m_objType",m_objType);

		return intReturn;

	};

};
