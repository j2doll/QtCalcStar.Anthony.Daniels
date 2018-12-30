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

#ifndef HTL_OBJECTREGISTRAR_TEMPFUNCS_CPP
#define HTL_OBJECTREGISTRAR_TEMPFUNCS_CPP

using namespace HTL;

//!Get the pointer to the HtlObject, this searches only a specific object map type
template<typename TObj>
HtlObject * HtlObjectRegistrar::GetHtlObjectPtr( HtlGUID128 & objGUID)
{
	HtlObject * ptrObjReturn = NULL;
	//first search the map of the template object
	strMapType = HTL_STRINGIZE(TObj);;
	//lock the map
	m_objMutex.lock(m_objKey);

	HtlObjectRegistrar::ObjectMapIterator iter;
	iter = m_objMetaMap.find(strMapType);
	if(iter != m_objMetaMap.end())
	{
		//then search that map
		HtlObjectMap* ptrTypeMap = NULL;
		ptrTypeMap = iter->second;
		//then check the map pointer
		if(ptrTypeMap)
		{
			ptrObjReturn = ptrTypeMap->GetHtlObjectPtr(objGUID);
		};
	};
	m_objMutex.unlock(m_objKey);
	return ptrObjReturn;
};
//map container accessors
template <typename TObj>
HtlObjectMap*  HtlObjectRegistrar::AddHtlMap(void)
{
	//first search the map of the template object
	std::string strMapType = HTL_STRINGIZE(TObj);;
	//lock the map
	m_objMutex.lock(m_objKey);
	ObjectMapIterPair iterInsert;
	HtlObjectMap * ptrNewMap = new HtlObjectMap();
	iterInsert = m_objMetaMap.insert(std::make_pair(strMapType,ptrNewMap));
	if(iterInsert.second == false)
	{//then already exist, delete the new one
		delete ptrNewMap;
	}
	HtlObjectMap* ptrMap = NULL;
	if(iterInsert.first != m_objMetaMap.end())
	{
		ptrMap = iterInsert.first->second;
	};
	m_objMutex.unlock(m_objKey);
	if(ptrMap)
	{
		return ptrMap;
	}else{
		return NULL;
	};
};

//map container accessors
template <typename TObj>
HtlObjectMap* HtlObjectRegistrar::AddHtlMap_NoLock(void)
{
	//first search the map of the template object
	std::string strMapType = HTL_STRINGIZE(TObj);
	//lock the map
	ObjectMapIterPair iterInsert;
	HtlObjectMap * ptrNewMap = new HtlObjectMap();
	iterInsert = m_objMetaMap.insert(std::make_pair(strMapType,ptrNewMap));
	if(iterInsert.second == false)
	{//then already exist, delete the new one
		delete ptrNewMap;
	}
	HtlObjectMap* ptrMap = NULL;
	if(iterInsert.first != m_objMetaMap.end())
	{
		ptrMap = iterInsert.first->second;
	};
	if(ptrMap)
	{
		return ptrMap;
	}else{
		return NULL;
	};
};

template <typename TObj>
void HtlObjectRegistrar::DeleteHtlMap(void)
{
	//first search the map of the template object
	strMapType = HTL_STRINGIZE(TObj);;
	//lock the map
	m_objMutex.lock(m_objKey);

	HtlObjectRegistrar::ObjectMapIterator iterFind;
	iterFind = m_objMetaMap.find(strMapType,ptrNewMap);
	HtlObjectMap* ptrMap = NULL;
	if(iterFind != m_objMetaMap.end())
	{
		ptrMap = iterFind->second;
	};
	if(ptrMap)
	{//then already exist, delete the new one
		delete ptrMap;
		m_objMetaMap.erase(iterFind);
	};
	m_objMutex.unlock(m_objKey);
	return;
};

