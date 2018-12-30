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


#ifndef HTL_RANDNUMGEN_H
#define HTL_RANDNUMGEN_H

#include "..\modHtlLibRefs.h"
#include "..\HtlMacro\modMemVarMacros.h"

namespace HTL
{
//#include "..\HtlBase\HtlString.h"

/* Maximum value that can be returned by the rand function. */
#ifndef RAND_MAX
#define RAND_MAX 0x7fff
#endif
	//!HtlRandNumGen is the base class for all random number generator
	/*!
	HtlRandNumGen is the base class for all random number generator.
	Htl has 3 random number generators, LCG, MLCG, and Mersenne Twister
	*/

	class HTL_DLLAPI HtlRandNumGen{

	public:
		
		//!VOID Constructor
		HtlRandNumGen(void);

		//!Virtual Destructor
		virtual ~HtlRandNumGen();

		//!Accessor for the distribution name
		//HTLMEMVAR_BYVAL_STYLE1(public,HtlString,strGenName);
		
		//!Accessor for previously generated random number
		//HTLMEMVAR_BYVAL_STYLE1(public,double,dblPrevious);

		//!Initialize the random number generator
		virtual void initialize(void);
		//!Gets the next random number generated
		virtual double next(void);
		//!Updates All Stream random numbers
		virtual double nextStream(void);
		//!Accessor for seed
		virtual void Set_dblSeed(double dblNum /* 0.0f <= dblNum <= 1.0f*/);
		//!gets the current rand variate for the selected stream
		double Get_dblStreamVal( int index /*0 <= index <= 127*/);


	protected:
		//!This is used in initializing of seed numbers only
		void seedRand(void);

	protected:
		//!Double seed for the random number generator
		double m_dblSeed;

		//!Buffer for mixing random numbers
		double m_arrDblBuffer[128];
	};//end HtlRandNumGen class definition

};//end HTL namespace

#endif