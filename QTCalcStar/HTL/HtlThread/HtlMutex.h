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

#ifndef HTL_MUTEX_H
#define HTL_MUTEX_H

#include "..\modHtlLibRefs.h"
#include "..\modHtlGlobal.h"
#include "..\modHtlGUID.h"
#include "..\modHtlContainer.h"
using namespace std;

namespace HTL{

	//!HtlMutexData is a struct that contains information about the locking thread.
	/*!
	HtlMutexData is a struct that contains information about the locking thread.
	This information includes the GUID of the locking thread, and time stamp information
	for determining how long the lock has been active for timeout overrides.
	*/
	struct HtlMutexData
	{

	};

	//!HtlMutex is a MUTual EXclusion locking mechanism for allowing multiple threads of execution to access protected code.
	/*!
	HtlMutex is a MUTual EXclusion locking mechanism for allowing multiple threads of execution to access protected code.
	The HtlMutex uses a First In First Out locking control mechanism for controlling thread access.
	Waiting threads are put to sleep until signaled it is their turn to access the protected code controlled by the MUTEX.
	Locks can be either timed or infinite and can allow for both recursive and non-recursive modes
	*/

	class HTL_DLLAPI HtlMutex{

	public:
		//!HtlSpinLock VOID Constructor
		/*!
			The HtlMutex has the option of Password protection for forcing Lock Releases.
			The password is a HtlGUID128 identifier.  If the void constructor is used,
			the password is set to NULL, or 00000000-00000000-00000000-00000000
			Password protection of the spinlock allows for ADMIN ONLY access,
			or owner access to the forceUnlock() feature.  This means that only the owner
			of the spinlock password can force a lock release.
		*/
		HtlMutex(void);

		//!HtlSpinLock Password Constructor
		HtlMutex(HtlGUID128 & objPassword);
		//!HtlMutex VOID Destructor
		/*!
		HtlMutex VOID Destructor. Note this destructor is not virtual
		because the Mutex Class is NOT intended to be inherited from.
		*/
		~HtlMutex();
		
		//!Boolean flag indicating if the Mutex is Recursive allowed. TRUE = Recursive, FALSE = NonRecursive
		HTLMEMVAR_BYVAL_STYLE1(public, bool, blnRecursive);	
		//!Enumerated flag indicating the Lock Operating Mode
		HTLMEMVAR_BYVAL_STYLE1(public, HtlLockMode, objLockMode);


		//!This Method locks the mutex
		void lock(HtlGUID128 & objThreadID);
		//!This Method trys to lock the mutex but passes through a failed lock
		bool tryLock(HtlGUID128 & objThreadID);
		//!This Method trys to lock the mutex with a TIMEOUT of Milliseconds
		bool tryLockTimeoutMsec(HtlGUID128 & objThreadID, int intMilliseconds);
		//!This Method trys to lock the mutex with a TIMEOUT of Seconds
		bool tryLockTimeoutSec(HtlGUID128 & objThreadID, int intSeconds);
		//!This Method forces the Mutex to Release its lock.
		/*!
			This Method forces the Mutex to Release its lock.
			IMPORTANT!!! Forcing a lock release is an EMERGENCY ADMIN override.
			It boots out the processing thread that is currently using the
			critical resource protected by the mutex.
		*/
		void forceUnlock(HtlGUID128 & objPassword);
		//!This Method unlocks the mutex
		void unlock(HtlGUID128 & objReqThreadID);


		private:
		//!The boolean flag indicating that the spinlock is locked = TRUE, or unlocked = FALSE
		bool m_blnLocked;
		//!The thread data of the currently locking thread
		HtlThreadData m_objCurrThread;
		//!The password protection for access to the forceUnlock feature of the spinlock
		HtlGUID128 m_objPassword;
		//!this is the locking thread GUID queue.  It is a FIFO Queue.
		Htl1DVector<HtlGUID128, HTL_GUID128> m_objTQueue;

	};

};//end namespace HTL
#endif