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

#ifndef HTL_THREADDATA_H
#define HTL_THREADDATA_H

#include <windows.h>
//#include <process.h>
#include <stdio.h>

#include "..\modHtlLibRefs.h"
#include "..\modHtlGlobal.h"
#include "..\modHtlGUID.h"
#include "..\modHtlString.h"
#include "..\modHtlMacro.h"
using namespace std;

namespace HTL{
	//typedef void * HANDLE;
	//typedef unsigned long DWORD;
	//!The enumerated type describing thread priority
    enum HtlPriority
	{
        IdlePriority = 0,

        LowestPriority = 1,
        LowPriority = 2,
        NormalPriority = 3,
        HighPriority = 4,
        HighestPriority = 5,

        TimeCriticalPriority = 8,

        InheritPriority = 10
    };

	template <>
	HTL_EXPORT void enumToString<HtlPriority>(HtlPriority enumVal, std::string & strReturn);
	
	template <>
	HTL_EXPORT void stringToEnum<HtlPriority>(std::string & strVal, HtlPriority & enumValReturn);
	//!The enumerated type for describing thread data
	enum HtlThreadState
	{
		ThreadCrash = -2,
		ThreadTerminated = -1,
		ThreadStopped = 0,
		ThreadPaused = 1,
		ThreadWaiting = 2,
		ThreadRunning = 3,
		ThreadFinished = 4,
		ThreadExitedNormal = 5
	};

	template <>
	HTL_EXPORT void enumToString<HtlThreadState>(HtlThreadState enumVal, std::string  & strReturn);
	
	template <>
	HTL_EXPORT void stringToEnum<HtlThreadState>(std::string  & strVal, HtlThreadState & enumValReturn);
	
	//!HtlThreadData is a struct that contains information about the locking thread.
	/*!
	HtlThreadData is a struct that contains information about the locking thread.
	This information includes the GUID of the locking thread, and time stamp information
	for determining how long the lock has been active for timeout overrides.
	*/
	struct HTL_DLLAPI HtlThreadData
	{
	public:
		HtlThreadData()
		{
			clear();
			m_objTGUID.newID();
		};



	public:
		//!Thread Global Unique IDentifier for locking protection purposes
		HtlGUID128 m_objTGUID;
		//!pointer to the parent Node
		HANDLE m_ptrWinHandle;
		//!pointer to the parent Node
		DWORD m_ptrWinAddr;	
		//!boolean flag to indicate the thread is running
		HtlThreadState m_objState;
		
		//!boolean flag to indicate the thread is running
		HtlPriority m_objPriority;
		//!pointer to the parent Node
		int m_intRetCode;
		//!pointer to the parent Node
		unsigned int  m_intStackSize;


	public:
		//!clear the thread data
		void clear(void)
		{
			m_objTGUID.setNull();
			m_ptrWinHandle = NULL;
			m_ptrWinAddr = 0;
			m_objState = ThreadStopped;
			m_intRetCode = 0;
			m_intStackSize = 0;
		};
	};

};//end namespace HTL

#endif //HTL_THREADDATA_H