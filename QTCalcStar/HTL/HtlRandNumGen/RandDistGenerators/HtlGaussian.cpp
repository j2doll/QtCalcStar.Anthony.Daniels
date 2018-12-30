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
#include ".\HtlGaussian.h"
#include "..\HtlRandNumGen.h"
#include "..\..\modHtlMath.h"

namespace HTL
{
	HtlGaussian::HtlGaussian()
	{
		this->m_dblMean = 0.0f;
		this->m_dblSigma = 1.0f;
		return;
	};

	HtlGaussian::~HtlGaussian()
	{

		return;
	};

	//!Gets the next random number generated
	double HtlGaussian::next(void)
	{
		//This gaussian rand num distribution is generated using the Box-Mueller Transformation
		//It starts out with Z0 and Z1 being normally distributed.  Then it transforms the 
		double Z0, Z1, U0, U1, PI, dblX, dblZ;
		PI = 3.1415928;
		U0 = this->m_ptrRNG->next();
		U1 = this->m_ptrRNG->next();
		//generate random variates on the Box-Mueller Circle
		Z0 = sqrt(-2.0f * log(U0))* cos(2.0f * PI * U1);
		Z1 = sqrt(-2.0f * log(U0))* sin(2.0f * PI * U1);
		//transform to pdf
		dblX = 0.0f + Z0 * 1.0f;
		//transform back to final gaussian form
		dblZ = (dblX - m_dblMean) / m_dblSigma;
		return dblZ;
	};
	//!Returns the mean of the distribution
	double HtlGaussian::mean() const
	{

		return m_dblMean;
	};
	//!Returns the variance of the distribution
	double HtlGaussian::variance() const
	{

		return (m_dblSigma * m_dblSigma);
	};
	//!Returns the prob density function at value x
	double HtlGaussian::density(double x) const
	{
		double dblZVal, PI;
		PI = 3.1415928;
		//Gaussian distribution
		dblZVal = (1 / (m_dblSigma * sqrt(2.0f * PI) ) ) * 
			exp( -1.0f * (pow(double(x - m_dblMean),2) / (2.0f* pow(double(m_dblSigma),2))));
		return dblZVal;
	};

};//end namespace HTL