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

#include ".\HtlMemAlloc.h"
#include <stdlib.h>

namespace HTL{
	//!HtlMemAlloc VOID Constructor
	void *qMemAlloc(size_t size)
	{
		return ::malloc(size);
	}

	void *qMemReAlloc(void *ptr, size_t size)
	{
		return ::realloc(ptr, size);
	}

	void qMemFree(void *ptr)
	{
		::free(ptr);
	}


	void *qMemAllocAligned(size_t size, size_t alignment)
	{
		return qMemReAllocAligned(0, size, 0, alignment);
	}

	void *qMemReAllocAligned(void *oldptr, size_t newsize, size_t oldsize, size_t alignment)
	{
		// fake an aligned allocation
		//Q_UNUSED(oldsize);

		void *actualptr = oldptr ? static_cast<void **>(oldptr)[-1] : 0;
		if (alignment <= sizeof(void*)) {
			// special, fast case
			void **newptr = static_cast<void **>(qMemReAlloc(actualptr, newsize + sizeof(void*)));
			if (!newptr)
				return 0;
			if (newptr == actualptr) {
				// realloc succeeded without reallocating
				return oldptr;
			}

			*newptr = newptr;
			return newptr + 1;
		}

		union { void *ptr; void **pptr; unsigned int* n; } real, faked;

		// qMalloc returns pointers aligned at least at sizeof(size_t) boundaries
		// but usually more (8- or 16-byte boundaries).
		// So we overallocate by alignment-sizeof(size_t) bytes, so we're guaranteed to find a
		// somewhere within the first alignment-sizeof(size_t) that is properly aligned.

		// However, we need to store the actual pointer, so we need to allocate actually size +
		// alignment anyway.

		real.ptr = qMemReAlloc(actualptr, newsize + alignment);
		if (!real.ptr)
			return 0;

		faked.n = real.n + alignment;
		//faked.n &= ~(alignment - 1);

		// now save the value of the real pointer at faked-sizeof(void*)
		// by construction, alignment > sizeof(void*) and is a power of 2, so
		// faked-sizeof(void*) is properly aligned for a pointer
		faked.pptr[-1] = real.ptr;

		return faked.ptr;
	}

	void qMemFreeAligned(void *ptr)
	{
		if (!ptr)
			return;
		void **ptr2 = static_cast<void **>(ptr);
		free(ptr2[-1]);
	}




};//end namespace HTL