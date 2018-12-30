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

#ifndef HTL_STOPWATCH_H
#define HTL_STOPWATCH_H
#include <string>
using namespace std;

#include "..\modHtlLibRefs.h"
#include "..\modHtlGlobal.h"


namespace HTL{
	typedef unsigned long usec_t;
	typedef unsigned long long utime_t;
	//!HtlStopWatch is a basic elapsed timer class that provides clock based elapsed times
	/*!
		HtlStopWatch is a basic elapsed timer class that provides clock based elapsed times
	*/

	class HTL_DLLAPI HtlStopWatch
	{

		HtlStopWatch();
		~HtlStopWatch();

	public:

		//!Time of the start point
		HTLMEMVAR_BYVAL_STYLE1(public, utime_t, TStart);
		//!Time of the stop point
		HTLMEMVAR_BYVAL_STYLE1(public, utime_t, TEnd);
		//!pointer to the parent Node
		HTLMEMVAR_BYVAL_STYLE1(public, bool, blnValid);
		//!Initialize the stop watch timer
		void initialize(void);


		//!Starts the elapsed timer
		void start();
		//!Stops the elapsed timer
		void stop();


		//!Gets the elapsed time in seconds
		usec_t secsElapsed() const;
		//!Gets the elapsed time in milliseconds
		utime_t msecsElapsed() const;
		//!Gets the elapsed time in nanoseconds
		utime_t nsecsElapsed() const;

		//!checls to see if timeout has expired
		bool hasExpired(utime_t msecsTimeout);
		
		//!get the frequency
		static utime_t GetCounterFreq();

	private:
		//the system clock frequency
		static utime_t m_uintCounterFreq;
	};

};//end namespace HTL
#endif //HTL_STOPWATCH_H