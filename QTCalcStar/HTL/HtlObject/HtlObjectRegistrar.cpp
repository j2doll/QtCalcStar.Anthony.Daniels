/*
**	This file is part of the Object Relational SQL DataBase (Htl).
**	This software was developed by:
**	
**  Anthony Daniels, Mi Yan
**	The University of Michigan
**	Department of Naval Architecture & Marine Engineering
**	Department of Computer Science
**
**  Object Relational SQL DataBase is free software: you can redistribute it and/or modify
**  it under the terms of the GNU Lesser General Public License as published by
**  the Free Software Foundation, either version 3 of the License, or
**  (at your option) any later version.
**
**  Object Relational SQL DataBase is distributed in the hope that it will be useful,
**  but WITHOUT ANY WARRANTY; without even the implied warranty of
**  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
**  GNU Lesser General Public License for more details.
**
**  You should have received a copy of the GNU Lesser General Public License
**  along with Object Relational SQL DataBase.  If not, see <http://www.gnu.org/licenses/>.
*/
#pragma once
#pragma warning(push)
#pragma warning (disable : 4005 ) /* macro redefinition */
#define HTL_DLLEXPORT
#pragma warning(pop)

#include ".\HtlObjectRegistrar.h"
#include ".\HtlObjectRegistrarTempFuncs.cpp"

using namespace HTL;

//!Generic Public Constructor 
HtlObjectRegistrar::HtlObjectRegistrar(void)
{
	return;
};

//!Default Destructor Method
HtlObjectRegistrar::~HtlObjectRegistrar(void)
{
	ClearRegistry();
	return;	
};

//!Get the pointer to the HtlObject
HtlObject * HtlObjectRegistrar::GetHtlObjectPtr( HtlGUID128 & objGUID)
{
	ObjectMapIterator iter;
	size_t intNumMaps;
	//lock the map
	m_objMutex.lock(m_objKey);

	HtlObject * ptrObj = NULL;
	HtlObjectMap* ptrMap = NULL;
	//safety checks
	intNumMaps = m_objMetaMap.size();
	if(intNumMaps <= 0)
	{	
		m_objMutex.unlock(m_objKey);
		return NULL;
	};
	for(iter = m_objMetaMap.begin(); iter!= m_objMetaMap.end(); ++iter)
	{
		ptrMap = iter->second;
		if(ptrMap)
		{
			ptrObj = ptrMap->GetHtlObjectPtr(objGUID);
			if(ptrObj)
			{
				//match found
				m_objMutex.unlock(m_objKey);
				return ptrObj;
			};//end object check
		};//end map check
	};//end for loop through maps

	m_objMutex.unlock(m_objKey);
	return ptrObj;	
};

//!Get a ISA Dialog by its GUID
bool HtlObjectRegistrar::DoesHtlObjectExist( HtlGUID128 & objGUID)
{
	ObjectMapIterator iter;
	size_t intNumMaps;
	//lock the map
	m_objMutex.lock(m_objKey);

	bool blnExist = false;
	HtlObjectMap* ptrMap = NULL;
	//safety checks
	intNumMaps = m_objMetaMap.size();
	if(intNumMaps <= 0)
	{	
		m_objMutex.unlock(m_objKey);
		return NULL;
	};
	for(iter = m_objMetaMap.begin(); iter!= m_objMetaMap.end(); ++iter)
	{
		ptrMap = iter->second;
		if(ptrMap)
		{
			blnExist = ptrMap->DoesHtlObjectExist(objGUID);
			if(blnExist)
			{
				//match found
				m_objMutex.unlock(m_objKey);
				return true;
			};//end object check
		};//end map check
	};//end for loop through maps
	//didn't find a match
	m_objMutex.unlock(m_objKey);
	return false;		
};


//!Clear the registry
void HtlObjectRegistrar::ClearRegistry(void)
{
	ObjectMapIterator iter;
	size_t intNumMaps;
	//lock the map
	m_objMutex.lock(m_objKey);

	bool blnExist = false;
	HtlObjectMap* ptrMap = NULL;
	//safety checks
	intNumMaps = m_objMetaMap.size();
	if(intNumMaps <= 0)
	{	
		m_objMutex.unlock(m_objKey);
		return;
	};
	for(iter = m_objMetaMap.begin(); iter!= m_objMetaMap.end(); ++iter)
	{
		ptrMap = iter->second;
		if(ptrMap)
		{
			delete ptrMap;
		};//end map check
	};//end for loop through maps
	m_objMetaMap.clear();
	//release the lock
	m_objMutex.unlock(m_objKey);
	return;		
};

