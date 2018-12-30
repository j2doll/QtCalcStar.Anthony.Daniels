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
#ifndef HtlMemVarItem_H
#define HtlMemVarItem_H
#include <string>
#include ".\HtlElement.h"

#include "..\modHtlGUID.h"
//#include "..\modHtlContainer.h"

namespace HTL{
	//Htl Attribute tags
#define HTL_strTYPE "T"
#define HTL_strBASETYPE "BT"
#define HTL_strSUBOBJTYPE "ST"
#define HTL_strSUBOBJBASETYPE "SBT"
#define HTL_strINTNUMDIM "N"
#define HTL_strITEM "IT_"



	//!Get Existing Element or Make an Element if it does not already exist
	HTL_DLLAPI HtlElement* GetOrMakeElement(HtlElement * ptrCurrNode,const std::string & strMemVarName);

	//!Set Attribute Type Information based on the XDL Standard for an element.
	HTL_DLLAPI int SetAttribTypeInfo(HtlElement * ptrCurrNode,std::string & strType, std::string & strBaseType);
	//!Set Attribute Type Information based on the XDL Standard for an element.
	HTL_DLLAPI int SetAttribTypeInfo(HtlElement * ptrCurrNode,std::string & strType, std::string & strBaseType,std::string & strSubObjType, std::string & strSubObjBaseType,std::string & strIntNumDim);
	//!Set Attribute Sub Element Type Information based on the XDL Standard for an element.
	HTL_DLLAPI int SetAttribSubTypeInfo(HtlElement * ptrCurrNode,std::string & strSubObjType, std::string & strSubObjBaseType,std::string & strIntNumDim);

	//!Set the Object Type Attribute
	HTL_DLLAPI int SetAttribType(HtlElement * ptrCurrNode,std::string & strType);
	//!Set the Object's HtlObjectType Enumerated Attribute
	HTL_DLLAPI int SetAttribBaseType(HtlElement * ptrCurrNode,std::string & strBaseType);

	//!Set the Sub-Object Type Attribute
	HTL_DLLAPI int SetAttribSubType(HtlElement * ptrCurrNode,std::string & strSubObjType);
	//!Set the Sub-Object's HtlObjectType Enumerated Attribute
	HTL_DLLAPI int SetAttribSubBaseType(HtlElement * ptrCurrNode,std::string & strSubObjBaseType);
	//!Set the Integer Number of Dimensions for the container
	HTL_DLLAPI int SetAttribIntNumDim(HtlElement * ptrCurrNode,std::string & strIntNumDim);



	//!Template function for setting default values for nodes
	template<class TObj>
	HTL_EXPORT int SetDefaultVal(TObj & objItem){ return 0;};
	//!Template function for setting default values for nodes
	template<>
	HTL_EXPORT int HTL::SetDefaultVal<bool>(bool & objItem);
	//!Template function for setting default values for nodes
	template<>
	HTL_EXPORT int HTL::SetDefaultVal<char>(char & objItem);
	//!Template function for setting default values for nodes
	template<>
	HTL_EXPORT int HTL::SetDefaultVal<unsigned char>(unsigned char & objItem);
	//!Template function for setting default values for nodes
	template<>
	HTL_EXPORT int HTL::SetDefaultVal<short>(short & objItem);
	//!Template function for setting default values for nodes
	template<>
	HTL_EXPORT int HTL::SetDefaultVal<unsigned short>(unsigned short & objItem);
	//!Template function for setting default values for nodes
	template<>
	HTL_EXPORT int HTL::SetDefaultVal<int>(int & objItem);
	//!Template function for setting default values for nodes
	template<>
	HTL_EXPORT int HTL::SetDefaultVal<unsigned int>(unsigned int & objItem);
	//!Template function for setting default values for nodes
	template<>
	HTL_EXPORT int HTL::SetDefaultVal<long>(long & objItem);
	//!Template function for setting default values for nodes
	template<>
	HTL_EXPORT int HTL::SetDefaultVal<unsigned long>(unsigned long & objItem);
	//!Template function for setting default values for nodes
	template<>
	HTL_EXPORT int HTL::SetDefaultVal<float>(float & objItem);
	//!Template function for setting default values for nodes
	template<>
	HTL_EXPORT int HTL::SetDefaultVal<double>(double & objItem);

	//STRUCT FOR HANDLING DIFFERENT ITEM TYPES///////////////////////////////////////////////////////////////////////
	//!This object is the template functor for serializing and deserializing any object type in HTL.
	/*!This object is the template functor for serializing and deserializing any object type in HTL.
	The two template arguments are the Object type (class) and its equivalent HtlObjectType enumerated
	type (e.g. CPP_DOUBLE or HTL_BASE).  Because it is a template functor all type resolutions are handled at
	compile time so the proper data handling is ensured.
	*/
	template<class TObj, HtlObjectType TBase>
	struct HtlMemVarItem
	{
	public:
		//!Set the Member Variable of the name strMemVarName to the ptrCurrNode.
		int Set(HtlElement * ptrCurrNode, const std::string & strMemVarName, TObj & varVal, bool blnWithSubObjects)
		{
			//unknown object type
			return 0;
		};
		//!Get the Member Variable of the name strMemVarName from the ptrCurrNode.
		int Get(HtlElement * ptrCurrNode, const std::string & strMemVarName, TObj & varVal)
		{
			//unknown object type
			return 0;
		};
	};

	//STRUCT FOR HANDLING CPP NATIVE TYPES///////////////////////////////////////////////////////////////////////
	//CPP_BOOL = 0,
	//CPP_CHAR = 1,
	//CPP_UCHAR = 2,
	//CPP_SHORT = 3,
	//CPP_USHORT = 4,
	//CPP_INT = 5,
	//CPP_UINT = 6, 
	//CPP_LONG = 7,
	//CPP_ULONG = 8,
	//CPP_FLOAT = 9,
	//CPP_DOUBLE = 10,

