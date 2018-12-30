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

#ifndef HTL_THREADMAP_H
#define HTL_THREADMAP_H

#include <map>

#include "..\modHtlLibRefs.h"
#include ".\HtlThreadData.h"
#include ".\HtlSpinLock.h"

using namespace std;

namespace HTL{

	class HtlThread;

	//This is a triplet tuple  for storing Tread Identificiation and pointer information
	struct HTL_DLLAPI HtlThreadID
	{
		HtlThreadID()
		{
			m_intWinID = 0;
			m_objGUID.setNull();
			m_ptrThread = NULL;
		};

	public:
		//!Windows thread ID
		DWORD m_intWinID;
		//!HtlThread 128 bit GUID
		HtlGUID128 m_objGUID;
		//!Pointer to the actual thread
		HtlThread* m_ptrThread;
	};

	/*!
	The HtlThreadMap is a thread safe wrapper around a std::map<HANDLE,HtlThreadID>
	It provides access globally to the threads that are active in the current process
	*/
	class HTL_DLLAPI HtlThreadMap
	{
	public:
		//!Register the thread with the map server
		void Register(HtlThreadID objTid);
		//!UnRegister the thread with the map server
		void UnRegister(HtlThreadID objTid);
		//!Find a thread based on its Windows ID handle
		HtlThreadID FindThread(DWORD intID);
		//!Find a thread based on the GUID handle
		HtlThreadID FindThread(HtlGUID128 objID);
	private:
		std::map<DWORD,HtlThreadID> m_objTMap;

		//!This is the spinlock mutex for thread constrol
		HtlSpinLock m_objLock;
	};

};//end namespace HTL
#endif //HTL_THREADDATA_H