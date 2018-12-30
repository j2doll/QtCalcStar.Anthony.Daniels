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

#ifndef HTL_LIST_MAP_H
#define HTL_LIST_MAP_H

#include ".\HtlContainer.h"
#include ".\HtlTreeNode.h"

namespace HTL
{


	//!HtlListMap is a one dimensional modified AVL Tree for objects.
	/*!
	HtlListMap is a one dimensional modified AVL Tree for objects.  HtlListMap is actually a combined data structure.
	It is BOTH an AVL tree AND a doubly linked list.  Each node of the map belongs to corresponding node in the AVL Tree
	and is in the properly sorted location in the doubly linked list according to its < operator.  This allows for fast
	tree based searches, as well as the ability to cycle through the entire tree as linked list.
	*/
	template<typename TKey,HtlObjectType TKeyEnum, typename TObj, HtlObjectType TObjEnum>
	class HtlListMap : public HtlContainer<TKey, TKeyEnum, TObj, TObjEnum>
	{
		//typedef qptrdiff difference_type;
		typedef TObj Value;
		typedef TObj *Pointer;
		typedef TObj &Reference;
		typedef const TObj & ConstReference;
		//HtlVector1D SUBCLASS DECLARATIONS////////////////////////////////////////
		//END HTLVECTOR1D SUBCLASS DEFINITIONS///////////////////////////////////////

		HtlDebugPrinter m_objPrint;
		//HtlVector1D CLASS DEFINITION/////////////////////////////////////////
	public:

		//!Void constructor
		HtlListMap() : HtlContainer()
		{

			std::string strFile = "HtlListMap.txt";
			m_objPrint.Set_blnPrintToFile(true);
			m_objPrint.Set_blnPrintToStream(false);
			m_objPrint.Set_blnPrintToTextEdit(false);
			m_objPrint.Set_strFileName(strFile);
			//comment out next line to enable debug dumping to file
			m_objPrint.Disable();
			m_ptrCursor = NULL;
			m_intSize = 0;
			m_objType = HTL_CONTAINER;
			m_strType = "HtlListMap";
			m_itemType = TObjEnum;
			m_chrNull = '\0';
			m_objHead.setNull();
			m_objHead.m_ptrNext = &m_objEnd;
			m_objHead.m_blnHead = true;

			m_objEnd.setNull();
			m_objEnd.m_ptrPrev = &m_objHead;
			m_objEnd.m_blnEnd = true;

		};

		//!Virtual destructor
		virtual ~HtlListMap(void)
		{
			clear();
		};
		//TEMPLATE MEMBER FUNCTIONS TO BE DEFINED BELOW
		//COMMENTED PROTOTYPES SHOWN FOR COMPACTNESS
		//!Vector size related methods
		//virtual size_t size(void) const;
		//virtual size_t count(void) const;
		//virtual void recount(void);
		//virtual bool isEmpty(void) const;
		//virtual size_t capacity(void) const;
		//!Clears the container
		//virtual void clear();
		//!Vector resizing related methods
		//virtual void resize(int size);
		//virtual void reserve(int size);

		//!Access to the actual data pointers
		//virtual TObj *Get_ptrData();

		//!Item accessor functions
		//virtual TObj &at(size_t i) ;
		//virtual const TObj &at(size_t i) const;
		//virtual TObj &operator[](size_t i);
		//virtual const TObj &operator[](size_t i) const;

		////Item Insertion and Removal member functions
		//virtual void append(const TObj &ptrObj);
		//virtual void prepend(const TObj &ptrObj);

		//Iterator insert( Iterator before, size_t n, const TObj &t);
		//inline void insert(Iterator before, const TObj &x){return insert(before,1,t);};

		//Iterator erase(Iterator begin,Iterator end);
		//inline Iterator erase(Iterator pos){return erase(pos, pos+1);};

		//inline Iterator begin() { return m_ptrData->m_arrObj; };
		//inline ConstIterator beginConst() const { return m_ptrData->m_arrObj; };
		//inline Iterator end() { return m_ptrData->m_arrObj + m_ptrData->m_intSize; };
		//inline ConstIterator endConst() const { return m_ptrData->m_arrObj + m_ptrData->m_intSize; };

		//inline Reference front() { return m_ptrData->m_arrObj; };
		//inline ConstReference front() const { return m_ptrData->m_arrObj; };
		//inline Reference back() {return m_ptrData->m_arrObj + (m_ptrData->m_intSize - 1); };
		//inline ConstReference back() const { return m_ptrData->m_arrObj + (m_ptrData->m_intSize - 1); };

