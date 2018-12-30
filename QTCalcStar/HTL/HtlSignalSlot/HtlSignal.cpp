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


#include ".\HtlSignal.h"

//STL streaming functions needed sscanf, sprintf
#include <iostream>

using namespace std;


namespace HTL
{

	////this function disconnects the slot from the signal
	//void HtlSignalBase::SlotDisconnect(HtlHasSlots* ptrObj)
	//	{
	//		HtlGUID128 objNullID;
	//		objNullID.newID();
	//		m_objLock.lock(objNullID);

	//		if(m_arrPtrSlots.size() <= 0){return;};//no entries to disconnect

	//		HtlConnectionList::iterator it = m_arrPtrSlots.begin();
	//		HtlConnectionList::iterator itEnd = m_arrPtrSlots.end();

	//		while(it != itEnd)
	//		{
	//			if((*it)->Get_ptrObj() == ptrObj)
	//			{
	//				delete *it;
	//				m_arrPtrSlots.erase(it);
	//				ptrObj->SignalDisconnect(this);
	//				m_objLock.unlock(objNullID);
	//				return;
	//			}
	//			++it;
	//		};
	//		m_objLock.unlock(objNullID);
	//		return;
	//	};

	//	//this function disconnects the slot from the signal
	//	void HtlSignalBase::SlotDisconnectAll(void)
	//	{
	//		HtlGUID128 objNullID;
	//		objNullID.newID();
	//		m_objLock.lock(objNullID);

	//		HtlConnectionList::const_iterator it = m_arrPtrSlots.begin();
	//		HtlConnectionList::const_iterator itEnd = m_arrPtrSlots.end();

	//		while(it != itEnd)
	//		{
	//			(*it)->Get_ptrObj()->SignalDisconnect(this);
	//			delete *it;
	//			++it;
	//		}

	//		m_arrPtrSlots.clear();
	//		m_objLock.unlock(objNullID);
	//		return;
	//	};
};