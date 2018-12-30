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
#pragma warning(push)
#pragma warning (disable : 4005 ) /* macro redefinition */
#define HTL_DLLEXPORT
#pragma warning(pop)

#include ".\GtVectorMath.h"

using namespace GT::GtMath;

namespace GT
{
	namespace GtMath
	{
		double Deg2Rad(double dblAngle)
		{
			return dblAngle * (3.1415926f/180.0f);
		};
		double Rad2Deg(double dblRadians)
		{
			return dblRadians * (180.0f / 3.1415926f);
		};



		//Cross product of two vectors
		GtPoint3DF Add2D(const GtPoint3DF & objPointA, const GtPoint3DF & objPointB)
		{
			GtPoint3DF objPointReturn;
			objPointReturn.x = objPointA.x + objPointB.x;
			objPointReturn.y = objPointA.y + objPointB.y;
			return objPointReturn;
		};

		GtPoint3DF Diff2D(const GtPoint3DF & objPointA, const GtPoint3DF & objPointB)
		{
			GtPoint3DF objPointReturn;
			objPointReturn.x = objPointA.x - objPointB.x;
			objPointReturn.y = objPointA.y - objPointB.y;
			return objPointReturn;
		};

		double Dot2D(const GtPoint3DF & objPointA, const GtPoint3DF & objPointB)
		{
			double dblReturnScalar;
			dblReturnScalar = objPointA.x * objPointB.x + objPointA.y * objPointB.y;
			return dblReturnScalar;
		};
		double Mag2D(const GtPoint3DF & objPointA)
		{
			double dblReturnMag;
			dblReturnMag = sqrt( pow( objPointA.x,2)+ pow( objPointA.y,2));
			return dblReturnMag;
		};

		double Angle2D(const GtPoint3DF & objPointA, const GtPoint3DF & objPointB )
		{
			double dblRadianReturn;
			dblRadianReturn = acos( Dot2D(objPointA,objPointB) / (Mag2D(objPointA) * Mag2D(objPointB) ) );
			return dblRadianReturn;
		};

		GtPoint3DF Perp2D(const GtPoint3DF & objPointA)
		{
			GtPoint3DF objPerpReturn;
			objPerpReturn.x = -(objPointA.y);
			objPerpReturn.y = (objPointA.x);
			return objPerpReturn;	
		};

		GtPoint3DF Perp3D(const GtPoint3DF & objPointA)
		{
			GtPoint3DF objPerpReturn;
			objPerpReturn.x = -(objPointA.y);
			objPerpReturn.y = (objPointA.x);
			objPerpReturn.z = objPointA.z;
			return objPerpReturn;	
		};
		GtPoint3DF Add3D(const GtPoint3DF & objPointA, const GtPoint3DF & objPointB)
		{
			GtPoint3DF objPointReturn;
			objPointReturn.x = objPointA.x + objPointB.x;
			objPointReturn.y = objPointA.y + objPointB.y;
			objPointReturn.z = objPointA.z + objPointB.z;
			return objPointReturn;
		};
		GtPoint3DF Diff3D(const GtPoint3DF & objPointA, const GtPoint3DF & objPointB)
		{
			GtPoint3DF objPointReturn;
			objPointReturn.x = objPointA.x - objPointB.x;
			objPointReturn.y = objPointA.y - objPointB.y;
			objPointReturn.z = objPointA.z - objPointB.z;
			return objPointReturn;
		};
		GtPoint3DF Cross3D(const GtPoint3DF & objPointA, const GtPoint3DF & objPointB)
		{
			GtPoint3DF objPointReturn;
			objPointReturn.x = (objPointA.y *objPointB.z) - (objPointA.z * objPointB.y);//i
			objPointReturn.y = -((objPointA.x *objPointB.z) - (objPointA.z * objPointB.x));//j
			objPointReturn.z = (objPointA.x *objPointB.y) - (objPointA.y * objPointB.x);//k
			return objPointReturn;
		};

		double Dot3D(const GtPoint3DF & objPointA, const GtPoint3DF & objPointB)
		{
			double dblReturnScalar;
			dblReturnScalar = objPointA.x * objPointB.x + objPointA.y * objPointB.y + objPointA.z * objPointB.z;
			return dblReturnScalar;
		};
		double Mag3D(const GtPoint3DF & objPointA)
		{
			double dblReturnMag;
			dblReturnMag = sqrt( pow( objPointA.x,2)+ pow( objPointA.y,2) + pow( objPointA.z,2));
			return dblReturnMag;
		};
		double Angle3D(const GtPoint3DF & objPointA, const GtPoint3DF & objPointB)
		{
			double dblRadianReturn;
			dblRadianReturn = acos( Dot3D(objPointA,objPointB) / (Mag3D(objPointA) * Mag3D(objPointB) ) );
			return dblRadianReturn;
		};

	};//end namespace GtMath

};//end namespace GT