		//inline void push_back(const TObj &t) { insert(t); };
		//inline void push_front(const TObj &t) { insert(t); };
		//void pop_back() { if(!isEmpty()){erase(end()-1);};};
		//void pop_front() { if(!isEmpty()){ erase(begin());};};

	protected:
		//!THIS IS THE POINTER TO THE ACTUAL VECTOR DATA THAT IS BEING MANAGED
		//the current cursor iterator
		HtlTreeNode<TKey, TObj> * m_ptrCursor;

		char m_chrNull;

		//!Size of the Tree character
		size_t m_intSize;

		HtlTreeNode<TKey, TObj> m_objSharedNull;

		//!This is the end node of the doubly linked vector tree
		HtlTreeNode<TKey, TObj> m_objEnd;
		//!This is the head that of the doubly linked vector tree
		HtlTreeNode<TKey, TObj> m_objHead;
	protected:

		//TEMPLATE MEMBER VARIABLE DECLARATION AND DEFINITION//////////////////////////////////
	public:
		//!HTL Container Analyzers
		//!Returns the length of the string minus the null terminator (\0)
		virtual size_t size(void) const
		{
			return this->m_intSize;
		};

		//!Returns the length of the string minus the null terminator (\0)
		virtual size_t count(void) const
		{
			return this->m_intSize;
		};

		//!Forces a recount of the length of the string minus the null terminator (\0)
		virtual void recount(void)
		{
			try
			{
				size_t intCounter = 0;
				HtlTreeNode<TKey, TObj> * ptrCounter;

				ptrCounter = &m_objHead;

				while ((ptrCounter->m_ptrNext != &m_objEnd) &&
					(ptrCounter->m_ptrNext != NULL))
				{
					intCounter++;
					ptrCounter = ptrCounter->m_ptrNext;
				}

				//assign new counter
				this->m_intSize = intCounter;
				return;
			}
			catch (...)
			{
				std::string errMsg;
				errMsg = "HtlListMap recount Error thrown";
				throw std::exception(errMsg.c_str());
			}
		};

		//!Returns if the map is empty
		virtual bool isEmpty(void) const
		{
			//safety check
			if (this->m_intSize <= 0)
			{
				return true;
			}
			else { return false; };

			return true;
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
				size_t intNumItems = size();
				if (intNumItems > 0)
				{
					HtlTreeNode<TKey, TObj>* ptrCurrNode = m_objHead.m_ptrNext;
					HtlTreeNode<TKey, TObj>* ptrNextNode = NULL;
					while ((ptrCurrNode != &m_objEnd) && (ptrCurrNode != NULL))
					{
						//get the next node
						ptrNextNode = ptrCurrNode->m_ptrNext;
						delete ptrCurrNode;
						ptrCurrNode = ptrNextNode;
					};
				};
				m_objHead.m_ptrNext = &m_objEnd;
				m_objEnd.m_ptrPrev = &m_objHead;
				m_intSize = 0;
				m_objLock.unlock(objNullID);

				return;
			}
			catch (...)
			{
				std::string errMsg;
				errMsg = "HtlListMap clear Error thrown";
				throw std::exception(errMsg.c_str());
			}
		};


		//!HTL container accessors
		virtual TKey & atkey(size_t i)
		{
			try
			{
				memset(&m_keyNull, 0, sizeof(TKey));
				//since the vector access is a doubly linked list and not aligned memory
				//we have to start at the head and cycle until we have reached location i.
				if (!m_objHead.m_ptrNext) { return m_keyNull; };
				if (i < this->m_intSize)
				{
					HtlTreeNode<TKey, TObj>* ptrCurrNode = &m_objHead;
					size_t j;
					for (j = 0; j <= i; j++)
					{
						if (!ptrCurrNode) { return m_keyNull; };
						ptrCurrNode = ptrCurrNode->m_ptrNext;
					};
					return (ptrCurrNode->m_objKey);
				}
				else {
					//invalid index return NULL
					return m_keyNull;
				};
				return m_keyNull;
			}
			catch (...)
			{
				std::string errMsg;
				errMsg = "HtlListMap atkey Error thrown";
				throw std::exception(errMsg.c_str());
			}
		};


