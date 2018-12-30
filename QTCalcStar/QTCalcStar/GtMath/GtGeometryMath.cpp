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
#include ".\GtGeometryMath.h"

#include <algorithm>
#include <numeric>

namespace GT
{

	namespace GtMath
	{

		void Matrix44Assign(float ptrMatrix[16],float * ptrMatrixOut/*[16] expected*/)
		{
			ptrMatrixOut[0] = ptrMatrix[0];
			ptrMatrixOut[1] = ptrMatrix[1];
			ptrMatrixOut[2] = ptrMatrix[2];
			ptrMatrixOut[3] = ptrMatrix[3];
			ptrMatrixOut[4] = ptrMatrix[4];
			ptrMatrixOut[5] = ptrMatrix[5];
			ptrMatrixOut[6] = ptrMatrix[6];
			ptrMatrixOut[7] = ptrMatrix[7];
			ptrMatrixOut[8] = ptrMatrix[8];
			ptrMatrixOut[9] = ptrMatrix[9];
			ptrMatrixOut[10] = ptrMatrix[10];
			ptrMatrixOut[11] = ptrMatrix[11];
			ptrMatrixOut[12] = ptrMatrix[12];
			ptrMatrixOut[13] = ptrMatrix[13];
			ptrMatrixOut[14] = ptrMatrix[14];
			ptrMatrixOut[15] = ptrMatrix[15];
		}

		void Matrix44Assign(float ptrMatrix[16],double * ptrMatrixOut/*[16] expected*/)
		{
			ptrMatrixOut[0] = double(ptrMatrix[0]);
			ptrMatrixOut[1] = double(ptrMatrix[1]);
			ptrMatrixOut[2] = double(ptrMatrix[2]);
			ptrMatrixOut[3] = double(ptrMatrix[3]);
			ptrMatrixOut[4] = double(ptrMatrix[4]);
			ptrMatrixOut[5] = double(ptrMatrix[5]);
			ptrMatrixOut[6] = double(ptrMatrix[6]);
			ptrMatrixOut[7] = double(ptrMatrix[7]);
			ptrMatrixOut[8] = double(ptrMatrix[8]);
			ptrMatrixOut[9] = double(ptrMatrix[9]);
			ptrMatrixOut[10] = double(ptrMatrix[10]);
			ptrMatrixOut[11] = double(ptrMatrix[11]);
			ptrMatrixOut[12] = double(ptrMatrix[12]);
			ptrMatrixOut[13] = double(ptrMatrix[13]);
			ptrMatrixOut[14] = double(ptrMatrix[14]);
			ptrMatrixOut[15] = double(ptrMatrix[15]);
		}

