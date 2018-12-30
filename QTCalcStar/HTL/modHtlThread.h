/*
	The High Performance Template Library is a Licensed as LGPL.
	It is intended to provide a base object architecture, with
	Serialization, thread control, etc.  
	It is based on a merger of QT, BOOST, STL, and SigSlots.
	License information is in the HtlLicense.h file
	October 2012
*/

#pragma once

#ifndef MOD_HTL_THREAD_H
#define MOD_HTL_THREAD_H
#include <string>
using namespace std;

#include ".\modHtlLibRefs.h"
#include ".\HtlThread\HtlThreadData.h"
#include ".\HtlThread\HtlSpinLock.h"
#include ".\HtlThread\HtlThreadMap.h"
#include ".\HtlThread\HtlMutex.h"
#include ".\HtlThread\HtlThread.h"

#endif //MOD_HTL_GLOBAL_H