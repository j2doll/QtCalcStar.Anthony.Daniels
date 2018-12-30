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
#ifndef GTCALC_SHEET_SERVER_H
#define GTCALC_SHEET_SERVER_H
#include <modHtlGlobal.h>
#include <modHtlGUID.h>
#include <HtlThread\HtlSpinLock.h>
#include <HtlContainer\HtlListMap.h>
#include <map>
#include <vector>
#include <string>

using namespace HTL;


namespace GT
{

	namespace GtCalc
	{

		//forward declaration
		class HtlObject;
		class QTSpreadSheet;

		class HTL_DLLAPI GtSheetServer
		{
		public:
			//!Generic Public Constructor 
			GtSheetServer(void);
			//!Default Destructor Method
			virtual ~GtSheetServer(void);

			static GtSheetServer* GetServerPtr(void);
			//!Get the pointer to the HtlObject
			QTSpreadSheet*  GetSheetPtr(HtlGUID128 & objGUID);
         QTSpreadSheet * GetSheetPtr(string & strName);
			//!Get a ISA Dialog by its GUID
			bool DoesSheetExist(HtlGUID128 & objGUID);
			bool DoesSheetExist(string & strName);
			//!Register an HtlObject to the server
			int RegisterSheet(QTSpreadSheet * ptrObj);
			//!Unregister an HtlObject from the server
			int UnRegisterSheet(QTSpreadSheet * ptrObj);
			//!Clear the registry
			void ClearRegistry(void);

		protected:

			HtlListMap<HtlGUID128, HTL_GUID128, QTSpreadSheet*, HTL_OBJECT_PTR> m_objSheetMap;

			HtlSpinLock m_objMutex;
		private:
			HtlGUID128 m_objKey;

			HtlDebugPrinter m_objPrint;
		};

		

	};//end namespace GtCalc
}//end namespace GT
#endif//Htl_OBJECTMAP_H
