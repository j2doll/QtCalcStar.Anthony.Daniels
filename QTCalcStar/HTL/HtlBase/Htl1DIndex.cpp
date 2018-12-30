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

#include ".\Htl1DIndex.h"
#include "..\modHtlArchive.h"

namespace HTL{
	//These are indexes for the various models
	//BEGIN Htl1DIndex DEFINITION SECTION/////////////////////////////////
	//!One Dimensional Index for lists, vectors, etc.

	Htl1DIndex::Htl1DIndex()
	{
		m_ptrParent = NULL;
		m_lngX = -1;
	};
	Htl1DIndex::~Htl1DIndex()
	{
		m_ptrParent = NULL;
		m_lngX = -1;
	};
	bool Htl1DIndex::operator==(const Htl1DIndex& ptrRHS) 
	{
		return (m_lngX == ptrRHS.m_lngX);
	};
	bool Htl1DIndex::operator!=(const Htl1DIndex& ptrRHS) 
	{
		return (m_lngX != ptrRHS.m_lngX);
	};
	bool Htl1DIndex::operator<=(const Htl1DIndex& ptrRHS) 
	{
		return (m_lngX <= ptrRHS.m_lngX);
	};
	bool Htl1DIndex::operator>=(const Htl1DIndex& ptrRHS) 
	{
		return (m_lngX >= ptrRHS.m_lngX);
	};
	bool Htl1DIndex::operator<(const Htl1DIndex& ptrRHS) 
	{
		return (m_lngX < ptrRHS.m_lngX);
	};
	bool Htl1DIndex::operator>(const Htl1DIndex& ptrRHS) 
	{
		return (m_lngX > ptrRHS.m_lngX);
	};

	//clearing methods
	void Htl1DIndex::ClearParent(void){m_ptrParent = NULL;};
	void Htl1DIndex::Clear(void)
	{
		m_ptrParent = NULL;
		m_lngX = -1;
	};
	void Htl1DIndex::Zero(void)
	{
		m_ptrParent = NULL;
		m_lngX = 0;
	};
	
		//Virtual Inheritance Serialization Engines
	//SERIALIZATION ACCESSOR MACRO///////////////////////////////////////
	int Htl1DIndex::Save(HTL::HtlElement * ptrCurrNode, std::string strMemVarName, bool blnWithSubObjects)
	{

		int intReturn = 0;
		//SAFETY CHECK //put at top of all Serialize Methods
		if(!ptrCurrNode){return 0;};
		//CALL PARENT CLASS Serialize()
		/*...*/
		HtlBase::Save(ptrCurrNode, strMemVarName, blnWithSubObjects);
		//Standard Member Variables
		intReturn &= SetHtlMemVar<long,CPP_LONG>(ptrCurrNode,"m_lngX",m_lngX,blnWithSubObjects);
		
		return intReturn;
	};

	int Htl1DIndex::Load(HTL::HtlElement * ptrCurrNode, std::string strMemVarName)
	{

		int intReturn = 0;
		//SAFETY CHECK //put at top of all Serialize Methods
		if(!ptrCurrNode){return 0;};
		//CALL PARENT CLASS Serialize()
		/*...*/
		HtlBase::Load(ptrCurrNode,strMemVarName);
		//Standard Member Variables
		intReturn &= GetHtlMemVar<long,CPP_LONG>(ptrCurrNode,"m_lngX",m_lngX);

		return intReturn;

	};

};