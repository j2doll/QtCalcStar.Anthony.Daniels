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

#ifndef HTL_SPINLOCK_H
#define HTL_SPINLOCK_H

#include "..\modHtlLibRefs.h"
#include ".\HtlThreadData.h"
using namespace std;

namespace HTL{

	//!HtlSpinLock is a MUTual EXclusion locking mechanism for allowing multiple threads of execution to access protected code.
	/*!
	HtlSpinLock is a MUTual EXclusion locking mechanism for allowing multiple threads of execution to access protected code.
	It uses a simple SPIN LOCK Approach to locking.
	IMPORTANT.  SPIN LOCKS ARE CPU WASTEFUL.  This class should only be used for fast action locking where the time the critical
	section is locked is relatively small.  Longer running critical sections should be protected with a Mutex.
	*/

	class HTL_DLLAPI HtlSpinLock{

	public:
		
		//!HtlSpinLock VOID Constructor
		/*!
			The Spin Lock has the option of Password protection for forcing Lock Releases.
			The password is a HtlGUID128 identifier.  If the void constructor is used,
			the password is set to NULL, or 00000000-00000000-00000000-00000000
			Password protection of the spinlock allows for ADMIN ONLY access,
			or owner access to the forceUnlock() feature.  This means that only the owner
			of the spinlock password can force a lock release.
		*/
		HtlSpinLock(void);

		//!HtlSpinLock Password Constructor
		HtlSpinLock(HtlGUID128 & objPassword);
		//!HtlSpinLock VOID Destructor

		/*!
		HtlSpinLock VOID Destructor. Note this destructor is not virtual
		because the Mutex Class is NOT intended to be inherited from.
		*/
		~HtlSpinLock();

		//!This Method locks the mutex
		/*!
		All locking and unlocking of the thread mutex is handled
		by passing the GUID of the requesting thread to the the spinlock.
		ALL threads have a 128 bit GUID attached to them that is accessible
		through the static function getThreadID(). This GUID acts as a key 
		ensuring that only the thread that set the lock can call the successive unlock.
		The ADMIN password can alternatively force an unlock and boot the calling thread out.
		*/
		void lock(HtlGUID128 & objThreadID);
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
	};//end class HtlSpinLock

};//end namespace HTL
#endif