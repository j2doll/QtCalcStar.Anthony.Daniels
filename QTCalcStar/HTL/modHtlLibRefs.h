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

/****************************************************************************
**
** Copyright (C) 2010 Nokia Corporation and/or its subsidiary(-ies).
** All rights reserved.
** Contact: Nokia Corporation (qt-info@nokia.com)
**
** This file is part of the QtCore module of the Qt Toolkit.
**
** $HTL_BEGIN_LICENSE:LGPL$
** Commercial Usage
** Licensees holding valid Qt Commercial licenses may use this file in
** accordance with the Qt Commercial License Agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and Nokia.
**
** GNU Lesser General Public License Usage
** Alternatively, this file may be used under the terms of the GNU Lesser
** General Public License version 2.1 as published by the Free Software
** Foundation and appearing in the file LICENSE.LGPL included in the
** packaging of this file.  Please review the following information to
** ensure the GNU Lesser General Public License version 2.1 requirements
** will be met: http://www.gnu.org/licenses/old-licenses/lgpl-2.1.html.
**
** In addition, as a special exception, Nokia gives you certain additional
** rights.  These rights are described in the Nokia Qt LGPL Exception
** version 1.1, included in the file LGPL_EXCEPTION.txt in this package.
**
** GNU General Public License Usage
** Alternatively, this file may be used under the terms of the GNU
** General Public License version 3.0 as published by the Free Software
** Foundation and appearing in the file LICENSE.GPL included in the
** packaging of this file.  Please review the following information to
** ensure the GNU General Public License version 3.0 requirements will be
** met: http://www.gnu.org/copyleft/gpl.html.
**
** If you have questions regarding the use of this file, please contact
** Nokia at qt-info@nokia.com.
** $HTL_END_LICENSE$
**
****************************************************************************/

/*
The High Performance Computing Template Library is a synthesis of the

QT, BOOST, and STL Libraries

The purpose is to provide a cohesive base architecture package encapsulated
in a dynamic link library or static library.  Some of the design principles:

VERY LIMITED use of macros.
Separate containers from algorithms
Mutex protection to allow for Multi-Thread Safety
*/

#pragma once
#pragma warning (disable : 4251 ) /* sprintf, sscanf unsafe */
#pragma warning (disable : 4996 ) /* The POSIX name for this item is deprecated. */

//Htl Dynamic Link Library definitions
#ifndef HTL_LIB_REFS_H
#define HTL_LIB_REFS_H

#ifdef HTL_DLLEXPORT
	//configure for dll export
	#define HTL_DLLAPI __declspec(dllexport)
#else
	//configure for dll import
	#define HTL_DLLAPI __declspec(dllimport)
#endif

#ifndef HTL_EXPORT
#define HTL_EXPORT __declspec(dllexport)
#endif

#ifndef HTL_IMPORT
#define HTL_IMPORT __declspec(dllimport)
#endif

#define HTL_VERSION_STR "0.1.0"
/*
   HTL_VERSION is (major << 16) + (minor << 8) + patch.
*/
#define HTL_VERSION 0x000100


#ifndef HTL_CPP_TYPEDEFS
#define HTL_CPP_TYPEDEFS
//!Unsigned 
		typedef unsigned char uchar;
		typedef unsigned short ushort;
		typedef unsigned int uint;
		typedef unsigned long ulong;
		typedef long long longlong;
		typedef unsigned long long ulonglong;
#define NULL 0
#endif

//Standard Template Library Includes
#ifndef HTL_STD_LIB_INCLUDES
	#define HTL_STD_LIB_INCLUDES
	#include <stdarg.h>
	#include <typeinfo>
	//streaming input / output
	//#include <conio.h>
	#include <istream>
	#include <ostream>
	#include <iostream>
	#include <sstream>
	#include <fstream>
	#include <stdio.h>
#endif


#endif