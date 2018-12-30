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

#ifndef HTL_OBJECT_H
#define HTL_OBJECT_H

#include "..\HtlBase\HtlBase.h"
#include "..\modHtlGUID.h"
#include "..\modHtlSignalSlot.h"
namespace HTL
{
	class HtlObjectMap;

	//!This is the base object that provides signals slots capability as well as a global unique identifier for the object.
	/*!
	This is the base object that provides signals slots capability as well as a
	global unique identifier for the object. It inherits the HtlBase serialization engine
	*/
	class HTL_DLLAPI HtlObject : public HtlHasSlots, public HtlBase
	{
	public:
		//default constructor
		HtlObject();
		//virtual destructor
		virtual ~HtlObject(void);

		//!Pointer to the Parent Object (object or collection)
		HTLMEMVAR_BYVAL_STYLE1(public,HtlObject*,ptrParent);
		//!Pointer to the Owner Object (object or parent of collection)
		HTLMEMVAR_BYVAL_STYLE1(public,HtlObject*,ptrOwner);
		//!pointer to the parent Node
		HTLMEMVAR_BYREF_STYLE1(public, HtlGUID128, objGUID);

		//!Returns true if object has changed
		inline bool IsChanged(void){return m_blnChanged;};
		inline void SetChanged(void){m_blnChanged = true;};

		//!Adds the object to the proper container based on the linkID
		virtual void AddBiDirPtr(HtlObject *ptrObj, std::string strLinkID);
		//!Removes the object from the proper container based on the linkID
		virtual void RemoveBiDirPtr(HtlObject *ptrObj, std::string strLinkID);

		//!returns get registry 
		static HtlObjectMap* GetObjRegistry(void);
		//!returns by GUID
		static HtlObject* Get_objRefPtr(HtlGUID128 & objGUID);
		//!returns by GUID string
		static HtlObject* Get_objRefPtr(std::string & strGUID);


		//SERIALIZATION FUNCTIONS///////////////////////////////////////
		//!Save member data to the current element node
		virtual int Save(HTL::HtlElement * ptrCurrNode, std::string strMemVarName, bool blnWithSubObjects);
		//!Load member data from the current element node
		virtual int Load(HTL::HtlElement * ptrCurrNode, std::string strMemVarName);

	protected:
		//!boolean object changed dirty flag
		bool m_blnChanged;
	};//end HtlBase class definition

};//end namspace Htl

#endif//HtlBASE_H


