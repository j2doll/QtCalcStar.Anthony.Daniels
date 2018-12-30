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
#include ".\HtlExponential.h"
#include "..\HtlRandNumGen.h"
#include "..\..\modHtlMath.h"

namespace HTL
{
	HtlExponential::HtlExponential()
	{
		this->m_dblBeta = 1.0f;
		return;
	};

	HtlExponential::~HtlExponential()
	{

		return;
	};

	//!Gets the next random number generated
	double HtlExponential::next(void)
	{
		//This Exponential rand num distribution is generated using the Box-Mueller Transformation
		//It starts out with Z0 and Z1 being normally distributed.  Then it transforms the 
		double  U0, PI, dblZ;
		PI = 3.1415928;
		U0 = this->m_ptrRNG->next();
		dblZ = -1.0f * m_dblBeta * log(U0);
		return dblZ;
	};
	//!Returns the mean of the distribution
	double HtlExponential::mean() const
	{

		return m_dblBeta;
	};
	//!Returns the variance of the distribution
	double HtlExponential::variance() const
	{
		return (m_dblBeta * m_dblBeta);
	};
	//!Returns the prob density function at value x
	double HtlExponential::density(double x) const
	{
		double dblZVal, PI;
		PI = 3.1415928;
		//Exponential distribution
		dblZVal = (1.0f / m_dblBeta) * exp((-x)/m_dblBeta);
		return dblZVal;
	};

};//end namespace HTL