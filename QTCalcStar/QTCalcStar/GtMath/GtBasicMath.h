/*
**	This file is part of the GT Core Library.
**  It is based on a merger of QT along with development of new classes.
**  License information is in the License.h file
**	This software was merged and developed by:
**	
**  Anthony Daniels
**	QT by Nokia
**
**  GT is free software: you can redistribute it and/or modify
**  it under the terms of the GNU Lesser General Public License as published by
**  the Free Software Foundation, either version 3 of the License, or
**  (at your option) any later version.
**
**  The United States of America Department of Defense has unlimited 
**	usage, redistribution, and modification rights to GT.
**
**  GT is distributed in the hope that it will be useful,
**  but WITHOUT ANY WARRANTY; without even the implied warranty of
**  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
**  GNU Lesser General Public License for more details.
**
**  You should have received a copy of the GNU Lesser General Public License
**  along with GT.  If not, see <http://www.gnu.org/licenses/>.
*/
#ifndef GT_BASICMATH_H
#define GT_BASICMATH_H
#include <math.h>


__declspec(dllexport) int gRound(double value);
__declspec(dllexport) double gRound(double value, unsigned int numdecimals);
__declspec(dllexport) double gTrunc(double value, unsigned int numdecimals);
__declspec(dllexport) double gFactorial(int intX);

__declspec(dllexport) double floor(double value, unsigned int numdecimals);
__declspec(dllexport) double ceil(double value, unsigned int numdecimals);

__declspec(dllexport) char * itoa(char * buf, int intValue);
__declspec(dllexport) char * uitoa(char * buf, unsigned int uintValue);
__declspec(dllexport) char * ltoa(char * buf, long lngValue);
__declspec(dllexport) char * ultoa(char * buf, unsigned long lngValue);
__declspec(dllexport) char * ftoa(char * buf, float sngValue);
__declspec(dllexport) char * dtoa(char * buf, double dblValue);
__declspec(dllexport) char * ftoa(char * buf, float sngValue,unsigned int numdecimals);
__declspec(dllexport) char * dtoa(char * buf, double dblValue,unsigned int numdecimals);

__declspec(dllexport) char * deg2rad(double deg, double& rad);
__declspec(dllexport) char * rad2deg(double deg, double& rad);

__declspec(dllexport) float linterp(float x1, float x, float x2, float y1, float y2);
#endif//GT_BASICMATH_H