		void InverseMatrix44(float ptrMatrix[16],float * ptrInverseMatrix /*[16] expected*/)
		{
			//pointer for output array not size safe
			//ptrMatrix[16],ptrInverseMatrix[16] ASSUMED COLUMN MAJOR FORMAT
			float sngEpsilon = (float)0.00001f;
			float a0 = ptrMatrix[ 0]*ptrMatrix[ 5] - ptrMatrix[ 1]*ptrMatrix[ 4];
			float a1 = ptrMatrix[ 0]*ptrMatrix[ 6] - ptrMatrix[ 2]*ptrMatrix[ 4];
			float a2 = ptrMatrix[ 0]*ptrMatrix[ 7] - ptrMatrix[ 3]*ptrMatrix[ 4];
			float a3 = ptrMatrix[ 1]*ptrMatrix[ 6] - ptrMatrix[ 2]*ptrMatrix[ 5];
			float a4 = ptrMatrix[ 1]*ptrMatrix[ 7] - ptrMatrix[ 3]*ptrMatrix[ 5];
			float a5 = ptrMatrix[ 2]*ptrMatrix[ 7] - ptrMatrix[ 3]*ptrMatrix[ 6];
			float b0 = ptrMatrix[ 8]*ptrMatrix[13] - ptrMatrix[ 9]*ptrMatrix[12];
			float b1 = ptrMatrix[ 8]*ptrMatrix[14] - ptrMatrix[10]*ptrMatrix[12];
			float b2 = ptrMatrix[ 8]*ptrMatrix[15] - ptrMatrix[11]*ptrMatrix[12];
			float b3 = ptrMatrix[ 9]*ptrMatrix[14] - ptrMatrix[10]*ptrMatrix[13];
			float b4 = ptrMatrix[ 9]*ptrMatrix[15] - ptrMatrix[11]*ptrMatrix[13];
			float b5 = ptrMatrix[10]*ptrMatrix[15] - ptrMatrix[11]*ptrMatrix[14];

			float det = a0*b5 - a1*b4 + a2*b3 + a3*b2 - a4*b1 + a5*b0;
			if (abs(det) > sngEpsilon)
			{
				ptrInverseMatrix[ 0] = + ptrMatrix[ 5]*b5 - ptrMatrix[ 6]*b4 + ptrMatrix[ 7]*b3;
				ptrInverseMatrix[ 4] = - ptrMatrix[ 4]*b5 + ptrMatrix[ 6]*b2 - ptrMatrix[ 7]*b1;
				ptrInverseMatrix[ 8] = + ptrMatrix[ 4]*b4 - ptrMatrix[ 5]*b2 + ptrMatrix[ 7]*b0;
				ptrInverseMatrix[12] = - ptrMatrix[ 4]*b3 + ptrMatrix[ 5]*b1 - ptrMatrix[ 6]*b0;
				ptrInverseMatrix[ 1] = - ptrMatrix[ 1]*b5 + ptrMatrix[ 2]*b4 - ptrMatrix[ 3]*b3;
				ptrInverseMatrix[ 5] = + ptrMatrix[ 0]*b5 - ptrMatrix[ 2]*b2 + ptrMatrix[ 3]*b1;
				ptrInverseMatrix[ 9] = - ptrMatrix[ 0]*b4 + ptrMatrix[ 1]*b2 - ptrMatrix[ 3]*b0;
				ptrInverseMatrix[13] = + ptrMatrix[ 0]*b3 - ptrMatrix[ 1]*b1 + ptrMatrix[ 2]*b0;
				ptrInverseMatrix[ 2] = + ptrMatrix[13]*a5 - ptrMatrix[14]*a4 + ptrMatrix[15]*a3;
				ptrInverseMatrix[ 6] = - ptrMatrix[12]*a5 + ptrMatrix[14]*a2 - ptrMatrix[15]*a1;
				ptrInverseMatrix[10] = + ptrMatrix[12]*a4 - ptrMatrix[13]*a2 + ptrMatrix[15]*a0;
				ptrInverseMatrix[14] = - ptrMatrix[12]*a3 + ptrMatrix[13]*a1 - ptrMatrix[14]*a0;
				ptrInverseMatrix[ 3] = - ptrMatrix[ 9]*a5 + ptrMatrix[10]*a4 - ptrMatrix[11]*a3;
				ptrInverseMatrix[ 7] = + ptrMatrix[ 8]*a5 - ptrMatrix[10]*a2 + ptrMatrix[11]*a1;
				ptrInverseMatrix[11] = - ptrMatrix[ 8]*a4 + ptrMatrix[ 9]*a2 - ptrMatrix[11]*a0;
				ptrInverseMatrix[15] = + ptrMatrix[ 8]*a3 - ptrMatrix[ 9]*a1 + ptrMatrix[10]*a0;

				float invDet = (1.0f)/det;
				ptrInverseMatrix[ 0] *= invDet;
				ptrInverseMatrix[ 1] *= invDet;
				ptrInverseMatrix[ 2] *= invDet;
				ptrInverseMatrix[ 3] *= invDet;
				ptrInverseMatrix[ 4] *= invDet;
				ptrInverseMatrix[ 5] *= invDet;
				ptrInverseMatrix[ 6] *= invDet;
				ptrInverseMatrix[ 7] *= invDet;
				ptrInverseMatrix[ 8] *= invDet;
				ptrInverseMatrix[ 9] *= invDet;
				ptrInverseMatrix[10] *= invDet;
				ptrInverseMatrix[11] *= invDet;
				ptrInverseMatrix[12] *= invDet;
				ptrInverseMatrix[13] *= invDet;
				ptrInverseMatrix[14] *= invDet;
				ptrInverseMatrix[15] *= invDet;
				return;
			}
			return;
		};

		void MultMatrix44Vector4(float ptrMatrix[16],float ptrVectorIn[4], float * ptrVectorOut/*[4] expected*/)
		{
			//pointer for output array not size safe
			ptrVectorOut[0] = ptrMatrix[0]*ptrVectorIn[0] + ptrMatrix[4]*ptrVectorIn[1] + ptrMatrix[8]*ptrVectorIn[2] + ptrMatrix[12]*ptrVectorIn[3];
			ptrVectorOut[1] = ptrMatrix[1]*ptrVectorIn[0] + ptrMatrix[5]*ptrVectorIn[1] + ptrMatrix[9]*ptrVectorIn[2] + ptrMatrix[13]*ptrVectorIn[3];
			ptrVectorOut[2] = ptrMatrix[2]*ptrVectorIn[0] + ptrMatrix[6]*ptrVectorIn[1] + ptrMatrix[10]*ptrVectorIn[2] + ptrMatrix[14]*ptrVectorIn[3];
			ptrVectorOut[3] = ptrMatrix[3]*ptrVectorIn[0] + ptrMatrix[7]*ptrVectorIn[1] + ptrMatrix[11]*ptrVectorIn[2] + ptrMatrix[15]*ptrVectorIn[3];

		};

		GtPoint3DF LocalToGlobalCoords(float ptrMatrix[16], const GtPoint3DF & ptrLocalPoint)
		{
			GtPoint3DF objGlobalPoint;
			//convert the point to 
			float sngGlobalVect[4],sngLocalVect[4];
			sngLocalVect[0] = (float)ptrLocalPoint.x;
			sngLocalVect[1] = (float)ptrLocalPoint.y;
			sngLocalVect[2] = (float)ptrLocalPoint.z;
			sngLocalVect[3] = 1.0f;
			//get the inverse of the viewing matrix
			GtMath::MultMatrix44Vector4(ptrMatrix,sngLocalVect,sngGlobalVect);
			objGlobalPoint.x = sngGlobalVect[0];
			objGlobalPoint.y = sngGlobalVect[1];
			objGlobalPoint.z = sngGlobalVect[2];
			return objGlobalPoint;
		};

