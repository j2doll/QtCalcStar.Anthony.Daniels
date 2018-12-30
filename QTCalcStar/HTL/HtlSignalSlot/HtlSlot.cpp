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


#include ".\HtlSlot.h"
#include ".\HtlSignal.h"
//STL streaming functions needed sscanf, sprintf
#include <iostream>

using namespace std;


namespace HTL
{

	HtlHasSlots::HtlHasSlots()
	{
		;//void constructor
	}

	//HtlHasSlots::HtlHasSlots(HtlHasSlots& rhs)
	//{
	//	HtlGUID128 objNullID;
	//	objNullID.newID();
	//	m_objLock.lock(objNullID);

	//	SignalList::const_iterator it = rhs.GetConnectedSignals()->begin();
	//	SignalList::const_iterator itEnd = rhs.GetConnectedSignals()->end();

	//	while(it != itEnd)
	//	{
	//		(*it)->SlotDuplicate(&rhs, this);
	//		m_arrPtrSenders.push_back(*it);
	//		++it;
	//	};
	//	m_objLock.unlock(objNullID);
	//} 

	HtlHasSlots::~HtlHasSlots()
	{
		SignalDisconnectAll();
	};

	SignalList* HtlHasSlots::GetConnectedSignals(void)
	{
		return &m_arrPtrSenders;
	};

	void HtlHasSlots::SignalConnect(HtlSignalBase* ptrSender)
	{
		try
		{
			HtlGUID128 objNullID;
			objNullID.newID();
			m_objLock.lock(objNullID);

			m_arrPtrSenders.push_back(ptrSender);

			m_objLock.unlock(objNullID);
		}
		catch (...)
		{
			std::string errMsg;
			errMsg = "HtlHasSlots SignalConnect Error thrown";
			throw std::exception(errMsg.c_str());
		}
	}

	void HtlHasSlots::SignalDisconnect(HtlSignalBase* ptrSender)
	{
		try
		{
			HtlGUID128 objNullID;
			objNullID.newID();
			m_objLock.lock(objNullID);

			SignalList::iterator it;
			for (it = m_arrPtrSenders.begin(); it != m_arrPtrSenders.end(); ++it)
			{
				if ((*it) == ptrSender)
				{
					(*it)->SlotDisconnectNR(this);
					m_arrPtrSenders.erase(it);
					m_objLock.unlock(objNullID);
					return;
				};
			};

			m_objLock.unlock(objNullID);
		}
		catch (...)
		{
			std::string errMsg;
			errMsg = "HtlHasSlots SignalDisconnect Error thrown";
			throw std::exception(errMsg.c_str());
		}
	}

	void HtlHasSlots::SignalDisconnectNR(HtlSignalBase* ptrSender)
	{
		try
		{
			HtlGUID128 objNullID;
			objNullID.newID();
			m_objLock.lock(objNullID);

			SignalList::iterator it;
			for (it = m_arrPtrSenders.begin(); it != m_arrPtrSenders.end(); ++it)
			{
				if ((*it) == ptrSender)
				{
					m_arrPtrSenders.erase(it);
					m_objLock.unlock(objNullID);
					return;
				};
			};

			m_objLock.unlock(objNullID);
			return;
		}
		catch (...)
		{
			std::string errMsg;
			errMsg = "HtlHasSlots SignalDisconnect Error thrown";
			throw std::exception(errMsg.c_str());
		}
	};

	void HtlHasSlots::SignalDisconnectAll()
	{
		try
		{
			HtlGUID128 objNullID;
			objNullID.newID();
			m_objLock.lock(objNullID);
			SignalList::const_iterator it = m_arrPtrSenders.begin();
			SignalList::const_iterator itEnd = m_arrPtrSenders.end();

			while (it != itEnd)
			{
				(*it)->SlotDisconnectNR(this);
				++it;
			}

			m_arrPtrSenders.clear();
			m_objLock.unlock(objNullID);
			return;
		}
		catch (...)
		{
			std::string errMsg;
			errMsg = "HtlHasSlots SignalDisconnectAll Error thrown";
			throw std::exception(errMsg.c_str());
		}
	}



};//end namespace HtlSlot