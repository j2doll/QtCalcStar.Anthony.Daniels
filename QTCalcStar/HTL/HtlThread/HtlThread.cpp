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

#include ".\HtlThread.h"
#include <process.h>

namespace HTL
{
	//!Global thread map server,  Get one of these per process.
	//!Embedded in the HTL dll.
	HtlThreadMap* GetThreadMapPtr(void)
	{
		static HtlThreadMap m_objThreadMap;
		return &(m_objThreadMap);
	};

	static DWORD CurrentThreadId()
	{
		return GetCurrentThreadId();
	};

	static HtlGUID128 CurrentThreadGUID()
	{
		HtlThreadID objCurrID;
		objCurrID = GetThreadMapPtr()->FindThread(GetCurrentThreadId());
		return objCurrID.m_objGUID;	
	};

	static HtlThread * CurrentThreadPtr(void)
	{
		HtlThreadID objCurrID;
		objCurrID = GetThreadMapPtr()->FindThread(GetCurrentThreadId());
		return objCurrID.m_ptrThread;	
	};


		//standard constructors
	HtlThread::HtlThread()
	{
		//!the thread boolean terminate flag
		m_blnTerminate = false;
		m_ptrThreadFunc = NULL;
		m_ptrParam = NULL;
	};

	HtlThread::~HtlThread()
	{
		this->cleanup();	
	};

	//!Initialize and create the thread in the suspended state
	int HtlThread::init(void)
	{
	
		if(!m_ptrThreadFunc){return -1;};//thread function not set
		DWORD intPtrT;
		//create the windows thread in suspended form during initialize
		m_objTData.m_ptrWinHandle = (HANDLE)CreateThread(NULL, //security
			0,//default stack size
			(LPTHREAD_START_ROUTINE)m_ptrThreadFunc,//pointer to the thread function
			(LPVOID)m_ptrParam,//argument list to the function ONLY ALLOW VOID*
			CREATE_SUSPENDED,//initialize suspended
			&intPtrT);//pointer to the actual thread
				
		m_objTData.m_ptrWinAddr = intPtrT;
		//register it with the thread map server
		HtlThreadID newThread;
		newThread.m_intWinID = m_objTData.m_ptrWinAddr;
		newThread.m_objGUID = m_objTData.m_objTGUID;
		newThread.m_ptrThread = this;
		GetThreadMapPtr()->Register(newThread);
		return 1;
	};



	//!START the thread with the set priority
	void HtlThread::start(void)
	{
		/*
		NOTE: we create the thread in the suspended state, set the
		priority and then resume the thread.

		since threads are created with normal priority by default, we
		could get into a case where a thread (with priority less than
		NormalPriority) tries to create a new thread (also with priority
		less than NormalPriority), but the newly created thread preempts
		its 'parent' and runs at normal priority.
		*/
		std::string strName = "HtlThread.txt";
		HTL::HtlDebugPrinter objDebug;
		objDebug.Set_strFileName(strName);
		objDebug.Set_blnPrintToFile(false);
		objDebug.DebugPrint(1,"HtlThread::start()\n");

		if (!m_objTData.m_ptrWinAddr) {
			objDebug.DebugPrint(1,"HtlThread::start: Failed to create thread\n");
			m_objTData.m_objState = ThreadFinished;
			return;
		}
		
		objDebug.DebugPrint(1,"Setting thread priority\n");
		int prio;
		switch (m_objTData.m_objPriority) {
	case IdlePriority:
		prio = THREAD_PRIORITY_IDLE;
		break;

	case LowestPriority:
		prio = THREAD_PRIORITY_LOWEST;
		break;

	case LowPriority:
		prio = THREAD_PRIORITY_BELOW_NORMAL;
		break;

	case NormalPriority:
		prio = THREAD_PRIORITY_NORMAL;
		break;

	case HighPriority:
		prio = THREAD_PRIORITY_ABOVE_NORMAL;
		break;

	case HighestPriority:
		prio = THREAD_PRIORITY_HIGHEST;
		break;

	case TimeCriticalPriority:
		prio = THREAD_PRIORITY_TIME_CRITICAL;
		break;

	case InheritPriority:
	default:
		prio = GetThreadPriority(GetCurrentThread());
		break;
		}

		if (!SetThreadPriority(m_objTData.m_ptrWinHandle, prio))
		{
			objDebug.DebugPrint(1,"HtlThread::start: Failed to set priority\n");
		}
		objDebug.DebugPrint(1,"Resuming Thread\n");
		m_objTData.m_objState = ThreadRunning;
		if (ResumeThread(m_objTData.m_ptrWinHandle) == (DWORD) -1)
		{
			objDebug.DebugPrint(1,"HtlThread::start: Failed to resume new thread\n");
		}	

	};

	//!PAUSE the thread
	void HtlThread::pause(void)
	{
		m_objTData.m_objState = ThreadPaused;
		SuspendThread(m_objTData.m_ptrWinHandle);
		return;
	};
	//!PAUSE the thread
	void HtlThread::resume(void)
	{
		m_objTData.m_objState = ThreadRunning;
		ResumeThread(m_objTData.m_ptrWinHandle);
		return;
	};
	//!STOP TERMINATE the thread
	void HtlThread::stop()
	{
		try{
		m_objTData.m_objState = ThreadTerminated;
		TerminateThread(m_objTData.m_ptrWinHandle, 0);
		}catch(...){
			//qWarning("QThread::wait: Thread tried to wait on itself");
			return;
		};

	};

	// default argument causes thread to block indefinately
	bool HtlThread::wait(unsigned long time)
	{


		if (m_objTData.m_ptrWinAddr == GetCurrentThreadId()) {
			//qWarning("QThread::wait: Thread tried to wait on itself");
			return false;
		}
		if ((m_objTData.m_objState == ThreadFinished) ||
			(m_objTData.m_objState != ThreadRunning) )
		{
			return true;
		};

		bool ret = false;
		switch (WaitForSingleObject(m_objTData.m_ptrWinHandle, time)) {
	case WAIT_OBJECT_0:
		ret = true;
		break;
	case WAIT_FAILED:
		//qErrnoWarning("QThread::wait: Thread wait failure");
		break;
	case WAIT_ABANDONED:
	case WAIT_TIMEOUT:
	default:
		break;
		};

		return ret;	

	};

	void HtlThread::sleep(unsigned long secs)
	{
		::Sleep(secs * 1000);
	};

	void HtlThread::msleep(unsigned long msecs)
	{
		::Sleep(msecs);
	};

	void HtlThread::usleep(unsigned long usecs)
	{
		::Sleep((usecs / 1000) + 1);
	};

	//the overridable thread function setup
	void HtlThread::initialize(void){return;};
	//the overridable thread function
	void HtlThread::run(void){return;};
	//the overridable thread function cleanup
	void HtlThread::cleanup(void){return;};



};//end HTL namespace