		GtPoint3DF GlobalToLocalCoords(float ptrMatrix[16], const GtPoint3DF & ptrGlobalPoint)
		{
			GtPoint3DF objLocalPoint;
			//convert the point to 
			float sngGlobalVect[4],sngLocalVect[4];
			float arrSngInverseView[16];
			sngGlobalVect[0] = (float)ptrGlobalPoint.x;
			sngGlobalVect[1] = (float)ptrGlobalPoint.y;
			sngGlobalVect[2] = (float)ptrGlobalPoint.z;
			sngGlobalVect[3] = 1.0f;
			//get the inverse of the viewing matrix
			GtMath::InverseMatrix44(ptrMatrix,arrSngInverseView);
			GtMath::MultMatrix44Vector4(arrSngInverseView,sngGlobalVect,sngLocalVect);
			objLocalPoint.x = sngLocalVect[0];
			objLocalPoint.y = sngLocalVect[1];
			objLocalPoint.z = sngLocalVect[2];

			return objLocalPoint;

		};


		void Matrix44Assign(double ptrMatrix[16],double * ptrMatrixOut/*[16] expected*/)
		{
			ptrMatrixOut[0] = ptrMatrix[0];
			ptrMatrixOut[1] = ptrMatrix[1];
			ptrMatrixOut[2] = ptrMatrix[2];
			ptrMatrixOut[3] = ptrMatrix[3];
			ptrMatrixOut[4] = ptrMatrix[4];
			ptrMatrixOut[5] = ptrMatrix[5];
			ptrMatrixOut[6] = ptrMatrix[6];
			ptrMatrixOut[7] = ptrMatrix[7];
			ptrMatrixOut[8] = ptrMatrix[8];
			ptrMatrixOut[9] = ptrMatrix[9];
			ptrMatrixOut[10] = ptrMatrix[10];
			ptrMatrixOut[11] = ptrMatrix[11];
			ptrMatrixOut[12] = ptrMatrix[12];
			ptrMatrixOut[13] = ptrMatrix[13];
			ptrMatrixOut[14] = ptrMatrix[14];
			ptrMatrixOut[15] = ptrMatrix[15];
		}

