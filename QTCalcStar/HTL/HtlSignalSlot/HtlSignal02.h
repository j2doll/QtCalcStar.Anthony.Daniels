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

#ifndef HTL_SIGNAL02_H
#define HTL_SIGNAL02_H

#include ".\HtlSignal.h"
#include ".\HtlConnection02.h"
#include "..\modHtlContainer.h"
#include <vector>

using namespace std;

namespace HTL
{

	//!This is a SIGNAL that has 2 arguments
	template<class arg1_type, class arg2_type>
	class HtlSignal02 : public HtlSignalBase
	{
	typedef Htl1DList<HtlConnection02Base<arg1_type, arg2_type>*,HtlUnknownType> HtlConnection02List;
	typedef HtlListNode<HtlConnection02Base<arg1_type, arg2_type>*>* HtlConn02Iterator;

	public:
		//!void constructor
		HtlSignal02()
		{
			;
		};
		//!destructor
		~HtlSignal02()
		{
			SlotDisconnectAll();
		};
	protected:
		//!This is the spinlock mutex for thread constrol
		HtlSpinLock m_objLock;
		//!Collection of connected slots for this signal
		HtlConnection02List m_arrPtrSlots;
	
	public:
		//!This connects the slot
		template<class TObj>
		void SlotConnect(TObj * ptrObj,  void (TObj::*ptrMemFunc)(arg1_type, arg2_type))
		{
			try
			{
				HtlGUID128 objNullID;
				objNullID.newID();
				m_objLock.lock(objNullID);
				//connect the signal 
				HtlConnection02<TObj, arg1_type, arg2_type>* conn =
					new HtlConnection02<TObj, arg1_type, arg2_type>(ptrObj, ptrMemFunc);
				m_arrPtrSlots.push_back(conn);
				//connect the slot
				ptrObj->SignalConnect(this);

				m_objLock.unlock(objNullID);
			}
			catch (...)
			{
				std::string errMsg;
				errMsg = "HtlSignal02 SlotConnect Error thrown";
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


				HtlConn02Iterator it = m_arrPtrSlots.begin();
				HtlConn02Iterator itEnd = m_arrPtrSlots.end();

				while (it != itEnd)
				{
					HtlConnection02Base<arg1_type, arg2_type>* ptrIt = *(it->get_value());
					if (ptrIt)
					{
						if (ptrIt->Get_ptrObj() == ptrNew)
						{
							//connect the signal 
							HtlConnection02<TObj, arg1_type, arg2_type>* conn =
								new HtlConnection02<TObj, arg1_type, arg2_type>(ptrObj, (*it)->m_ptrMemFunc);
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
				errMsg = "HtlSignal02 SlotDuplicate Error thrown";
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
					HtlConnection02Base<arg1_type, arg2_type>* ptrIt = m_arrPtrSlots.at(i);
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
				errMsg = "HtlSignal02 SlotDisconnect Error thrown";
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
					HtlConnection02Base<arg1_type, arg2_type>* ptrIt = m_arrPtrSlots.at(i);
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
				errMsg = "HtlSignal02 SlotDisconnectNR Error thrown";
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
					HtlConnection02Base<arg1_type, arg2_type>* ptrIt = m_arrPtrSlots.at(i);
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
				errMsg = "HtlSignal02 SlotDisconnectAll Error thrown";
				throw std::exception(errMsg.c_str());
			}
		};

		//!This emits the signal
		void Emit(arg1_type a1, arg2_type a2)
		{
			try
			{
				if (m_arrPtrSlots.size() <= 0) { return; };//no entries to disconnect

				HtlGUID128 objNullID;
				objNullID.newID();
				m_objLock.lock(objNullID);

				HtlConn02Iterator it = m_arrPtrSlots.begin();
				HtlConn02Iterator itEnd = m_arrPtrSlots.end();

				while (it != itEnd)
				{
					HtlConnection02Base<arg1_type, arg2_type>* ptrIt = *(it->get_value());
					if (ptrIt)
					{
						ptrIt->Emit(a1, a2);
					}
					it = m_arrPtrSlots.next();
				};
				m_objLock.unlock(objNullID);
				return;
			}
			catch (...)
			{
				std::string errMsg;
				errMsg = "HtlSignal02 Emit Error thrown";
				throw std::exception(errMsg.c_str());
			}
		}
		//!This Emits the signal
		void operator()(arg1_type a1, arg2_type a2)
		{
			try
			{
				if (m_arrPtrSlots.size() <= 0) { return; };//no entries to disconnect

				HtlGUID128 objNullID;
				objNullID.newID();
				m_objLock.lock(objNullID);

				HtlConn02Iterator it = m_arrPtrSlots.begin();
				HtlConn02Iterator itEnd = m_arrPtrSlots.end();

				while (it != itEnd)
				{
					HtlConnection02Base<arg1_type, arg2_type>* ptrIt = *(it->get_value());
					if (ptrIt)
					{
						ptrIt->Emit(a1, a2);
					}
					it = m_arrPtrSlots.next();
				};
				m_objLock.unlock(objNullID);
				return;
			}
			catch (...)
			{
				std::string errMsg;
				errMsg = "HtlSignal02 Emit Error thrown";
				throw std::exception(errMsg.c_str());
			}
		}

private:

	};//end HtlSignal02 class

};//end namespace HTL

#endif