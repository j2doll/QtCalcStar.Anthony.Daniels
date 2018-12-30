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

#include ".\HtlSpinLock.h"

namespace HTL{
	//!HtlSpinLock VOID Constructor
	HtlSpinLock::HtlSpinLock(void)
	{
		//set unlocked
		m_blnLocked = false;
		m_objPassword.setNull();
	};

	//!HtlSpinLock Password Constructor
	HtlSpinLock::HtlSpinLock(HtlGUID128 & objPassword)
	{
		//set unlocked
		m_blnLocked = false;	
		m_objPassword = objPassword;
	};

	//!HtlSpinLock VOID Destructor
	/*!
	HtlSpinLock VOID Destructor. Note this destructor is not virtual
	because the Mutex Class is NOT intended to be inherited from.
	*/
	HtlSpinLock::~HtlSpinLock()
	{
		m_blnLocked = false;
	};

	//!This Method locks the mutex
	void HtlSpinLock::lock(HtlGUID128 & objThreadID)
	{
		while(m_blnLocked)
		{
			//spin here until unlocked
		};
		//unlocked now//set lock
		m_blnLocked = true;
		//set current thread data
		m_objCurrThread.m_objTGUID = objThreadID;
		//control is now given to threadID
		return;	
	};

	//!This Method forces the Mutex to Release its lock.
	/*!
	This Method forces the Mutex to Release its lock.
	IMPORTANT!!! Forcing a lock release is an EMERGENCY ADMIN override.
	It boots out the processing thread that is currently using the
	critical resource protected by the mutex.
	*/
	void HtlSpinLock::forceUnlock(HtlGUID128 & objPassword)
	{
		//check password, if match then allow forced unlock and thread ID clearing	
		if(m_objPassword == objPassword)
		{
			//PASSWORD MATCH, ACCESS GRANTED
			//clear the threadID first then unlock the spinlock
			m_objCurrThread.clear();
			m_blnLocked = false;
		};
		return;
	};

	//!This Method unlocks the mutex
	void HtlSpinLock::unlock(HtlGUID128 & objReqThreadID)
	{
		//check incoming threadID requesting the unlock with
		//the current owning threadID, if they are a match, grant the unlock
		if(m_objCurrThread.m_objTGUID == objReqThreadID)
		{
			//KEYS match, this is the locking thread
			//ALLOW UNLOCK
			m_objCurrThread.clear();
			m_blnLocked = false;
		};
		return;
	};

};//end namespace HTL

