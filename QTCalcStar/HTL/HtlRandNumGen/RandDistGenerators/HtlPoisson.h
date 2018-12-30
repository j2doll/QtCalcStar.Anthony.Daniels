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



#ifndef HTL_Poisson_H
#define HTL_Poisson_H
#include "..\HtlRandNumDist.h"

namespace HTL
{
	//forward declarations
	class HtlString;
	class HtlRandNumGen;

	//!HtlRandNumDist is the base class for all random number distributions
	/*!
	HtlRandNumDist is the base class for all random number distributions.
	HtlRandNumDist is also known as the HtlUniform distribution
	*/

	class HTL_DLLAPI HtlPoisson : public HtlRandNumDist
	{

	public:
		
		//!HtlRandNumDist VOID Constructor
		/*!
			The HtlRandNumDist is the base class for all random number distributions.
			It is the same as an HtlUniform distribution between [0,1].
		*/
		HtlPoisson();

		//!HtlRandNumDist VOID Destructor
		/*!
		HtlRandNumDist VOID Destructor. Note this is the virtual destructor.  
		*/
		virtual ~HtlPoisson();

		//!Distribution Mean Value
		HTLMEMVAR_BYREF_STYLE1(public, double, dblLambda);

		//!Gets the next random number generated
		virtual double next(void);
		//!Returns the mean of the distribution
		virtual double mean() const;
		//!Returns the variance of the distribution
		virtual double variance() const;
		//!Returns the prob density function at value x
		virtual double density(double x) const;

	private:

		double m_dblUNext;

	};//end class HtlRandNumDist

};//end HTL namespace

#endif //HTL_RANDNUMDIST_H