		virtual TObj & at(size_t i)
		{
			try
			{
				//since the vector access is a doubly linked list and not aligned memory
				//we have to start at the head and cycle until we have reached location i.
				if (!m_objHead.m_ptrNext) { return m_objNull; };
				if (i < this->m_intSize)
				{
					HtlTreeNode<TKey, TObj>* ptrCurrNode = &m_objHead;
					size_t j;
					for (j = 0; j <= i; j++)
					{
						if (!ptrCurrNode) { return m_objNull; };
						ptrCurrNode = ptrCurrNode->m_ptrNext;
					};
					return (ptrCurrNode->m_objData);
				}
				else {
					//invalid index return NULL
					return m_objNull;
				};
				return m_objNull;
			}
			catch (...)
			{
				std::string errMsg;
				errMsg = "HtlListMap at Error thrown";
				throw std::exception(errMsg.c_str());
			}
		};
		//!HTL container accessor operator
		virtual TObj & operator[](size_t i)
		{
			try
			{
				//since the vector access is a doubly linked list and not aligned memory
				//we have to start at the head and cycle until we have reached location i.
				if (!m_objHead.m_ptrNext) { return m_objNull; };
				if (i < this->m_intSize)
				{
					HtlTreeNode<TKey, TObj>* ptrCurrNode = &m_objHead;
					size_t j;
					for (j = 0; j <= i; j++)
					{
						if (!ptrCurrNode) { return m_objNull; };
						ptrCurrNode = ptrCurrNode->m_ptrNext;
					};
					if (ptrCurrNode)
					{
						return (ptrCurrNode->m_objData);
					}
					else {
						return m_objNull;
					};
				}
				else {
					//invalid index return NULL
					return m_objNull;
				};
				return m_objNull;
			}
			catch (...)
			{
				std::string errMsg;
				errMsg = "HtlListMap at Error thrown";
				throw std::exception(errMsg.c_str());
			}
		};


		//!Inserts a node into the tree
		int insert(TKey &key, TObj &item)
		{
			try
			{
				//safety checks
				m_objPrint.DebugPrint(1, "\nHtlListMap::insert()\n");
				bool blnNewNode = false;
				HtlGUID128 objNullID;
				objNullID.newID();
				m_objLock.lock(objNullID);

				HtlTreeNode<TKey, TObj>* ptrExistNode = NULL;
				HtlTreeNode<TKey, TObj>* ptrCursor = NULL;
				//FIRST SEARCH FOR A MATCH
				m_objPrint.DebugPrint(1, "Check to see if already in map.\n");
				ptrExistNode = this->find(key);
				if (ptrExistNode)
				{
					//then match found, update the data for that key
					//m_objPrint.DebugPrint(1,"Existing %s\n", ptrExistNode->m_objKey.toStdString().c_str());
					ptrExistNode->m_objData = item;
					m_objLock.unlock(objNullID);
					return 2;
				}
				//create and insert new element
				HtlTreeNode<TKey, TObj> * ptrNewNode = new HtlTreeNode<TKey, TObj>();

				ptrNewNode->m_objKey = key;
				ptrNewNode->m_objData = item;

				//insert into doubly linked list via pushback
				HtlTreeNode<TKey, TObj>* ptrBegin = m_objEnd.m_ptrPrev;

				ptrNewNode->m_ptrPrev = ptrBegin;
				ptrBegin->m_ptrNext = ptrNewNode;

				ptrNewNode->m_ptrNext = &m_objEnd;
				m_objEnd.m_ptrPrev = ptrNewNode;

				m_intSize++;
				m_objPrint.DebugPrint(1, "Map size %02d\n", m_intSize);
				m_objLock.unlock(objNullID);
				return 1;
			}
			catch (...)
			{
				std::string errMsg;
				errMsg = "HtlListMap insert Error thrown";
				throw std::exception(errMsg.c_str());
			}
		};



		//!Erases a node from the tree
		int erase(TKey & key)
		{
			try
			{
				//safety checks
				bool blnPlaced = false;
				bool blnNewNode = false;
				HtlGUID128 objNullID;
				objNullID.newID();

				HtlTreeNode<TKey, TObj>* ptrCurrNode = NULL;
				ptrCurrNode = this->find(key);
				if (!ptrCurrNode) { return 0; };

				m_objLock.lock(objNullID);
				//create and insert new element
				//insert into doubly linked list
				HtlTreeNode<TKey, TObj>* ptrBegin = ptrCurrNode->m_ptrPrev;
				HtlTreeNode<TKey, TObj>* ptrAfter = ptrCurrNode->m_ptrNext;
				//safety checks
				if (ptrCurrNode == &m_objEnd)
				{
					m_objLock.unlock(objNullID);
					return -1;
				};
				if (ptrCurrNode == &m_objHead)
				{
					m_objLock.unlock(objNullID);
					return -1;
				};


				delete ptrCurrNode;
				ptrBegin->m_ptrNext = ptrAfter;
				ptrAfter->m_ptrPrev = ptrBegin;
				m_intSize--;

				m_objLock.unlock(objNullID);
				return 1;
			}
			catch (...)
			{
				std::string errMsg;
				errMsg = "HtlListMap erase Error thrown";
				throw std::exception(errMsg.c_str());
			}
		};

