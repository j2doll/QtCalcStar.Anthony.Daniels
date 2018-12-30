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

#include ".\HtlMLCGenerator.h"
#include <time.h>

namespace HTL{
	//!HtlRandNumGen VOID Constructor
	HtlMLCGenerator::HtlMLCGenerator(void)
	{
		//set the seed to zero
		m_dblSeed = 0.0f;
		//m_dblPrevious = 0.0f;
		//m_strGenName.clear();
	};

	//!HtlRandNumGen VOID Destructor
	HtlMLCGenerator::~HtlMLCGenerator()
	{
		//set the seed to zero
		m_dblSeed = 0.0f;
		//m_dblPrevious = 0.0f;
		//m_strGenName.clear();
	};
	
	void HtlMLCGenerator::initialize(void)
	{
		//initialize the seeding value
		seedRand();
		//initialize the streams
		nextStream();
		return;
	};


	double HtlMLCGenerator::next(void)
	{
		//safety check
		if (m_dblSeed <= 0.0)
		{
			//need to initialize the seed value
			initialize();
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
	double HtlMLCGenerator::nextStream(void)
	{
		if (m_dblSeed <= 0.0)
		{
			initialize();
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