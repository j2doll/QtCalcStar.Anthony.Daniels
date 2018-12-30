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
#pragma once

#ifndef GT_VECTORMATH_H
#define GT_VECTORMATH_H
#include ".\GtBasicMath.h"

#include "..\GtGeometry\GtPoint3DF.h"
#include "..\GtGeometry\GtAABox.h"

using namespace GT::GtCore;

namespace GT
{
	namespace GtMath
	{
		HTL_DLLAPI double Deg2Rad(double dblAngle);
		HTL_DLLAPI double Rad2Deg(double dblRadians);

		HTL_DLLAPI GtPoint3DF Add2D(const GtPoint3DF & objPointA, const GtPoint3DF & objPointB);
		HTL_DLLAPI GtPoint3DF Diff2D(const GtPoint3DF & objPointA, const GtPoint3DF & objPointB);
		HTL_DLLAPI double Dot2D(const GtPoint3DF & objPointA, const GtPoint3DF & objPointB);
		HTL_DLLAPI double Mag2D(const GtPoint3DF & objPointA);
		HTL_DLLAPI double Angle2D(const GtPoint3DF & objPointA, const GtPoint3DF & objPointB);
		HTL_DLLAPI GtPoint3DF Perp2D(const GtPoint3DF & objPointA);

		HTL_DLLAPI GtPoint3DF Add3D(const GtPoint3DF & objPointA, const GtPoint3DF & objPointB);
		HTL_DLLAPI GtPoint3DF Diff3D(const GtPoint3DF & objPointA, const GtPoint3DF & objPointB);
		HTL_DLLAPI GtPoint3DF Cross3D(const GtPoint3DF & objPointA, const GtPoint3DF & objPointB);
		HTL_DLLAPI double Dot3D(const GtPoint3DF & objPointA, const GtPoint3DF & objPointB);
		HTL_DLLAPI double Mag3D(const GtPoint3DF & objPointA);
		HTL_DLLAPI double Angle3D(const GtPoint3DF & objPointA, const GtPoint3DF & objPointB);
		HTL_DLLAPI GtPoint3DF Perp3D(const GtPoint3DF & objPointA);



		
	};//end namespace GtMath
};//end namespace GT
#endif