template <typename TObj>
void HtlObjectRegistrar::DeleteHtlMap_NoLock(void)
{
	//first search the map of the template object
	strMapType = HTL_STRINGIZE(TObj);;
	//lock the map
	HtlObjectRegistrar::ObjectMapIterator iterFind;
	iterFind = m_objMetaMap.find(strMapType,ptrNewMap);
	HtlObjectMap* ptrMap = NULL;
	if(iterFind != m_objMetaMap.end())
	{
		ptrMap = iterFind->second;
	};
	if(ptrMap)
	{//then already exist, delete the new one
		delete ptrMap;
		m_objMetaMap.erase(iterFind);
	};
	return;
};

template <typename TObj>
HtlObjectMap* HtlObjectRegistrar::GetHtlMapPtr(void)
{
	//first search the map of the template object
	strMapType = HTL_STRINGIZE(TObj);;
	//lock the map
	m_objMutex.lock(m_objKey);

	HtlObjectRegistrar::ObjectMapIterator iterFind;
	iterFind = m_objMetaMap.find(strMapType);
	HtlObjectMap* ptrMap = NULL;

	if(iterFind != m_objMetaMap.end())
	{
		ptrMap = iterFind->second;
	};
	if(ptrMap)
	{	
		m_objMutex.unlock(m_objKey);
		return ptrMap;
	}else{
		m_objMutex.unlock(m_objKey);
		return NULL;
	};
	return NULL;
};
//!Register an ISA dialog to the server
template<typename TObj>
int HtlObjectRegistrar::RegisterHtlObject(HtlObject * ptrObj)
{
	//first search the map of the template object
	std::string strMapType = HTL_STRINGIZE(TObj);;
	//lock the map
	m_objMutex.lock(m_objKey);
	ObjectMapIterator iterFind;
	iterFind = m_objMetaMap.find(strMapType);
	HtlObjectMap* ptrMap = NULL;
	if(iterFind != m_objMetaMap.end())
	{
		ptrMap = iterFind->second;
	};
	if(ptrMap)
	{
		ptrMap->RegisterHtlObject(ptrObj);
	}else{
		//need to create the map first
		ptrMap = AddHtlMap_NoLock<TObj>();
		if(ptrMap)
		{
			ptrMap->RegisterHtlObject(ptrObj);
		}else{
			//failed to create new map
			m_objMutex.unlock(m_objKey);
			return 0;
		};
	};
	//successful
	m_objMutex.unlock(m_objKey);
	return 1;
};

template<typename TObj>
int HtlObjectRegistrar::RegisterHtlObject(HtlObject * ptrObj, HtlGUID128 & objGUID)
{
	//first search the map of the template object
	std::string strMapType;
	strMapType = HTL_STRINGIZE(TObj);
	//lock the map
	m_objMutex.lock(m_objKey);
	ObjectMapIterator iterFind;
	iterFind = m_objMetaMap.find(strMapType);
	HtlObjectMap* ptrMap = NULL;
	if(iterFind != m_objMetaMap.end())
	{
		ptrMap = iterFind->second;
	};
	if(ptrMap)
	{
		ptrMap->RegisterHtlObject(ptrObj, objGUID);
	}else{
		//need to create the map first
		ptrMap = AddHtlMap_NoLock<TObj>();
		if(ptrMap)
		{
			ptrMap->RegisterHtlObject(ptrObj, objGUID);
		}else{
			//failed to create new map
			m_objMutex.unlock(m_objKey);
			return 0;
		};
	};
	//successful
	m_objMutex.unlock(m_objKey);
	return 1;
};

