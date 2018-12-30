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
#ifndef HtlMemVar2_H
#define HtlMemVar2_H
#include "..\modHtlGlobal.h"
#include ".\HtlElement.h"
#include ".\HtlMemVarItem.h"

namespace HTL{

	class HtlBase;
	class HtlString;
	class HtlGUID64;
	class HtlGUID128;
	class HtlGUID256;

   template<typename TIndex, HtlObjectType TIndexEnum, typename TObj, HtlObjectType TObjEnum>
	class HtlContainer;
//#########################################################################################################################>
	//MAIN SET MEMBER VARIABLE AND GET MEMBER VARIABLE FUNCTIONS
	//#########################################################################################################################>
	//STRUCT FOR HANDLING DIFFERENT ITEM TYPES///////////////////////////////////////////////////////////////////////
	
	//!HTL Main Set Member Variable Function
	/*!HTL Main Set Member Variable Function.  This in turn creates an appropriate HtlMemVarItem object, 
	which is a template functor object that does the actual serializing of the member variable being handled.  
	Since HtlMemVarItem is a template object, automatically deduces the correct type to use at compile time 
	and handles the serialization of the appropriate type.*/
	HTL_DLLAPI int SetMemVar(HtlElement * ptrCurrNode, const std::string strMemVarName, bool & varVal);
	HTL_DLLAPI int SetMemVar(HtlElement * ptrCurrNode, const std::string strMemVarName, short & varVal);
	HTL_DLLAPI int SetMemVar(HtlElement * ptrCurrNode, const std::string strMemVarName, unsigned short & varVal);
	HTL_DLLAPI int SetMemVar(HtlElement * ptrCurrNode, const std::string strMemVarName, int & varVal);
	HTL_DLLAPI int SetMemVar(HtlElement * ptrCurrNode, const std::string strMemVarName, unsigned int & varVal);
	HTL_DLLAPI int SetMemVar(HtlElement * ptrCurrNode, const std::string strMemVarName, long & varVal);
	HTL_DLLAPI int SetMemVar(HtlElement * ptrCurrNode, const std::string strMemVarName, unsigned long & varVal);
	HTL_DLLAPI int SetMemVar(HtlElement * ptrCurrNode, const std::string strMemVarName, float & varVal);
	HTL_DLLAPI int SetMemVar(HtlElement * ptrCurrNode, const std::string strMemVarName, double & varVal);
	HTL_DLLAPI int SetMemVar(HtlElement * ptrCurrNode, const std::string strMemVarName, std::string & varVal);
	HTL_DLLAPI int SetMemVar(HtlElement * ptrCurrNode, const std::string strMemVarName, HtlGUID64 * ptrGuid);
	HTL_DLLAPI int SetMemVar(HtlElement * ptrCurrNode, const std::string strMemVarName, HtlGUID128 * ptrGuid);
	HTL_DLLAPI int SetMemVar(HtlElement * ptrCurrNode, const std::string strMemVarName, HtlGUID256 * ptrGuid);
	HTL_DLLAPI int SetMemVar(HtlElement * ptrCurrNode, const std::string strMemVarName, HtlString * ptrStr);
	HTL_DLLAPI int SetMemVar(HtlElement * ptrCurrNode, const std::string strMemVarName, HtlBase * ptrObj, bool blnSubObjects);

	//!HTL Main Get Member Variable Function
	/*!HTL Main Get Member Variable Function.  This in turn creates an appropriate HtlMemVarItem object, 
	which is a template functor object that does the actual de-serializing of the member variable being handled.  
	Since HtlMemVarItem is a template object, automatically deduces the correct type to use at compile time 
	and handles the de-serialization of the appropriate type.*/

	HTL_DLLAPI int GetMemVar(HtlElement * ptrCurrNode, const std::string strMemVarName, bool & varVal);
	HTL_DLLAPI int GetMemVar(HtlElement * ptrCurrNode, const std::string strMemVarName, short & varVal);
	HTL_DLLAPI int GetMemVar(HtlElement * ptrCurrNode, const std::string strMemVarName, unsigned short & varVal);
	HTL_DLLAPI int GetMemVar(HtlElement * ptrCurrNode, const std::string strMemVarName, int & varVal);
	HTL_DLLAPI int GetMemVar(HtlElement * ptrCurrNode, const std::string strMemVarName, unsigned int & varVal);
	HTL_DLLAPI int GetMemVar(HtlElement * ptrCurrNode, const std::string strMemVarName, long & varVal);
	HTL_DLLAPI int GetMemVar(HtlElement * ptrCurrNode, const std::string strMemVarName, unsigned long & varVal);
	HTL_DLLAPI int GetMemVar(HtlElement * ptrCurrNode, const std::string strMemVarName, float & varVal);
	HTL_DLLAPI int GetMemVar(HtlElement * ptrCurrNode, const std::string strMemVarName, double & varVal);
	HTL_DLLAPI int GetMemVar(HtlElement * ptrCurrNode, const std::string strMemVarName, std::string & varVal);
	HTL_DLLAPI int GetMemVar(HtlElement * ptrCurrNode, const std::string strMemVarName, HtlGUID64 * ptrGuid);
	HTL_DLLAPI int GetMemVar(HtlElement * ptrCurrNode, const std::string strMemVarName, HtlGUID128 * ptrGuid);
	HTL_DLLAPI int GetMemVar(HtlElement * ptrCurrNode, const std::string strMemVarName, HtlGUID256 * ptrGuid);
	HTL_DLLAPI int GetMemVar(HtlElement * ptrCurrNode, const std::string strMemVarName, HtlString * ptrStr);
	HTL_DLLAPI int GetMemVar(HtlElement * ptrCurrNode, const std::string strMemVarName, HtlBase * ptrObj);

};//end namespace 
#endif