		void Matrix44Assign(double ptrMatrix[16],float * ptrMatrixOut/*[16] expected*/)
		{
			ptrMatrixOut[0] = float(ptrMatrix[0]);
			ptrMatrixOut[1] = float(ptrMatrix[1]);
			ptrMatrixOut[2] = float(ptrMatrix[2]);
			ptrMatrixOut[3] = float(ptrMatrix[3]);
			ptrMatrixOut[4] = float(ptrMatrix[4]);
			ptrMatrixOut[5] = float(ptrMatrix[5]);
			ptrMatrixOut[6] = float(ptrMatrix[6]);
			ptrMatrixOut[7] = float(ptrMatrix[7]);
			ptrMatrixOut[8] = float(ptrMatrix[8]);
			ptrMatrixOut[9] = float(ptrMatrix[9]);
			ptrMatrixOut[10] = float(ptrMatrix[10]);
			ptrMatrixOut[11] = float(ptrMatrix[11]);
			ptrMatrixOut[12] = float(ptrMatrix[12]);
			ptrMatrixOut[13] = float(ptrMatrix[13]);
			ptrMatrixOut[14] = float(ptrMatrix[14]);
			ptrMatrixOut[15] = float(ptrMatrix[15]);
		}
		void InverseMatrix44(double ptrMatrix[16],double * ptrInverseMatrix /*[16] expected*/)
		{
			//pointer for output array not size safe
			//ptrMatrix[16],ptrInverseMatrix[16] ASSUMED COLUMN MAJOR FORMAT
			double sngEpsilon = 0.00001;
			double a0 = ptrMatrix[ 0]*ptrMatrix[ 5] - ptrMatrix[ 1]*ptrMatrix[ 4];
			double a1 = ptrMatrix[ 0]*ptrMatrix[ 6] - ptrMatrix[ 2]*ptrMatrix[ 4];
			double a2 = ptrMatrix[ 0]*ptrMatrix[ 7] - ptrMatrix[ 3]*ptrMatrix[ 4];
			double a3 = ptrMatrix[ 1]*ptrMatrix[ 6] - ptrMatrix[ 2]*ptrMatrix[ 5];
			double a4 = ptrMatrix[ 1]*ptrMatrix[ 7] - ptrMatrix[ 3]*ptrMatrix[ 5];
			double a5 = ptrMatrix[ 2]*ptrMatrix[ 7] - ptrMatrix[ 3]*ptrMatrix[ 6];
			double b0 = ptrMatrix[ 8]*ptrMatrix[13] - ptrMatrix[ 9]*ptrMatrix[12];
			double b1 = ptrMatrix[ 8]*ptrMatrix[14] - ptrMatrix[10]*ptrMatrix[12];
			double b2 = ptrMatrix[ 8]*ptrMatrix[15] - ptrMatrix[11]*ptrMatrix[12];
			double b3 = ptrMatrix[ 9]*ptrMatrix[14] - ptrMatrix[10]*ptrMatrix[13];
			double b4 = ptrMatrix[ 9]*ptrMatrix[15] - ptrMatrix[11]*ptrMatrix[13];
			double b5 = ptrMatrix[10]*ptrMatrix[15] - ptrMatrix[11]*ptrMatrix[14];

			double det = a0*b5 - a1*b4 + a2*b3 + a3*b2 - a4*b1 + a5*b0;
			if (abs(det) > sngEpsilon)
			{
				ptrInverseMatrix[ 0] = + ptrMatrix[ 5]*b5 - ptrMatrix[ 6]*b4 + ptrMatrix[ 7]*b3;
				ptrInverseMatrix[ 4] = - ptrMatrix[ 4]*b5 + ptrMatrix[ 6]*b2 - ptrMatrix[ 7]*b1;
				ptrInverseMatrix[ 8] = + ptrMatrix[ 4]*b4 - ptrMatrix[ 5]*b2 + ptrMatrix[ 7]*b0;
				ptrInverseMatrix[12] = - ptrMatrix[ 4]*b3 + ptrMatrix[ 5]*b1 - ptrMatrix[ 6]*b0;
				ptrInverseMatrix[ 1] = - ptrMatrix[ 1]*b5 + ptrMatrix[ 2]*b4 - ptrMatrix[ 3]*b3;
				ptrInverseMatrix[ 5] = + ptrMatrix[ 0]*b5 - ptrMatrix[ 2]*b2 + ptrMatrix[ 3]*b1;
				ptrInverseMatrix[ 9] = - ptrMatrix[ 0]*b4 + ptrMatrix[ 1]*b2 - ptrMatrix[ 3]*b0;
				ptrInverseMatrix[13] = + ptrMatrix[ 0]*b3 - ptrMatrix[ 1]*b1 + ptrMatrix[ 2]*b0;
				ptrInverseMatrix[ 2] = + ptrMatrix[13]*a5 - ptrMatrix[14]*a4 + ptrMatrix[15]*a3;
				ptrInverseMatrix[ 6] = - ptrMatrix[12]*a5 + ptrMatrix[14]*a2 - ptrMatrix[15]*a1;
				ptrInverseMatrix[10] = + ptrMatrix[12]*a4 - ptrMatrix[13]*a2 + ptrMatrix[15]*a0;
				ptrInverseMatrix[14] = - ptrMatrix[12]*a3 + ptrMatrix[13]*a1 - ptrMatrix[14]*a0;
				ptrInverseMatrix[ 3] = - ptrMatrix[ 9]*a5 + ptrMatrix[10]*a4 - ptrMatrix[11]*a3;
				ptrInverseMatrix[ 7] = + ptrMatrix[ 8]*a5 - ptrMatrix[10]*a2 + ptrMatrix[11]*a1;
				ptrInverseMatrix[11] = - ptrMatrix[ 8]*a4 + ptrMatrix[ 9]*a2 - ptrMatrix[11]*a0;
				ptrInverseMatrix[15] = + ptrMatrix[ 8]*a3 - ptrMatrix[ 9]*a1 + ptrMatrix[10]*a0;

				double invDet = (1.0f)/det;
				ptrInverseMatrix[ 0] *= invDet;
				ptrInverseMatrix[ 1] *= invDet;
				ptrInverseMatrix[ 2] *= invDet;
				ptrInverseMatrix[ 3] *= invDet;
				ptrInverseMatrix[ 4] *= invDet;
				ptrInverseMatrix[ 5] *= invDet;
				ptrInverseMatrix[ 6] *= invDet;
				ptrInverseMatrix[ 7] *= invDet;
				ptrInverseMatrix[ 8] *= invDet;
				ptrInverseMatrix[ 9] *= invDet;
				ptrInverseMatrix[10] *= invDet;
				ptrInverseMatrix[11] *= invDet;
				ptrInverseMatrix[12] *= invDet;
				ptrInverseMatrix[13] *= invDet;
				ptrInverseMatrix[14] *= invDet;
				ptrInverseMatrix[15] *= invDet;
				return;
			}
			return;
		};

		void MultMatrix44Vector4(double ptrMatrix[16],double ptrVectorIn[4], double * ptrVectorOut/*[4] expected*/)
		{
			//pointer for output array not size safe
			ptrVectorOut[0] = ptrMatrix[0]*ptrVectorIn[0] + ptrMatrix[4]*ptrVectorIn[1] + ptrMatrix[8]*ptrVectorIn[2] + ptrMatrix[12]*ptrVectorIn[3];
			ptrVectorOut[1] = ptrMatrix[1]*ptrVectorIn[0] + ptrMatrix[5]*ptrVectorIn[1] + ptrMatrix[9]*ptrVectorIn[2] + ptrMatrix[13]*ptrVectorIn[3];
			ptrVectorOut[2] = ptrMatrix[2]*ptrVectorIn[0] + ptrMatrix[6]*ptrVectorIn[1] + ptrMatrix[10]*ptrVectorIn[2] + ptrMatrix[14]*ptrVectorIn[3];
			ptrVectorOut[3] = ptrMatrix[3]*ptrVectorIn[0] + ptrMatrix[7]*ptrVectorIn[1] + ptrMatrix[11]*ptrVectorIn[2] + ptrMatrix[15]*ptrVectorIn[3];

		};

