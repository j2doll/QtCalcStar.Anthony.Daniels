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


#ifndef HTL_ENUMS_H
#define HTL_ENUMS_H
#include <string>
#include "..\modHtlLibRefs.h"

namespace HTL
{

	//!These are the template functions for conversion of enumerated types
	//to and from string form.

	template <typename T>
	HTL_EXPORT void enumToString(T enumVal, std::string & strReturn){return;};
	
	template <typename T>
	HTL_EXPORT void stringToEnum(std::string & strVal, T & enumValReturn){return;};


	//!HtlObjectType is an enumerated type that provides base class information
	/*!
	HtlObjectType is an enumerated type that provides base class information.
	It is often used in serialization and object querying and as a template argument. 
	The default is HtlUnknown Type.

	*/
	enum HTL_DLLAPI HtlObjectType
	{
		HtlUnknownType = -1,
		CPP_BOOL = 0,
		CPP_CHAR = 1,
		CPP_UCHAR = 2,
		CPP_SHORT = 3,
		CPP_USHORT = 4,
		CPP_INT = 5,
		CPP_UINT = 6, 
		CPP_LONG = 7,
		CPP_ULONG = 8,
		CPP_LONGLONG = 9,
		CPP_ULONGLONG = 10,
		CPP_FLOAT = 11,
		CPP_DOUBLE = 12,

		HTL_BASE = 20,
		HTL_BASE_PTR = 21,
		HTL_OBJECT = 22,
		HTL_OBJECT_PTR = 23,
		HTL_CONTAINER = 24,
		HTL_CONTAINER_PTR = 25,
		HTL_STRING = 26,
		HTL_ENUM = 27,
		HTL_GUID64 = 28,
		HTL_GUID128 = 29,
		HTL_GUID256 = 30,

		STL_STRING = 31,
		STL_CONTAINER = 32,
		STL_CONTAINER_PTR = 33
	};
	template <>
	HTL_EXPORT void enumToString<HtlObjectType>(HtlObjectType enumVal, std::string & strReturn);
	
	template <>
	HTL_EXPORT void stringToEnum<HtlObjectType>(std::string & strVal, HtlObjectType & enumValReturn);

	//!This is the enumerated type that determines recursive or non-recursive behavior of an object
	enum HTL_DLLAPI HtlRecursionMode
	{ 
		NonRecursive = 0,
		Recursive = 1
	};

	//!This is the enumerated type that indicates locking mode of an object
	enum HTL_DLLAPI HtlLockMode
	{ 
		InfiniteLock = 0,
		TimedLock = 1,
		ScopedLock = 2,
	};

	//!Enumerated Node Type Listing
	enum HTL_DLLAPI HtlArchNodeType
	{	
		NODE = 0,
		ELEMENT = 1,
		ATTRIBUTE = 2,
		COMMENT = 3,
		PROCESS = 4,
		DOCUMENT = 5
	};


};//end namespace HTL
#endif