template<typename TObj>
int HtlObjectRegistrar::UpdateHtlObject(HtlObject * ptrObj, HtlGUID128 & objNewGUID)
{
	//first search the map of the template object
	std::string strMapType = HTL_STRINGIZE(TObj);;
	//lock the map
	m_objMutex.lock(m_objKey);
	ObjectMapIterator iterFind;
	iterFind = m_objMetaMap.find(strMapType);
	HtlObjectMap* ptrMap = NULL;
	if(iterFind != m_objMetaMap.end())
	{
		ptrMap = iterFind->second;
	};
	if(ptrMap)
	{
		ptrMap->UpdateHtlObject(ptrObj, objNewGUID);
	}else{
		//need to create the map first
		ptrMap = AddHtlMap_NoLock<TObj>();
		if(ptrMap)
		{
			ptrMap->UpdateHtlObject(ptrObj, objNewGUID);
		}else{
			//failed to create new map
			m_objMutex.unlock(m_objKey);
			return 0;
		};
	};
	//successful
	m_objMutex.unlock(m_objKey);
	return 1;
};

template<typename TObj>
int HtlObjectRegistrar::UpdateHtlObject(HtlGUID128 & objGUID, HtlObject * ptrNewObj)
{
	//first search the map of the template object
	std::string strMapType = HTL_STRINGIZE(TObj);;
	//lock the map
	m_objMutex.lock(m_objKey);

	ObjectMapIterator iterFind;
	iterFind = m_objMetaMap.find(strMapType);
	HtlObjectMap* ptrMap = NULL;
	if(iterFind != m_objMetaMap.end())
	{
		ptrMap = iterFind->second;
	};
	if(ptrMap)
	{
		ptrMap->UpdateHtlObject(objGUID, ptrNewObj);
	}else{
		//need to create the map first
		ptrMap = AddHtlMap_NoLock<TObj>();
		if(ptrMap)
		{
			ptrMap->UpdateHtlObject(objGUID, ptrNewObj);
		}else{
			//failed to create new map
			m_objMutex.unlock(m_objKey);
			return 0;
		};
	};
	//successful
	m_objMutex.unlock(m_objKey);
	return 1;
};

//!Unregister an ISA dialog
template<typename TObj>
int HtlObjectRegistrar::UnRegisterHtlObject(const HtlObject * ptrObj)
{
	//first search the map of the template object
	std::string strMapType = HTL_STRINGIZE(TObj);;
	//lock the map
	m_objMutex.lock(m_objKey);

	ObjectMapIterator iterFind;
	iterFind = m_objMetaMap.find(strMapType);
	HtlObjectMap* ptrMap = NULL;
	if(iterFind != m_objMetaMap.end())
	{
		ptrMap = iterFind->second;
	};
	if(ptrMap)
	{
		ptrMap->UnRegisterHtlObject(ptrObj);
	}else{
		//need to create the map first
		ptrMap = AddHtlMap_NoLock<TObj>();
		if(ptrMap)
		{
			ptrMap->UnRegisterHtlObject(ptrObj);
		}else{
			//failed to create new map
			m_objMutex.unlock(m_objKey);
			return 0;
		};
	};
	//successful
	m_objMutex.unlock(m_objKey);
	return 1;
};

template<typename TObj>
int HtlObjectRegistrar::UnRegisterHtlObject(const HtlGUID128 & objGUID)
{
	//first search the map of the template object
	strMapType = HTL_STRINGIZE(TObj);
	//lock the map
	m_objMutex.lock(m_objKey);

	HtlObjectRegistrar::ObjectMapIterator iterFind;
	iterFind = m_objMetaMap.find(strMapType);
	HtlObjectMap* ptrMap = NULL;
	if(iterFind != m_objMetaMap.end())
	{
		ptrMap = iterFind->second;
	};
	if(ptrMap)
	{
		ptrMap->UnRegisterHtlObject(objGUID);
	}else{
		//need to create the map first
		ptrMap = AddHtlMap_NoLock<TObj>();
		if(ptrMap)
		{
			ptrMap->UnRegisterHtlObject(objGUID);
		}else{
			//failed to create new map
			m_objMutex.unlock(m_objKey);
			return 0;
		};
	};
	//successful
	m_objMutex.unlock(m_objKey);
	return 1;
};

#endif