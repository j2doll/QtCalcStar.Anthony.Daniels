/*
**	This file is part of the Hpc Template Library (HTL or Htl).
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
#pragma warning(push)
#pragma warning (disable : 4005 ) /* macro redefinition */
#define HTL_DLLEXPORT
#pragma warning(pop)

#include ".\GtSheetServer.h"
#include ".\GtCellData.h"
#include ".\QTSpreadSheet.h"
#include <modHtlBase.h>


namespace GT
{
	namespace GtCalc
	{
		//!Generic Public Constructor 
		GtSheetServer::GtSheetServer(void)
		{
			std::string strFile = "GtSheetServer.txt";
			m_objPrint.Set_blnPrintToFile(true);
			m_objPrint.Set_blnPrintToStream(false);
			m_objPrint.Set_blnPrintToTextEdit(false);
			m_objPrint.Set_strFileName(strFile);
			//comment out next line to enable debug dumping to file
			//m_objPrint.Disable();

			m_objKey.newID();
			return;
		};

		//!Default Destructor Method
		GtSheetServer::~GtSheetServer(void)
		{
			ClearRegistry();
			return;
		};

		//!Get the pointer to the QTSpreadSheet
		QTSpreadSheet * GtSheetServer::GetSheetPtr(HtlGUID128 & objGUID)
		{
			m_objPrint.DebugPrint(1, "GtSheetServer::GetQTSpreadSheetPtr\n");
         QTSpreadSheet * ptrObj = NULL;
			HtlTreeNode<HtlGUID128, QTSpreadSheet*> * ptrIter;
			std::string strSearchGUID = objGUID.toStdString();
			if (m_objSheetMap.size() <= 0) { return NULL; };
			//safe to proceed
			m_objPrint.DebugPrint(1, "Searching GUID: %s\n", strSearchGUID.c_str());
			ptrIter = m_objSheetMap.find(objGUID);
			if (ptrIter != NULL)
			{
				ptrObj = (*ptrIter).value();
				m_objPrint.DebugPrint(1, "Iterator Found: %p\n", ptrObj);
				if (ptrObj)
				{
					std::string strFoundGUID = ptrObj->Get_objGUID().toStdString();
					m_objPrint.DebugPrint(1, "Found GUID: %s\n", strFoundGUID.c_str());
				}
			}
			return ptrObj;
		};


		//!Get the pointer to the QTSpreadSheet
		QTSpreadSheet * GtSheetServer::GetSheetPtr(string & strName)
		{
			QTSpreadSheet * ptrSheet = NULL;

			int iNumSheets = m_objSheetMap.size();
			if (iNumSheets <= 0) { return false; };
			//safe to proceed
			for (int i = 0; i < iNumSheets; i++)
			{
				ptrSheet = m_objSheetMap.at(i);
				string strTemp;
				strTemp = ptrSheet->Get_strName();
				if (strTemp == strName)
				{
					return ptrSheet;
				}

			};

			//no match found
			return NULL;
		};
		//!Get a ISA Dialog by its GUID
		bool GtSheetServer::DoesSheetExist(HtlGUID128 & objGUID)
		{
			QTSpreadSheet * ptrObj = NULL;
			HtlTreeNode<HtlGUID128, QTSpreadSheet*> * ptrIter;

			if (m_objSheetMap.size() <= 0) { return false; };
			//safe to proceed
			ptrIter = m_objSheetMap.find(objGUID);
			if (ptrIter != NULL)
			{
				ptrObj = (*ptrIter).value();
			}
			else {
				return false;
			};
			if (ptrObj)
			{
				return true;
			}
			else {
				return false;
			};

		};
		
		//!Get a ISA Dialog by its GUID
		bool GtSheetServer::DoesSheetExist(string & strName)
		{
			QTSpreadSheet * ptrSheet = NULL;

			int iNumSheets = m_objSheetMap.size();
			if (iNumSheets <= 0) { return false; };
			//safe to proceed
			for (int i = 0; i < iNumSheets; i++)
			{
				ptrSheet = m_objSheetMap.at(i);
				string strTemp;
				strTemp = ptrSheet->Get_strName();
				if (strTemp == strName)
				{
					return true;
				}

			};
			
			//no match found
			return false;
		};
		//!Register an ISA dialog to the server
		int GtSheetServer::RegisterSheet(QTSpreadSheet * ptrObj)
		{
			std::string strGUID;
			//safety check
			if (!ptrObj) { return 0; };
			//lock the map
			m_objMutex.lock(m_objKey);
			m_objPrint.DebugPrint(1, "\nGtSheetServer::RegisterQTSpreadSheet1\n");
			m_objPrint.DebugPrint(1, "placing %s\n", ptrObj->Get_strType().c_str());
			HtlTreeNode<HtlGUID128, QTSpreadSheet*> * ptrIter;

			strGUID = ptrObj->Get_objGUID().toStdString();
			m_objPrint.DebugPrint(1, "Search GUID: %s\n", strGUID.c_str());
			ptrIter = m_objSheetMap.find(ptrObj->Get_objGUID());
			if (ptrIter == NULL)
			{	//then not inserted
				strGUID = ptrObj->Get_objGUID().toStdString();
				m_objPrint.DebugPrint(1, "New GUID: %s\n", strGUID.c_str());
				//then not found, insert it
				m_objSheetMap.insert(ptrObj->Get_objGUID(), ptrObj);
			}
			else {
				strGUID = ptrIter->key().toStdString();
				m_objPrint.DebugPrint(1, "Found GUID: %s\n", strGUID.c_str());
				//match found, new pointer, update the pointer
				strGUID = ptrObj->Get_objGUID().toStdString();
				m_objPrint.DebugPrint(1, "New GUID: %s\n", strGUID.c_str());
				ptrIter->setValue(ptrObj);

			};
			//unlock the map
			m_objMutex.unlock(m_objKey);

			return 1;
		};

		//!Unregister an ISA dialog
		int GtSheetServer::UnRegisterSheet(QTSpreadSheet * ptrObj)
		{
			HtlGUID128 objKeyToDel;
			//lock the map
			m_objMutex.lock(m_objKey);
			//safety check
			if (!ptrObj)
			{
				//release the lock
				m_objMutex.unlock(m_objKey);
				return 0;
			};
			//search for the object in the registry
			if (m_objSheetMap.size() > 0)
			{
				objKeyToDel = ptrObj->Get_objGUID();
				m_objSheetMap.erase(objKeyToDel);
			};

			//release the lock
			m_objMutex.unlock(m_objKey);
			return 1;
		};
		//!Clear the registry
		void GtSheetServer::ClearRegistry(void)
		{
			m_objSheetMap.clear();
		};

		GtSheetServer* GtSheetServer::GetServerPtr(void)
		{
			static GtSheetServer g_objServer;
			return &g_objServer;
		};

	};//end namespace GtCalc
}//end namespace GT