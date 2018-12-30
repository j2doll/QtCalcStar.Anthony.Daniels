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

#ifndef HTL_CONTAINER_H
#define HTL_CONTAINER_H
#include "..\modHtlLibRefs.h"
#include "..\modHtlBase.h"

#include "..\modHtlArchive.h"
#include "..\HtlThread\HtlSpinLock.h"
namespace HTL
{
	//!This the container base class.  ALL HTL containers inherit from this base class.
	template<typename TIndex,HtlObjectType TIndexEnum, typename TObj, HtlObjectType TObjEnum>
	class HtlContainer : public HtlBase
	{
	public:

		//Void Constructor
		inline HtlContainer<TIndex,TIndexEnum, TObj,TObjEnum>()
			:HtlBase()
		{
			m_objType = HTL_CONTAINER;
			m_indexType = TIndexEnum;
			m_itemType = TObjEnum;
		};

		//Virtual destructor
		virtual ~HtlContainer(void)
		{
			//Clear the container upon quiting
			clear();
		};
		//!commonly used typedefs (STL compatible)
		typedef unsigned long size_type;
		typedef TObj value_type;
		typedef TObj objType;
		typedef TObj* pointer;
		typedef const TObj* const_pointer;
		typedef TObj& reference;
		typedef const TObj& const_reference;

		//!Enumerated Index Type 
		HTLMEMVAR_BYVAL_STYLE1(public, HtlObjectType, indexType);
		//!Enumerated Item Type 
		HTLMEMVAR_BYVAL_STYLE1(public, HtlObjectType, itemType);


		//!Vector size related methods
		virtual size_t size(void) const{ return 0;};
		//!Vector size related methods
		virtual size_t count(void) const{return 0;};
		//!Force a recount of the vector
		virtual void recount(void){return;};
		//!Is the vector empty
		virtual bool isEmpty(void) {return true;};
		//!Find the capacity of the container
		virtual size_t capacity(void){return 0;};
		//!Clears the container
		virtual void clear(void){return;};


		//!Access to the actual data pointers
		virtual TObj *Get_ptrData(){return NULL;};
		
		//!Item accessor functions
		virtual TObj &at(TIndex i){return m_objNull;};
		//!Item accessor operator
		virtual TObj &operator[](TIndex i){return m_objNull;};
		
	protected:
		TIndex m_keyNull;
		//!Null object
		TObj m_objNull;
		//!This is the spinlock mutex for thread control
		HtlSpinLock m_objLock;

		HtlDebugPrinter m_objDebug;
		
	public:
	//Virtual Inheritance Serialization Engines
	//SERIALIZATION ACCESSOR MACRO///////////////////////////////////////
	//!Save the Container to the HTLElement
	virtual int Save(HTL::HtlElement * ptrCurrNode, std::string strMemVarName, bool blnWithSubObjects)
	{
		try
		{
			int intReturn = 0;
			//SAFETY CHECK //put at top of all Serialize Methods
			if (!ptrCurrNode) { return 0; };
			//CALL PARENT CLASS Serialize()
			/*...*/
			HtlBase::Save(ptrCurrNode, strMemVarName, blnWithSubObjects);
			//Standard Member Variables
			std::string m_strItemType, strSubBaseType, strIntNumDim;

			m_strItemType = HTL_STRINGIZE(TObj);
			HTL::enumToString<HtlObjectType>(m_itemType, strSubBaseType);
			strIntNumDim = "1";

			HTL::SetAttribSubTypeInfo(ptrCurrNode, m_strItemType, strSubBaseType, strIntNumDim);

			//Sub Object Member Variables
			if (blnWithSubObjects)
			{
				/*...*/
			};

			return intReturn;
		}
		catch (...)
		{
			std::string errMsg;
			errMsg = "HtlContainer Save Error thrown";
			throw std::exception(errMsg.c_str());
		}
	};
	//!Load the container from the current HtlElement
	virtual int Load(HTL::HtlElement * ptrCurrNode, std::string strMemVarName)
	{
		try
		{
			int intReturn = 0;
			//SAFETY CHECK //put at top of all Serialize Methods
			if (!ptrCurrNode) { return 0; };
			//CALL PARENT CLASS Serialize()
			/*...*/
			HtlBase::Load(ptrCurrNode, strMemVarName);
			//Standard Member Variables

			return intReturn;
		}
		catch (...)
		{
			std::string errMsg;
			errMsg = "HtlContainer Load Error thrown";
			throw std::exception(errMsg.c_str());
		}
	};


	};//end HtlBase class definition

};//end namspace Htl

#endif//HtlBASE_H


