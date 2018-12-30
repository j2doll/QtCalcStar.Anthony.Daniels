/*
**	This file is part of the Hpc Template Library (Htl or Htl).
**  It is based on a merger of QT, STL, and SigSlots along with development of new classes.
**  License information is in the HtlLicense.h file
**	This software was merged and developed by:
**	
**  Anthony Daniels
**	QT, STL, SigSlots
**
**  Htl is free software: you can redistribute it and/or modify
**  it under the terms of the GNU Lesser General Public License as published by
**  the Free Software Foundation, either version 3 of the License, or
**  (at your option) any later version.
**
**  The United States of America Department of Defense has unlimited 
**	usage, redistribution, and modification rights to HtlStar.
**
**  Htl is distributed in the hope that it will be useful,
**  but WITHOUT ANY WARRANTY; without even the implied warranty of
**  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
**  GNU Lesser General Public License for more details.
**
**  You should have received a copy of the GNU Lesser General Public License
**  along with Htl.  If not, see <http://www.gnu.org/licenses/>.
*/

#pragma once
#ifndef HTL_OBJECTMAP_H
#define HTL_OBJECTMAP_H

#include "..\modHtlGUID.h"
#include "..\HtlThread\HtlSpinLock.h"
#include "..\HtlContainer\HtlListMap.h"
#include <map>
#include <vector>
#include <string>

namespace HTL{

	//forward declaration
	class HtlObject;
	class HtlSpinLock;

	class HTL_DLLAPI HtlObjectMap
	{
	public:
		//!Generic Public Constructor 
		HtlObjectMap(void);

		//!Default Destructor Method
		virtual ~HtlObjectMap(void);
		//!Get the pointer to the HtlObject
		HtlObject * GetHtlObjectPtr(HtlGUID128 & objGUID);
		//!Get a ISA Dialog by its GUID
		bool DoesHtlObjectExist(HtlGUID128 & objGUID);

		//!Register an HtlObject to the server
		int RegisterHtlObject(HtlObject * ptrObj);
		int RegisterHtlObject(HtlObject * ptrObj, HtlGUID128 & objGUID);

		//!Update either the GUID or the Pointer
		int UpdateHtlObject(HtlObject * ptrObj, HtlGUID128 & objNewGUID);
		int UpdateHtlObject(HtlGUID128 & objGUID, HtlObject * ptrNewObj);

		//!Unregister an HtlObject from the server
		int UnRegisterHtlObject(HtlObject * ptrObj);
		int UnRegisterHtlObject(HtlGUID128 & objGUID);

		//!Clear the registry
		void ClearRegistry(void);

	protected:
		//modMap<HtlGUID128, HtlObject*> m_objHtlObjectMap;
		HtlListMap<HtlGUID128,HTL_GUID128, HtlObject*,HTL_OBJECT_PTR> m_objHtlObjectMap;

		HtlSpinLock m_objMutex;
	private:
		HtlGUID128 m_objKey;

		HtlDebugPrinter m_objPrint;
	};

};//end namespace Htl

#endif//Htl_OBJECTMAP_H
