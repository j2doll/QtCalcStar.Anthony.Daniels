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


#ifndef HTL_MLCGENERATOR_H
#define HTL_MLCGENERATOR_H

#include "..\HtlRandNumGen.h"
namespace HTL
{

	//!HtlLCGenerator is a Multiple Linear Congruental Random Number Generator
	/*!
	HtlLCGenerator is a MultipleLinear Congruental Random Number Generator
	
	*/

	class HTL_DLLAPI HtlMLCGenerator: public HtlRandNumGen{

	public:
		
		//!HtlMLCGenerator VOID Constructor
		/*!
			The HtlMLCGenerator is the base class for all random number generators that are 
			in turn used for the distribution random number generator
		*/
		HtlMLCGenerator(void);

		//!HtlMLCGenerator VOID Destructor
		/*!
		HtlMLCGenerator VOID Destructor. Note this is the virtual destructor.  
		*/
		virtual ~HtlMLCGenerator();

		//initialize the random number generator
		virtual void initialize(void);
		//!Gets the next random number generated
		virtual double next(void);
		//!Updates All Stream random numbers
		virtual double nextStream(void);


	};//end HtlLCGenerator class definition

};//end HTL namespace

#endif // HTL_MLCGENERATOR_H