		GtPoint3DF LocalToGlobalCoords(double ptrMatrix[16], const GtPoint3DF & ptrLocalPoint)
		{
			GtPoint3DF objGlobalPoint;
			//convert the point to 
			double sngGlobalVect[4],sngLocalVect[4];
			sngLocalVect[0] = ptrLocalPoint.x;
			sngLocalVect[1] = ptrLocalPoint.y;
			sngLocalVect[2] = ptrLocalPoint.z;
			sngLocalVect[3] = 1.0f;
			//get the inverse of the viewing matrix
			GtMath::MultMatrix44Vector4(ptrMatrix,sngLocalVect,sngGlobalVect);
			objGlobalPoint.x = sngGlobalVect[0];
			objGlobalPoint.y = sngGlobalVect[1];
			objGlobalPoint.z = sngGlobalVect[2];
			return objGlobalPoint;
		};

		GtPoint3DF GlobalToLocalCoords(double ptrMatrix[16], const GtPoint3DF & ptrGlobalPoint)
		{
			GtPoint3DF objLocalPoint;
			//convert the point to 
			double sngGlobalVect[4],sngLocalVect[4];
			double arrSngInverseView[16];
			sngGlobalVect[0] = ptrGlobalPoint.x;
			sngGlobalVect[1] = ptrGlobalPoint.y;
			sngGlobalVect[2] = ptrGlobalPoint.z;
			sngGlobalVect[3] = 1.0f;
			//get the inverse of the viewing matrix
			GtMath::InverseMatrix44(ptrMatrix,arrSngInverseView);
			GtMath::MultMatrix44Vector4(arrSngInverseView,sngGlobalVect,sngLocalVect);
			objLocalPoint.x = sngLocalVect[0];
			objLocalPoint.y = sngLocalVect[1];
			objLocalPoint.z = sngLocalVect[2];

			return objLocalPoint;

		};


		void EulerAnglesToAxesRxRyRz(GtPoint3DF objAnglesDeg,GtPoint3DF & objRetXDir, GtPoint3DF & objRetYDir, GtPoint3DF & objRetZDir)
		{
			float M[3][3];
			memset(M,0,sizeof(M));
			//incoming rotation angles <Rx,Ry,Rz>
			//rotation multiplication matrix order Rx*Ry*Rz
			float sngRadX,sngRadY,sngRadZ;
			//convert degrees to radians
			sngRadX = (float)GtMath::Deg2Rad(objAnglesDeg.x);
			sngRadY = (float)GtMath::Deg2Rad(objAnglesDeg.y);
			sngRadZ = (float)GtMath::Deg2Rad(objAnglesDeg.z);
		
			float    Sx    = sinf(sngRadX);
			float    Sy    = sinf(sngRadY);
			float    Sz    = sinf(sngRadZ);
			float    Cx    = cosf(sngRadX);
			float    Cy    = cosf(sngRadY);
			float    Cz    = cosf(sngRadZ);

			M[0][0]=Cy*Cz;
			M[0][1]=-Cy*Sz;
			M[0][2]=Sy;
			M[1][0]=Cz*Sx*Sy+Cx*Sz;
			M[1][1]=Cx*Cz-Sx*Sy*Sz;
			M[1][2]=-Cy*Sx;
			M[2][0]=-Cx*Cz*Sy+Sx*Sz;
			M[2][1]=Cz*Sx+Cx*Sy*Sz;
			M[2][2]=Cx*Cy;
			//CALCULATE THE RETURN DIRECTIONS VECTORS

			objRetXDir.x = M[0][0];
			objRetXDir.y = M[0][1];
			objRetXDir.z = M[0][2];

			objRetYDir.x = M[1][0];
			objRetYDir.y = M[1][1];
			objRetYDir.z = M[1][2];

			objRetZDir.x = M[2][0];
			objRetZDir.y = M[2][1];
			objRetZDir.z = M[2][2];
		};