		//
		//!Returns the beginning node of the linked list and sets the cursor to that node.
		HtlTreeNode<TKey, TObj> * begin(void)
		{
			try
			{
				m_ptrCursor = &m_objHead;
				return &m_objHead;
			}
			catch (...)
			{
				std::string errMsg;
				errMsg = "HtlListMap begin Error thrown";
				throw std::exception(errMsg.c_str());
			}
		};
		//!Returns the end node
		HtlTreeNode<TKey, TObj> *  end(void)
		{
			try
			{
				return &m_objEnd;
			}
			catch (...)
			{
				std::string errMsg;
				errMsg = "HtlListMap end Error thrown";
				throw std::exception(errMsg.c_str());
			}
		};

		//!Advances the cursor to the next available node in the linked list
		HtlTreeNode<TKey, TObj> * next(void)
		{
			try
			{
				if (m_ptrCursor)
				{
					m_ptrCursor = m_ptrCursor->m_ptrNext;
					if (!m_ptrCursor)
					{
						return end();
					};
					return m_ptrCursor;
				};
				return end();
			}
			catch (...)
			{
				std::string errMsg;
				errMsg = "HtlListMap next Error thrown";
				throw std::exception(errMsg.c_str());
			}
		};

		//!Rewinds the cursor to the previous available node in the linked list
		HtlTreeNode<TKey, TObj> * previous(void)
		{
			try
			{
				if (m_ptrCursor)
				{
					m_ptrCursor = m_ptrCursor->m_ptrPrev;
					return m_ptrCursor;
				};
				return NULL;
			}
			catch (...)
			{
				std::string errMsg;
				errMsg = "HtlListMap next Error thrown";
				throw std::exception(errMsg.c_str());
			}
		};
		//!Returns the current cursor location key
		TKey cursorKey(void)
		{
			try
			{
				if (m_ptrCursor)
				{
					return m_ptrCursor->m_objKey;
				};
			}
			catch (...)
			{
				std::string errMsg;
				errMsg = "HtlListMap next Error thrown";
				throw std::exception(errMsg.c_str());
			}
		};
		//!Returns the current cursor location value
		Reference cursorValue(void)
		{
			try
			{
				if (m_ptrCursor)
				{
					return m_ptrCursor->m_arrObj;
				};
			}
			catch (...)
			{
				std::string errMsg;
				errMsg = "HtlListMap cursorValue Error thrown";
				throw std::exception(errMsg.c_str());
			}
		};


		Reference front(void)
		{
			try
			{
				if (m_objHead.m_ptrNext)
				{
					return (m_objHead.m_ptrNext->m_arrObj);
				};
				return m_objNull;
			}
			catch (...)
			{
				std::string errMsg;
				errMsg = "HtlListMap front Error thrown";
				throw std::exception(errMsg.c_str());
			}
		};
		ConstReference front(void) const
		{
			try
			{
				if (m_objHead.m_ptrNext)
				{
					return (m_objHead.m_ptrNext->m_arrObj);
				};
				return m_objNull;
			}
			catch (...)
			{
				std::string errMsg;
				errMsg = "HtlListMap front Error thrown";
				throw std::exception(errMsg.c_str());
			}
		};
		Reference back(void)
		{
			try
			{
				if (m_objEnd.m_ptrPrev)
				{
					return (m_objEnd.m_ptrPrev->m_arrObj);
				};
				return m_objNull;
			}
			catch (...)
			{
				std::string errMsg;
				errMsg = "HtlListMap back Error thrown";
				throw std::exception(errMsg.c_str());
			}
		};
		ConstReference back(void) const
		{
			try
			{
				if (m_objEnd.m_ptrPrev)
				{
					return (m_objEnd.m_ptrPrev->m_arrObj);
				};
				return m_objNull;
			}
			catch (...)
			{
				std::string errMsg;
				errMsg = "HtlListMap back Error thrown";
				throw std::exception(errMsg.c_str());
			}
		};
		void push_back(TKey &key, TObj &item)
		{
			try
			{
				//safety checks
				m_objPrint.DebugPrint(1, "\nHtlListMap::insert()\n");
				HtlGUID128 objNullID;
				objNullID.newID();
				m_objLock.lock(objNullID);

				//create and insert new element
				HtlTreeNode<TKey, TObj> * ptrNewNode = new HtlTreeNode<TKey, TObj>();

				ptrNewNode->m_objKey = key;
				ptrNewNode->m_objData = item;

				//insert into doubly linked list via pushback
				HtlTreeNode<TKey, TObj>* ptrBegin = m_objEnd.m_ptrPrev;

				ptrNewNode->m_ptrPrev = ptrBegin;
				ptrBegin->m_ptrNext = ptrNewNode;

				ptrNewNode->m_ptrNext = &m_objEnd;
				m_objEnd.m_ptrPrev = ptrNewNode;

				m_intSize++;
				if ((ptrNewNode->m_ptrPrev == NULL) || (ptrNewNode->m_ptrNext == NULL))
					LocalDebugPrint("ListMap.txt", "push_back", "error inserting new element;");

				m_objPrint.DebugPrint(1, "Map size %02d\n", m_intSize);
				m_objLock.unlock(objNullID);
				return;
			}
			catch (...)
			{
				std::string errMsg;
				errMsg = "HtlListMap pushback Error thrown";
				throw std::exception(errMsg.c_str());
			}
		};

