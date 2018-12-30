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


#ifndef HTL_BASICMATH_H
#define HTL_BASICMATH_H

#include "..\modHtlLibRefs.h"
//SUPERSET OF STL MATH
#include <math.h>

namespace HTL
{

	namespace Math{
		HTL_DLLAPI double hround(double value, unsigned int numdecimals = 0);
		HTL_DLLAPI double htrunc(double value, unsigned int numdecimals = 0);

		HTL_DLLAPI double hfloor(double value, unsigned int numdecimals = 0);
		HTL_DLLAPI double hceil(double value, unsigned int numdecimals = 0);

		HTL_DLLAPI char * itoa(char * buf, int intValue);
		HTL_DLLAPI char * uitoa(char * buf, unsigned int uintValue);
		HTL_DLLAPI char * ltoa(char * buf, long lngValue);
		HTL_DLLAPI char * ultoa(char * buf, unsigned long lngValue);
		HTL_DLLAPI char * ftoa(char * buf, float sngValue);
		HTL_DLLAPI char * dtoa(char * buf, double dblValue);
		HTL_DLLAPI char * ftoa(char * buf, float sngValue,unsigned int numdecimals);
		HTL_DLLAPI char * dtoa(char * buf, double dblValue,unsigned int numdecimals);


		HTL_DLLAPI double factorial(int intX);
	};//end namespace Math

};//end HTL namespace

#endif //HTL_BASICMATH_H