	//CPP_BOOL###############################>>
	template<>
	struct HtlMemVarItem<bool,CPP_BOOL>
	{
	public:
		int Set(HtlElement * ptrCurrNode, const std::string & strMemVarName, bool & varVal, bool blnWithSubObjects)
		{
			try{
				HtlElement* ptrMemVarNode = GetOrMakeElement(ptrCurrNode,strMemVarName);
				if(ptrMemVarNode)
				{//add the attributes and set the value
					std::string strT, strBT;
					strT = "bool"; strBT = "CPP_BOOL";
					SetAttribTypeInfo(ptrMemVarNode,strT,strBT);
					ptrMemVarNode->Set_strValue(varVal);
				};
			}catch(...){
				
            std::string errMsg;
            errMsg = "HtlMemVarItem Set CPP_BOOL Error thrown";
            throw std::exception(errMsg.c_str());
            return -1;
			};
			return 1;
		};//end Set
		int Get(HtlElement * ptrCurrNode, const std::string & strMemVarName, bool & varVal)
		{
		//return ORSDB::GetXMLNative<string>(ptrCurrNode,strMemVarName, varVal);
			//Now that we have the member variable value, write the element
			try{
				if(!ptrCurrNode){return 0;};
				HtlElement * ptrMemVarNode = NULL;
				ptrMemVarNode = ptrCurrNode->GetSubElement(strMemVarName);
				if(ptrMemVarNode)
				{
					ptrMemVarNode->Get_strValue(varVal);
					return 1;
				}else{
					return 0;
				};
				return 1;
			}catch(...){
            std::string errMsg;
            errMsg = "HtlMemVarItem Get CPP_BOOL Error thrown";
            throw std::exception(errMsg.c_str());
            return -1;
			};
		};//end Get
	};//end GetMemVarItem
	
	//CPP_CHAR###############################>>
	template<>
	struct HtlMemVarItem<char,CPP_CHAR>
	{
	public:
		int Set(HtlElement * ptrCurrNode, const std::string & strMemVarName, char & varVal, bool blnWithSubObjects)
		{
			try{
				HtlElement* ptrMemVarNode = GetOrMakeElement(ptrCurrNode,strMemVarName);
				if(ptrMemVarNode)
				{//add the attributes and set the value
					std::string strT, strBT;
					strT = "char"; strBT = "CPP_CHAR";
					SetAttribTypeInfo(ptrMemVarNode,strT,strBT);
					ptrMemVarNode->Set_strValue(varVal);
				};
			}catch(...){
            std::string errMsg;
            errMsg = "HtlMemVarItem Set CPP_CHAR Error thrown";
            throw std::exception(errMsg.c_str());
            return -1;
			};
			return 1;
		};//end Set
		int Get(HtlElement * ptrCurrNode, const std::string & strMemVarName, char & varVal)
		{
		//return ORSDB::GetXMLNative<string>(ptrCurrNode,strMemVarName, varVal);
			//Now that we have the member variable value, write the element
			try{
				if(!ptrCurrNode){return 0;};
				HtlElement * ptrMemVarNode = NULL;
				ptrMemVarNode = ptrCurrNode->GetSubElement(strMemVarName);
				if(ptrMemVarNode)
				{
					ptrMemVarNode->Get_strValue(varVal);
					return 1;
				}else{
					return 0;
				};
				return 1;
			}catch(...){
            std::string errMsg;
            errMsg = "HtlMemVarItem Get CPP_CHAR Error thrown";
            throw std::exception(errMsg.c_str());
            return -1;
			};
		};//end Get
	};//end GetMemVarItem

	//CPP_Uchar###############################>>
	template<>
	struct HtlMemVarItem<unsigned char,CPP_UCHAR>
	{
	public:
		int Set(HtlElement * ptrCurrNode, const std::string & strMemVarName,unsigned char & varVal, bool blnWithSubObjects)
		{
			try{
				HtlElement* ptrMemVarNode = GetOrMakeElement(ptrCurrNode,strMemVarName);
				if(ptrMemVarNode)
				{//add the attributes and set the value
					std::string strT, strBT;
					strT = "uchar"; strBT = "CPP_UCHAR";
					SetAttribTypeInfo(ptrMemVarNode,strT,strBT);
					ptrMemVarNode->Set_strValue(varVal);
				};
			}catch(...){
            std::string errMsg;
            errMsg = "HtlMemVarItem Set CPP_UCHAR Error thrown";
            throw std::exception(errMsg.c_str());
            return -1;
			};
			return 1;
		};//end Set
		int Get(HtlElement * ptrCurrNode, const std::string & strMemVarName,unsigned char & varVal)
		{
		//return ORSDB::GetXMLNative<string>(ptrCurrNode,strMemVarName, varVal);
			//Now that we have the member variable value, write the element
			try{
				if(!ptrCurrNode){return 0;};
				HtlElement * ptrMemVarNode = NULL;
				ptrMemVarNode = ptrCurrNode->GetSubElement(strMemVarName);
				if(ptrMemVarNode)
				{
					ptrMemVarNode->Get_strValue(varVal);
					return 1;
				}else{
					return 0;
				};
				return 1;
			}catch(...){
            std::string errMsg;
            errMsg = "HtlMemVarItem Get CPP_UCHAR Error thrown";
            throw std::exception(errMsg.c_str());
            return -1;
			};
		};//end Get
	};//end GetMemVarItem

	//CPP_SHORT###############################>>
	template<>
	struct HtlMemVarItem<short,CPP_SHORT>
	{
	public:
		int Set(HtlElement * ptrCurrNode, const std::string & strMemVarName, short & varVal, bool blnWithSubObjects)
		{
			try{
				HtlElement* ptrMemVarNode = GetOrMakeElement(ptrCurrNode,strMemVarName);
				if(ptrMemVarNode)
				{//add the attributes and set the value
					std::string strT, strBT;
					strT = "short"; strBT = "CPP_SHORT";
					SetAttribTypeInfo(ptrMemVarNode,strT,strBT);
					ptrMemVarNode->Set_strValue(varVal);
				};
			}catch(...){
				
            std::string errMsg;
            errMsg = "HtlMemVarItem Set CPP_SHORT Error thrown";
            throw std::exception(errMsg.c_str());
            return -1;
			};
			return 1;
		};//end Set
		int Get(HtlElement * ptrCurrNode, const std::string & strMemVarName, short & varVal)
		{
		//return ORSDB::GetXMLNative<string>(ptrCurrNode,strMemVarName, varVal);
			//Now that we have the member variable value, write the element
			try{
				if(!ptrCurrNode){return 0;};
				HtlElement * ptrMemVarNode = NULL;
				ptrMemVarNode = ptrCurrNode->GetSubElement(strMemVarName);
				if(ptrMemVarNode)
				{
					ptrMemVarNode->Get_strValue(varVal);
					return 1;
				}else{
					return 0;
				};
				return 1;
			}catch(...){
            std::string errMsg;
            errMsg = "HtlMemVarItem Get CPP_SHORT Error thrown";
            throw std::exception(errMsg.c_str());
            return -1;
			};
		};//end Get
	};//end GetMemVarItem

