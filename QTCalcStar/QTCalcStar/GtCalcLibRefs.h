/*
**	This file is part of the GtCalc Function Evaluator library.
**  License information is in the GtLicense.h file.
**	This software was developed by:
**	
**  Anthony Daniels (copyright 2014)
** AnthonyDaniels99@gmail.com
**
**  GtCalc is free software: you can redistribute it and/or modify
**  it under the terms of the GNU Lesser General Public License as published by
**  the Free Software Foundation, either version 3 of the License, or
**  (at your option) any later version.
**
**
**  GtCalc is distributed in the hope that it will be useful,
**  but WITHOUT ANY WARRANTY; without even the implied warranty of
**  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
**  GNU Lesser General Public License for more details.
**
**  You should have received a copy of the GNU Lesser General Public License
**  along with GtCalc.  If not, see <http://www.gnu.org/licenses/>.
*/
#pragma once

//Gt Dynamic Link Library definitions
#ifndef GtCalc_LIB_REFS_H
#define GtCalc_LIB_REFS_H

#ifdef HTL_DLLEXPORT
	//configure for dll export
	#define HTL_DLLAPI __declspec(dllexport)
#else
	//configure for dll import
	#define HTL_DLLAPI __declspec(dllimport)
#endif

#ifndef GtCalc_EXPORT
#define GtCalc_EXPORT __declspec(dllexport)
#endif

#ifndef GtCalc_IMPORT
#define GtCalc_IMPORT __declspec(dllimport)
#endif

#define GtCalc_VERSION_STR "0.1.0"
/*
   Gt_VERSION is (major << 16) + (minor << 8) + patch.
*/
#define GtCalc_VERSION 0x000100

#ifndef GtCalc_CPP_TYPEDEFS
#define GtCalc_CPP_TYPEDEFS
//!Unsigned 
	typedef unsigned int uint;
	typedef unsigned short ushort;
	typedef unsigned long ulong;
	typedef unsigned char uchar;
#endif

//Standard Template Library Includes
#ifndef GtCalc_STD_LIB_INCLUDES
	#define GtCalc_STD_LIB_INCLUDES
#include <stdlib.h>
#include <string>
#include <vector>
#include <ctype.h>
#include <math.h>
#endif

#endif
