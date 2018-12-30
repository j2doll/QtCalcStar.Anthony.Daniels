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

#ifndef HTL_1DLIST_H
#define HTL_1DLIST_H

#include ".\HtlContainer.h"
#include ".\HtlListNode.h"

namespace HTL
{


	//!HtlList is a one dimensional doubly linked list for objects.
	/*!
	Htl1DList is a one dimensional modified AVL Tree for objects.  Htl1DList is actually a combined data structure.
	It is BOTH an AVL tree AND a doubly linked list.  Each node of the map belongs to corresponding node in the AVL Tree
	and is in the properly sorted location in the doubly linked list according to its < operator.  This allows for fast
	tree based searches, as well as the ability to cycle through the entire tree as linked list.
	*/
	template<typename TObj, HtlObjectType TObjEnum>
	class Htl1DList : public HtlContainer<size_t,CPP_INT, TObj,TObjEnum>
	{
		//typedef qptrdiff difference_type;
		typedef TObj Value;
		typedef TObj *Pointer;
		typedef TObj &Reference;
		typedef const TObj & ConstReference;
		//HtlVector1D SUBCLASS DECLARATIONS////////////////////////////////////////
		//END HTLVECTOR1D SUBCLASS DEFINITIONS///////////////////////////////////////


		//HtlVector1D CLASS DEFINITION/////////////////////////////////////////
	public:

		//!Void constructor
		Htl1DList() : HtlContainer()
		{
			m_strType.clear();
			m_intSize = 0;
			m_objType = HTL_CONTAINER;
			m_strType = "Htl1DList";
			m_itemType = TObjEnum;
			m_chrNull = '\0';
			m_objHead.m_ptrNext = &m_objEnd;
			m_objEnd.m_ptrPrev = &m_objHead;
			m_ptrCursor = NULL;
		};

		//!Virtual destructor
		virtual ~Htl1DList(void)
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

		//the current cursor iterator
		HtlListNode<TObj> * m_ptrCursor;

		char m_chrNull;

		//!Size of the List number of objects
		size_t m_intSize;

		static HtlListNode<TObj>  m_objSharedNull;