	//CPP_USHORT###############################>>
	template<>
	struct HtlMemVarItem<unsigned short,CPP_USHORT>
	{
	public:
		int Set(HtlElement * ptrCurrNode, const std::string & strMemVarName,unsigned short & varVal, bool blnWithSubObjects)
		{
			try{
				HtlElement* ptrMemVarNode = GetOrMakeElement(ptrCurrNode,strMemVarName);
				if(ptrMemVarNode)
				{//add the attributes and set the value
					std::string strT, strBT;
					strT = "ushort"; strBT = "CPP_USHORT";
					SetAttribTypeInfo(ptrMemVarNode,strT,strBT);
					ptrMemVarNode->Set_strValue(varVal);
				};
			}catch(...){
            std::string errMsg;
            errMsg = "HtlMemVarItem Set CPP_USHORT Error thrown";
            throw std::exception(errMsg.c_str());
            return -1;
			};
			return 1;
		};//end Set
		int Get(HtlElement * ptrCurrNode, const std::string & strMemVarName,unsigned short & varVal)
		{
		//return ORSDB::GetXMLNative<string>(ptrCurrNode,strMemVarName, varVal);
			//Now that we have the member variable value, write the element
			try{
				if(!ptrCurrNode){return 0;};
				HtlElement * ptrMemVarNode = NULL;
				ptrMemVarNode = ptrCurrNode->GetSubElement(strMemVarName);
				if(ptrMemVarNode)
				{
					ptrMemVarNode->Get_strValue(varVal);
					return 1;
				}else{
					return 0;
				};
				return 1;
			}catch(...){
            std::string errMsg;
            errMsg = "HtlMemVarItem Get CPP_USHORT Error thrown";
            throw std::exception(errMsg.c_str());
            return -1;
			};
		};//end Get
	};//end GetMemVarItem

	//CPP_INT###############################>>
	template<>
	struct HtlMemVarItem<int,CPP_INT>
	{
	public:
		int Set(HtlElement * ptrCurrNode, const std::string & strMemVarName, int & varVal, bool blnWithSubObjects)
		{
			try{
				HtlElement* ptrMemVarNode = GetOrMakeElement(ptrCurrNode,strMemVarName);
				if(ptrMemVarNode)
				{//add the attributes and set the value
					std::string strT, strBT;
					strT = "int"; strBT = "CPP_INT";
					SetAttribTypeInfo(ptrMemVarNode,strT,strBT);
					ptrMemVarNode->Set_strValue(varVal);
				};
			}catch(...){
            std::string errMsg;
            errMsg = "HtlMemVarItem Set CPP_INT Error thrown";
            throw std::exception(errMsg.c_str());
            return -1;
			};
			return 1;
		};//end Set
		int Get(HtlElement * ptrCurrNode, const std::string & strMemVarName, int & varVal)
		{
		//return ORSDB::GetXMLNative<string>(ptrCurrNode,strMemVarName, varVal);
			//Now that we have the member variable value, write the element
			try{
				if(!ptrCurrNode){return 0;};
				HtlElement * ptrMemVarNode = NULL;
				ptrMemVarNode = ptrCurrNode->GetSubElement(strMemVarName);
				if(ptrMemVarNode)
				{
					ptrMemVarNode->Get_strValue(varVal);
					return 1;
				}else{
					return 0;
				};
				return 1;
			}catch(...){
            std::string errMsg;
            errMsg = "HtlMemVarItem Get CPP_INT Error thrown";
            throw std::exception(errMsg.c_str());
            return -1;
			};
		};//end Get
	};//end GetMemVarItem

	//CPP_UINT###############################>>
	template<>
	struct HtlMemVarItem<unsigned int,CPP_UINT>
	{
	public:
		int Set(HtlElement * ptrCurrNode, const std::string & strMemVarName,unsigned int & varVal, bool blnWithSubObjects)
		{
			try{
				HtlElement* ptrMemVarNode = GetOrMakeElement(ptrCurrNode,strMemVarName);
				if(ptrMemVarNode)
				{//add the attributes and set the value
					std::string strT, strBT;
					strT = "uint"; strBT = "CPP_UINT";
					SetAttribTypeInfo(ptrMemVarNode,strT,strBT);
					ptrMemVarNode->Set_strValue(varVal);
				};
			}catch(...){
            std::string errMsg;
            errMsg = "HtlMemVarItem Set CPP_UINT Error thrown";
            throw std::exception(errMsg.c_str());
            return -1;
			};
			return 1;
		};//end Set
		int Get(HtlElement * ptrCurrNode, const std::string & strMemVarName,unsigned int & varVal)
		{
		//return ORSDB::GetXMLNative<string>(ptrCurrNode,strMemVarName, varVal);
			//Now that we have the member variable value, write the element
			try{
				if(!ptrCurrNode){return 0;};
				HtlElement * ptrMemVarNode = NULL;
				ptrMemVarNode = ptrCurrNode->GetSubElement(strMemVarName);
				if(ptrMemVarNode)
				{
					ptrMemVarNode->Get_strValue(varVal);
					return 1;
				}else{
					return 0;
				};
				return 1;
			}catch(...){
            std::string errMsg;
            errMsg = "HtlMemVarItem Get CPP_UINT Error thrown";
            throw std::exception(errMsg.c_str());
            return -1;
			};
		};//end Get
	};//end GetMemVarItem



	//CPP_LONG###############################>>
	template<>
	struct HtlMemVarItem<long,CPP_LONG>
	{
	public:
		int Set(HtlElement * ptrCurrNode, const std::string & strMemVarName, long & varVal, bool blnWithSubObjects)
		{
			try{
				HtlElement* ptrMemVarNode = GetOrMakeElement(ptrCurrNode,strMemVarName);
				if(ptrMemVarNode)
				{//add the attributes and set the value
					std::string strT, strBT;
					strT = "long"; strBT = "CPP_LONG";
					SetAttribTypeInfo(ptrMemVarNode,strT,strBT);
					ptrMemVarNode->Set_strValue(varVal);
				};
			}catch(...){
            std::string errMsg;
            errMsg = "HtlMemVarItem Set CPP_LONG Error thrown";
            throw std::exception(errMsg.c_str());
            return -1;
			};
			return 1;
		};//end Set
		int Get(HtlElement * ptrCurrNode, const std::string & strMemVarName, long & varVal)
		{
		//return ORSDB::GetXMLNative<string>(ptrCurrNode,strMemVarName, varVal);
			//Now that we have the member variable value, write the element
			try{
				if(!ptrCurrNode){return 0;};
				HtlElement * ptrMemVarNode = NULL;
				ptrMemVarNode = ptrCurrNode->GetSubElement(strMemVarName);
				if(ptrMemVarNode)
				{
					ptrMemVarNode->Get_strValue(varVal);
					return 1;
				}else{
					return 0;
				};
				return 1;
			}catch(...){
            std::string errMsg;
            errMsg = "HtlMemVarItem Get CPP_LONG Error thrown";
            throw std::exception(errMsg.c_str());
            return -1;
			};
		};//end Get
	};//end GetMemVarItem