		void EulerAnglesToAxesRxRzRy(GtPoint3DF objAnglesDeg,GtPoint3DF & objRetXDir, GtPoint3DF & objRetYDir, GtPoint3DF & objRetZDir)
		{
			float M[3][3];
			memset(M,0,sizeof(M));
			//incoming rotation angles <Rx,Ry,Rz>
			//rotation multiplication matrix order Rx*Ry*Rz
			float sngRadX,sngRadY,sngRadZ;
			//convert degrees to radians
			sngRadX = (float)GtMath::Deg2Rad(objAnglesDeg.x);
			sngRadY = (float)GtMath::Deg2Rad(objAnglesDeg.y);
			sngRadZ = (float)GtMath::Deg2Rad(objAnglesDeg.z);
		
			float    Sx    = sinf(sngRadX);
			float    Sy    = sinf(sngRadY);
			float    Sz    = sinf(sngRadZ);
			float    Cx    = cosf(sngRadX);
			float    Cy    = cosf(sngRadY);
			float    Cz    = cosf(sngRadZ);

			M[0][0]=Cy*Cz;
			M[0][1]=-Sz;
			M[0][2]=Cz*Sy;
			M[1][0]=Sx*Sy+Cx*Cy*Sz;
			M[1][1]=Cx*Cz;
			M[1][2]=-Cy*Sx+Cx*Sy*Sz;
			M[2][0]=-Cx*Sy+Cy*Sx*Sz;
			M[2][1]=Cz*Sx;
			M[2][2]=Cx*Cy+Sx*Sy*Sz;

			//CALCULATE THE RETURN DIRECTIONS VECTORS

			objRetXDir.x = M[0][0];
			objRetXDir.y = M[0][1];
			objRetXDir.z = M[0][2];

			objRetYDir.x = M[1][0];
			objRetYDir.y = M[1][1];
			objRetYDir.z = M[1][2];

			objRetZDir.x = M[2][0];
			objRetZDir.y = M[2][1];
			objRetZDir.z = M[2][2];

		};

		void EulerAnglesToAxesRyRxRz(GtPoint3DF objAnglesDeg,GtPoint3DF & objRetXDir, GtPoint3DF & objRetYDir, GtPoint3DF & objRetZDir)
		{
			float M[3][3];
			memset(M,0,sizeof(M));
			//incoming rotation angles <Rx,Ry,Rz>
			//rotation multiplication matrix order Rx*Ry*Rz
			float sngRadX,sngRadY,sngRadZ;
			//convert degrees to radians
			sngRadX = (float)GtMath::Deg2Rad(objAnglesDeg.x);
			sngRadY = (float)GtMath::Deg2Rad(objAnglesDeg.y);
			sngRadZ = (float)GtMath::Deg2Rad(objAnglesDeg.z);
		
			float    Sx    = sinf(sngRadX);
			float    Sy    = sinf(sngRadY);
			float    Sz    = sinf(sngRadZ);
			float    Cx    = cosf(sngRadX);
			float    Cy    = cosf(sngRadY);
			float    Cz    = cosf(sngRadZ);

			M[0][0]=Cy*Cz+Sx*Sy*Sz;
			M[0][1]=Cz*Sx*Sy-Cy*Sz;
			M[0][2]=Cx*Sy;
			M[1][0]=Cx*Sz;
			M[1][1]=Cx*Cz;
			M[1][2]=-Sx;
			M[2][0]=-Cz*Sy+Cy*Sx*Sz;
			M[2][1]=Cy*Cz*Sx+Sy*Sz;
			M[2][2]=Cx*Cy;

			//CALCULATE THE RETURN DIRECTIONS VECTORS

			objRetXDir.x = M[0][0];
			objRetXDir.y = M[0][1];
			objRetXDir.z = M[0][2];

			objRetYDir.x = M[1][0];
			objRetYDir.y = M[1][1];
			objRetYDir.z = M[1][2];

			objRetZDir.x = M[2][0];
			objRetZDir.y = M[2][1];
			objRetZDir.z = M[2][2];

		};

		void EulerAnglesToAxesRyRzRx(GtPoint3DF objAnglesDeg,GtPoint3DF & objRetXDir, GtPoint3DF & objRetYDir, GtPoint3DF & objRetZDir)
		{
			float M[3][3];
			memset(M,0,sizeof(M));
			//incoming rotation angles <Rx,Ry,Rz>
			//rotation multiplication matrix order Rx*Ry*Rz
			float sngRadX,sngRadY,sngRadZ;
			//convert degrees to radians
			sngRadX = (float)GtMath::Deg2Rad(objAnglesDeg.x);
			sngRadY = (float)GtMath::Deg2Rad(objAnglesDeg.y);
			sngRadZ = (float)GtMath::Deg2Rad(objAnglesDeg.z);
		
			float    Sx    = sinf(sngRadX);
			float    Sy    = sinf(sngRadY);
			float    Sz    = sinf(sngRadZ);
			float    Cx    = cosf(sngRadX);
			float    Cy    = cosf(sngRadY);
			float    Cz    = cosf(sngRadZ);

			M[0][0]=Cy*Cz;
			M[0][1]=Sx*Sy-Cx*Cy*Sz;
			M[0][2]=Cx*Sy+Cy*Sx*Sz;
			M[1][0]=Sz;
			M[1][1]=Cx*Cz;
			M[1][2]=-Cz*Sx;
			M[2][0]=-Cz*Sy;
			M[2][1]=Cy*Sx+Cx*Sy*Sz;
			M[2][2]=Cx*Cy-Sx*Sy*Sz;
			//CALCULATE THE RETURN DIRECTIONS VECTORS

			objRetXDir.x = M[0][0];
			objRetXDir.y = M[0][1];
			objRetXDir.z = M[0][2];

			objRetYDir.x = M[1][0];
			objRetYDir.y = M[1][1];
			objRetYDir.z = M[1][2];

			objRetZDir.x = M[2][0];
			objRetZDir.y = M[2][1];
			objRetZDir.z = M[2][2];

		};