		//!This is the end node of the doubly linked vector tree
		HtlListNode<TObj> m_objEnd;
		//!This is the head that of the doubly linked vector tree
		HtlListNode<TObj>m_objHead;
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
				HtlListNode<TObj> * ptrCounter;

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
				errMsg = "Htl1DList Recount Error thrown";
				throw std::exception(errMsg.c_str());
			}
		};

		//!Returns if the map is empty
		virtual bool isEmpty(void) const
		{
			//safety check
			if(this->m_intSize <= 0)
			{return true;}else{return false;};
			//shouldn't get here
			return true;
		};
		//

		//!Clears the container
		virtual void clear(void)
		{
			try
			{
				//lock the container before modifying it
				HtlGUID128 objNullID;
				objNullID.newID();
				m_objLock.lock(objNullID);
				if (size() > 0)
				{
					HtlListNode<TObj>* ptrCurrNode = m_objHead.m_ptrNext;
					HtlListNode<TObj>* ptrNextNode = NULL;
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
				errMsg = "Htl1DList Clear Error thrown";
				throw std::exception(errMsg.c_str());
			}
		};


		//!HTL container accessors
		virtual TObj & at(size_t i)
		{
			try
			{
				//since the vector access is a doubly linked list and not aligned memory
				//we have to start at the head and cycle until we have reached location i.
				if (!m_objHead.m_ptrNext) { return m_objNull; };
				if (i < this->m_intSize)
				{
					HtlListNode<TObj>* ptrCurrNode = &m_objHead;
					size_t j;
					for (j = 0; j <= i; j++)
					{
						if (!ptrCurrNode) { return m_objNull; };
						ptrCurrNode = ptrCurrNode->m_ptrNext;
					};
					return (ptrCurrNode->m_data);
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
				errMsg = "Htl1DList At Error thrown";
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
					HtlListNode<TObj>* ptrCurrNode = &m_objHead;
					size_t j;
					for (j = 0; j <= i; j++)
					{
						if (!ptrCurrNode) { return m_objNull; };
						ptrCurrNode = ptrCurrNode->m_ptrNext;
					};
					if (ptrCurrNode)
					{
						return (ptrCurrNode->m_data);
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
				errMsg = "Htl1DList At Error thrown";
				throw std::exception(errMsg.c_str());
			}
		};


		//!Inserts a node into the tree
		int insert(size_t indexBefore,TObj &item)	
		{
			try
			{
				//safety checks
				bool blnPlaced = false;
				bool blnNewNode = false;
				HtlGUID128 objNullID;
				objNullID.newID();
				m_objLock.lock(objNullID);
				HtlListNode<TObj>* ptrCurrNode = NULL;
				//safety check on index
				if ((indexBefore < 0) || (indexBefore >= m_intSize)) { return -1; };//outside of bounds
				//get the cursor location to insert before
				if (indexBefore < this->m_intSize)
				{
					ptrCurrNode = &m_objHead;
					size_t j;
					for (j = 0; j <= indexBefore; j++)
					{
						if (!ptrCurrNode) { return -1; };
						ptrCurrNode = ptrCurrNode->m_ptrNext;
					};
				}
				//create and insert new element

				HtlListNode<TObj> * ptrNewNode = new HtlListNode<TObj>();
				ptrNewNode->m_data = item;
				//insert into doubly linked list
				HtlListNode<TObj>* ptrBegin = ptrCurrNode->m_ptrPrev;

				ptrNewNode->m_ptrPrev = ptrBegin;
				ptrBegin->m_ptrNext = ptrNewNode;

				ptrNewNode->m_ptrNext = ptrCurrNode;
				ptrCurrNode->m_ptrPrev = ptrNewNode;

				m_intSize++;

				m_objLock.unlock(objNullID);
				return 1;
			}
			catch (...)
			{
				std::string errMsg;
				errMsg = "Htl1DList insert Error thrown";
				throw std::exception(errMsg.c_str());
			}
		};



		//!Erases a node from the tree
		int erase(size_t index)
		{
			try
			{
				//safety checks
				bool blnPlaced = false;
				bool blnNewNode = false;
				HtlGUID128 objNullID;
				objNullID.newID();
				m_objLock.lock(objNullID);
				HtlListNode<TObj>* ptrCurrNode = NULL;
				//safety check on index
				if ((index < 0) || (index >= m_intSize)) { return -1; };//outside of bounds
				//get the cursor location to insert before
				if (index < this->m_intSize)
				{
					ptrCurrNode = &m_objHead;
					size_t j;
					for (j = 0; j <= index; j++)
					{
						if (!ptrCurrNode) { return -1; };
						ptrCurrNode = ptrCurrNode->m_ptrNext;
					};
				}
				//create and insert new element
				//insert into doubly linked list
				HtlListNode<TObj>* ptrBegin = ptrCurrNode->m_ptrPrev;
				HtlListNode<TObj>* ptrAfter = ptrCurrNode->m_ptrNext;
				//safety checks
				if (ptrCurrNode == &m_objEnd) { return -1; };
				if (ptrCurrNode == &m_objHead) { return -1; };

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
				errMsg = "Htl1DList erase Error thrown";
				throw std::exception(errMsg.c_str());
			}
		};

		//
		//!Returns the beginning node of the linked list and sets the cursor to that node.
		HtlListNode<TObj> * begin(void) 
		{ 
			try
			{
				m_ptrCursor = &m_objHead;
				return &m_objHead;
			}
			catch (...)
			{
				std::string errMsg;
				errMsg = "Htl1DList begin Error thrown";
				throw std::exception(errMsg.c_str());
			}
		};
		//!Returns the end node
		HtlListNode<TObj> *  end(void) 
		{
			try
			{
				return &m_objEnd;
			}
			catch (...)
			{
				std::string errMsg;
				errMsg = "Htl1DList end Error thrown";
				throw std::exception(errMsg.c_str());
			}
		};

		//!Advances the cursor to the next available node in the linked list
		HtlListNode<TObj> * next(void)
		{
			try
			{
				if (m_ptrCursor)
				{
					m_ptrCursor = m_ptrCursor->m_ptrNext;
					return m_ptrCursor;
				};
				return NULL;
			}
			catch (...)
			{
				std::string errMsg;
				errMsg = "Htl1DList next Error thrown";
				throw std::exception(errMsg.c_str());
			}
		};

		//!Rewinds the cursor to the previous available node in the linked list
		HtlListNode<TObj> * previous(void)
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
				errMsg = "Htl1DList previous Error thrown";
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
					return m_ptrCursor->m_data;
				};
			}
			catch (...)
			{
				std::string errMsg;
				errMsg = "Htl1DList cursorValue Error thrown";
				throw std::exception(errMsg.c_str());
			}
		};


		Reference front(void) 
		{ 
			try
			{
				if (m_objHead.m_ptrNext)
				{
					return (m_objHead.m_ptrNext->m_data);
				};
				return m_objNull;
			}
			catch (...)
			{
				std::string errMsg;
				errMsg = "Htl1DList front Error thrown";
				throw std::exception(errMsg.c_str());
			}
		};
		ConstReference front(void) const 
		{
			try
			{
				if (m_objHead.m_ptrNext)
				{
					return (m_objHead.m_ptrNext->m_data);
				};
				return m_objNull;
			}
			catch (...)
			{
				std::string errMsg;
				errMsg = "Htl1DList front Error thrown";
				throw std::exception(errMsg.c_str());
			}
		};

		Reference back(void) 
		{
			try
			{
				if (m_objEnd.m_ptrPrev)
				{
					return (m_objEnd.m_ptrPrev->m_data);
				};
				return m_objNull;
			}
			catch (...)
			{
				std::string errMsg;
				errMsg = "Htl1DList back Error thrown";
				throw std::exception(errMsg.c_str());
			}
		};

		ConstReference back(void) const
		{
			try
			{
				if (m_objEnd.m_ptrPrev)
				{
					return (m_objEnd.m_ptrPrev->m_data);
				};
				return m_objNull;
			}
			catch (...)
			{
				std::string errMsg;
				errMsg = "Htl1DList back Error thrown";
				throw std::exception(errMsg.c_str());
			}
		};

		void push_back(TObj item)
		{
			try
			{

				if (m_intSize <= 0)
				{
					//reinforce beginning state
					m_objHead.m_ptrNext = &m_objEnd;
					m_objEnd.m_ptrPrev = &m_objHead;
				}

				//safety checks
				HtlGUID128 objNullID;
				objNullID.newID();
				m_objLock.lock(objNullID);
				HtlListNode<TObj>* ptrCurrNode = NULL;
				ptrCurrNode = m_objEnd.m_ptrPrev;
				//create and insert new element

				HtlListNode<TObj> * ptrNewNode = new HtlListNode<TObj>();
				if (ptrNewNode == NULL) { return; };
				ptrNewNode->m_data = item;
				//insert into doubly linked list
				ptrCurrNode->m_ptrNext = ptrNewNode;
				ptrNewNode->m_ptrPrev = ptrCurrNode;

				m_objEnd.m_ptrPrev = ptrNewNode;
				ptrNewNode->m_ptrNext = &m_objEnd;

				m_intSize++;

				m_objLock.unlock(objNullID);
				return;
			}
			catch (...)
			{
				std::string errMsg;
				errMsg = "Htl1DList push_back Error thrown";
				throw std::exception(errMsg.c_str());
			}
		};


		void push_front(TObj item)
		{
			try
			{
				if (m_intSize <= 0)
				{
					//reinforce beginning state
					m_objHead.m_ptrNext = &m_objEnd;
					m_objEnd.m_ptrPrev = &m_objHead;
				}

				//safety checks
				HtlGUID128 objNullID;
				objNullID.newID();
				m_objLock.lock(objNullID);
				HtlListNode<TObj>* ptrCurrNode = NULL;
				ptrCurrNode = m_objHead.m_ptrNext;
				//create and insert new element

				HtlListNode<TObj> * ptrNewNode = new HtlListNode<TObj>();
				if (ptrNewNode == NULL) { return; };
				ptrNewNode->m_data = item;
				//insert into doubly linked list
				m_objHead.m_ptrNext = ptrNewNode;
				ptrNewNode->m_ptrPrev = &m_objHead;

				ptrCurrNode->m_ptrPrev = ptrNewNode;
				ptrNewNode->m_ptrNext = ptrCurrNode;

				m_intSize++;

				m_objLock.unlock(objNullID);
				return;
			}
			catch (...)
			{
				std::string errMsg;
				errMsg = "Htl1DList push_front Error thrown";
				throw std::exception(errMsg.c_str());
			}
		};

		void pop_back()
		{
			try
			{
				//safety checks
				HtlGUID128 objNullID;
				objNullID.newID();
				m_objLock.lock(objNullID);
				HtlListNode<TObj>* ptrCurrNode = NULL;
				ptrCurrNode = m_objEnd.m_ptrPrev;
				if (ptrCurrNode == NULL) { return; };
				if (ptrCurrNode == &m_objHead) { return; };

				HtlListNode<TObj>* ptrBegin = ptrCurrNode->m_ptrPrev;
				if (ptrBegin == NULL) { return; };

				ptrBegin->m_ptrNext = &m_objEnd;
				m_objEnd.m_ptrPrev = ptrBegin;

				delete ptrCurrNode;
				m_intSize--;

				m_objLock.unlock(objNullID);
				return;
			}
			catch (...)
			{
				std::string errMsg;
				errMsg = "Htl1DList pop_back Error thrown";
				throw std::exception(errMsg.c_str());
			}
		};

		void pop_front()
		{
			try
			{
				//safety checks
				HtlGUID128 objNullID;
				objNullID.newID();
				m_objLock.lock(objNullID);
				HtlListNode<TObj>* ptrCurrNode = NULL;
				ptrCurrNode = m_objHead.m_ptrNext;
				if (ptrCurrNode == NULL) { return; };
				if (ptrCurrNode == &m_objEnd) { return; };

				HtlListNode<TObj>* ptrAfter = ptrCurrNode->m_ptrNext;
				if (ptrAfter == NULL) { return; };

				ptrAfter->m_ptrPrev = &m_objHead;
				m_objHead.m_ptrNext = ptrAfter;

				delete ptrCurrNode;
				m_intSize--;

				m_objLock.unlock(objNullID);
				return;
			}
			catch (...)
			{
				std::string errMsg;
				errMsg = "Htl1DList pop_front Error thrown";
				throw std::exception(errMsg.c_str());
			}
		};


