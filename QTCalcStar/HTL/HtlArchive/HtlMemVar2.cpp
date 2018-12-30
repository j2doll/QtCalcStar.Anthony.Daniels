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

#include ".\HtlMemVar2.h"
#include "..\modHtlBase.h"
#include "..\modHtlGUID.h"
#include "..\modHtlContainer.h"
using namespace HTL;

namespace HTL
{

	//SET MEMBER VARIABLES//////////////////////////////////////////////////
	int SetMemVar(HtlElement * ptrCurrNode, const std::string strMemVarName, bool & varVal)
	{
		//safety check on pointer
		if(!ptrCurrNode){return 0;};
		HtlMemVarItem<bool,CPP_BOOL> objItem;
		return objItem.Set(ptrCurrNode, strMemVarName, varVal, false);
	};
	int SetMemVar(HtlElement * ptrCurrNode, const std::string strMemVarName, short & varVal)
	{
		//safety check on pointer
		if(!ptrCurrNode){return 0;};
		HtlMemVarItem<short,CPP_SHORT> objItem;
		return objItem.Set(ptrCurrNode, strMemVarName, varVal, false);
	};
	int SetMemVar(HtlElement * ptrCurrNode, const std::string strMemVarName, unsigned short & varVal)
	{
		//safety check on pointer
		if(!ptrCurrNode){return 0;};
		HtlMemVarItem<unsigned short,CPP_USHORT> objItem;
		return objItem.Set(ptrCurrNode, strMemVarName, varVal, false);
	};
	int SetMemVar(HtlElement * ptrCurrNode, const std::string strMemVarName, int & varVal)
	{
		//safety check on pointer
		if(!ptrCurrNode){return 0;};
		HtlMemVarItem<int,CPP_INT> objItem;
		return objItem.Set(ptrCurrNode, strMemVarName, varVal, false);
	};
	int SetMemVar(HtlElement * ptrCurrNode, const std::string strMemVarName, unsigned int & varVal)
	{
		//safety check on pointer
		if(!ptrCurrNode){return 0;};
		HtlMemVarItem<unsigned int,CPP_UINT> objItem;
		return objItem.Set(ptrCurrNode, strMemVarName, varVal, false);
	};
	int SetMemVar(HtlElement * ptrCurrNode, const std::string strMemVarName, long & varVal)
	{
		//safety check on pointer
		if(!ptrCurrNode){return 0;};
		HtlMemVarItem<long,CPP_LONG> objItem;
		return objItem.Set(ptrCurrNode, strMemVarName, varVal, false);
	};
	int SetMemVar(HtlElement * ptrCurrNode, const std::string strMemVarName, unsigned long & varVal)
	{
		//safety check on pointer
		if(!ptrCurrNode){return 0;};
		HtlMemVarItem<unsigned long,CPP_ULONG> objItem;
		return objItem.Set(ptrCurrNode, strMemVarName, varVal, false);
	};
	int SetMemVar(HtlElement * ptrCurrNode, const std::string strMemVarName, float & varVal)
	{
		//safety check on pointer
		if(!ptrCurrNode){return 0;};
		HtlMemVarItem<float,CPP_FLOAT> objItem;
		return objItem.Set(ptrCurrNode, strMemVarName, varVal, false);
	};
	int SetMemVar(HtlElement * ptrCurrNode, const std::string strMemVarName, double & varVal)
	{
		//safety check on pointer
		if(!ptrCurrNode){return 0;};
		HtlMemVarItem<double,CPP_DOUBLE> objItem;
		return objItem.Set(ptrCurrNode, strMemVarName, varVal, false);
	};
	int SetMemVar(HtlElement * ptrCurrNode, const std::string strMemVarName, std::string & varVal)
	{
		//safety check on pointer
		if(!ptrCurrNode){return 0;};
		HtlMemVarItem<std::string,STL_STRING> objItem;
		return objItem.Set(ptrCurrNode, strMemVarName, varVal, false);

	};
	int SetMemVar(HtlElement * ptrCurrNode, const std::string strMemVarName, HtlGUID64 * ptrGuid)
	{
		//safety check on pointer
		if(!ptrCurrNode){return 0;};
		HtlMemVarItem<HtlGUID64,HTL_GUID64> objItem;
		return objItem.Set(ptrCurrNode, strMemVarName, *ptrGuid, false);
	};
	int SetMemVar(HtlElement * ptrCurrNode, const std::string strMemVarName, HtlGUID128 * ptrGuid)
	{
		//safety check on pointer
		if(!ptrCurrNode){return 0;};
		HtlMemVarItem<HtlGUID128,HTL_GUID128> objItem;
		return objItem.Set(ptrCurrNode, strMemVarName, *ptrGuid, false);
	};
	int SetMemVar(HtlElement * ptrCurrNode, const std::string strMemVarName, HtlGUID256 * ptrGuid)
	{
		//safety check on pointer
		if(!ptrCurrNode){return 0;};
		HtlMemVarItem<HtlGUID256,HTL_GUID256> objItem;
		return objItem.Set(ptrCurrNode, strMemVarName, *ptrGuid, false);
	};
	int SetMemVar(HtlElement * ptrCurrNode, const std::string strMemVarName, HtlString * ptrStr)
	{
		//safety check on pointer
		if(!ptrCurrNode){return 0;};
		HtlMemVarItem<HtlString,HTL_STRING> objItem;
		return objItem.Set(ptrCurrNode, strMemVarName, *ptrStr, false);

	};
	int SetMemVar(HtlElement * ptrCurrNode, const std::string strMemVarName, HtlBase * ptrObj, bool blnSubObjects)
	{
		//safety check on pointer
		if(!ptrCurrNode){return 0;};
		HtlMemVarItem<HtlBase* ,HTL_BASE_PTR> objItem;
		return objItem.Set(ptrCurrNode, strMemVarName, ptrObj, blnSubObjects);
	};