	//CPP_ULONG###############################>>
	template<>
	struct HtlMemVarItem<unsigned long,CPP_ULONG>
	{
	public:
		int Set(HtlElement * ptrCurrNode, const std::string & strMemVarName,unsigned long & varVal, bool blnWithSubObjects)
		{
			try{
				HtlElement* ptrMemVarNode = GetOrMakeElement(ptrCurrNode,strMemVarName);
				if(ptrMemVarNode)
				{//add the attributes and set the value
					std::string strT, strBT;
					strT = "ulong"; strBT = "CPP_ULONG";
					SetAttribTypeInfo(ptrMemVarNode,strT,strBT);
					ptrMemVarNode->Set_strValue(varVal);
				};
			}catch(...){
            std::string errMsg;
            errMsg = "HtlMemVarItem Set CPP_ULONG Error thrown";
            throw std::exception(errMsg.c_str());
            return -1;
			};
			return 1;
		};//end Set
		int Get(HtlElement * ptrCurrNode, const std::string & strMemVarName,unsigned long & varVal)
		{
		//return ORSDB::GetXMLNative<string>(ptrCurrNode,strMemVarName, varVal);
			//Now that we have the member variable value, write the element
			try{
				if(!ptrCurrNode){return 0;};
				HtlElement * ptrMemVarNode = NULL;
				ptrMemVarNode = ptrCurrNode->GetSubElement(strMemVarName);
				if(ptrMemVarNode)
				{
					ptrMemVarNode->Get_strValue(varVal);
					return 1;
				}else{
					return 0;
				};
				return 1;
			}catch(...){
            std::string errMsg;
            errMsg = "HtlMemVarItem Get CPP_ULONG Error thrown";
            throw std::exception(errMsg.c_str());
            return -1;
			};
		};//end Get
	};//end GetMemVarItem


	

	//CPP_FLOAT###############################>>
	template<>
	struct HtlMemVarItem<float,CPP_FLOAT>
	{
	public:
		int Set(HtlElement * ptrCurrNode, const std::string & strMemVarName, float & varVal, bool blnWithSubObjects)
		{
			try{
				HtlElement* ptrMemVarNode = GetOrMakeElement(ptrCurrNode,strMemVarName);
				if(ptrMemVarNode)
				{//add the attributes and set the value
					std::string strT, strBT;
					strT = "float"; strBT = "CPP_FLOAT";
					SetAttribTypeInfo(ptrMemVarNode,strT,strBT);
					ptrMemVarNode->Set_strValue(varVal);
				};
			}catch(...){
            std::string errMsg;
            errMsg = "HtlMemVarItem Set CPP_FLOAT Error thrown";
            throw std::exception(errMsg.c_str());
            return -1;
			};
			return 1;
		};//end Set
		int Get(HtlElement * ptrCurrNode, const std::string & strMemVarName, float & varVal)
		{
		//return ORSDB::GetXMLNative<string>(ptrCurrNode,strMemVarName, varVal);
			//Now that we have the member variable value, write the element
			try{
				if(!ptrCurrNode){return 0;};
				HtlElement * ptrMemVarNode = NULL;
				ptrMemVarNode = ptrCurrNode->GetSubElement(strMemVarName);
				if(ptrMemVarNode)
				{
					ptrMemVarNode->Get_strValue(varVal);
					return 1;
				}else{
					return 0;
				};
				return 1;
			}catch(...){
            std::string errMsg;
            errMsg = "HtlMemVarItem Get CPP_FLOAT Error thrown";
            throw std::exception(errMsg.c_str());
            return -1;
			};
		};//end Get
	};//end GetMemVarItem

	//CPP_Ufloat###############################>>
	template<>
	struct HtlMemVarItem<double,CPP_DOUBLE>
	{
	public:
		int Set(HtlElement * ptrCurrNode, const std::string & strMemVarName,double & varVal, bool blnWithSubObjects)
		{
			try{
				HtlElement* ptrMemVarNode = GetOrMakeElement(ptrCurrNode,strMemVarName);
				if(ptrMemVarNode)
				{//add the attributes and set the value
					std::string strT, strBT;
					strT = "double"; strBT = "CPP_DOUBLE";
					SetAttribTypeInfo(ptrMemVarNode,strT,strBT);
					ptrMemVarNode->Set_strValue(varVal);
				};
			}catch(...){
            std::string errMsg;
            errMsg = "HtlMemVarItem Set CPP_DOUBLE Error thrown";
            throw std::exception(errMsg.c_str());
            return -1;
			};
			return 1;
		};//end Set
		int Get(HtlElement * ptrCurrNode, const std::string & strMemVarName,double & varVal)
		{
		//return ORSDB::GetXMLNative<string>(ptrCurrNode,strMemVarName, varVal);
			//Now that we have the member variable value, write the element
			try{
				if(!ptrCurrNode){return 0;};
				HtlElement * ptrMemVarNode = NULL;
				ptrMemVarNode = ptrCurrNode->GetSubElement(strMemVarName);
				if(ptrMemVarNode)
				{
					ptrMemVarNode->Get_strValue(varVal);
					return 1;
				}else{
					return 0;
				};
				return 1;
			}catch(...){
            std::string errMsg;
            errMsg = "HtlMemVarItem Get CPP_DOUBLE Error thrown";
            throw std::exception(errMsg.c_str());
            return -1;
			};
		};//end Get
	};//end GetMemVarItem

//HANDLING FOR HTL DATA TYPES
		//HTL_BASE = 20,
		//HTL_BASE_PTR = 21,
		//HTL_OBJECT = 22,
		//HTL_OBJECT_PTR = 23,
		//HTL_CONTAINER = 24,
		//HTL_CONTAINER_PTR = 25,
		//HTL_STRING = 26,
		//HTL_ENUM = 27,
		//HTL_GUID64 = 28,
		//HTL_GUID128 = 29,
		//HTL_GUID256 = 30

