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
#ifndef HTL_TYPEINFO_H
#define HTL_TYPEINFO_H
#include "..\modHtlLibRefs.h"

namespace HTL{
	//REMOVE POINTER TYPE CASTING
	template <class T>
	struct RemovePointer
	{
		typedef T type;
	};

	template <class T>
	struct RemovePointer<T*>
	{
		typedef T type;
	};

	template <class T>
	struct RemoveAllPointers
	{
	public:
		typedef T type;
	};

	template <class T>
	struct RemoveAllPointers<T*>
	{
	public:
		typedef typename RemoveAllPointers<T>::type type;
	};
	//IS POINTER TYPE CHECK
	template <typename T>
	struct IsPointerType
	{     
		enum { value = false };
	};
	template <typename T>
	struct IsPointerType<T*>
	{
		enum { value = true };

	};
	template <typename T>
	bool IsPointer(void)
	{
		return IsPointerType<T>::value;
	};

	//Create Oject Type CHECK

	//IS VOID TYPE CHECK
	template <typename T>
	struct IsVoidType
	{     
		enum { value = false };
	};
	template <>
	struct IsVoidType<void>
	{
		enum { value = true };
	};
	template <typename T>
	bool IsVoid(void)
	{
		return IsVoidType<T>::value;
	};

	//IS TYPE CHECK
	//is
	template <typename B,typename D>
	bool DoesObjectInheritFrom( D & ptrObj)
	{     
		try{
			B objCheck;
			if(typeid(objCheck) == typeid((B)ptrObj))
			{
				return true;
			}else{
				return false;
			};
		}catch(...){
			return false;
		}
	};
	template <typename T,typename X>
	bool IsObjectType( X & ptrObj)
	{     
		try{
			T objCheck;
			if(typeid(objCheck) == typeid(ptrObj))
			{
				return true;
			}else{
				return false;
			};
		}catch(...){
			return false;
		}
	};
//!NullObjReturnType///////////////////////////////////////////////////////////
#pragma warning( push )
#pragma warning( disable : 4700) 
	//Default Null Object Returner
	template <typename T>
	struct NullObjReturnType
	{     
		static T DefReturn(void)
		{
			T objVal;
			return objVal;
		};
	};
#pragma warning( pop )

	template <typename T>
	struct NullObjReturnType<T*>
	{
		static T* DefReturn(void)
		{
			return NULL;
		};
	};

	template <typename T>
	struct NullObjReturnType<T&>
	{
		static T& DefReturn(void)
		{
			return NULL;
		};
	};

	template <>
	struct NullObjReturnType<void>
	{
		//sepecialization for void object
		static void DefReturn(void)
		{
			return;
		};
	};
	//shorts signed and unsigned
	template <>
	struct NullObjReturnType<short>
	{
		//sepecialization for short object
		static short DefReturn(void)
		{
			return 0;
		};
	};
	template <>
	struct NullObjReturnType<unsigned short>
	{
		//sepecialization for short object
		static unsigned short DefReturn(void)
		{
			return 0;
		};
	};
	//ints signed and unsigned
	template <>
	struct NullObjReturnType<int>
	{
		//sepecialization for short object
		static int DefReturn(void)
		{
			return 0;
		};
	};
	template <>
	struct NullObjReturnType<unsigned int>
	{
		//sepecialization for short object
		static unsigned int DefReturn(void)
		{
			return 0;
		};
	};
	//longs signed and unsigned
	template <>
	struct NullObjReturnType<long>
	{
		//sepecialization for short object
		static long DefReturn(void)
		{
			return 0;
		};
	};
	template <>
	struct NullObjReturnType<unsigned long>
	{
		//sepecialization for short object
		static unsigned long DefReturn(void)
		{
			return 0;
		};
	};
	//floats and doubles
	template <>
	struct NullObjReturnType<float>
	{
		//sepecialization for short object
		static float DefReturn(void)
		{
			return 0.0f;
		};
	};
	template <>
	struct NullObjReturnType<double>
	{
		//sepecialization for short object
		static double DefReturn(void)
		{
			return 0.0f;
		};
	};
	//chars signed and unsigned
	template <>
	struct NullObjReturnType<char>
	{
		//sepecialization for short object
		static char DefReturn(void)
		{
			return 0;
		};
	};
	template <>
	struct NullObjReturnType<unsigned char>
	{
		//sepecialization for short object
		static unsigned char DefReturn(void)
		{
			return 0;
		};
	};

//OBJECT TYPE INFORMATION

template <typename T>
class TypeInfo
{
public:
    enum {
        isPointer = false,
        isComplex = true,
        isStatic = true,
        isLarge = (sizeof(T)>sizeof(void*)),
        isDummy = false
    };
};

template <typename T>
class TypeInfo<T*>
{
public:
    enum {
        isPointer = true,
        isComplex = false,
        isStatic = false,
        isLarge = false,
        isDummy = false
    };
};

template <>
class TypeInfo<bool>
{
public:
    enum {isPointer = false, isComplex = false, isStatic = false, isLarge = false, isDummy = false };
};
template <>
class TypeInfo<char>
{
public:
    enum {isPointer = false, isComplex = false, isStatic = false, isLarge = false, isDummy = false };
};
template <>
class TypeInfo<unsigned char>
{
public:
    enum {isPointer = false, isComplex = false, isStatic = false, isLarge = false, isDummy = false };
};
template <>
class TypeInfo<short>
{
public:
    enum {isPointer = false, isComplex = false, isStatic = false, isLarge = false, isDummy = false };
};
template <>
class TypeInfo<unsigned short>
{
public:
    enum {isPointer = false, isComplex = false, isStatic = false, isLarge = false, isDummy = false };
};
template <>
class TypeInfo<int>
{
public:
    enum {isPointer = false, isComplex = false, isStatic = false, isLarge = false, isDummy = false };
};
template <>
class TypeInfo<unsigned int>
{
public:
    enum {isPointer = false, isComplex = false, isStatic = false, isLarge = false, isDummy = false };
};
template <>
class TypeInfo<long>
{
public:
    enum {isPointer = false, isComplex = false, isStatic = false, isLarge = false, isDummy = false };
};
template <>
class TypeInfo<unsigned long>
{
public:
    enum {isPointer = false, isComplex = false, isStatic = false, isLarge = false, isDummy = false };
};
template <>
class TypeInfo<float>
{
public:
    enum {isPointer = false, isComplex = false, isStatic = false, isLarge = false, isDummy = false };
};
template <>
class TypeInfo<double>
{
public:
    enum {isPointer = false, isComplex = false, isStatic = false, isLarge = false, isDummy = false };
};



};//end HTL namespace
#endif