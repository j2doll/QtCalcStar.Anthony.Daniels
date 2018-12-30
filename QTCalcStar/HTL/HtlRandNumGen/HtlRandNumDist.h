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


#ifndef HTL_RANDNUMDIST_H
#define HTL_RANDNUMDIST_H

#include "..\modHtlLibRefs.h"
#include "..\modHtlMacro.h"

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

	class HTL_DLLAPI HtlRandNumDist
	{

	public:
		
		//!HtlRandNumDist VOID Constructor
		/*!
			The HtlRandNumDist is the base class for all random number distributions.
			It is the same as an HtlUniform distribution between [0,1].
		*/
		HtlRandNumDist();

		//!HtlRandNumDist VOID Destructor
		/*!
		HtlRandNumDist VOID Destructor. Note this is the virtual destructor.  
		*/
		virtual ~HtlRandNumDist();
		
		//creation of 
		void createRNG(const char * ptrName);
		void createRNG(const HtlString  & strName);

		void clearRNG(void);
		void clear(void);

		//!Initialize the random number generator
		void initialize(void);
		//!Gets the next random number generated
		virtual double next(void);
		//!Updates All Stream random numbers
		double nextStream(void);
		//!gets the current rand variate for the selected stream
		double Get_dblStreamVal( int index /*0 <= index <= 127*/);

		//!Return a number shifted to lie between A <= x <= B
		int intNextAB( const int & A, const int & B );
		float sngNextAB(const float & A, const float & B);
		double dblNextAB(const double & A, const double & B);

		//!Returns the mean of the distribution
		virtual double mean() const { return 0.5; };
		//!Returns the variance of the distribution
		virtual double variance() const { return 1.0/12.0; };
		//!Returns the prob density function at value x
		virtual double density(double x) const { return (x < 0.0 || x > 1.0) ? 0 : 1.0; };


	protected:
		//!Pointer to the Random Number Generator
		HtlRandNumGen * m_ptrRNG;
		//!buffer for mixing random numbers
		double m_arrDblBuffer[128];

	};//end class HtlRandNumDist

	typedef HtlRandNumDist HtlUniform;

};//end HTL namespace

#endif //HTL_RANDNUMDIST_H