	//HTL_BASE###############################>>
	template<class TObj>
	struct HtlMemVarItem<TObj,HTL_BASE>
	{
	public:
		int Set(HtlElement * ptrCurrNode, const std::string & strMemVarName,TObj & varVal, bool blnWithSubObjects)
		{
			try{
				HtlElement* ptrMemVarNode = GetOrMakeElement(ptrCurrNode,strMemVarName);
				if(ptrMemVarNode)
				{//add the attributes and set the value
					std::string strT, strBT;
					strT = varVal.Get_strType();
					strBT = "HTL_BASE";
					SetAttribTypeInfo(ptrMemVarNode,strT,strBT);
					if(blnWithSubObjects)
					{
						varVal.Save(ptrMemVarNode, strMemVarName, blnWithSubObjects);
					};
				};
			}catch(...){
            std::string errMsg;
            errMsg = "HtlMemVarItem Set HTL_BASE Error thrown";
            throw std::exception(errMsg.c_str());
            return -1;
			};
			return 1;
		};//end Set
		int Get(HtlElement * ptrCurrNode, const std::string & strMemVarName,TObj & varVal)
		{

			//Now that we have the member variable value, write the element
			try{
				if(!ptrCurrNode){return 0;};
				HtlElement * ptrMemVarNode = NULL;
				ptrMemVarNode = ptrCurrNode->GetSubElement(strMemVarName);
				if(ptrMemVarNode)
				{
					varVal.Load(ptrMemVarNode,strMemVarName);
					return 1;
				}else{
					return 0;
				};
				return 1;
			}catch(...){
            std::string errMsg;
            errMsg = "HtlMemVarItem Get HTL_BASE Error thrown";
            throw std::exception(errMsg.c_str());
            return -1;
			};
		};//end Get
	};//end GetMemVarItem

	//HTL_BASE_PTR###############################>>
	template<class TObj>
	struct HtlMemVarItem<TObj,HTL_BASE_PTR>
	{
	public:
		int Set(HtlElement * ptrCurrNode, const std::string & strMemVarName,TObj & varVal, bool blnWithSubObjects)
		{
			try{
				if(!varVal){return 0;};
				HtlElement* ptrMemVarNode = GetOrMakeElement(ptrCurrNode,strMemVarName);
				if(ptrMemVarNode)
				{//add the attributes and set the value
					std::string strT, strBT;
					strT = varVal->Get_strType();
					strBT = "HTL_BASE_PTR";
					SetAttribTypeInfo(ptrMemVarNode,strT,strBT);
					if(blnWithSubObjects)
					{
						varVal->Save(ptrMemVarNode, strMemVarName, blnWithSubObjects);
					};
				};
			}catch(...){
            std::string errMsg;
            errMsg = "HtlMemVarItem Set HTL_BASE_PTR Error thrown";
            throw std::exception(errMsg.c_str());
            return -1;
			};
			return 1;
		};//end Set
		int Get(HtlElement * ptrCurrNode, const std::string & strMemVarName,TObj & varVal)
		{
	
			//Now that we have the member variable value, write the element
			try{
				if(!ptrCurrNode){return 0;};
				HtlElement * ptrMemVarNode = NULL;
				ptrMemVarNode = ptrCurrNode->GetSubElement(strMemVarName);
				if(ptrMemVarNode)
				{
					varVal->Load(ptrMemVarNode,strMemVarName);
					return 1;
				}else{
					return 0;
				};
				return 1;
			}catch(...){
            std::string errMsg;
            errMsg = "HtlMemVarItem Get HTL_BASE_PTR Error thrown";
            throw std::exception(errMsg.c_str());
            return -1;
			};
		};//end Get
	};//end GetMemVarItem

	//HTL_OBJECT###############################>>
	template<class TObj>
	struct HtlMemVarItem<TObj,HTL_OBJECT>
	{
	public:
		int Set(HtlElement * ptrCurrNode, const std::string & strMemVarName,TObj & varVal, bool blnWithSubObjects)
		{
			try{
				HtlElement* ptrMemVarNode = GetOrMakeElement(ptrCurrNode,strMemVarName);
				if(ptrMemVarNode)
				{//add the attributes and set the value
					std::string strT, strBT;
					strT = varVal.Get_strType();
					strBT = "HTL_OBJECT";
					SetAttribTypeInfo(ptrMemVarNode,strT,strBT);
					if(blnWithSubObjects)
					{
						varVal.Save(ptrMemVarNode, strMemVarName, blnWithSubObjects);
					};
				};
			}catch(...){
            std::string errMsg;
            errMsg = "HtlMemVarItem Set HTL_OBJECT Error thrown";
            throw std::exception(errMsg.c_str());
				return -1;
			};
			return 1;
		};//end Set
		int Get(HtlElement * ptrCurrNode, const std::string & strMemVarName,TObj & varVal)
		{
			//Now that we have the member variable value, write the element
			try{
				if(!ptrCurrNode){return 0;};
				HtlElement * ptrMemVarNode = NULL;
				ptrMemVarNode = ptrCurrNode->GetSubElement(strMemVarName);
				if(ptrMemVarNode)
				{
					varVal.Load(ptrMemVarNode,strMemVarName);
					return 1;
				}else{
					return 0;
				};
				return 1;
			}catch(...){
            std::string errMsg;
            errMsg = "HtlMemVarItem Get HTL_OBJECT Error thrown";
            throw std::exception(errMsg.c_str());
            return -1;
			};
		};//end Get
	};//end GetMemVarItem

