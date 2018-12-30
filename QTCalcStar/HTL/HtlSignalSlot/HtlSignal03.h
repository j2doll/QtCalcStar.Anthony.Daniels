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

#ifndef HTL_SIGNAL03_H
#define HTL_SIGNAL03_H

#include ".\HtlSignal.h"
#include ".\HtlConnection03.h"
#include "..\modHtlContainer.h"
#include <vector>

using namespace std;

namespace HTL
{

	//!This is a SIGNAL that has 3 arguments
	template<class arg1_type, class arg2_type, class arg3_type>
	class HtlSignal03 : public HtlSignalBase
	{
	typedef Htl1DList<HtlConnection03Base<arg1_type, arg2_type, arg3_type>*,HtlUnknownType> HtlConnection03List;
	typedef HtlListNode<HtlConnection03Base<arg1_type, arg2_type, arg3_type>*>* HtlConn03Iterator;

	public:
		//void constructor
		HtlSignal03()
		{
			;
		};

		~HtlSignal03()
		{
			SlotDisconnectAll();
		};
	protected:
		//!This is the spinlock mutex for thread constrol
		HtlSpinLock m_objLock;
		//!Collection of connected slots for this signal
		HtlConnection03List m_arrPtrSlots;
	
	public:

		//!This connects a slot
		template<class TObj>
		void SlotConnect(TObj * ptrObj,  void (TObj::*ptrMemFunc)(arg1_type, arg2_type, arg3_type))
		{
			try
			{
				HtlGUID128 objNullID;
				objNullID.newID();
				m_objLock.lock(objNullID);
				//connect the signal 
				HtlConnection03<TObj, arg1_type, arg2_type, arg3_type>* conn =
					new HtlConnection03<TObj, arg1_type, arg2_type, arg3_type>(ptrObj, ptrMemFunc);
				m_arrPtrSlots.push_back(conn);
				//connect the slot
				ptrObj->SignalConnect(this);

				m_objLock.unlock(objNullID);
			}
			catch (...)
			{
				std::string errMsg;
				errMsg = "HtlSignal03 SlotConnect Error thrown";
				throw std::exception(errMsg.c_str());
			}
		};

	
		//!This function duplicates the signal with the new object
		template<class TObj>
		void SlotDuplicate(const HtlHasSlots* ptrOld, HtlHasSlots* ptrNew)
		{
			try
			{
				if (m_arrPtrSlots.size() <= 0) { return; };//no entries to disconnect

				HtlGUID128 objNullID;
				objNullID.newID();
				m_objLock.lock(objNullID);


				HtlConn03Iterator it = m_arrPtrSlots.begin();
				HtlConn03Iterator itEnd = m_arrPtrSlots.end();

				while (it != itEnd)
				{
					HtlConnection03Base<arg1_type, arg2_type, arg3_type>* ptrIt = *(it->get_value());
					if (ptrIt)
					{
						if (ptrIt->Get_ptrObj() == ptrNew)
						{
							//connect the signal 
							HtlConnection03<TObj, arg1_type, arg2_type, arg3_type>* conn =
								new HtlConnection03<TObj, arg1_type, arg2_type, arg3_type>(ptrObj, (*it)->m_ptrMemFunc);
							m_arrPtrSlots.push_back(conn);
							m_objLock.unlock(objNullID);
							return;
						}
					}
					it = m_arrPtrSlots.next();
				};

				m_objLock.unlock(objNullID);
				return;
			}
			catch (...)
			{
				std::string errMsg;
				errMsg = "HtlSignal03 SlotConnect Error thrown";
				throw std::exception(errMsg.c_str());
			}
		};

