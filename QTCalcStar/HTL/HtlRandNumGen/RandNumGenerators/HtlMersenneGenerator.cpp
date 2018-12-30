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

#include ".\HtlMersenneGenerator.h"
#include <time.h>

namespace HTL{
	//!HtlRandNumGen VOID Constructor
	HtlMersenneGenerator::HtlMersenneGenerator(void)
		: HtlRandNumGen ()
	{
		//set the seed to zero
		m_dblSeed = 0.0f;
      m_blnLocked = false;
		//m_dblPrevious = 0.0f;
		//m_strGenName.clear();
	};

	//!HtlRandNumGen VOID Destructor
	HtlMersenneGenerator::~HtlMersenneGenerator()
	{
		//set the seed to zero
		m_dblSeed = 0.0f;
		//m_dblPrevious = 0.0f;
		//m_strGenName.clear();
	};

	void HtlMersenneGenerator::initialize(void)
	{
		//initialize the seeding value
		seedRand();

		unsigned long ulngSeed;

		ulngSeed = (unsigned long)(m_dblSeed * 1000000000000.0f);

		state[0] = ulngSeed & 0xFFFFFFFFUL; // for > 32 bit machines
		for (int i = 1; i < n; ++i) {
			state[i] = 1812433253UL * (state[i - 1] ^ (state[i - 1] >> 30)) + i;
			// see Knuth TAOCP Vol2. 3rd Ed. P.106 for multiplier
			// in the previous versions, MSBs of the seed affect only MSBs of the array state
			// 2002/01/09 modified by Makoto Matsumoto
			state[i] &= 0xFFFFFFFFUL; // for > 32 bit machines
		}
		p = n; // force gen_state() to be called for next random number
		//initialize the streams
		nextStream();
		return;
	};


	double HtlMersenneGenerator::next(void)
	{
      while (m_blnLocked)
      {
         //spin;
      }
      m_blnLocked = true;//lock critical section

		if (p == n) gen_state(); // new state vector needed
		// gen_state() is split off to be non-inline, because it is only called once
		// in every 624 calls and otherwise irand() would become too big to get inlined
		unsigned long x = state[p++];
		x ^= (x >> 11);
		x ^= (x << 7) & 0x9D2C5680UL;
		x ^= (x << 15) & 0xEFC60000UL;
		unsigned long ulngResult =  x ^ (x >> 18);
		m_dblSeed = static_cast<double>(ulngResult);
      double dblRet = (m_dblSeed * (1. / 4294967295.));// divided by 2^32 - 1

      m_blnLocked = false;//unlock critical section
		return dblRet;
	};

///PRIVATE FUNCTIONS////////
// initialization of static private members
unsigned long HtlMersenneGenerator::state[n] = {0x0UL};
int HtlMersenneGenerator::p = 0;

void HtlMersenneGenerator::gen_state() { // generate new state vector
  for (int i = 0; i < (n - m); ++i)
    state[i] = state[i + m] ^ twist(state[i], state[i + 1]);
  for (int i = n - m; i < (n - 1); ++i)
    state[i] = state[i + m - n] ^ twist(state[i], state[i + 1]);
  state[n - 1] = state[m - 1] ^ twist(state[n - 1], state[0]);
  p = 0; // reset position
}
// inline for speed, must therefore reside in header file
unsigned long HtlMersenneGenerator::twist(unsigned long u, unsigned long v)
{
  return (((u & 0x80000000UL) | (v & 0x7FFFFFFFUL)) >> 1)
    ^ ((v & 1UL) ? 0x9908B0DFUL : 0x0UL);
};



};//end HTL namespace 