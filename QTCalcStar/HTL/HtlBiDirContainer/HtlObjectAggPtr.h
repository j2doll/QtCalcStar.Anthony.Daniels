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
#ifndef HTLOBJECT_AGGREGATEPTR_H
#define HTLOBJECT_AGGREGATEPTR_H
#include "..\modHtlBase.h"
#include "..\modHtlGUID.h"
namespace HTL
{
	class HtlObject;
//ORSDBObject Pointer TypeDef
	class HTL_DLLAPI HtlObjectAggPtr
		: public HtlBase
	{
	public:
		HtlObjectAggPtr();
		HtlObjectAggPtr(const HtlObjectAggPtr& rhs);
		virtual ~HtlObjectAggPtr();

		void SetNull(void);

		bool IsNull(void);
		
		bool IsValid(void);

		HtlObject* GetObjPtr(void);

		void SetObjPtr(HtlObject* ptrObj);

		void SetObjPtr(HtlGUID128 objGUID);

		void SyncObjPtr(void);

		//overload the pointer scope operator
		HtlObject* operator ->();

		HtlObjectAggPtr & operator = (const HtlObjectAggPtr & rhs);

		HtlObjectAggPtr & operator = (HtlObject* & rhs);

		HtlObjectAggPtr & operator = (HtlObject* rhs);

		HtlObjectAggPtr & operator = (HtlGUID128 & rhs);

		//!Boolean Logic Operator Overloads
		//All boolean comparisons are based on GUIDs ONLY by design
		bool operator == (HtlObjectAggPtr & ptrRHS ); 
		bool operator != (HtlObjectAggPtr & ptrRHS ); 
		bool operator < (HtlObjectAggPtr & ptrRHS ); 
		bool operator > (HtlObjectAggPtr & ptrRHS ); 
		bool operator <= (HtlObjectAggPtr & ptrRHS ); 
		bool operator >= (HtlObjectAggPtr & ptrRHS ); 



	public:
		//Virtual Inheritance Serialization Engines
		//SERIALIZATION FUNCTIONS///////////////////////////////////////
		//!Save member data to the current element node
		virtual int Save(HTL::HtlElement * ptrCurrNode, std::string strMemVarName, bool blnWithSubObjects);
		//!Load member data from the current element node
		virtual int Load(HTL::HtlElement * ptrCurrNode, std::string strMemVarName);

	public:
		HtlObject* m_ptrObject;
		HtlGUID128 m_objGUID;
	};

};//end namespace ORSDB

#endif //#ifndef ORSDBOBJECT_H


