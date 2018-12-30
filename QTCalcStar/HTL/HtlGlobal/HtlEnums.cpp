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

#include ".\HtlEnums.h"


namespace HTL{

	template <>
	void enumToString<HtlObjectType>(HtlObjectType enumVal, std::string & strReturn)
	{
		try{
			switch(enumVal)
			{
				//HTL CPLUSPLUS NATIVE TYPES
			case HtlUnknownType: {strReturn = "HtlUnknownType";  return; break;};
			case CPP_BOOL: {strReturn = "CPP_BOOL";  return; break;};
			case CPP_CHAR: {strReturn = "CPP_CHAR";  return; break;};
			case CPP_UCHAR: {strReturn = "CPP_UCHAR";  return; break;};
			case CPP_SHORT: {strReturn = "CPP_SHORT";  return; break;};
			case CPP_USHORT: {strReturn = "CPP_USHORT";  return; break;};
			case CPP_INT: {strReturn = "CPP_INT";  return; break;};
			case CPP_UINT: {strReturn = "CPP_UINT";  return; break;};
			case CPP_LONG: {strReturn = "CPP_LONG";  return; break;};
			case CPP_ULONG: {strReturn = "CPP_ULONG";  return; break;};
			case CPP_FLOAT: {strReturn = "CPP_FLOAT";  return; break;};
			case CPP_DOUBLE: {strReturn = "CPP_DOUBLE";  return; break;};
				//HTL SERIALIZABLE OBJECTS
			case HTL_BASE: {strReturn = "HTL_BASE";  return; break;};
			case HTL_BASE_PTR: {strReturn = "HTL_BASE_PTR";  return; break;};
			case HTL_OBJECT: {strReturn = "HTL_OBJECT";  return; break;};
			case HTL_OBJECT_PTR: {strReturn = "HTL_OBJECT_PTR";  return; break;};
			case HTL_CONTAINER: {strReturn = "HTL_CONTAINER";  return; break;};
			case HTL_CONTAINER_PTR: {strReturn = "HTL_CONTAINER_PTR";  return; break;};
			case HTL_STRING: {strReturn = "HTL_STRING";  return; break;};
			case HTL_ENUM: {strReturn = "HTL_ENUM";  return; break;};
			case HTL_GUID64: {strReturn = "HTL_GUID64";  return; break;};	
			case HTL_GUID128: {strReturn = "HTL_GUID128";  return; break;};
			case HTL_GUID256: {strReturn = "HTL_GUID256";  return; break;};
				//STL SUPPORTED ITEMS
			case STL_STRING: {strReturn = "STL_STRING";  return; break;};	
			case STL_CONTAINER: {strReturn = "STL_CONTAINER";  return; break;};
			case STL_CONTAINER_PTR: {strReturn = "STL_CONTAINER_PTR";  return; break;};

				//DEFUALT UNKNOWN
			default: {strReturn = "HtlUnknownType";  return; break;};

			};
		}catch(...){
			strReturn = "";
		};
		return;
	};
	
	template <>
	void stringToEnum<HtlObjectType>(std::string & strVal, HtlObjectType & enumValReturn)
	{
		try{
			if(strVal.empty()){enumValReturn = HtlUnknownType; return;};
			//check by comparison
			//HTL CPLUSPLUS NATIVE TYPES
			if(strVal == "CPP_BOOL"){enumValReturn = CPP_BOOL; return;};
			if(strVal == "CPP_CHAR"){enumValReturn = CPP_CHAR; return;};
			if(strVal == "CPP_UCHAR"){enumValReturn = CPP_UCHAR; return;};
			if(strVal == "CPP_SHORT"){enumValReturn = CPP_SHORT; return;};
			if(strVal == "CPP_USHORT"){enumValReturn = CPP_USHORT; return;};
			if(strVal == "CPP_INT"){enumValReturn = CPP_INT; return;};
			if(strVal == "CPP_UINT"){enumValReturn = CPP_UINT; return;};
			if(strVal == "CPP_LONG"){enumValReturn = CPP_LONG; return;};
			if(strVal == "CPP_ULONG"){enumValReturn = CPP_ULONG; return;};
			if(strVal == "CPP_FLOAT"){enumValReturn = CPP_FLOAT; return;};
			if(strVal == "CPP_DOUBLE"){enumValReturn = CPP_DOUBLE; return;};
			//HTL SERIALIZABLE OBJECTS
			if(strVal == "HTL_BASE"){enumValReturn = HTL_BASE; return;};
			if(strVal == "HTL_BASE_PTR"){enumValReturn = HTL_BASE_PTR; return;};
			if(strVal == "HTL_OBJECT"){enumValReturn = HTL_OBJECT; return;};
			if(strVal == "HTL_OBJECT_PTR"){enumValReturn = HTL_OBJECT_PTR; return;};
			if(strVal == "HTL_CONTAINER"){enumValReturn = HTL_CONTAINER; return;};
			if(strVal == "HTL_CONTAINER_PTR"){enumValReturn = HTL_CONTAINER_PTR; return;};
			if(strVal == "HTL_STRING"){enumValReturn = HTL_STRING; return;};
			if(strVal == "HTL_ENUM"){enumValReturn = HTL_ENUM; return;};
			if(strVal == "HTL_GUID64"){enumValReturn = HTL_GUID64; return;};
			if(strVal == "HTL_GUID128"){enumValReturn = HTL_GUID128; return;};
			if(strVal == "HTL_GUID256"){enumValReturn = HTL_GUID256; return;};
			//STL SUPPORTED ITEMS
			if(strVal == "STL_STRING"){enumValReturn = STL_STRING; return;};
			if(strVal == "STL_CONTAINER"){enumValReturn = STL_CONTAINER; return;};
			if(strVal == "STL_CONTAINER_PTR"){enumValReturn = STL_CONTAINER_PTR; return;};


			//DEFUALT UNKNOWN
			enumValReturn = HtlUnknownType;
			return;
		}catch(...){
			enumValReturn = HtlUnknownType;
			return;
		};
	};

};//end namespace HTL