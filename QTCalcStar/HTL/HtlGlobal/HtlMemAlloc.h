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

#ifndef HTL_MEM_ALLOC_H
#define HTL_MEM_ALLOC_H

#include "..\modHtlLibRefs.h"

namespace HTL{
	//MEMORY ALLOCATION FUNCTIONS///////////////////////////>>>
	//UNALIGNED MEMORY FUNCTIONS
	//!requests memory allocation for the desired size UNALIGNED. Returns NULL if unsuccessful.
	HTL_DLLAPI void* qMemAlloc(size_t intSize);
	//!Requests a memory re-allocation to an UNALIGNED new location. Returns NULL if unsuccessful.
	HTL_DLLAPI void* qMemReAlloc(void *ptr, size_t size);
	
	//ALIGNED MEMORY FUNCTIONS
	//!request memory allocation aligned to the desired location.  Returns NULL if unsuccessful.
	HTL_DLLAPI void* qMemAllocAligned(size_t size, size_t alignment);
	//!Requests a memory re-allocation to an aligned new location. Returns NULL if unsuccessful.
	HTL_DLLAPI void* qMemReAllocAligned(void *oldptr, size_t newsize, size_t oldsize, size_t alignment);

	//MEMORY FREE FUNCTIONS///////////////////////////>>>

	HTL_DLLAPI void qMemFree(void *ptr);

	HTL_DLLAPI void qMemFreeAligned(void *ptr);

};//end namespace HTL

#endif // HTL_MEM_ALLOC_H