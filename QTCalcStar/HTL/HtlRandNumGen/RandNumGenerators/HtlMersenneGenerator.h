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

// mtrand.h
// C++ include file for MT19937, with initialization improved 2002/1/26.
// Coded by Takuji Nishimura and Makoto Matsumoto.
// Ported to C++ by Jasper Bedaux 2003/1/1 (see http://www.bedaux.net/mtrand/).
// The generators returning floating point numbers are based on
// a version by Isaku Wada, 2002/01/09
//
// Copyright (C) 1997 - 2002, Makoto Matsumoto and Takuji Nishimura,
// All rights reserved.
//
// Redistribution and use in source and binary forms, with or without
// modification, are permitted provided that the following conditions
// are met:
//
// 1. Redistributions of source code must retain the above copyright
//    notice, this list of conditions and the following disclaimer.
//
// 2. Redistributions in binary form must reproduce the above copyright
//    notice, this list of conditions and the following disclaimer in the
//    documentation and/or other materials provided with the distribution.
//
// 3. The names of its contributors may not be used to endorse or promote
//    products derived from this software without specific prior written
//    permission.
//
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
// "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
// LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
// A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR
// CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
// EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
// PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR
// PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF
// LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
// NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
// SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
//
// Any feedback is very welcome.
// http://www.math.keio.ac.jp/matumoto/emt.html
// email: matumoto@math.keio.ac.jp
//
// Feedback about the C++ port should be sent to Jasper Bedaux,
// see http://www.bedaux.net/mtrand/ for e-mail address and info.


#ifndef HTL_MERSENNEGENERATOR_H
#define HTL_MERSENNEGENERATOR_H

#include "..\HtlRandNumGen.h"

namespace HTL
{
	//!HtlMersenneGenerator is a Mersenne Twister Random Number Generator
	/*!
	HtlMersenneGenerator is a Mersenne Twister Random Number Generator
	
	*/

	class HTL_DLLAPI HtlMersenneGenerator : public HtlRandNumGen
	{

	public:
		
		//!HtlMersenneGenerator VOID Constructor
		/*!
			The HtlMersenneGenerator is the base class for all random number generators that are 
			in turn used for the distribution random number generator
		*/
		HtlMersenneGenerator(void);

		//!HtlMersenneGenerator VOID Destructor
		/*!
		HtlMersenneGenerator VOID Destructor. Note this is the virtual destructor.  
		*/
		virtual ~HtlMersenneGenerator();

		//initialize the random number generator
		virtual void initialize(void);
		//!Gets the next random number generated
		virtual double next(void);

	private:
		static const int n = 624;
		static const int m = 397; // compile time constants
		// the variables below are static (no duplicates can exist)
		static unsigned long state[n]; // state vector array
		static int p; // position in state array

		// private functions used to generate the pseudo random numbers
		unsigned long twist(unsigned long, unsigned long); // used by gen_state()
		void gen_state(); // generate new state
   private:
      bool m_blnLocked;
	};//end HtlLCGenerator class definition

};//end HTL namespace

#endif // HTL_MERSENNEGENERATOR_H