/*
**	This file is part of the Hpc Template Library (Htl or HTL).
**  It is based on a merger of QT, STL, and SigSlots along with development of new classes.
**  License information is in the HtlLicense.h file
**	This software was merged and developed by:
**	
**  Anthony Daniels
**	QT (Nokia),
**	STL(Microsoft),
**	SigSlots
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

#ifndef STL_MAP_H
#define STL_MAP_H

#include <map>
using namespace std;

#include ".\HtlContainer.h"

namespace HTL
{


	//!HtlMap is a one dimensional modified AVL Tree for objects.
	/*!
	HtlMap is a one dimensional modified AVL Tree for objects.  HtlMap is actually a combined data structure.
	It is BOTH an AVL tree AND a doubly linked list.  Each node of the map belongs to corresponding node in the AVL Tree
	and is in the properly sorted location in the doubly linked list according to its < operator.  This allows for fast
	tree based searches, as well as the ability to cycle through the entire tree as linked list.
	*/
	template<typename TKey,HtlObjectType TKeyEnum, typename TObj, HtlObjectType TObjEnum>
	class StlMap :public HtlContainer<TKey,TKeyEnum,TObj,TObjEnum>
	{

	protected:

		std::map<TKey, TObj> m_map;

		//StlMap CLASS DEFINITION/////////////////////////////////////////
	public:
		typedef typename std::map<TKey, TObj>::iterator StlMapIterator;
		//!Void constructor
		StlMap():HtlContainer()
		{
			m_objType = HTL_CONTAINER;
			m_strType = "StlMap";
			m_itemType = TObjEnum;
		};

		//!Virtual destructor
		virtual ~StlMap(void)
		{
			m_map.clear();
		};

		//TEMPLATE MEMBER VARIABLE DECLARATION AND DEFINITION//////////////////////////////////
	public:
		//!HTL Container Analyzers
		//!Returns the length of the string minus the null terminator (\0)
		virtual size_t size(void) const
		{
			return m_map.size();
		};

		//!Returns the length of the string minus the null terminator (\0)
		virtual size_t count(void) const
		{
			return m_map.size();
		};

		//!Returns if the map is empty
		virtual bool isEmpty(void) const
		{
			if (m_map.size() <= 0)
			{
				return true;
			}else{
				return false;
			};
		};





		//!Clears the container
		virtual void clear(void)
		{
			try
			{
				//lock the container before modifying it
				HtlGUID128 objNullID;
				objNullID.newID();
				m_objLock.lock(objNullID);
				if (m_map.size() > 0)
				{
					m_map.clear();
				};

				m_objLock.unlock(objNullID);

				return;
			}
			catch (...)
			{
				std::string errMsg;
				errMsg = "StlMap clear Error thrown";
				throw std::exception(errMsg.c_str());
			}
		};
		//!Item accessor function
		StlMapIterator begin(void)
		{
			return m_map.begin();
		};
		StlMapIterator end(void)
		{
			return m_end.end();
		};
		StlMapIterator find(TKey &key)
		{
			try
			{
				return m_end.find(key);
			}
			catch (...)
			{
				std::string errMsg;
				errMsg = "StlMap find Error thrown";
				throw std::exception(errMsg.c_str());
			}
		};
		//!Inserts a node into the tree
		int insert(TKey &key, TObj &item)	
		{
			try
			{
				//safety checks
				bool blnPlaced = false;
				bool blnNewNode = false;
				HtlGUID128 objNullID;
				objNullID.newID();
				m_objLock.lock(objNullID);
				//call the STL map insert now that we are locked
				m_map.insert(std::make_pair(key, item));

				m_objLock.unlock(objNullID);
				return 1;
			}
			catch (...)
			{
				std::string errMsg;
				errMsg = "StlMap insert Error thrown";
				throw std::exception(errMsg.c_str());
			}
		};



		//!Erases a node from the tree
		int erase(TKey objKeyToDelete)
		{
			try
			{
				if (!m_ptrRoot) { return 0; };
				bool blnErased = false;
				HtlGUID128 objNullID;
				objNullID.newID();
				m_objLock.lock(objNullID);
				//call the STL map erase now that we are locked
				m_map.erase(objKeyToDelete);

				m_objLock.unlock(objNullID);

				return 1;
			}
			catch (...)
			{
				std::string errMsg;
				errMsg = "StlMap erase Error thrown";
				throw std::exception(errMsg.c_str());
			}
		};

		//
	

public:
		//Virtual Inheritance Serialization Engines
		//SERIALIZATION ACCESSOR MACRO///////////////////////////////////////
	//!Save the HtlMap to the current HtlElement
		virtual int Save(HTL::HtlElement * ptrCurrNode, std::string strMemVarName, bool blnWithSubObjects)
		{

			int intReturn = 0;
			//SAFETY CHECK //put at top of all Serialize Methods
			if(!ptrCurrNode){return 0;};
			//CALL PARENT CLASS Serialize()
			/*...*/
			HtlContainer::Save(ptrCurrNode, strMemVarName, blnWithSubObjects);
			//Standard Member Variables
			std::string strIntNumDim;
			strIntNumDim = "1";

			HTL::SetAttribIntNumDim(ptrCurrNode,strIntNumDim);

			//Now that we have the member variable value, write the element
			try{
				bool blnFinished = false;
				int intReturn = 1;
				size_t i, intNumItems;
				char chrBuf[256];
				std::string strIndexName;
				//Iterator iter;
				HtlElement * ptrNewElement = NULL;
				//CALL PARENT CLASS SERIALIZATION FIRST
				if(ptrCurrNode)
				{
					//get the number of elements
					intNumItems = size();
					//set the elements to XML
					map<TKey,TObj>::iterator ptrCursor;
					i = 0;
					ptrCursor = m_map.begin();
					while ( !blnFinished)
					{
						itoa(i,chrBuf,10);
						strIndexName = "IT_";
						strIndexName += chrBuf;
						//create the Pair Element

						HtlElement* ptrPairElement = ptrCurrNode->AddSubElement();
						ptrPairElement->Set_strName(strIndexName);
						//SOME FUNCTION FOR SETTING THE XML ITEM REGARDLESS OF TYPE
						TKey objKeyTemp = ptrCursor->first;
						HTL::SetHtlMemVar<TKey,TKeyEnum>(ptrPairElement,"m_objKey",objKeyTemp,blnWithSubObjects);
						TObj objValTemp = ptrCursor->second;
						HTL::SetHtlMemVar<TObj,TObjEnum>(ptrPairElement,"m_objValue",objValTemp,blnWithSubObjects);
						//index cursor
						i++;
						++ptrCursor;

						if(ptrCursor == m_map.end()){blnFinished = true;};
					};
				};//end valid new node check
				return 1;
			}catch(...){
				std::string errMsg;
				errMsg = "StlMap Save Error thrown";
				throw std::exception(errMsg.c_str());
				return -1;
			};

			return intReturn;

		};
		//!Load the HtlMap from the current HtlElement
		virtual int Load(HTL::HtlElement * ptrCurrNode, std::string strMemVarName)
		{

			int intReturn = 0;
			//SAFETY CHECK //put at top of all Serialize Methods
			if(!ptrCurrNode){return 0;};
			//CALL PARENT CLASS Serialize()
			/*...*/
			HtlContainer::Load(ptrCurrNode,strMemVarName);
			//Standard Member Variables
			int intTemp;
			size_t i, intNumItems;
			std::string strNodeName, strIndexName, strItemTypeName,strElementName;
			HtlElement * ptrCurrElement = NULL;
			HtlAttribute * ptrCurrAttribute = NULL;
			try{
				intReturn = 1;
				intTemp = 1;

				intNumItems = ptrCurrNode->CountSubElements();
				if(size() != intNumItems)
				{
					//resize(intNumItems);
				};
				for(i = 0; i < intNumItems;i++)
				{
					ptrCurrElement = ptrCurrNode->GetSubElement(i);
					strElementName = ptrCurrElement->Get_strName();
					if(strElementName.find(HTL_strITEM) != string::npos)
					{
						if(ptrCurrElement)
						{
							TKey objKeyTemp;
							HTL::GetHtlMemVar<TKey,TKeyEnum>(ptrCurrElement,"m_objKey",objKeyTemp);
							TObj objValTemp;
							HTL::GetHtlMemVar<TObj,TObjEnum>(ptrCurrElement,"m_objValue",objValTemp);
							//insert the node into the tree
							m_map.insert(std::make_pair(objKeyTemp,objValTemp));
						};
					};
				};
				return intReturn;
			}catch(...){
				std::string errMsg;
				errMsg = "StlMap Load Error thrown";
				throw std::exception(errMsg.c_str());
				return -1;
			};
			return intReturn;

		};


	};//end StlMap class definition

};//end namespace HTL
#endif