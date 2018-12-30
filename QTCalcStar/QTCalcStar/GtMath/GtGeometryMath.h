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
#ifndef GT_GEOMETRYMATH_H
#define GT_GEOMETRYMATH_H

namespace GT{
	namespace GtMath{

		//IMPORTANT GT USED COLUMN MAJOR CARRAYS IN ORDER TO BE COMPATIBLE WITH OPENGL
		/* EXAMPLE 4 X 4 MATRIX
		M0,M4,M8,M12
		M1,M5,M9,M13
		M2,M6,M10,M14
		M3,M7,M11,M16
		*/

		HTL_DLLAPI void Matrix44Assign(float ptrMatrix[16],float * ptrMatrixOut/*[16] expected*/);
		HTL_DLLAPI void Matrix44Assign(float ptrMatrix[16],double * ptrMatrixOut/*[16] expected*/);
		HTL_DLLAPI void InverseMatrix44(float ptrMatrix[16],float * ptrInverseMatrix/*[16] expected*/);
		HTL_DLLAPI void MultMatrix44Vector4(float ptrMatrix[16],float ptrVectorIn[4], float * ptrVectorOut/*[4] expected*/);
		HTL_DLLAPI GtPoint3DF LocalToGlobalCoords(float ptrMatrix[16], const GtPoint3DF & ptrLocalPoint);
		HTL_DLLAPI GtPoint3DF GlobalToLocalCoords(float ptrMatrix[16], const GtPoint3DF & ptrLocalPoint);

		HTL_DLLAPI void Matrix44Assign(double ptrMatrix[16],double * ptrMatrixOut/*[16] expected*/);
		HTL_DLLAPI void Matrix44Assign(double ptrMatrix[16],float * ptrMatrixOut/*[16] expected*/);
		HTL_DLLAPI void InverseMatrix44(double ptrMatrix[16],double * ptrInverseMatrix/*[16] expected*/);
		HTL_DLLAPI void MultMatrix44Vector4(double ptrMatrix[16],double ptrVectorIn[4], double * ptrVectorOut/*[4] expected*/);
		HTL_DLLAPI GtPoint3DF LocalToGlobalCoords(double ptrMatrix[16], const GtPoint3DF & ptrLocalPoint);
		HTL_DLLAPI GtPoint3DF GlobalToLocalCoords(double ptrMatrix[16], const GtPoint3DF & ptrLocalPoint);

		//Euler Angle to Transformation Matrices Axes
		HTL_DLLAPI void EulerAnglesToAxesRxRyRz(GtPoint3DF objAnglesDeg,GtPoint3DF & objRetXDir, GtPoint3DF & objRetYDir, GtPoint3DF & objRetZDir);
		HTL_DLLAPI void EulerAnglesToAxesRxRzRy(GtPoint3DF objAnglesDeg,GtPoint3DF & objRetXDir, GtPoint3DF & objRetYDir, GtPoint3DF & objRetZDir);
		HTL_DLLAPI void EulerAnglesToAxesRyRxRz(GtPoint3DF objAnglesDeg,GtPoint3DF & objRetXDir, GtPoint3DF & objRetYDir, GtPoint3DF & objRetZDir);
		HTL_DLLAPI void EulerAnglesToAxesRyRzRx(GtPoint3DF objAnglesDeg,GtPoint3DF & objRetXDir, GtPoint3DF & objRetYDir, GtPoint3DF & objRetZDir);
		HTL_DLLAPI void EulerAnglesToAxesRzRxRy(GtPoint3DF objAnglesDeg,GtPoint3DF & objRetXDir, GtPoint3DF & objRetYDir, GtPoint3DF & objRetZDir);
		HTL_DLLAPI void EulerAnglesToAxesRzRyRx(GtPoint3DF objAnglesDeg,GtPoint3DF & objRetXDir, GtPoint3DF & objRetYDir, GtPoint3DF & objRetZDir);

		HTL_DLLAPI GtPoint3DF RotatePoint( const GtPoint3DF& p, const GtPoint3DF& center, const GtPoint3DF& axis, double theta );


	};//end namespace GtMath
};//end namespace GT

#endif