	//HTL_OBJECT_PTR###############################>>
	template<class TObj>
	struct HtlMemVarItem<TObj,HTL_OBJECT_PTR>
	{
	public:
		int Set(HtlElement * ptrCurrNode, const std::string & strMemVarName,TObj & varVal, bool blnWithSubObjects)
		{
			try{
				if(!varVal){return 0;};
				HtlElement* ptrMemVarNode = GetOrMakeElement(ptrCurrNode,strMemVarName);
				if(ptrMemVarNode)
				{//add the attributes and set the value
					std::string strT, strBT;
					strT = varVal->Get_strType();
					strBT = "HTL_OBJECT_PTR";
					SetAttribTypeInfo(ptrMemVarNode,strT,strBT);
					if(blnWithSubObjects)
					{
						varVal->Save(ptrMemVarNode, strMemVarName, blnWithSubObjects);
					};
				};
			}catch(...){
            std::string errMsg;
            errMsg = "HtlMemVarItem Set HTL_OBJECT_PTR Error thrown";
            throw std::exception(errMsg.c_str());
				return -1;
			};
			return 1;
		};//end Set
		int Get(HtlElement * ptrCurrNode, const std::string & strMemVarName,TObj & varVal)
		{
			//Now that we have the member variable value, write the element
			try{
				if(!ptrCurrNode){return 0;};
				HtlElement * ptrMemVarNode = NULL;
				ptrMemVarNode = ptrCurrNode->GetSubElement(strMemVarName);
				if(ptrMemVarNode)
				{
					varVal->Load(ptrMemVarNode,strMemVarName);
					return 1;
				}else{
					return 0;
				};
				return 1;
			}catch(...){
            std::string errMsg;
            errMsg = "HtlMemVarItem Get HTL_OBJECT_PTR Error thrown";
            throw std::exception(errMsg.c_str());
            return -1;
			};
		};//end Get
	};//end GetMemVarItem

	//HTL_CONTAINER###############################>>
	template<class TObj>
	struct HtlMemVarItem<TObj,HTL_CONTAINER>
	{
	public:
		int Set(HtlElement * ptrCurrNode, const std::string & strMemVarName,TObj & varVal, bool blnWithSubObjects)
		{
			try{
				HtlElement* ptrMemVarNode = GetOrMakeElement(ptrCurrNode,strMemVarName);
				if(ptrMemVarNode)
				{//add the attributes and set the value
					std::string strT, strBT;
					strT = varVal.Get_strType();
					strBT = "HTL_CONTAINER";
					SetAttribTypeInfo(ptrMemVarNode,strT,strBT);
					if(blnWithSubObjects)
					{
						varVal.Save(ptrMemVarNode, strMemVarName, blnWithSubObjects);
					};
				};
			}catch(...){
            std::string errMsg;
            errMsg = "HtlMemVarItem Set HTL_CONTAINER Error thrown";
            throw std::exception(errMsg.c_str());
				return -1;
			};
			return 1;
		};//end Set
		int Get(HtlElement * ptrCurrNode, const std::string & strMemVarName,TObj & varVal)
		{
			//Now that we have the member variable value, write the element
			try{
				if(!ptrCurrNode){return 0;};
				HtlElement * ptrMemVarNode = NULL;
				ptrMemVarNode = ptrCurrNode->GetSubElement(strMemVarName);
				if(ptrMemVarNode)
				{
					varVal.Load(ptrMemVarNode,strMemVarName);
					return 1;
				}else{
					return 0;
				};
				return 1;
			}catch(...){
            std::string errMsg;
            errMsg = "HtlMemVarItem Get HTL_CONTAINER Error thrown";
            throw std::exception(errMsg.c_str());
            return -1;
			};
		};//end Get
	};//end GetMemVarItem

	//HTL_CONTAINER_PTR###############################>>
	template<class TObj>
	struct HtlMemVarItem<TObj,HTL_CONTAINER_PTR>
	{
	public:
		int Set(HtlElement * ptrCurrNode, const std::string & strMemVarName,TObj & varVal, bool blnWithSubObjects)
		{
			try{
				if(!varVal){return 0;};
				HtlElement* ptrMemVarNode = GetOrMakeElement(ptrCurrNode,strMemVarName);
				if(ptrMemVarNode)
				{//add the attributes and set the value
					std::string strT, strBT;
					strT = varVal->Get_strType();
					strBT = "HTL_CONTAINER_PTR";
					SetAttribTypeInfo(ptrMemVarNode,strT,strBT);
					if(blnWithSubObjects)
					{
						varVal->Save(ptrMemVarNode, strMemVarName, blnWithSubObjects);
					};
				};
			}catch(...){
            std::string errMsg;
            errMsg = "HtlMemVarItem Set HTL_CONTAINER_PTR Error thrown";
            throw std::exception(errMsg.c_str());
				return -1;
			};
			return 1;
		};//end Set
		int Get(HtlElement * ptrCurrNode, const std::string & strMemVarName,TObj & varVal)
		{
			//Now that we have the member variable value, write the element
			try{
				if(!ptrCurrNode){return 0;};
				HtlElement * ptrMemVarNode = NULL;
				ptrMemVarNode = ptrCurrNode->GetSubElement(strMemVarName);
				if(ptrMemVarNode)
				{
					varVal->Load(ptrMemVarNode,strMemVarName);
					return 1;
				}else{
					return 0;
				};
				return 1;
			}catch(...){
            std::string errMsg;
            errMsg = "HtlMemVarItem Get HTL_CONTAINER_PTR Error thrown";
            throw std::exception(errMsg.c_str());
            return -1;
			};
		};//end Get
	};//end GetMemVarItem


	//HTL_STRING###############################>>
	template<class TObj>
	struct HtlMemVarItem<TObj,HTL_STRING>
	{
	public:
		int Set(HtlElement * ptrCurrNode, const std::string & strMemVarName,TObj & varVal, bool blnWithSubObjects)
		{
			try{
				HtlElement* ptrMemVarNode = GetOrMakeElement(ptrCurrNode,strMemVarName);
				if(ptrMemVarNode)
				{//add the attributes and set the value
					std::string strT, strBT, strData;
					strT = "HtlString";
					strBT = "HTL_STRING";
					SetAttribTypeInfo(ptrMemVarNode,strT,strBT);
					strData = varVal.unicode();
					ptrMemVarNode->Set_strValue(strData);
				};
			}catch(...){
            std::string errMsg;
            errMsg = "HtlMemVarItem Set HTL_STRING Error thrown";
            throw std::exception(errMsg.c_str());
				return -1;
			};
			return 1;
		};//end Set
		int Get(HtlElement * ptrCurrNode, const std::string & strMemVarName,TObj & varVal)
		{
			//Now that we have the member variable value, write the element
			try{
				if(!ptrCurrNode){return 0;};
				HtlElement * ptrMemVarNode = NULL;
				ptrMemVarNode = ptrCurrNode->GetSubElement(strMemVarName);
				if(ptrMemVarNode)
				{
					std::string strData;
					strData = ptrMemVarNode->Get_strValue();
					varVal = strData.c_str();
					return 1;
				}else{
					return 0;
				};
				return 1;
			}catch(...){
            std::string errMsg;
            errMsg = "HtlMemVarItem Get HTL_STRING Error thrown";
            throw std::exception(errMsg.c_str());
            return -1;
			};
		};//end Get
	};//end GetMemVarItem