		HtlTreeNode<TKey, TObj> * find(TKey& key)
		{	
			try
			{
				m_objPrint.DebugPrint(1, "HtlListMap::find()\n");
				bool blnMatchFound = false;
				HtlTreeNode<TKey, TObj> * ptrCursor = NULL;
				//m_objPrint.DebugPrint(1,"Searching for %s\n", key.toStdString().c_str());
				//special case, NO nodes
				if ((m_objHead.m_ptrNext == &m_objEnd) || (m_intSize <= 0))
				{
					return NULL;
				};
				ptrCursor = &m_objHead;
				m_objPrint.DebugPrint(1, "ListMap Contents\n");
				ptrCursor = ptrCursor->m_ptrNext;//first element
				while ((ptrCursor) && (ptrCursor != &m_objEnd) && (!blnMatchFound))
				{

					if (ptrCursor == &m_objEnd) { return NULL; };
					//m_objPrint.DebugPrint(1,"item %s\n", ptrCursor->m_objKey.toStdString().c_str());
					if (key == ptrCursor->m_objKey)
					{
						m_objPrint.DebugPrint(1, "MATCH FOUND!!!\n");
						blnMatchFound = true;
						//then match found  erase the node
						return ptrCursor;
					}
					else {
						ptrCursor = ptrCursor->m_ptrNext;
					};

				};
				m_objPrint.DebugPrint(1, "HtlListMap::end find()\n");
				return NULL;
			}
			catch (...)
			{
				std::string errMsg;
				errMsg = "HtlListMap find Error thrown";
				throw std::exception(errMsg.c_str());
			}
		};


	public:
		//Virtual Inheritance Serialization Engines
		//SERIALIZATION ACCESSOR MACRO///////////////////////////////////////
	//!Save the HtlListMap to the current HtlElement
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
					HtlTreeNode<TKey, TObj> * ptrCursor = NULL;
					i = 0;
					ptrCursor = begin();
					ptrCursor = next();
					while ( !blnFinished)
					{
						itoa(i,chrBuf,10);
						strIndexName = "IT_";
						strIndexName += chrBuf;
						//create the Pair Element

						HtlElement* ptrPairElement = ptrCurrNode->AddSubElement();
						ptrPairElement->Set_strName(strIndexName);
						//SOME FUNCTION FOR SETTING THE XML ITEM REGARDLESS OF TYPE
						if(ptrCursor)
						{
							TKey objKeyTemp = ptrCursor->key();
							HTL::SetHtlMemVar<TKey,TKeyEnum>(ptrPairElement,"m_objKey",objKeyTemp,blnWithSubObjects);
							TObj objValTemp = ptrCursor->value();
							HTL::SetHtlMemVar<TObj,TObjEnum>(ptrPairElement,"m_objValue",objValTemp,blnWithSubObjects);
						};
						//index cursor
						i++;
						ptrCursor = next();

						if(!ptrCursor){blnFinished = true;};
						if(ptrCursor == end()){blnFinished = true;};
					};
				};//end valid new node check
				return 1;
			}catch(...){
				std::string errMsg;
				errMsg = "HtlListMap Save Error thrown";
				throw std::exception(errMsg.c_str());
				return -1;
			};

			return intReturn;

		};
		//!Load the HtlListMap from the current HtlElement
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
							insert(objKeyTemp,objValTemp);
						};
					};
				};
				return intReturn;
			}catch(...){
				std::string errMsg;
				errMsg = "HtlListMap Load Error thrown";
				throw std::exception(errMsg.c_str());
				return -1;
			};
			return intReturn;

		};


	};//end HtlListMap class definition


	//Htl1DVector MEMBER FUNCTION DECLARATIONS
};//end namespace HTL
#endif