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

#include ".\HtlRandNumGen.h"
#include <time.h>

namespace HTL{
	//!HtlRandNumGen VOID Constructor
	HtlRandNumGen::HtlRandNumGen(void)
	{
		//set the seed to zero
		m_dblSeed = 0.0f;
		//m_dblPrevious = 0.0f;
		//m_strGenName.clear();
	};

	//!HtlRandNumGen VOID Destructor
	HtlRandNumGen::~HtlRandNumGen()
	{
		//set the seed to zero
		m_dblSeed = 0.0f;
		//m_dblPrevious = 0.0f;
		//m_strGenName.clear();
	};

	/* 0.0f <= dblNum <= 1.0f*/
	void HtlRandNumGen::Set_dblSeed(double dblNum) 
	{
		if( (dblNum > 1.0f) || (dblNum < 0.0f))
		{
			//Throw(Logic_error("Newran: seed out of range"));
			return;
		};
		//iseed = 2147483648L * s;         // for Mother
		m_dblSeed = (long)(dblNum*2147483648L);
		//initialize the streams
		nextStream();
		return;
	};

	//!gets the current rand variate for the selected stream
	//*0 <= index <= 127
	double HtlRandNumGen::Get_dblStreamVal( int index )
	{
		if( (index >= 0) && (index <= 127))
		{
			//valid index, return stream at requested index
			return m_arrDblBuffer[index];
		}else{
			return -1.0f;//error value	
		};
	};

	void HtlRandNumGen::initialize(void)
	{
		//initialize the seeding value
		seedRand();
		//initialize the streams
		nextStream();
		return;
	};
	void HtlRandNumGen::seedRand(void)
	{
		time_t uintSeed;
		//this employs an LCG generator to get the seeding value
		//STL LIBRARY DEPENDANT LINE OF CODE!!!
		//based off of the CPU clock time
		uintSeed = (unsigned int)time(NULL);
		uintSeed = rand();
		m_dblSeed = (double)uintSeed;
		//LCG shifter , this is for notes only...
		//NOT intended to be part of code //RAND_MAX = 32767
		//uintSeed = uintSeed * 1103515245 + 12345;
		//uintReturn = (unsigned int) (uintSeed / 65536) % 32768;

		//use the built in rand function to auto-generate the seed value
		//double dblAutoSeed = ((double)uintSeed)/((double)RAND_MAX);
		//m_dblSeed = (long)(dblAutoSeed*2147483648L);

		//initialize the streams
		
		return;
	};

	double HtlRandNumGen::next(void)
	{
		//safety check
		if (m_dblSeed <= 0.0)
		{
			//need to initialize the seed value
			seedRand();
		};
		// m = 2147483647 = 2^31 - 1; a = 16807;
		// 127773 = m div a; 2836 = m mod a
		long iseed = (long)m_dblSeed;
		long hi = iseed / 127773L;                 // integer division
		long lo = iseed - hi * 127773L;            // modulo
		iseed = 16807 * lo - 2836 * hi;
		if (iseed <= 0) iseed += 2147483647L;
		m_dblSeed = (double)iseed;
		
		return m_dblSeed*4.656612875e-10;
	};

	//!Gets the next random number generated
	double HtlRandNumGen::nextStream(void)
	{
		if (m_dblSeed <= 0.0)
		{
			seedRand();
		};
		//select number stream to update
		int iSel = (int)(next()*128);               // 0 <= i < 128
		
		for (int i = 0; i < 128; i++)
		{
			m_arrDblBuffer[i] = next();
		};
		//return the randomly selected stream
		return m_arrDblBuffer[iSel];

	};



};//end HTL namespace 