		void EulerAnglesToAxesRzRxRy(GtPoint3DF objAnglesDeg,GtPoint3DF & objRetXDir, GtPoint3DF & objRetYDir, GtPoint3DF & objRetZDir)
		{
			float M[3][3];
			memset(M,0,sizeof(M));
			//incoming rotation angles <Rx,Ry,Rz>
			//rotation multiplication matrix order Rx*Ry*Rz
			float sngRadX,sngRadY,sngRadZ;
			//convert degrees to radians
			sngRadX = (float)GtMath::Deg2Rad(objAnglesDeg.x);
			sngRadY = (float)GtMath::Deg2Rad(objAnglesDeg.y);
			sngRadZ = (float)GtMath::Deg2Rad(objAnglesDeg.z);
		
			float    Sx    = sinf(sngRadX);
			float    Sy    = sinf(sngRadY);
			float    Sz    = sinf(sngRadZ);
			float    Cx    = cosf(sngRadX);
			float    Cy    = cosf(sngRadY);
			float    Cz    = cosf(sngRadZ);

			M[0][0]=Cy*Cz-Sx*Sy*Sz;
			M[0][1]=-Cx*Sz;
			M[0][2]=Cz*Sy+Cy*Sx*Sz;
			M[1][0]=Cz*Sx*Sy+Cy*Sz;
			M[1][1]=Cx*Cz;
			M[1][2]=-Cy*Cz*Sx+Sy*Sz;
			M[2][0]=-Cx*Sy;
			M[2][1]=Sx;
			M[2][2]=Cx*Cy;
			//CALCULATE THE RETURN DIRECTIONS VECTORS

			objRetXDir.x = M[0][0];
			objRetXDir.y = M[0][1];
			objRetXDir.z = M[0][2];

			objRetYDir.x = M[1][0];
			objRetYDir.y = M[1][1];
			objRetYDir.z = M[1][2];

			objRetZDir.x = M[2][0];
			objRetZDir.y = M[2][1];
			objRetZDir.z = M[2][2];

		};

		void EulerAnglesToAxesRzRyRx(GtPoint3DF objAnglesDeg,GtPoint3DF & objRetXDir, GtPoint3DF & objRetYDir, GtPoint3DF & objRetZDir)
		{
			float M[3][3];
			memset(M,0,sizeof(M));
			//incoming rotation angles <Rx,Ry,Rz>
			//rotation multiplication matrix order Rx*Ry*Rz
			float sngRadX,sngRadY,sngRadZ;
			//convert degrees to radians
			sngRadX = (float)GtMath::Deg2Rad(objAnglesDeg.x);
			sngRadY = (float)GtMath::Deg2Rad(objAnglesDeg.y);
			sngRadZ = (float)GtMath::Deg2Rad(objAnglesDeg.z);
		
			float    Sx    = sinf(sngRadX);
			float    Sy    = sinf(sngRadY);
			float    Sz    = sinf(sngRadZ);
			float    Cx    = cosf(sngRadX);
			float    Cy    = cosf(sngRadY);
			float    Cz    = cosf(sngRadZ);

			M[0][0]=Cy*Cz;
			M[0][1]=Cz*Sx*Sy-Cx*Sz;
			M[0][2]=Cx*Cz*Sy+Sx*Sz;
			M[1][0]=Cy*Sz;
			M[1][1]=Cx*Cz+Sx*Sy*Sz;
			M[1][2]=-Cz*Sx+Cx*Sy*Sz;
			M[2][0]=-Sy;
			M[2][1]=Cy*Sx;
			M[2][2]=Cx*Cy;
			//CALCULATE THE RETURN DIRECTIONS VECTORS

			objRetXDir.x = M[0][0];
			objRetXDir.y = M[0][1];
			objRetXDir.z = M[0][2];

			objRetYDir.x = M[1][0];
			objRetYDir.y = M[1][1];
			objRetYDir.z = M[1][2];

			objRetZDir.x = M[2][0];
			objRetZDir.y = M[2][1];
			objRetZDir.z = M[2][2];

		};

		GtPoint3DF RotatePoint( const GtPoint3DF& p, const GtPoint3DF& center, const GtPoint3DF& axis, double theta )
		{
			double const c = cos( theta );
			double const s = sin( theta );
			double const C = 1.0 - c;
			GtPoint3DF tmp = p - center;
			return( center +
				GtPoint3DF( tmp[0] * ( axis[0] * axis[0] * C + c ) +
				tmp[1] * ( axis[0] * axis[1] * C - axis[2] * s ) +
				tmp[2] * ( axis[0] * axis[2] * C + axis[1] * s ),
				tmp[0] * ( axis[1] * axis[0] * C + axis[2] * s ) +
				tmp[1] * ( axis[1] * axis[1] * C + c) +
				tmp[2] * ( axis[1] * axis[2] * C - axis[0] * s ),
				tmp[0] * ( axis[2] * axis[0] * C - axis[1] * s ) +
				tmp[1] * ( axis[2] * axis[1] * C + axis[0] * s ) +
				tmp[2] * ( axis[2] * axis[2] * C + c ) ) );
		}


	};//end namespace GtMath

};//end namespace GT