	//GET MEMBER VARIABLES//////////////////////////////////////////////////
	int GetMemVar(HtlElement * ptrCurrNode, const std::string strMemVarName, bool & varVal)
	{
		//safety check on pointer
		if(!ptrCurrNode){return 0;};
		HtlMemVarItem<bool,CPP_BOOL> objItem;
		return objItem.Get(ptrCurrNode, strMemVarName, varVal);
	};
	int GetMemVar(HtlElement * ptrCurrNode, const std::string strMemVarName, short & varVal)
	{
		//safety check on pointer
		if(!ptrCurrNode){return 0;};
		HtlMemVarItem<short,CPP_SHORT> objItem;
		return objItem.Get(ptrCurrNode, strMemVarName, varVal);
	};
	int GetMemVar(HtlElement * ptrCurrNode, const std::string strMemVarName, unsigned short & varVal)
	{
		//safety check on pointer
		if(!ptrCurrNode){return 0;};
		HtlMemVarItem<unsigned short,CPP_USHORT> objItem;
		return objItem.Get(ptrCurrNode, strMemVarName, varVal);
	};
	int GetMemVar(HtlElement * ptrCurrNode, const std::string strMemVarName, int & varVal)
	{
		//safety check on pointer
		if(!ptrCurrNode){return 0;};
		HtlMemVarItem<int,CPP_INT> objItem;
		return objItem.Get(ptrCurrNode, strMemVarName, varVal);
	};
	int GetMemVar(HtlElement * ptrCurrNode, const std::string strMemVarName, unsigned int & varVal)
	{
		//safety check on pointer
		if(!ptrCurrNode){return 0;};
		HtlMemVarItem<unsigned int,CPP_UINT> objItem;
		return objItem.Get(ptrCurrNode, strMemVarName, varVal);
	};
	int GetMemVar(HtlElement * ptrCurrNode, const std::string strMemVarName, long & varVal)
	{
		//safety check on pointer
		if(!ptrCurrNode){return 0;};
		HtlMemVarItem<long,CPP_LONG> objItem;
		return objItem.Get(ptrCurrNode, strMemVarName, varVal);
	};
	int GetMemVar(HtlElement * ptrCurrNode, const std::string strMemVarName, unsigned long & varVal)
	{
		//safety check on pointer
		if(!ptrCurrNode){return 0;};
		HtlMemVarItem<unsigned long,CPP_ULONG> objItem;
		return objItem.Get(ptrCurrNode, strMemVarName, varVal);
	};
	int GetMemVar(HtlElement * ptrCurrNode, const std::string strMemVarName, float & varVal)
	{
		//safety check on pointer
		if(!ptrCurrNode){return 0;};
		HtlMemVarItem<float,CPP_FLOAT> objItem;
		return objItem.Get(ptrCurrNode, strMemVarName, varVal);
	};
	int GetMemVar(HtlElement * ptrCurrNode, const std::string strMemVarName, double & varVal)
	{
		//safety check on pointer
		if(!ptrCurrNode){return 0;};
		HtlMemVarItem<double,CPP_DOUBLE> objItem;
		return objItem.Get(ptrCurrNode, strMemVarName, varVal);
	};
	int GetMemVar(HtlElement * ptrCurrNode, const std::string strMemVarName, std::string & varVal)
	{
		//safety check on pointer
		if(!ptrCurrNode){return 0;};
		HtlMemVarItem<std::string,STL_STRING> objItem;
		return objItem.Get(ptrCurrNode, strMemVarName, varVal);

	};
	int GetMemVar(HtlElement * ptrCurrNode, const std::string strMemVarName, HtlGUID64 * ptrGuid)
	{
		//safety check on pointer
		if(!ptrCurrNode){return 0;};
		HtlMemVarItem<HtlGUID64,HTL_GUID64> objItem;
		return objItem.Get(ptrCurrNode, strMemVarName, *ptrGuid);
	};
	int GetMemVar(HtlElement * ptrCurrNode, const std::string strMemVarName, HtlGUID128 * ptrGuid)
	{
		//safety check on pointer
		if(!ptrCurrNode){return 0;};
		HtlMemVarItem<HtlGUID128,HTL_GUID128> objItem;
		return objItem.Get(ptrCurrNode, strMemVarName, *ptrGuid);
	};
	int GetMemVar(HtlElement * ptrCurrNode, const std::string strMemVarName, HtlGUID256 * ptrGuid)
	{
		//safety check on pointer
		if(!ptrCurrNode){return 0;};
		HtlMemVarItem<HtlGUID256,HTL_GUID256> objItem;
		return objItem.Get(ptrCurrNode, strMemVarName, *ptrGuid);
	};
	int GetMemVar(HtlElement * ptrCurrNode, const std::string strMemVarName, HtlString * ptrStr)
	{
		//safety check on pointer
		if(!ptrCurrNode){return 0;};
		HtlMemVarItem<HtlString,HTL_STRING> objItem;
		return objItem.Get(ptrCurrNode, strMemVarName, *ptrStr);

	};
	int GetMemVar(HtlElement * ptrCurrNode, const std::string strMemVarName, HtlBase * ptrObj)
	{
		//safety check on pointer
		if(!ptrCurrNode){return 0;};
		HtlMemVarItem<HtlBase* ,HTL_BASE_PTR> objItem;
		return objItem.Get(ptrCurrNode, strMemVarName, ptrObj);
	};









};