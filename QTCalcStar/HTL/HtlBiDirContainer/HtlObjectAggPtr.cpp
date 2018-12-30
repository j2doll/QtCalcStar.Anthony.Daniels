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

#include ".\HtlObjectAggPtr.h"
#include "..\modHtlObject.h"
#include "..\modHtlArchive.h"

namespace HTL
{
	//VIRTUAL INHERITANCE SERIALIZATION ENGINES
	//XML SERIALIZATION////////////////////////////////////////
	HtlObjectAggPtr::HtlObjectAggPtr() : HtlBase()
	{
		m_strType = "HtlObjectAggPtr";
		m_objType = HTL_BASE;
		SetNull();
	};
	HtlObjectAggPtr::HtlObjectAggPtr(const HtlObjectAggPtr& rhs)
	{
		if(this != &rhs)
		{
			m_strType = "HtlObjectAggPtr";
			m_objType = HTL_BASE;
			m_ptrObject = rhs.m_ptrObject;
			m_objGUID = rhs.m_objGUID;
		}
		return;
	};
	HtlObjectAggPtr::~HtlObjectAggPtr()
	{
		m_ptrObject = NULL;
		m_objGUID.setNull();
	};

	void HtlObjectAggPtr::SetNull(void)
	{
		m_ptrObject = NULL;
		m_objGUID.setNull();
	};
	bool HtlObjectAggPtr::IsNull(void)
	{
		if( (m_ptrObject == NULL) && (m_objGUID.isNull()) )
		{
			return true;
		};
		return false;
	};
	bool HtlObjectAggPtr::IsValid(void)
	{
		//dont know if this works
		if(typeid(m_ptrObject) == typeid(HtlObject*))
		{
			return true;
		};
		return false;
	};

	HtlObject* HtlObjectAggPtr::GetObjPtr(void)
	{
		if(m_ptrObject)
		{
			return m_ptrObject;
		}else{
			if(!m_objGUID.isNull())
			{
				//try and find the pointer from the GUID through the registrar
				m_ptrObject = HtlObject::Get_objRefPtr(m_objGUID);
				if(!m_ptrObject)
				{
					//std::cout << "OBJECT GUID NOT FOUND!!!...\n";
				};
			};
			return m_ptrObject;
		};
	};
	void HtlObjectAggPtr::SetObjPtr(HtlObject* ptrObj)
	{
		try{

			if(ptrObj)
			{
				m_ptrObject = ptrObj;
				try{
					m_objGUID = ptrObj->Get_objGUID();
				}catch(...){
					std::cout << "Error extracting GUID from object...\n";
				};
			};
		}catch(...){
			std::cout << "Error setting pointer...\n";
			this->SetNull();
		};
	};
	void HtlObjectAggPtr::SetObjPtr(HtlGUID128 objGUID)
	{
		m_objGUID = objGUID;
		//try and find the pointer from the GUID through the registrar
		m_ptrObject = HtlObject::Get_objRefPtr(objGUID);
	};

	void HtlObjectAggPtr::SyncObjPtr(void)
	{
		//try and find the pointer from the GUID through the registrar
		m_ptrObject = HtlObject::Get_objRefPtr(m_objGUID);
	};

	//overload the pointer scope operator
	HtlObject* HtlObjectAggPtr::operator ->()
	{
		if(m_ptrObject)
		{
			return m_ptrObject;
		}else{
			//try and find the pointer from the GUID through the registrar
			m_ptrObject = HtlObject::Get_objRefPtr(m_objGUID);
			return m_ptrObject;
		};
	};

	HtlObjectAggPtr & HtlObjectAggPtr::operator = (const HtlObjectAggPtr & rhs)
	{
		if(this != &rhs)
		{
			m_strType = "HtlObjectAggPtr";
			m_objType = HTL_GUID128;
			m_ptrObject = rhs.m_ptrObject;
			m_objGUID = rhs.m_objGUID;
		}
		return *this;
	};

	HtlObjectAggPtr & HtlObjectAggPtr::operator = (HtlObject* & rhs)
	{
		m_strType = "HtlObjectAggPtr";
		m_objType = HTL_GUID128;
		m_ptrObject = rhs;
		m_objGUID = rhs->Get_objGUID();
		return *this;
	};
	HtlObjectAggPtr & HtlObjectAggPtr::operator = (HtlObject* rhs)
	{
		m_strType = "HtlObjectAggPtr";
		m_objType = HTL_GUID128;
		m_ptrObject = rhs;
		m_objGUID = rhs->Get_objGUID();
		return *this;
	};
	HtlObjectAggPtr & HtlObjectAggPtr::operator = (HtlGUID128 & rhs)
	{
		m_strType = "HtlObjectAggPtr";
		m_objType = HTL_GUID128;
		m_objGUID = rhs;
		//try and find the pointer from the GUID through the registrar
		m_ptrObject = HtlObject::Get_objRefPtr(rhs);
		return *this;
	};


	//!Boolean Logic Operator Overloads
	//All boolean comparisons are based on GUIDs ONLY by design
	bool HtlObjectAggPtr::operator == (HtlObjectAggPtr & ptrRHS ) 
	{
		return (m_objGUID == ptrRHS.m_objGUID);
	};

	bool HtlObjectAggPtr::operator != (HtlObjectAggPtr & ptrRHS ) 
	{
		return (m_objGUID != ptrRHS.m_objGUID);
	};

	bool HtlObjectAggPtr::operator < (HtlObjectAggPtr & ptrRHS ) 
	{
		return (m_objGUID < ptrRHS.m_objGUID);
	};

	bool HtlObjectAggPtr::operator > (HtlObjectAggPtr & ptrRHS ) 
	{
		return (m_objGUID > ptrRHS.m_objGUID);
	};

	bool HtlObjectAggPtr::operator <= (HtlObjectAggPtr & ptrRHS ) 
	{
		return (m_objGUID <= ptrRHS.m_objGUID);
	};

	bool HtlObjectAggPtr::operator >= (HtlObjectAggPtr & ptrRHS ) 
	{
		return (m_objGUID >= ptrRHS.m_objGUID);
	};




	//Virtual Inheritance Serialization Engines
	//SERIALIZATION ACCESSOR MACRO///////////////////////////////////////
	int HtlObjectAggPtr::Save(HTL::HtlElement * ptrCurrNode, std::string strMemVarName, bool blnWithSubObjects)
	{

		int intReturn = 0;
		//SAFETY CHECK //put at top of all Serialize Methods
		if(!ptrCurrNode){return 0;};
		//CALL PARENT CLASS Serialize()
		/*...*/
		HtlBase::Save(ptrCurrNode, strMemVarName, blnWithSubObjects);
		//Standard Member Variables
		intReturn &= SetHtlMemVar<HtlGUID128,HTL_GUID128>(ptrCurrNode,"m_objGUID",m_objGUID,blnWithSubObjects);

		return intReturn;
	};

	int HtlObjectAggPtr::Load(HTL::HtlElement * ptrCurrNode, std::string strMemVarName)
	{

		int intReturn = 0;
		//SAFETY CHECK //put at top of all Serialize Methods
		if(!ptrCurrNode){return 0;};
		//CALL PARENT CLASS Serialize()
		/*...*/
		HtlBase::Load(ptrCurrNode,strMemVarName);
		//Standard Member Variables
		intReturn &= GetHtlMemVar<HtlGUID128,HTL_GUID128>(ptrCurrNode,"m_objGUID",m_objGUID);
		//for debugging
		std::string strTemp;
		strTemp = m_objGUID.toStdString();

		strTemp.clear();
		return intReturn;

	};

};//end namespace HTL