typedef float Matrix[3][3];
struct EulerAngle { float X,Y,Z; };

/*
// Euler Order enum.
enum EEulerOrder
{
    ORDER_XYZ,
    ORDER_YZX,
    ORDER_ZXY,
    ORDER_ZYX,
    ORDER_YXZ,
    ORDER_XZY
};


Matrix EulerAnglesToMatrix(const EulerAngle &inEulerAngle,EEulerOrder EulerOrder)
{
    // Convert Euler Angles passed in a vector of Radians
    // into a rotation matrix.  The individual Euler Angles are
    // processed in the order requested.
    Matrix Mx;

    const FLOAT    Sx    = sinf(inEulerAngle.X);
    const FLOAT    Sy    = sinf(inEulerAngle.Y);
    const FLOAT    Sz    = sinf(inEulerAngle.Z);
    const FLOAT    Cx    = cosf(inEulerAngle.X);
    const FLOAT    Cy    = cosf(inEulerAngle.Y);
    const FLOAT    Cz    = cosf(inEulerAngle.Z);

    switch(EulerOrder)
    {
    case ORDER_XYZ:
        Mx.M[0][0]=Cy*Cz;
        Mx.M[0][1]=-Cy*Sz;
        Mx.M[0][2]=Sy;
        Mx.M[1][0]=Cz*Sx*Sy+Cx*Sz;
        Mx.M[1][1]=Cx*Cz-Sx*Sy*Sz;
        Mx.M[1][2]=-Cy*Sx;
        Mx.M[2][0]=-Cx*Cz*Sy+Sx*Sz;
        Mx.M[2][1]=Cz*Sx+Cx*Sy*Sz;
        Mx.M[2][2]=Cx*Cy;
        break;

    case ORDER_YZX:
        Mx.M[0][0]=Cy*Cz;
        Mx.M[0][1]=Sx*Sy-Cx*Cy*Sz;
        Mx.M[0][2]=Cx*Sy+Cy*Sx*Sz;
        Mx.M[1][0]=Sz;
        Mx.M[1][1]=Cx*Cz;
        Mx.M[1][2]=-Cz*Sx;
        Mx.M[2][0]=-Cz*Sy;
        Mx.M[2][1]=Cy*Sx+Cx*Sy*Sz;
        Mx.M[2][2]=Cx*Cy-Sx*Sy*Sz;
        break;

    case ORDER_ZXY:
        Mx.M[0][0]=Cy*Cz-Sx*Sy*Sz;
        Mx.M[0][1]=-Cx*Sz;
        Mx.M[0][2]=Cz*Sy+Cy*Sx*Sz;
        Mx.M[1][0]=Cz*Sx*Sy+Cy*Sz;
        Mx.M[1][1]=Cx*Cz;
        Mx.M[1][2]=-Cy*Cz*Sx+Sy*Sz;
        Mx.M[2][0]=-Cx*Sy;
        Mx.M[2][1]=Sx;
        Mx.M[2][2]=Cx*Cy;
        break;

    case ORDER_ZYX:
        Mx.M[0][0]=Cy*Cz;
        Mx.M[0][1]=Cz*Sx*Sy-Cx*Sz;
        Mx.M[0][2]=Cx*Cz*Sy+Sx*Sz;
        Mx.M[1][0]=Cy*Sz;
        Mx.M[1][1]=Cx*Cz+Sx*Sy*Sz;
        Mx.M[1][2]=-Cz*Sx+Cx*Sy*Sz;
        Mx.M[2][0]=-Sy;
        Mx.M[2][1]=Cy*Sx;
        Mx.M[2][2]=Cx*Cy;
        break;

    case ORDER_YXZ:
        Mx.M[0][0]=Cy*Cz+Sx*Sy*Sz;
        Mx.M[0][1]=Cz*Sx*Sy-Cy*Sz;
        Mx.M[0][2]=Cx*Sy;
        Mx.M[1][0]=Cx*Sz;
        Mx.M[1][1]=Cx*Cz;
        Mx.M[1][2]=-Sx;
        Mx.M[2][0]=-Cz*Sy+Cy*Sx*Sz;
        Mx.M[2][1]=Cy*Cz*Sx+Sy*Sz;
        Mx.M[2][2]=Cx*Cy;
        break;

    case ORDER_XZY:
        Mx.M[0][0]=Cy*Cz;
        Mx.M[0][1]=-Sz;
        Mx.M[0][2]=Cz*Sy;
        Mx.M[1][0]=Sx*Sy+Cx*Cy*Sz;
        Mx.M[1][1]=Cx*Cz;
        Mx.M[1][2]=-Cy*Sx+Cx*Sy*Sz;
        Mx.M[2][0]=-Cx*Sy+Cy*Sx*Sz;
        Mx.M[2][1]=Cz*Sx;
        Mx.M[2][2]=Cx*Cy+Sx*Sy*Sz;
        break;
    }
    return(Mx);
}*/