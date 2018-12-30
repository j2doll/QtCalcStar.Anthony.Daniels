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

#include ".\HtlThreadMap.h"
#include ".\HtlSpinLock.h"

namespace HTL
{
		//!Register the thread with the map server
	void HtlThreadMap::Register(HtlThreadID objTid)
	{
		DWORD key = objTid.m_intWinID;
		std::map<DWORD,HtlThreadID>::iterator iter;
		//lock the container before modifying it
		HtlGUID128 objNullID;
		objNullID.newID();
		m_objLock.lock(objNullID);
		//search to see if already there
		iter = m_objTMap.find(key);
		if(iter != m_objTMap.end())
		{
			//then match found. assign the threadId
			iter->second = objTid;
		}else{
			//don't have it, register it
			m_objTMap.insert(std::make_pair(key,objTid));
		};
		m_objLock.unlock(objNullID);
	};
		//!UnRegister the thread with the map server
	void HtlThreadMap::UnRegister(HtlThreadID objTid)
	{
		DWORD key = objTid.m_intWinID;
		std::map<DWORD,HtlThreadID>::iterator iter;
		//lock the container before modifying it
		HtlGUID128 objNullID;
		objNullID.newID();
		m_objLock.lock(objNullID);
		//search to see if already there
		iter = m_objTMap.find(key);
		if(iter != m_objTMap.end())
		{
			//then match found. erase it
			m_objTMap.erase(iter);
		};
		m_objLock.unlock(objNullID);	

	};
	//!Find a thread based on its Windows ID handle
	HtlThreadID HtlThreadMap::FindThread(DWORD intID)
	{		
		HtlThreadID objBlank;
		std::map<DWORD,HtlThreadID>::iterator iter;
		//lock the container before modifying it
		HtlGUID128 objNullID;
		objNullID.newID();
		m_objLock.lock(objNullID);
		//search to see if already there
		iter = m_objTMap.find(intID);
		if(iter != m_objTMap.end())
		{
			//then match found. erase it
			return iter->second;
		};
		m_objLock.unlock(objNullID);
		//didin't find it, return NULL equivalent
		return objBlank;
	};
		//!Find a thread based on the GUID handle
	HtlThreadID HtlThreadMap::FindThread(HtlGUID128 objID)
	{
		HtlThreadID objBlank;
		std::map<DWORD,HtlThreadID>::iterator iter;
		//lock the container before modifying it
		HtlGUID128 objNullID;
		objNullID.newID();
		m_objLock.lock(objNullID);
		//search to see if already there
		
		for(iter = m_objTMap.begin(); iter != m_objTMap.end(); ++iter)
		{
			if(iter->second.m_objGUID == objID)
			{//then match
				return iter->second;
			};
		};
		m_objLock.unlock(objNullID);		
		
		//didn't find it return NULL equivalent
		return objBlank;
	};





};//end namespace HTL