		//!This function disconnects the slot from the signal
		virtual void SlotDisconnect(HtlHasSlots* ptrObj)
		{
			try
			{
				if (m_arrPtrSlots.size() <= 0) { return; };//no entries to disconnect

				HtlGUID128 objNullID;
				objNullID.newID();
				m_objLock.lock(objNullID);

				size_t i, numCon;
				numCon = m_arrPtrSlots.size();
				for (i = 0; i < numCon; i++)
				{
					HtlConnection03Base<arg1_type, arg2_type, arg3_type>* ptrIt = m_arrPtrSlots.at(i);
					if (ptrIt)
					{
						if (ptrIt->Get_ptrObj() == ptrObj)
						{
							delete ptrIt;
							m_arrPtrSlots.erase(i);
							ptrObj->SignalDisconnectNR(this);
							m_objLock.unlock(objNullID);
							return;
						}
					}
				};
				m_objLock.unlock(objNullID);
				return;
			}
			catch (...)
			{
				std::string errMsg;
				errMsg = "HtlSignal03 SlotDisconnect Error thrown";
				throw std::exception(errMsg.c_str());
			}
		};
		//!This function disconnects the slot from the signal
		virtual void SlotDisconnectNR(HtlHasSlots* ptrObj)
		{
			try
			{
				if (m_arrPtrSlots.size() <= 0) { return; };//no entries to disconnect

				HtlGUID128 objNullID;
				objNullID.newID();
				m_objLock.lock(objNullID);

				size_t i, numCon;
				numCon = m_arrPtrSlots.size();
				for (i = 0; i < numCon; i++)
				{
					HtlConnection03Base<arg1_type, arg2_type, arg3_type>* ptrIt = m_arrPtrSlots.at(i);
					if (ptrIt)
					{
						if (ptrIt->Get_ptrObj() == ptrObj)
						{
							delete ptrIt;
							m_arrPtrSlots.erase(i);
							m_objLock.unlock(objNullID);
							return;
						}
					}
				};
				m_objLock.unlock(objNullID);
				return;
			}
			catch (...)
			{
				std::string errMsg;
				errMsg = "HtlSignal03 SlotDisconnectNR Error thrown";
				throw std::exception(errMsg.c_str());
			}
		};
		//!This function disconnects the slot from the signal
		virtual void SlotDisconnectAll(void)
		{
			try
			{
				if (m_arrPtrSlots.size() <= 0) { return; };//no entries to disconnect

				HtlGUID128 objNullID;
				objNullID.newID();
				m_objLock.lock(objNullID);

				size_t i, numCon;
				numCon = m_arrPtrSlots.size();
				for (i = 0; i < numCon; i++)
				{
					HtlConnection03Base<arg1_type, arg2_type, arg3_type>* ptrIt = m_arrPtrSlots.at(i);
					if (ptrIt)
					{
						ptrIt->Get_ptrObj()->SignalDisconnectNR(this);
						delete ptrIt;
					}
				};
				m_arrPtrSlots.clear();
				m_objLock.unlock(objNullID);
				return;
			}
			catch (...)
			{
				std::string errMsg;
				errMsg = "HtlSignal03 SlotDisconnectAll Error thrown";
				throw std::exception(errMsg.c_str());
			}
		};
		//!This Emits the signal
		void Emit(arg1_type a1, arg2_type a2, arg3_type a3)
		{
			try
			{
				if (m_arrPtrSlots.size() <= 0) { return; };//no entries to disconnect

				HtlGUID128 objNullID;
				objNullID.newID();
				m_objLock.lock(objNullID);

				HtlConn03Iterator it = m_arrPtrSlots.begin();
				HtlConn03Iterator itEnd = m_arrPtrSlots.end();

				while (it != itEnd)
				{
					HtlConnection03Base<arg1_type, arg2_type, arg3_type>* ptrIt = *(it->get_value());
					if (ptrIt)
					{
						ptrIt->Emit(a1, a2, a3);
					}
					it = m_arrPtrSlots.next();
				};
				m_objLock.unlock(objNullID);
				return;
			}
			catch (...)
			{
				std::string errMsg;
				errMsg = "HtlSignal03 Emit Error thrown";
				throw std::exception(errMsg.c_str());
			}
		}
		
		//!This Emits the signal
		void operator()(arg1_type a1, arg2_type a2, arg3_type a3)
		{
			try
			{
				if (m_arrPtrSlots.size() <= 0) { return; };//no entries to disconnect

				HtlGUID128 objNullID;
				objNullID.newID();
				m_objLock.lock(objNullID);

				HtlConn03Iterator it = m_arrPtrSlots.begin();
				HtlConn03Iterator itEnd = m_arrPtrSlots.end();

				while (it != itEnd)
				{
					HtlConnection03Base<arg1_type, arg2_type, arg3_type>* ptrIt = *(it->get_value());
					if (ptrIt)
					{
						ptrIt->Emit(a1, a2, a3);
					}
					it = m_arrPtrSlots.next();
				};
				m_objLock.unlock(objNullID);
				return;
			}
			catch (...)
			{
				std::string errMsg;
				errMsg = "HtlSignal03 Emit Error thrown";
				throw std::exception(errMsg.c_str());
			}
		}

private:

	};//end HtlSignal03 class

};//end namespace HTL

#endif