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
#ifndef HTL_OBJECTREGISTRAR_H
#define HTL_OBJECTREGISTRAR_H
#include ".\HtlObjectMap.h"

namespace HTL{

	class HtlObject;

	class HTL_DLLAPI HtlObjectRegistrar 
	{
	public:
		//!Generic Public Constructor 
		HtlObjectRegistrar(void);

		//!Default Destructor Method
		virtual ~HtlObjectRegistrar(void);
		//!Get the pointer to the HtlObject this DOES A FULL MAP SEARCH of all of the different classes
		HtlObject * GetHtlObjectPtr(HtlGUID128 & objGUID);

		//!Get the pointer to the HtlObject, this searches only a specific object map type
		template<typename TObj>
		HtlObject * GetHtlObjectPtr(HtlGUID128 & objGUID);
		//!Get a HtlObject by its GUID
		bool DoesHtlObjectExist( HtlGUID128 & objGUID);

		//map container accessors
		template <typename TObj>
		HtlObjectMap*  AddHtlMap(void);

		template <typename TObj>
		void DeleteHtlMap(void);

		template <typename TObj>
		HtlObjectMap* GetHtlMapPtr(void);



		//!Register an ISA dialog to the server
		template<typename TObj>
		int RegisterHtlObject(HtlObject * ptrObj);
		
		template<typename TObj>
		int RegisterHtlObject(HtlObject * ptrObj, HtlGUID128 & objGUID);

		template<typename TObj>
		int UpdateHtlObject(HtlObject * ptrObj, HtlGUID128 & objNewGUID);

		template<typename TObj>
		int UpdateHtlObject(HtlGUID128 & objGUID, HtlObject * ptrNewObj);

		//!Unregister an ISA dialog
		template<typename TObj>
		int UnRegisterHtlObject(const HtlObject * ptrObj);

		template<typename TObj>
		int UnRegisterHtlObject(const HtlGUID128 & objGUID);

		//!Clear the registry
		void ClearRegistry(void);

	protected:
		//object meta map
		std::map<string, HtlObjectMap*> m_objMetaMap;

		HtlSpinLock m_objMutex;

	private:

		HtlGUID128 m_objKey;
		//map container accessors
		template <typename TObj>
		HtlObjectMap*  AddHtlMap_NoLock(void);

		template <typename TObj>
		void DeleteHtlMap_NoLock(void);
		
	};//enD class definition

};//end namespace Htl

#endif//HtlOBJECTREGISTRAR_H
