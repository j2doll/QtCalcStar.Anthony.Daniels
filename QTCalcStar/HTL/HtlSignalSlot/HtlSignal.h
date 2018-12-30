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

#ifndef HTL_SIGNAL_H
#define HTL_SIGNAL_H

#include "..\modHtlLibRefs.h"
#include "..\HtlGlobal\HtlEnums.h"
#include "..\HtlGUID\HtlGUID128.h"
#include "..\HtlThread\HtlSpinLock.h"
#include <vector>

using namespace std;

namespace HTL
{
	class HtlHasSlots;
	//!This is the base class for signals. It has virtual functions that need to be overloaded.
	class HTL_DLLAPI HtlSignalBase
	{
	public:

		//!this function disconnects the slot from the signal
		virtual void SlotDisconnect(HtlHasSlots* pslot){};
		//!this function disconnects the slot from the signal NON Recursive
		virtual void SlotDisconnectNR(HtlHasSlots* pslot){};
		//!this function disconnects the slot from the signal
		virtual void SlotDisconnectAll(void){};

	protected:
		//!This is the spinlock mutex for thread constrol
		HtlSpinLock m_objLock;
		//!Collection of connected slots for this signal
		//HtlConnectionList m_arrPtrSlots; //EACH SIGNAL TYPE WILL HAVE ITS OWN COLLECTION
	};


};//end namespace HTL
#endif