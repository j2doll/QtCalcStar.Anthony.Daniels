/*
The High Performance Template Library is a Licensed as LGPL.
It is intended to provide a base object Architecture, with
Serialization, thread control, etc.  
It is based on a merger of QT, BOOST, STL, and SigSlots.
License information is in the HtlLicense.h file
October 2012
*/
#pragma once
#pragma warning(push)
#pragma warning (disable : 4005 ) /* macro redefinition */
#define HTL_DLLEXPORT
#pragma warning(pop)

#include ".\HtlMap.h"

namespace HTL
{
//compiler test vectors
	HtlMap<int,CPP_INT, double, CPP_DOUBLE> arrDblTest;
	
};