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
#include <windows.h>
#include ".\HtlStopWatch.h"
using namespace std;

namespace HTL{


	typedef ULONGLONG (WINAPI *PtrGetTickCount64)(void);
	static PtrGetTickCount64 ptrGetTickCount64 = 0;

	utime_t HtlStopWatch::m_uintCounterFreq = 0;
	//!get the frequency
	utime_t HtlStopWatch::GetCounterFreq()
	{
		return m_uintCounterFreq;
	};

	static inline utime_t ticksToNanoseconds(utime_t ticks)
	{
		if (HtlStopWatch::GetCounterFreq() > 0) {
			// QueryPerformanceCounter uses an arbitrary frequency
			utime_t seconds = ticks / HtlStopWatch::GetCounterFreq();
			utime_t nanoSeconds = (ticks - seconds * HtlStopWatch::GetCounterFreq()) * 1000000000 / HtlStopWatch::GetCounterFreq();
			return seconds * 1000000000 + nanoSeconds;
		} else {
			// GetTickCount(64) return milliseconds
			return ticks * 1000000;
		}
	}

	static utime_t getTickCount()
	{

		// This avoids a division by zero and disables the high performance counter if it's not available
		if (HtlStopWatch::GetCounterFreq() > 0) {
			LARGE_INTEGER counter;

			if (QueryPerformanceCounter(&counter)) {
				return counter.QuadPart;
			} else {
				// qWarning("QueryPerformanceCounter failed, although QueryPerformanceFrequency succeeded.");
				return 0;
			};
		};
		return 0;
	};
	HtlStopWatch::HtlStopWatch()
	{
		//initialize the frequency converter.
		initialize();

	};
	HtlStopWatch::~HtlStopWatch()
	{

	};

	void HtlStopWatch::initialize(void)
	{

		// Retrieve the number of high-resolution performance counter ticks per second
		LARGE_INTEGER frequency;
		if (!QueryPerformanceFrequency(&frequency))
		{
			m_uintCounterFreq = 0;
		} else {
			m_uintCounterFreq = frequency.QuadPart;
		};
	};
	//!Starts the elapsed timer
	void HtlStopWatch::start()
	{
		m_TStart = getTickCount();
		m_TEnd = 0;
	};

	//!Stops the elapsed timer
	void HtlStopWatch::stop()
	{

		m_TEnd = getTickCount();		

	};

	//!Gets the elapsed time in seconds
	usec_t HtlStopWatch::secsElapsed() const
	{
		utime_t elapsed = getTickCount() - m_TStart;
		return (usec_t)(ticksToNanoseconds(elapsed) / 1000000);
	};
	//!Gets the elapsed time in milliseconds
	utime_t HtlStopWatch::msecsElapsed() const
	{
		utime_t elapsed = getTickCount() - m_TStart;
		return ticksToNanoseconds(elapsed) / 1000;
	};
	//!Gets the elapsed time in nanoseconds
	utime_t HtlStopWatch::nsecsElapsed() const
	{
		utime_t elapsed = getTickCount() - m_TStart;
		return ticksToNanoseconds(elapsed);	

	};

	//!checls to see if timeout has expired
	bool HtlStopWatch::hasExpired(utime_t msecsTimeout)
	{
		utime_t elapsed = getTickCount() - m_TStart;
		utime_t intMSecs = ticksToNanoseconds(elapsed) / 1000;

		return (intMSecs < msecsTimeout);
	};

};//end namespace HTL