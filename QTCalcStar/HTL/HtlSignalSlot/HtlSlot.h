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

#ifndef HTL_SLOT_H
#define HTL_SLOT_H

#include "..\modHtlLibRefs.h"
#include "..\HtlGlobal\HtlEnums.h"
#include "..\HtlGUID\HtlGUID128.h"
#include "..\HtlThread\HtlSpinLock.h"

#include <vector>

using namespace std;

namespace HTL{
		//forward declaration
	class HtlSignalBase;

	typedef std::vector<HtlSignalBase*> SignalList;
	/*
	Unlike sigslots, the signal slots portion of HTL assumes a multithreaded local paradigm.
	Thus the need for templating on the my_policy is not needed.
	*/
	class HTL_DLLAPI HtlHasSlots
	{
	private:


	public:
		//!default void constructor
		HtlHasSlots();
		//!void destructor
		virtual ~HtlHasSlots();

		//!Get the collection of signals currently connected to by reference
		SignalList * GetConnectedSignals(void);


		//!Add this signal to the connected list as a sender
		void SignalConnect(HtlSignalBase* sender);
		//!Remove this signal from the connected list as a sender
		void SignalDisconnect(HtlSignalBase* sender);
		//!Remove this signal from the connected list as a sender NON RECURSIVE
		void SignalDisconnectNR(HtlSignalBase* sender);
		//!Disconnect all signals currently connected to
		void SignalDisconnectAll();

	private:
		//!This is the spinlock mutex for thread constrol
		HtlSpinLock m_objLock;

		//!This is the list of connections that we currently have
		SignalList m_arrPtrSenders;
	};//end class definition

};//end HTL namespace
#endif
