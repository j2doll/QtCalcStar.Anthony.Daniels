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
#include ".\HtlPoisson.h"
#include "..\HtlRandNumGen.h"
#include "..\..\modHtlMath.h"

namespace HTL
{
	HtlPoisson::HtlPoisson()
	{
		this->m_dblLambda = 1.0f;
		return;
	};

	HtlPoisson::~HtlPoisson()
	{

		return;
	};

	//!Gets the next random number generated
	double HtlPoisson::next(void)
	{
		//This Poisson rand num distribution is generated using the Box-Mueller Transformation
		//It starts out with Z0 and Z1 being normally distributed.  Then it transforms the 
		double U0, dblA, dblB;
		int i;
		bool blnFound = false;		

		dblA = exp(-m_dblLambda); 
		dblB = 1.0f; 
		i = 0;
		do
		{
			blnFound = false;
			U0 = this->m_ptrRNG->next();
			dblB = dblB * U0;
			if(dblB < dblA)
			{
				//return 
				blnFound = true;
				return (double(i));
			}else{
				i = i + 1;
			};
		}while(!blnFound);

		
		return (double(i));
	};
	//!Returns the mean of the distribution
	double HtlPoisson::mean() const
	{

		return m_dblLambda;
	};
	//!Returns the variance of the distribution
	double HtlPoisson::variance() const
	{

		return m_dblLambda;
	};
	//!Returns the prob density function at value x
	double HtlPoisson::density(double x) const
	{
		double dblZVal;
		int intX;

		if(x < 0){return 0;};
		intX = int(Math::hround(x));
		// = (exp ( -lambda) * pow(lambda,intX))/factorial(intX)
		dblZVal =(exp ( -m_dblLambda) * pow(m_dblLambda,intX))/ Math::factorial(intX);
		return dblZVal;
	};

};//end namespace HTL