public:
		//Virtual Inheritance Serialization Engines
		//SERIALIZATION ACCESSOR MACRO///////////////////////////////////////
	//!Save the Htl1DList to the current HtlElement
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
					HtlListNode<TObj> * ptrCursor = NULL;
					i = 0;
					ptrCursor = begin();
					ptrCursor = next();
					while ( !blnFinished)
					{
						itoa(i,chrBuf,10);
						strIndexName = "IT_";
						strIndexName += chrBuf;
						//SOME FUNCTION FOR SETTING THE XML ITEM REGARDLESS OF TYPE
						HTL::SetHtlMemVar<TObj,TObjEnum>(ptrCurrNode,strIndexName,
							ptrCursor->m_data,blnWithSubObjects);
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
				errMsg = "Htl1DList Save Error thrown";
				throw std::exception(errMsg.c_str());
				return -1;
			};

			return intReturn;

		};
		//!Load the Htl1DList from the current HtlElement
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
							strIndexName = ptrCurrElement->Get_strName();
							//T objVal = at(i);
							ptrCurrAttribute = ptrCurrElement->GetAttribute(HTL_strTYPE);
							if(ptrCurrAttribute)
							{
								strItemTypeName = ptrCurrAttribute->Get_strValue();
							};

							TObj objTemp;
							HTL::SetDefaultVal<TObj>(objTemp);

							//then use object factory to create the item since the item is currently NULL
							//HTL::CreateObject<T,TSubObj>(strItemTypeName,objTemp);
							//take the newly created object and de-serialize it with the XML data
							intTemp = HTL::GetHtlMemVar<TObj,TObjEnum>(ptrCurrNode,strIndexName,objTemp);
							if(intTemp < 0){intReturn = -1;};
							push_back(objTemp);
						};
					};
				};
				return intReturn;
			}catch(...){
				std::string errMsg;
				errMsg = "Htl1DList Load Error thrown";
				throw std::exception(errMsg.c_str());
				return -1;
			};
			return intReturn;

		};


	};//end Htl1DList class definition


	//Htl1DVector MEMBER FUNCTION DECLARATIONS
};//end namespace HTL
#endif