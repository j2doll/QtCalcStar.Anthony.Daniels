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

#include ".\HtlRandNumDist.h"
#include ".\HtlRandNumGen.h"

#include "..\modHtlString.h"
#include "..\HtlMath\HtlBasicMath.h"

#include ".\RandNumGenerators\HtlLCGenerator.h"
#include ".\RandNumGenerators\HtlMLCGenerator.h"
#include ".\RandNumGenerators\HtlMersenneGenerator.h"
using namespace HTL;
namespace HTL{
	//!HtlRandNumGen VOID Constructor
	HtlRandNumDist::HtlRandNumDist()
	{
		m_ptrRNG = NULL;
		clear();
		createRNG("default");
	};
	//!HtlRandNumGen VOID Constructor
	HtlRandNumDist::~HtlRandNumDist()
	{
		clear();
	}

	//creation of Random Number Generator
	void HtlRandNumDist::createRNG(const char * ptrName)
	{
		//safety check on already existing number generator
		if(m_ptrRNG){clearRNG();};
		//should be using an object factory, but don't have
		//it written yet because have no map class
		//so instead using if then statements for testing

		if(ptrName == "HtlLCGenerator"){m_ptrRNG = new HtlLCGenerator();m_ptrRNG->initialize(); return;};
		if(ptrName == "HtlMLCGenerator"){m_ptrRNG = new HtlMLCGenerator();m_ptrRNG->initialize(); return;};
		if(ptrName == "HtlMersenneGenerator"){m_ptrRNG = new HtlMersenneGenerator();m_ptrRNG->initialize(); return;};
		if(ptrName == "default"){m_ptrRNG = new HtlRandNumGen();m_ptrRNG->initialize(); return;};
		//else create default generator
		m_ptrRNG = new HtlRandNumGen();
		m_ptrRNG->initialize();
	};

	void HtlRandNumDist::createRNG(const HtlString  & strName)
	{
		//safety check on already existing number generator
		if(m_ptrRNG){clearRNG();};
		//should be using an object factory, but don't have
		//it written yet because have no map class
		//so instead using if then statements for testing

		if(strName == "HtlLCGenerator"){m_ptrRNG = new HtlLCGenerator();m_ptrRNG->initialize(); return;};
		if(strName == "HtlMLCGenerator"){m_ptrRNG = new HtlMLCGenerator();m_ptrRNG->initialize(); return;};
		if(strName == "HtlMersenneGenerator"){m_ptrRNG = new HtlMersenneGenerator();m_ptrRNG->initialize(); return;};
		if(strName == "default"){m_ptrRNG = new HtlRandNumGen();m_ptrRNG->initialize(); return;};
		//else create default generator
		m_ptrRNG = new HtlRandNumGen();
		m_ptrRNG->initialize();

	};

	void HtlRandNumDist::clearRNG(void)
	{
		if(m_ptrRNG){delete m_ptrRNG; m_ptrRNG = NULL;};
		m_ptrRNG = NULL;
	};

	void HtlRandNumDist::clear(void)
	{
		//clear the random number generator
		clearRNG();
		return;
	};

	//!Initialize the random number generator
	void HtlRandNumDist::initialize(void)
	{
		//safety check
		if(!m_ptrRNG){return;};
		return m_ptrRNG->initialize();
	};

	//!Gets the next random number generated
	double HtlRandNumDist::next(void)
	{
		//safety check
		if(!m_ptrRNG){return -1.0;};
		return m_ptrRNG->next();
	};

	//!Updates All Stream random numbers
	double HtlRandNumDist::nextStream(void)
	{
		//select number stream to update 
		// 0 <= i < 128
		int iSel = (int)(next()*128);              

		for (int i = 0; i < 128; i++)
		{
			m_arrDblBuffer[i] = next();
		};
		//return the randomly selected stream
		return m_arrDblBuffer[iSel];
	};

	//!gets the current rand variate for the selected stream
	double HtlRandNumDist::Get_dblStreamVal( int index /*0 <= index <= 127*/)
	{
		if( (index >= 0) && (index <= 127))
		{
			//valid index, return stream at requested index
			return m_arrDblBuffer[index];
		}else{
			return -1.0f;//error value	
		};	
	};

	//!Return a number shifted to lie between A <= x <= B
	int HtlRandNumDist::intNextAB( const int & A, const int & B )
	{
		return (int)( Math::hround(next()*( B - A) + A) );
	};

	float HtlRandNumDist::sngNextAB(const float & A, const float & B)
	{
		return (float)(next()*( B - A) + A);
	};

	double HtlRandNumDist::dblNextAB(const double & A, const double & B)
	{
		return (double)(next()*( B - A) + A);
	};


};//end HTL namespace