	//HTL_ENUM###############################>>
	template<class TObj>
	struct HtlMemVarItem<TObj,HTL_ENUM>
	{
	public:
		int Set(HtlElement * ptrCurrNode, const std::string & strMemVarName,TObj & varVal, bool blnWithSubObjects)
		{
			try{
				HtlElement* ptrMemVarNode = GetOrMakeElement(ptrCurrNode,strMemVarName);
				if(ptrMemVarNode)
				{//add the attributes and set the value
					std::string strT, strBT,strData;
					strT = "HtlString";
					strBT = "HTL_ENUM";
					SetAttribTypeInfo(ptrMemVarNode,strT,strBT);
					HTL::enumToString<TObj>(varVal,strData);
					ptrMemVarNode->Set_strValue(strData);
				};
			}catch(...){
            std::string errMsg;
            errMsg = "HtlMemVarItem Set HTL_ENUM Error thrown";
            throw std::exception(errMsg.c_str());
				return -1;
			};
			return 1;
		};//end Set
		int Get(HtlElement * ptrCurrNode, const std::string & strMemVarName,TObj & varVal)
		{
			//Now that we have the member variable value, write the element
			try{
				if(!ptrCurrNode){return 0;};
				HtlElement * ptrMemVarNode = NULL;
				ptrMemVarNode = ptrCurrNode->GetSubElement(strMemVarName);
				if(ptrMemVarNode)
				{
					std::string strData;
					strData = ptrMemVarNode->Get_strValue();
					HTL::stringToEnum<TObj>(strData,varVal);
					return 1;
				}else{
					return 0;
				};
				return 1;
			}catch(...){
            std::string errMsg;
            errMsg = "HtlMemVarItem Get HTL_ENUM Error thrown";
            throw std::exception(errMsg.c_str());
            return -1;
			};
		};//end Get
	};//end GetMemVarItem

	//HTL_GUID64###############################>>
	template<>
	struct HtlMemVarItem<HtlGUID64,HTL_GUID64>
	{
	public:
		int Set(HtlElement * ptrCurrNode, const std::string & strMemVarName,HtlGUID64 & varVal, bool blnWithSubObjects)
		{
			try{
				HtlElement* ptrMemVarNode = GetOrMakeElement(ptrCurrNode,strMemVarName);
				if(ptrMemVarNode)
				{//add the attributes and set the value
					std::string strT, strBT, strData;
					strT = "HtlGuid64";
					strBT = "HTL_GUID64";
					SetAttribTypeInfo(ptrMemVarNode,strT,strBT);
					strData = varVal.toStdString();
					ptrMemVarNode->Set_strValue(strData);
				};
			}catch(...){
            std::string errMsg;
            errMsg = "HtlMemVarItem Set HTL_GUID64 Error thrown";
            throw std::exception(errMsg.c_str());
				return -1;
			};
			return 1;
		};//end Set
		int Get(HtlElement * ptrCurrNode, const std::string & strMemVarName,HtlGUID64 & varVal)
		{
			//Now that we have the member variable value, write the element
			try{
				if(!ptrCurrNode){return 0;};
				HtlElement * ptrMemVarNode = NULL;
				ptrMemVarNode = ptrCurrNode->GetSubElement(strMemVarName);
				if(ptrMemVarNode)
				{
					std::string strData;
					strData = ptrMemVarNode->Get_strValue();
					varVal.fromStdString(strData);
					return 1;
				}else{
					return 0;
				};
				return 1;
			}catch(...){
            std::string errMsg;
            errMsg = "HtlMemVarItem Get HTL_GUID64 Error thrown";
            throw std::exception(errMsg.c_str());
            return -1;
			};
		};//end Get
	};//end GetMemVarItem

	//HTL_GUID128###############################>>
	template<>
	struct HtlMemVarItem<HtlGUID128,HTL_GUID128>
	{
	public:
		int Set(HtlElement * ptrCurrNode, const std::string & strMemVarName,HtlGUID128 & varVal, bool blnWithSubObjects)
		{
			try{
				HtlElement* ptrMemVarNode = GetOrMakeElement(ptrCurrNode,strMemVarName);
				if(ptrMemVarNode)
				{//add the attributes and set the value
					std::string strT, strBT, strData;
					strT = "HtlGUID128";
					strBT = "HTL_GUID128";
					SetAttribTypeInfo(ptrMemVarNode,strT,strBT);
					strData = varVal.toStdString();
					ptrMemVarNode->Set_strValue(strData);
				};
			}catch(...){
            std::string errMsg;
            errMsg = "HtlMemVarItem Set HTL_GUID128 Error thrown";
            throw std::exception(errMsg.c_str());
				return -1;
			};
			return 1;
		};//end Set
		int Get(HtlElement * ptrCurrNode, const std::string & strMemVarName,HtlGUID128 & varVal)
		{
			//Now that we have the member variable value, write the element
			try{
				if(!ptrCurrNode){return 0;};
				HtlElement * ptrMemVarNode = NULL;
				ptrMemVarNode = ptrCurrNode->GetSubElement(strMemVarName);
				if(ptrMemVarNode)
				{
					std::string strData;
					strData = ptrMemVarNode->Get_strValue();
					varVal.fromStdString(strData);
					return 1;
				}else{
					return 0;
				};
				return 1;
			}catch(...){
            std::string errMsg;
            errMsg = "HtlMemVarItem Get HTL_GUID128 Error thrown";
            throw std::exception(errMsg.c_str());
            return -1;
			};
		};//end Get
	};//end GetMemVarItem

