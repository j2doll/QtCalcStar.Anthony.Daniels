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

#include ".\HtlObject.h"
#include "..\modHtlArchive.h"
#include ".\HtlObjectMap.h"


namespace HTL
{

		//default constructor
		HtlObject::HtlObject()
			: HtlBase(), HtlHasSlots()
		{
			m_objType = HTL_OBJECT;
			m_objGUID.newID();
			//set the change flag
			m_blnChanged = false;
		};

		//virtual destructor
		HtlObject::~HtlObject(void){};


		//!Adds the object to the proper container based on the linkID
		void HtlObject::AddBiDirPtr(HtlObject *ptrObj, std::string strLinkID){};
		//!Removes the object from the proper container based on the linkID
		void HtlObject::RemoveBiDirPtr(HtlObject *ptrObj, std::string strLinkID){};

		//!Gets the pointer to the global registry object
		HtlObjectMap* HtlObject::GetObjRegistry(void)
		{
			//!Static Object Registry that all ORSDBObject register with
			static HtlObjectMap g_objRegistry;
			return &g_objRegistry;
		};

		//!returns by GUID
		HtlObject* HtlObject::Get_objRefPtr(HtlGUID128 & objGUID)
		{
			return GetObjRegistry()->GetHtlObjectPtr(objGUID);
		};
		//!returns by GUID
		HtlObject* HtlObject::Get_objRefPtr(std::string & strGUID)
		{
			HtlGUID128 objGUID;
			objGUID.fromStdString(strGUID);
			return GetObjRegistry()->GetHtlObjectPtr(objGUID);
		};

	//Virtual Inheritance Serialization Engines
	//SERIALIZATION ACCESSOR MACRO///////////////////////////////////////
	int HtlObject::Save(HTL::HtlElement * ptrCurrNode, std::string strMemVarName, bool blnWithSubObjects)
	{

		int intReturn = 0;
		//SAFETY CHECK //put at top of all Serialize Methods
		if(!ptrCurrNode){return 0;};
		//reset the change dirty flag
		m_blnChanged = false;
		//CALL PARENT CLASS Serialize()
		/*...*/
		HtlBase::Save(ptrCurrNode, strMemVarName, blnWithSubObjects);
		//Standard Member Variables
		intReturn &= SetHtlMemVar<HtlGUID128,HTL_GUID128>(ptrCurrNode,"m_objGUID",m_objGUID,blnWithSubObjects);
		//Sub Object Member Variables
		if(blnWithSubObjects)
		{
			/*...*/
		};

		return intReturn;


	};

	int HtlObject::Load(HTL::HtlElement * ptrCurrNode, std::string strMemVarName)
	{

		int intReturn = 0;
		//SAFETY CHECK //put at top of all Serialize Methods
		if(!ptrCurrNode){return 0;};
		//CALL PARENT CLASS Serialize()
		/*...*/
		HtlBase::Load(ptrCurrNode,strMemVarName);
		//Standard Member Variables
		intReturn &= GetHtlMemVar<HtlGUID128,HTL_GUID128>(ptrCurrNode,"m_objGUID",m_objGUID);
		return intReturn;

	};


};