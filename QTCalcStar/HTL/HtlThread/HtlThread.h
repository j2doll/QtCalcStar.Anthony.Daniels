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

#ifndef HTL_THREAD_H
#define HTL_THREAD_H

#include ".\HtlThreadMap.h"
#include "..\modHtlSignalSlot.h"
#include "..\modHtlGUID.h"
using namespace std;

namespace HTL{

	typedef DWORD(*VoidFuncPtr)(void* ptrParam);

	//!Get the pointer to the global thread map server
	static HtlThreadMap* GetThreadMapPtr(void);
	//!Get the handle to the current thread ID
	static DWORD CurrentThreadId(void);
	//!Get the GUID to the current thread GUID
	static HtlGUID128 CurrentThreadGUID(void);
	//!Get the pointer to the current thread
	static HtlThread * CurrentThreadPtr(void);


	class HTL_DLLAPI HtlThread : public HtlHasSlots
	{
	public:
		//standard constructors
		HtlThread();
		~HtlThread();

		//!the thread data structured variable
		HTLMEMVAR_BYVAL_STYLE1(public, HtlThreadData, objTData);
		//!the thread boolean terminate flag
		HTLMEMVAR_BYVAL_STYLE1(public, bool, blnTerminate);
		//!the thread boolean terminate flag
		HTLMEMVAR_BYVAL_STYLE1(public, VoidFuncPtr, ptrThreadFunc);
		//!the thread boolean terminate flag
		HTLMEMVAR_BYVAL_STYLE1(public, void*, ptrParam);
		//!Initialize and create the thread in the suspended state
		int init(void);
		//!START the thread with the set priority
		void start(void);
		//!PAUSE the thread
		void pause(void);
		//!RESUME the thread
		void resume(void);
		//!STOP TERMINATE the thread
		void stop(void);

		//!default argument causes thread to block indefinately
		bool wait(unsigned long time = ULONG_MAX);
		//!Sleep thread for seconds
		static void sleep(unsigned long);
		//!Sleep thread for milliseconds
		static void msleep(unsigned long);
		//!Sleep thread for microseconds
		static void usleep(unsigned long);

		//SIGNALS////////////////////////////////////////////////
		//!Thread Started signal
		HtlSignal00 started();
		//!Thread Stopped signal
		HtlSignal00 stopped();
		//!Thread terminated signal
		HtlSignal00 terminated();
		//!Thread state change signal
		HtlSignal00 state_changed();

	protected:
		//!the overridable thread function setup
		virtual void initialize(void);
		//!the overridable thread function
		virtual void run(void);
		//!the overridable thread function cleanup
		virtual void cleanup(void);

	};//end HtlThread class definition


};//end namespace HTL

#endif