	//HTL_GUID128###############################>>
	template<>
	struct HtlMemVarItem<HtlGUID256,HTL_GUID256>
	{
	public:
		int Set(HtlElement * ptrCurrNode, const std::string & strMemVarName,HtlGUID256 & varVal, bool blnWithSubObjects)
		{
			try{
				HtlElement* ptrMemVarNode = GetOrMakeElement(ptrCurrNode,strMemVarName);
				if(ptrMemVarNode)
				{//add the attributes and set the value
					std::string strT, strBT, strData;
					strT = "HtlGUID256";
					strBT = "HTL_GUID256";
					SetAttribTypeInfo(ptrMemVarNode,strT,strBT);
					strData = varVal.toStdString();
					ptrMemVarNode->Set_strValue(strData);
				};
			}catch(...){
            std::string errMsg;
            errMsg = "HtlMemVarItem Set HTL_GUID256 Error thrown";
            throw std::exception(errMsg.c_str());
				return -1;
			};
			return 1;
		};//end Set
		int Get(HtlElement * ptrCurrNode, const std::string & strMemVarName,HtlGUID256 & varVal)
		{
			//Now that we have the member variable value, write the element
			try{
				if(!ptrCurrNode){return 0;};
				HtlElement * ptrMemVarNode = NULL;
				ptrMemVarNode = ptrCurrNode->GetSubElement(strMemVarName);
				if(ptrMemVarNode)
				{
					std::string strData;
					strData = ptrMemVarNode->Get_strValue();
					varVal.fromStdString(strData);
					return 1;
				}else{
					return 0;
				};
				return 1;
			}catch(...){
            std::string errMsg;
            errMsg = "HtlMemVarItem Get HTL_GUID256 Error thrown";
            throw std::exception(errMsg.c_str());
            return -1;
			};
		};//end Get
	};//end GetMemVarItem

	//STL_STRING###############################>>
	template<class TObj>
	struct HtlMemVarItem<TObj,STL_STRING>
	{
	public:
		int Set(HtlElement * ptrCurrNode, const std::string & strMemVarName,TObj & varVal, bool blnWithSubObjects)
		{
			try{
				HtlElement* ptrMemVarNode = GetOrMakeElement(ptrCurrNode,strMemVarName);
				if(ptrMemVarNode)
				{//add the attributes and set the value
					std::string strT, strBT, strData;
					strT = "string";
					strBT = "STL_STRING";
					SetAttribTypeInfo(ptrMemVarNode,strT,strBT);
					strData = varVal.c_str();
					ptrMemVarNode->Set_strValue(strData);
				};
			}catch(...){
            std::string errMsg;
            errMsg = "HtlMemVarItem Set STL_STRING Error thrown";
            throw std::exception(errMsg.c_str());
				return -1;
			};
			return 1;
		};//end Set
		int Get(HtlElement * ptrCurrNode, const std::string & strMemVarName,TObj & varVal)
		{
			//Now that we have the member variable value, write the element
			try{
				if(!ptrCurrNode){return 0;};
				HtlElement * ptrMemVarNode = NULL;
				ptrMemVarNode = ptrCurrNode->GetSubElement(strMemVarName);
				if(ptrMemVarNode)
				{
					std::string strData;
					strData = ptrMemVarNode->Get_strValue();
					varVal = strData.c_str();
					return 1;
				}else{
					return 0;
				};
				return 1;
			}catch(...){
            std::string errMsg;
            errMsg = "HtlMemVarItem Get STL_STRING Error thrown";
            throw std::exception(errMsg.c_str());
            return -1;
			};
		};//end Get
	};//end GetMemVarItem

	//STL_CONTAINER###############################>>
	template<class TObj>
	struct HtlMemVarItem<TObj,STL_CONTAINER>
	{
	public:
		int Set(HtlElement * ptrCurrNode, const std::string & strMemVarName,TObj & varVal, bool blnWithSubObjects)
		{
			try{
				HtlElement* ptrMemVarNode = GetOrMakeElement(ptrCurrNode,strMemVarName);
				if(ptrMemVarNode)
				{//add the attributes and set the value
					std::string strT, strBT;
					strT = varVal.Get_strType();
					strBT = "STL_CONTAINER";
					SetAttribTypeInfo(ptrMemVarNode,strT,strBT);
					if(blnWithSubObjects)
					{
						varVal.Save(ptrMemVarNode, strMemVarName, blnWithSubObjects);
					};
				};
			}catch(...){
            std::string errMsg;
            errMsg = "HtlMemVarItem Set STL_CONTAINER Error thrown";
            throw std::exception(errMsg.c_str());
				return -1;
			};
			return 1;
		};//end Set
		int Get(HtlElement * ptrCurrNode, const std::string & strMemVarName,TObj & varVal)
		{
			//Now that we have the member variable value, write the element
			try{
				if(!ptrCurrNode){return 0;};
				HtlElement * ptrMemVarNode = NULL;
				ptrMemVarNode = ptrCurrNode->GetSubElement(strMemVarName);
				if(ptrMemVarNode)
				{
					varVal.Load(ptrMemVarNode,strMemVarName);
					return 1;
				}else{
					return 0;
				};
				return 1;
			}catch(...){
            std::string errMsg;
            errMsg = "HtlMemVarItem Get STL_CONTAINER Error thrown";
            throw std::exception(errMsg.c_str());
            return -1;
			};
		};//end Get
	};//end GetMemVarItem

	//STL_CONTAINER_PTR###############################>>
	template<class TObj>
	struct HtlMemVarItem<TObj,STL_CONTAINER_PTR>
	{
	public:
		int Set(HtlElement * ptrCurrNode, const std::string & strMemVarName,TObj & varVal, bool blnWithSubObjects)
		{
			try{
				if(!varVal){return 0;};
				HtlElement* ptrMemVarNode = GetOrMakeElement(ptrCurrNode,strMemVarName);
				if(ptrMemVarNode)
				{//add the attributes and set the value
					std::string strT, strBT;
					strT = varVal->Get_strType();
					strBT = "HTL_CONTAINER_PTR";
					SetAttribTypeInfo(ptrMemVarNode,strT,strBT);
					if(blnWithSubObjects)
					{
						varVal->Save(ptrMemVarNode, strMemVarName, blnWithSubObjects);
					};
				};
			}catch(...){
            std::string errMsg;
            errMsg = "HtlMemVarItem Set STL_CONTAINER_PTR Error thrown";
            throw std::exception(errMsg.c_str());
				return -1;
			};
			return 1;
		};//end Set
		int Get(HtlElement * ptrCurrNode, const std::string & strMemVarName,TObj & varVal)
		{
			//Now that we have the member variable value, write the element
			try{
				if(!ptrCurrNode){return 0;};
				HtlElement * ptrMemVarNode = NULL;
				ptrMemVarNode = ptrCurrNode->GetSubElement(strMemVarName);
				if(ptrMemVarNode)
				{
					varVal->Load(ptrMemVarNode,strMemVarName);
					return 1;
				}else{
					return 0;
				};
				return 1;
			}catch(...){
            std::string errMsg;
            errMsg = "HtlMemVarItem Get STL_CONTAINER_PTR Error thrown";
            throw std::exception(errMsg.c_str());
				return -1;
			};
		};//end Get
	};//end GetMemVarItem
};//end namespace HTL
#endif