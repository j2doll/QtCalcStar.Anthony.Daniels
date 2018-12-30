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

#ifndef HTL_MAP_H
#define HTL_MAP_H

#include ".\HtlContainer.h"
#include ".\HtlTreeNode.h"

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
	class HtlMap : public HtlContainer<TKey,TKeyEnum,TObj,TObjEnum>
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
		HtlMap() : HtlContainer()
		{
			m_intSize = 0;
			m_objType = HTL_CONTAINER;
			m_strType = "HtlMap";
			m_itemType = TObjEnum;
			m_chrNull = '\0';
			m_objHead.setNull();
			m_objHead.m_ptrNext = &m_objEnd;

			m_objEnd.setNull();
			m_objEnd.m_ptrPrev = &m_objHead;

			m_ptrRoot = NULL;
			std::string strName = "HtlMap.txt";
			m_objDebug.Set_strFileName(strName);
			m_objDebug.Set_blnPrintToFile(true);

			//COMMENT OUT TO ENABLE DEBUG PRINTING
			m_objDebug.Disable();

		};

		//!Virtual destructor
		virtual ~HtlMap(void)
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
		HtlTreeNode<TKey,TObj> * m_ptrRoot;
		//the current cursor iterator
		HtlTreeNode<TKey,TObj> * m_ptrCursor;

		char m_chrNull;

		//!Size of the Tree character
		size_t m_intSize;

		static HtlTreeNode<TKey,TObj>  m_objSharedNull;

		//!This is the end node of the doubly linked vector tree
		HtlTreeNode<TKey,TObj> m_objEnd;
		//!This is the head that of the doubly linked vector tree
		HtlTreeNode<TKey,TObj> m_objHead;
	protected:

		//TEMPLATE MEMBER VARIABLE DECLARATION AND DEFINITION//////////////////////////////////
	public:
		//!HTL Container Analyzers
		//!Returns the length of the string minus the null terminator (\0)
		virtual size_t size(void) const
		{
			if(!m_ptrRoot){return 0;};
			return this->m_intSize;
		};

		//!Returns the length of the string minus the null terminator (\0)
		virtual size_t count(void) const
		{
			if(!m_ptrRoot){return 0;};
			return this->m_intSize;
		};

		//!Forces a recount of the length of the string minus the null terminator (\0)
		virtual void recount(void)
		{
			try
			{
				size_t intCounter = 0;
				//safety check
				if (!m_ptrRoot) { return; };
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
				errMsg = "HtlMap recount Error thrown";
				throw std::exception(errMsg.c_str());
			}
		};

		//!Returns if the map is empty
		virtual bool isEmpty(void) const
		{
			try
			{
				//safety check
				if (!m_ptrRoot) { return true; };

				if (this->m_intSize <= 0)
				{
					return true;
				}
				else { return false; };

				return true;
			}
			catch (...)
			{
				std::string errMsg;
				errMsg = "HtlMap recount Error thrown";
				throw std::exception(errMsg.c_str());
			}
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
				if (size() > 0)
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
				m_ptrRoot = NULL;
				m_intSize = 0;

				m_objLock.unlock(objNullID);

				return;
			}
			catch (...)
			{
				std::string errMsg;
				errMsg = "HtlMap clear Error thrown";
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
				errMsg = "HtlMap at Error thrown";
				throw std::exception(errMsg.c_str());
			}
		};

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
				errMsg = "HtlMap atkey Error thrown";
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
				errMsg = "HtlMap at[] Error thrown";
				throw std::exception(errMsg.c_str());
			}
		};


		//!Inserts a node into the tree
		int insert(TKey &key, TObj &item)	
		{
			try
			{
				m_objDebug.DebugPrint(1, "\nHtlMap::insert()\n");
				//safety checks
				bool blnPlaced = false;
				bool blnNewNode = false;
				HtlGUID128 objNullID;
				objNullID.newID();
				m_objLock.lock(objNullID);

				if (m_ptrRoot)
				{
					//see if existing node
					HtlTreeNode<TKey, TObj> * ptrFound = findNode(m_ptrRoot, key);
					if (ptrFound)
					{
						m_objDebug.DebugPrint(1, "existing node, updating item\n");
						//then node already exists, overwrite the object data and quit
						ptrFound->m_objData = item;
						//already existing assignment
						m_objLock.unlock(objNullID);
						return 2;
					}
				}
				//Not already existing, insert it
				//Insert into the Linked List first
				m_objDebug.DebugPrint(1, "Insert into the Linked List\n");
				HtlTreeNode<TKey, TObj>* ptrCursor = NULL;
				ptrCursor = m_objHead.m_ptrNext;

				while ((key > ptrCursor->m_objKey) &&
					(ptrCursor != &m_objEnd))
				{
					ptrCursor = ptrCursor->m_ptrNext;
				}
				//we have found the insert point
				m_objDebug.DebugPrint(1, "Insert point found ptrCursor %p\n", ptrCursor);
				m_objDebug.DebugPrint(1, "ptrHead %p ptrEnd %p\n", &m_objHead, &m_objEnd);
				m_objDebug.DebugPrint(1, "keyHead %d keyEnd %d\n", m_objHead.m_objKey, m_objEnd.m_objKey);
				//make the new node
				HtlTreeNode<TKey, TObj>* ptrNewNode = new HtlTreeNode<TKey, TObj>();
				ptrNewNode->m_objKey = key;
				ptrNewNode->m_objData = item;
				m_objDebug.DebugPrint(1, "NEW Node Created %p\n", ptrNewNode);
				HtlTreeNode<TKey, TObj>* ptrBegin = NULL;
				ptrBegin = ptrCursor->m_ptrPrev;
				//make the insert
				m_objDebug.DebugPrint(1, "step01: ptrBegin %p \n", ptrBegin);
				ptrBegin->m_ptrNext = ptrNewNode;
				ptrNewNode->m_ptrPrev = ptrBegin;
				m_objDebug.DebugPrint(1, "step02 ptrCursor %p\n", ptrCursor);
				ptrNewNode->m_ptrNext = ptrCursor;
				ptrCursor->m_ptrPrev = ptrNewNode;
				m_objDebug.DebugPrint(1, "step03\n", ptrNewNode);
				m_intSize++;//increment counter
				m_objDebug.DebugPrint(1, "Insert it into the tree\n");
				//now insert it into the tree
				if (!m_ptrRoot)
				{
					m_ptrRoot = ptrNewNode;
					blnPlaced = true;
					//new root item
				}
				else {
					blnPlaced = placeNode(m_ptrRoot, ptrNewNode);
					if (blnPlaced)
					{
						//update the height differentials and balance the new tree model
						m_objDebug.DebugPrint(1, "update sync tree\n");
						this->updateSync();
					};
				};
				m_objLock.unlock(objNullID);
				return 1;
			}
			catch (...)
			{
				std::string errMsg;
				errMsg = "HtlMap atkey Error thrown";
				throw std::exception(errMsg.c_str());
			}
		};


		//!Erases a node from the tree
		int erase(TKey key)
		{
			try
			{
				m_objDebug.DebugPrint(1, "\nHtlMap::erase()\n");
				if (!m_ptrRoot) { return 0; };
				bool blnErased = false;
				HtlGUID128 objNullID;
				objNullID.newID();
				m_objLock.lock(objNullID);
				m_objDebug.DebugPrint(1, "finding node...\n");
				HtlTreeNode<TKey, TObj> * ptrFound = findList(key);

				if (ptrFound)
				{
					m_objDebug.DebugPrint(1, "NodeFound...%p\n", ptrFound);
					HtlTreeNode<TKey, TObj> * ptrParent = ptrFound->m_ptrParent;
					//then node already exists,
					//delete the node and collapse the tree nodes about the point, then balanceMap
					if (ptrParent)
					{
						m_objDebug.DebugPrint(1, "has parent...\n");
						//remove node from parent
						if (ptrFound->isLeft())
						{
							m_objDebug.DebugPrint(1, "isLeft...\n");
							ptrParent->m_ptrLeft = NULL;
						};
						if (ptrFound->isRight())
						{
							m_objDebug.DebugPrint(1, "isRight...\n");
							ptrParent->m_ptrRight = NULL;
						};
						//place sub nodes
						if (ptrFound->m_ptrLeft)
						{
							//node being erased has a left node that needs placing
							m_objDebug.DebugPrint(1, "placing left...\n");
							placeNode(m_ptrRoot, ptrFound->m_ptrLeft);
						};
						if (ptrFound->m_ptrRight)
						{
							//node being erased has a left node that needs placing
							m_objDebug.DebugPrint(1, "placing right...\n");
							placeNode(m_ptrRoot, ptrFound->m_ptrRight);
						};
						//Delete the node now that parent relationship and children
						//have been stitched into the tree without the node being erased
						//erase if rom the doubly linked list
						m_objDebug.DebugPrint(1, "erasing from linked list...\n");
						eraseList(ptrFound);

						//now delete it from memory
						m_objDebug.DebugPrint(1, "deleting node...\n");
						delete ptrFound;
						ptrFound = NULL;
						blnErased = true;

					}
					else {
						//then this is the root we are deleting
						//make left new root and place right
						m_objDebug.DebugPrint(1, "NO PARENT must be root...\n");
						if (ptrFound->m_ptrLeft)
						{
							m_objDebug.DebugPrint(1, "making left parent...\n");
							m_ptrRoot = ptrFound->m_ptrLeft;
							m_ptrRoot->m_ptrParent = NULL;
							if (ptrFound->m_ptrRight)
							{
								m_objDebug.DebugPrint(1, "placing right...\n");
								placeNode(m_ptrRoot, ptrFound->m_ptrRight);
							};
						}
						else if (ptrFound->m_ptrRight) {
							//no left only right, make this new root
							m_objDebug.DebugPrint(1, "making right parent...\n");
							m_ptrRoot = ptrFound->m_ptrRight;
							m_ptrRoot->m_ptrParent = NULL;
							//no left to place
						};
						m_objDebug.DebugPrint(1, "erasing from list...\n");
						//erase if rom the doubly linked list
						eraseList(ptrFound);

						m_objDebug.DebugPrint(1, "deleting node...\n");
						delete ptrFound;
						ptrFound = NULL;
						blnErased = true;
					};//end valid parent checkl

					m_objDebug.DebugPrint(1, "rebalancing tree...\n");
					//rebalance the tree
					this->updateSync();
				};

				if (blnErased)
				{
					m_intSize--;
				};
				m_objDebug.DebugPrint(1, "ERASE COMPLETE...\n");
				m_objLock.unlock(objNullID);

				return 1;
			}
			catch (...)
			{
				std::string errMsg;
				errMsg = "HtlMap erase Error thrown";
				throw std::exception(errMsg.c_str());
			}
		};

		//
		//!Returns the beginning node of the linked list and sets the cursor to that node.
		HtlTreeNode<TKey,TObj> * begin(void) 
		{ 
			try
			{
				m_ptrCursor = &m_objHead;
				return &m_objHead;
			}
			catch (...)
			{
				std::string errMsg;
				errMsg = "HtlMap begin Error thrown";
				throw std::exception(errMsg.c_str());
			}
		};
		//!Returns the end node
		HtlTreeNode<TKey,TObj> *  end(void) 
		{
			try
			{
				return &m_objEnd;
			}
			catch (...)
			{
				std::string errMsg;
				errMsg = "HtlMap end Error thrown";
				throw std::exception(errMsg.c_str());
			}
		};
		//!Returns the end node
		HtlTreeNode<TKey,TObj> *  root(void) 
		{
			try
			{
				return m_ptrRoot;
			}
			catch (...)
			{
				std::string errMsg;
				errMsg = "HtlMap root Error thrown";
				throw std::exception(errMsg.c_str());
			}
		};
		//!Advances the cursor to the next available node in the linked list
		HtlTreeNode<TKey,TObj> * next(void)
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
				errMsg = "HtlMap next Error thrown";
				throw std::exception(errMsg.c_str());
			}
		};

		//!Rewinds the cursor to the previous available node in the linked list
		HtlTreeNode<TKey,TObj> * previous(void)
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
				errMsg = "HtlMap previous Error thrown";
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
				errMsg = "HtlMap cursorKey Error thrown";
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
				errMsg = "HtlMap cursorValue Error thrown";
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
				errMsg = "HtlMap front Error thrown";
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
				errMsg = "HtlMap front Error thrown";
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
				errMsg = "HtlMap back Error thrown";
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
				errMsg = "HtlMap back Error thrown";
				throw std::exception(errMsg.c_str());
			}
		};


		HtlTreeNode<TKey, TObj> * findList(TKey& key)
		{	
			try
			{
				bool blnMatchFound = false;
				HtlTreeNode<TKey, TObj>* ptrRet = NULL;
				HtlTreeNode<TKey, TObj>* ptrCurrNode = &m_objHead;

				while ((ptrCurrNode) && (ptrCurrNode != &m_objEnd) && (!blnMatchFound))
				{
					if (key == ptrCurrNode->m_objKey)
					{
						//match found
						blnMatchFound = true;
						ptrRet = ptrCurrNode;
					}
					else {
						//no match get next node
						ptrCurrNode = ptrCurrNode->m_ptrNext;
					}
				}

				return ptrRet;
			}
			catch (...)
			{
				std::string errMsg;
				errMsg = "HtlMap findList Error thrown";
				throw std::exception(errMsg.c_str());
			}
		};



		HtlTreeNode<TKey, TObj> * findTree(TKey& key)
		{	
			try
			{
				if (!m_ptrRoot) { return NULL; };
				return findNode(m_ptrRoot, key);
			}
			catch (...)
			{
				std::string errMsg;
				errMsg = "HtlMap findTree Error thrown";
				throw std::exception(errMsg.c_str());
			}
		};

	private:
		//!Finds the desired key starting at the ptrCurrNode
		HtlTreeNode<TKey, TObj> * findNode(HtlTreeNode<TKey, TObj> * ptrCurrNode, TKey& key)
		{
			try
			{
				if (key == ptrCurrNode->m_objKey)
				{
					//then match.  return the iterator for this node
					return ptrCurrNode;
				}
				else {
					if (ptrCurrNode->m_ptrLeft)
					{
						HtlTreeNode<TKey, TObj> * ptrFound = findNode(ptrCurrNode->m_ptrLeft, key);
						if (ptrFound) { return ptrFound; };
					};
					if (ptrCurrNode->m_ptrRight)
					{
						HtlTreeNode<TKey, TObj> * ptrFound = findNode(ptrCurrNode->m_ptrRight, key);
						if (ptrFound) { return ptrFound; };
					};
					//key not found
					return NULL;
				};
				//shouldn't get here
				return NULL;
			}
			catch (...)
			{
				std::string errMsg;
				errMsg = "HtlMap findNode Error thrown";
				throw std::exception(errMsg.c_str());
			}
		};
		//!Places the desired node into the proper location
		bool placeNode(HtlTreeNode<TKey, TObj> * ptrParent, HtlTreeNode<TKey, TObj> * ptrNodeToPlace)
		{
			try
			{
				bool blnPlacedLeft = false;
				bool blnPlacedRight = false;
				if (ptrNodeToPlace->m_objKey <= ptrParent->m_objKey)
				{//then going to be on the left of the parent
					if (ptrParent->m_ptrLeft)
					{
						//then need to place it in the next level
						return placeNode(ptrParent->m_ptrLeft, ptrNodeToPlace);
					}
					else {
						ptrParent->m_ptrLeft = ptrNodeToPlace;
						ptrNodeToPlace->m_ptrParent = ptrParent;
						blnPlacedLeft = true;
						return blnPlacedLeft;
					};
				}
				else {
					//then going to be on the right of the parent
					if (ptrParent->m_ptrRight)
					{
						//then need to place it in the next level
						return placeNode(ptrParent->m_ptrRight, ptrNodeToPlace);
					}
					else {
						ptrParent->m_ptrRight = ptrNodeToPlace;
						ptrNodeToPlace->m_ptrParent = ptrParent;
						blnPlacedRight = true;
						return blnPlacedRight;
					};
				};//end of parent inequality
				//shouldn't make it here
				return false;
			}
			catch (...)
			{
				std::string errMsg;
				errMsg = "HtlMap placeNode Error thrown";
				throw std::exception(errMsg.c_str());
			}
		};
		//!Calculates the  node heights
		int nodeHeight(HtlTreeNode<TKey, TObj> * ptrCurrent)
		{
			if(ptrCurrent)
			{
				int intNodeH;
				m_objDebug.DebugPrint(1, "node height before...\n");
				ptrCurrent->heightNode(intNodeH);
				m_objDebug.DebugPrint(1, "node height after...\n");
				return ptrCurrent->m_intBalance;
			}else{
				return 0;
			};
			//shouldn't make it here
			return -1;
		};
		//!Balances the current node based on its node height
		int nodeBalance(HtlTreeNode<TKey, TObj> * ptrCurrent)
		{
			try
			{
				bool blnRotation = false;
				m_objDebug.DebugPrint(1, "ptrCurrent->m_intBalance... %d\n", ptrCurrent->m_intBalance);
				//this assumes node heights have been updated,
				//otherwise call nodeHeight(m_ptrRoot);
				if (abs(ptrCurrent->m_intBalance) <= 1)
				{//node balanced, no action needed
					if (ptrCurrent->m_ptrLeft)
					{
						m_objDebug.DebugPrint(1, "Recursive LEFT...\n");
						nodeBalance(ptrCurrent->m_ptrLeft);
					};

					if (ptrCurrent->m_ptrRight)
					{
						m_objDebug.DebugPrint(1, "Recursive RIGHT...\n");
						nodeBalance(ptrCurrent->m_ptrRight);
					};
					return 0;
				};

				//Get type of rotation
				//LEFT ROTATIONS
				if (ptrCurrent->m_intBalance > 1)
				{
					//then  LEFT BIASED unbalanced
					if (ptrCurrent->m_ptrLeft)
					{
						m_objDebug.DebugPrint(1, "Left m_intBalance... %d\n", ptrCurrent->m_ptrLeft->m_intBalance);
						if (ptrCurrent->m_ptrLeft->m_intBalance > 0)
						{
							//PERFORM LEFT LEFT ROTATION
							blnRotation = true;
							m_objDebug.DebugPrint(1, "rotateLeftLeft...\n");
							this->rotateLeftLeft(ptrCurrent);
						}
						else {
							//PERFORM LEFT RIGHT ROTATION
							blnRotation = true;
							m_objDebug.DebugPrint(1, "rotateLeftRight...\n");
							this->rotateLeftRight(ptrCurrent);
						};
					}
					else {
						//PERFORM LEFT NULL ROTATION
						blnRotation = true;
						m_objDebug.DebugPrint(1, "rotateLeftNull...\n");
						this->rotateLeftNull(ptrCurrent);
					};
				};

				//Get type of rotation
				if (ptrCurrent->m_intBalance < 1)
				{
					//then  RIGHT BIASED unbalanced
					if (ptrCurrent->m_ptrRight)
					{
						m_objDebug.DebugPrint(1, "Right m_intBalance... %d\n", ptrCurrent->m_ptrRight->m_intBalance);
						if (ptrCurrent->m_ptrRight->m_intBalance < 0)
						{
							//PERFORM RIGHT RIGHT ROTATION
							blnRotation = true;
							m_objDebug.DebugPrint(1, "rotateRightRight...\n");
							this->rotateRightRight(ptrCurrent);
						}
						else {
							//PERFORM RIGHT LEFT ROTATION
							blnRotation = true;
							m_objDebug.DebugPrint(1, "rotateRightLeft...\n");
							this->rotateRightLeft(ptrCurrent);
						};
					}
					else {
						//PERFORM RIGHT LEFT ROTATION
						blnRotation = true;
						m_objDebug.DebugPrint(1, "rotateRightNull...\n");
						this->rotateRightNull(ptrCurrent);
					};
				};

				if (blnRotation)
				{
					m_objDebug.DebugPrint(1, "rotation success, recalc heights...\n");
					nodeHeight(m_ptrRoot);
					nodeBalance(m_ptrRoot);
				}
				else {
					m_objDebug.DebugPrint(1, "rotateRightNull...\n");
					if (ptrCurrent->m_ptrLeft)
					{
						m_objDebug.DebugPrint(1, "Recursive LEFT...\n");
						nodeBalance(ptrCurrent->m_ptrLeft);
					};

					if (ptrCurrent->m_ptrRight)
					{
						m_objDebug.DebugPrint(1, "Recursive RIGHT...\n");
						nodeBalance(ptrCurrent->m_ptrRight);
					};
				};

				return 1;
			}
			catch (...)
			{
				std::string errMsg;
				errMsg = "HtlMap nodeBalance Error thrown";
				throw std::exception(errMsg.c_str());
			}
		};

		//!Erases the node from the doubly linked list data structure
		void eraseList(HtlTreeNode<TKey, TObj> * ptrNode)
		{
			try
			{

				bool blnMatchFound = false;
				HtlTreeNode<TKey, TObj> * ptrCursor = NULL;

				//special case, NO nodes
				if (m_objHead.m_ptrNext == &m_objEnd)
				{
					return;
				};
				ptrCursor = &m_objHead;
				while ((ptrCursor) && (ptrCursor != &m_objEnd) && (!blnMatchFound))
				{
					if (ptrNode->m_objKey == ptrCursor->m_objKey)
					{
						//then match found  erase the node
						ptrCursor->m_ptrPrev->m_ptrNext = ptrCursor->m_ptrNext;
						ptrCursor->m_ptrNext->m_ptrPrev = ptrCursor->m_ptrPrev;
					};
					ptrCursor = ptrCursor->m_ptrNext;
				};

				ptrCursor = &m_objHead;
				while ((ptrCursor) && (ptrCursor != &m_objEnd))
				{
					if (ptrCursor->m_ptrLeft == ptrNode)
					{
						ptrCursor->m_ptrLeft = NULL;
					}
					if (ptrCursor->m_ptrRight == ptrNode)
					{
						ptrCursor->m_ptrRight = NULL;
					}
					ptrCursor = ptrCursor->m_ptrNext;
				};
				return;
			}
			catch (...)
			{
				std::string errMsg;
				errMsg = "HtlMap eraseList Error thrown";
				throw std::exception(errMsg.c_str());
			}
		};

		//!Update and Synchronizes the AVL Tree and doubly linked list data structures
		void updateSync(void)
		{
			try
			{
				HtlTreeNode<TKey, TObj> * ptrCurrNode = NULL;
				HtlTreeNode<TKey, TObj> * ptrFront = NULL;
				if (!m_ptrRoot) { return; };
				//update node heights
				m_objDebug.DebugPrint(1, "calc node height...\n");
				this->nodeHeight(m_ptrRoot);
				//balance the new tree
				m_objDebug.DebugPrint(1, "tree rebalancing...\n");
				this->nodeBalance(m_ptrRoot);

				return;
			}
			catch (...)
			{
				std::string errMsg;
				errMsg = "HtlMap updateSync Error thrown";
				throw std::exception(errMsg.c_str());
			}
		};

		//!Left Left Rotation operation for AVL Tree
		/*!
		This is a Left Left Rotation, this occurs when A >= +2
		and BL >= +1 indexed height
		 A                           BL
		/  \                        /  \
		BL   BR   LeftLeftRot==>  CL    A
		/  \                           /  \
		CL  CR                        CR   BR
		*/
		void rotateLeftLeft(HtlTreeNode<TKey,TObj>* ptrNode)
		{
			try
			{
				m_objDebug.DebugPrint(1, "HtlMap::rotateLeftLeft()\n");
				HtlTreeNode<TKey, TObj>* ptrTemp = NULL;
				HtlTreeNode<TKey, TObj>* ptrParent = NULL;
				HtlTreeNode<TKey, TObj>* ptrATop = NULL;
				HtlTreeNode<TKey, TObj>* ptrBL = NULL;
				HtlTreeNode<TKey, TObj>* ptrBR = NULL;
				HtlTreeNode<TKey, TObj>* ptrCL = NULL;
				HtlTreeNode<TKey, TObj>* ptrCR = NULL;

				ptrParent = ptrNode->m_ptrParent;
				ptrATop = ptrNode;
				ptrBL = ptrNode->m_ptrLeft;
				ptrBR = ptrNode->m_ptrRight;
				if (ptrBL)
				{
					ptrCL = ptrBL->m_ptrLeft;
					ptrCR = ptrBL->m_ptrRight;
				};

				//set parent link first
				if (!ptrParent)
				{
					m_ptrRoot = ptrBL;
					ptrBL->m_ptrParent = NULL;
				}
				else {
					if (ptrATop->isLeft())
					{
						ptrParent->m_ptrLeft = ptrBL;
					};
					if (ptrATop->isRight())
					{
						ptrParent->m_ptrRight = ptrBL;
					};
					ptrBL->m_ptrParent = ptrATop->m_ptrParent;
				}

				//rotate A

				if (ptrATop)
				{
					ptrATop->m_ptrParent = ptrBL;
					ptrATop->m_ptrLeft = ptrCR;
					ptrATop->m_ptrRight = ptrBR;
				};
				if (ptrBL)
				{
					ptrBL->m_ptrRight = ptrATop;
				};
				//sub tree C
				if (ptrCR)
				{
					ptrCR->m_ptrParent = ptrATop;
				};
				if (ptrBR)
				{
					ptrBR->m_ptrParent = ptrATop;
				};
				return;
			}
			catch (...)
			{
				std::string errMsg;
				errMsg = "HtlMap rotateLeftLeft Error thrown";
				throw std::exception(errMsg.c_str());
			}
		};

		//!Left Right Rotation operation for AVL Tree
		/*!
		This is a Left Right Rotation, this occurs when A >= +2
		and BL <= -1 indexed height
		  A							 _CR_
		 /  \						/    \
		BL   BR   LeftRightRot==>  BL       A
		/  \                      /  \     /  \
		CL  CR                    CL   DL   DR   BR
		    / \
		   DL  DR
		*/
		void rotateLeftRight(HtlTreeNode<TKey,TObj>* ptrNode)
		{
			try
			{
				if (!ptrNode) { return; };
				m_objDebug.DebugPrint(1, "HtlMap::rotateLeftRight()\n");
				HtlTreeNode<TKey, TObj>* ptrTemp = NULL;
				HtlTreeNode<TKey, TObj>* ptrParent = NULL;
				HtlTreeNode<TKey, TObj>* ptrATop = NULL;
				HtlTreeNode<TKey, TObj>* ptrBL = NULL;
				HtlTreeNode<TKey, TObj>* ptrBR = NULL;
				HtlTreeNode<TKey, TObj>* ptrCL = NULL;
				HtlTreeNode<TKey, TObj>* ptrCR = NULL;
				HtlTreeNode<TKey, TObj>* ptrDL = NULL;
				HtlTreeNode<TKey, TObj>* ptrDR = NULL;



				ptrATop = ptrNode;
				ptrParent = ptrNode->m_ptrParent;
				ptrBL = ptrNode->m_ptrLeft;
				ptrBR = ptrNode->m_ptrRight;
				if (ptrBL)
				{
					ptrCL = ptrBL->m_ptrLeft;
					ptrCR = ptrBL->m_ptrRight;
					if (ptrCR)
					{
						ptrDL = ptrCR->m_ptrLeft;
						ptrDR = ptrCR->m_ptrRight;
					};
				};

				//set parent link first
				if (!ptrParent)
				{
					m_ptrRoot = ptrCR;
					ptrCR->m_ptrParent = NULL;
				}
				else {
					if (ptrATop->isLeft())
					{
						ptrParent->m_ptrLeft = ptrCR;
					};
					if (ptrATop->isRight())
					{
						ptrParent->m_ptrRight = ptrCR;
					};
					ptrCR->m_ptrParent = ptrATop->m_ptrParent;
				}

				//rotate A
				//ptrBL
				if (ptrCR) { ptrCR->m_ptrLeft = ptrBL; };
				if (ptrBL) { ptrBL->m_ptrParent = ptrCR; };

				//ptrBL subtree
				if (ptrBL) { ptrBL->m_ptrLeft = ptrCL; };
				if (ptrCL) { ptrCL->m_ptrParent = ptrBL; };

				if (ptrBL) { ptrBL->m_ptrRight = ptrDL; };
				if (ptrDL) { ptrDL->m_ptrParent = ptrBL; };

				//ptrA
				if (ptrCR) { ptrCR->m_ptrRight = ptrATop; };
				if (ptrATop) { ptrATop->m_ptrParent = ptrCR; };

				//ptrA subtree
				if (ptrATop) { ptrATop->m_ptrLeft = ptrDR; };
				if (ptrDR) { ptrDR->m_ptrParent = ptrATop; };

				if (ptrATop) { ptrATop->m_ptrRight = ptrBR; };
				if (ptrBR) { ptrBR->m_ptrParent = ptrATop; };

				return;
			}
			catch (...)
			{
				std::string errMsg;
				errMsg = "HtlMap rotateLeftRight Error thrown";
				throw std::exception(errMsg.c_str());
			}
		};

		void rotateLeftNull(HtlTreeNode<TKey,TObj>* ptrNode)
		{


		};
		//!Right Right Rotation for AVL Tree
		/*!
		This is a Right Right Rotation, this occurs when A >= +2
		and BL >= +1 indexed height
		  A                           BR
		/  \                         /  \
		BL   BR   RightRightRot==>  A    CR
		    /  \                   /  \
		   CL  CR                 BL   CL
		*/
		void rotateRightRight(HtlTreeNode<TKey,TObj>* ptrNode)
		{
			try
			{
				if (!ptrNode) { return; };
				m_objDebug.DebugPrint(1, "HtlMap::rotateRightRight()\n");
				HtlTreeNode<TKey, TObj>* ptrTemp = NULL;
				HtlTreeNode<TKey, TObj>* ptrATop = NULL;
				HtlTreeNode<TKey, TObj>* ptrParent = NULL;
				HtlTreeNode<TKey, TObj>* ptrBL = NULL;
				HtlTreeNode<TKey, TObj>* ptrBR = NULL;
				HtlTreeNode<TKey, TObj>* ptrCL = NULL;
				HtlTreeNode<TKey, TObj>* ptrCR = NULL;

				//SET INITIAL TREE
				ptrATop = ptrNode;
				ptrParent = ptrNode->m_ptrParent;
				ptrBL = ptrNode->m_ptrLeft;
				ptrBR = ptrNode->m_ptrRight;
				if (ptrNode->m_ptrRight)
				{
					ptrCL = ptrNode->m_ptrRight->m_ptrLeft;
					ptrCR = ptrNode->m_ptrRight->m_ptrRight;
				}

				//set parent link first
				if (!ptrParent)
				{
					m_ptrRoot = ptrBR;
					ptrBR->m_ptrParent = NULL;
				}
				else {
					if (ptrATop->isLeft())
					{
						ptrParent->m_ptrLeft = ptrBR;
					};
					if (ptrATop->isRight())
					{
						ptrParent->m_ptrRight = ptrBR;
					};
					ptrBR->m_ptrParent = ptrATop->m_ptrParent;
				}
				//rotate A
				if (ptrATop)
				{

					ptrATop->m_ptrParent = ptrBR;
					ptrATop->m_ptrLeft = ptrBL;
					ptrATop->m_ptrRight = ptrCL;
				};
				if (ptrBR)
				{
					ptrBR->m_ptrLeft = ptrATop;
				};
				//sub tree C
				if (ptrBL)
				{
					ptrBL->m_ptrParent = ptrATop;
				};
				if (ptrCL)
				{
					ptrCL->m_ptrParent = ptrATop;
				};

				return;
			}
			catch (...)
			{
				std::string errMsg;
				errMsg = "HtlMap rotateRightRight Error thrown";
				throw std::exception(errMsg.c_str());
			}
		};

		//!Right Left Rotation for AVL Tree
		/*!
		This is a Left Right Rotation, this occurs when A >= +2
		and BL <= -1 indexed height
		  A                           _CL_
		/  \                         /    \
		BL   BR   RightLeftRot==>   A      BR
		    /  \                   /  \    /  \
		   CL  CR                BL   DL  DR   CR
		  / \
		DL  DR
		*/
		void rotateRightLeft(HtlTreeNode<TKey,TObj>* ptrNode)
		{
			try
			{
				if (!ptrNode) { return; };
				m_objDebug.DebugPrint(1, "HtlMap::rotateRightLeft()\n");
				HtlTreeNode<TKey, TObj>* ptrTemp = NULL;
				HtlTreeNode<TKey, TObj>* ptrParent = NULL;
				HtlTreeNode<TKey, TObj>* ptrATop = NULL;
				HtlTreeNode<TKey, TObj>* ptrBL = NULL;
				HtlTreeNode<TKey, TObj>* ptrBR = NULL;
				HtlTreeNode<TKey, TObj>* ptrCL = NULL;
				HtlTreeNode<TKey, TObj>* ptrCR = NULL;
				HtlTreeNode<TKey, TObj>* ptrDL = NULL;
				HtlTreeNode<TKey, TObj>* ptrDR = NULL;
				//set nodes
				ptrATop = ptrNode;
				ptrParent = ptrATop->m_ptrParent;
				ptrBL = ptrNode->m_ptrLeft;
				ptrBR = ptrNode->m_ptrRight;
				if (ptrBR)
				{
					ptrCL = ptrBR->m_ptrLeft;
					ptrCR = ptrBR->m_ptrRight;
					if (ptrCL)
					{
						ptrDL = ptrCL->m_ptrLeft;
						ptrDR = ptrCL->m_ptrRight;
					};
				};

				//set parent link first
				if (!ptrParent)
				{
					m_ptrRoot = ptrCL;
					ptrCL->m_ptrParent = NULL;
				}
				else {
					if (ptrATop->isLeft())
					{
						ptrParent->m_ptrLeft = ptrCL;
					};
					if (ptrATop->isRight())
					{
						ptrParent->m_ptrRight = ptrCL;
					};
					ptrCL->m_ptrParent = ptrATop->m_ptrParent;
				}

				//rotate A
				//ptrBL
				if (ptrATop) { ptrATop->m_ptrParent = ptrCL; };
				if (ptrCL) { ptrCL->m_ptrLeft = ptrATop; };

				//ptrA subtree
				if (ptrATop) { ptrATop->m_ptrLeft = ptrBL; };
				if (ptrBL) { ptrBL->m_ptrParent = ptrATop; };

				if (ptrATop) { ptrATop->m_ptrRight = ptrDL; };
				if (ptrDL) { ptrDL->m_ptrParent = ptrATop; };

				//ptrBR
				if (ptrCL) { ptrCL->m_ptrRight = ptrBR; };
				if (ptrBR) { ptrBR->m_ptrParent = ptrCL; };

				//ptrBR subtree
				if (ptrBR) { ptrBR->m_ptrLeft = ptrDR; };
				if (ptrDR) { ptrDR->m_ptrParent = ptrBR; };

				if (ptrBR) { ptrBR->m_ptrRight = ptrCR; };
				if (ptrCR) { ptrCR->m_ptrParent = ptrATop; };
			}
			catch (...)
			{
				std::string errMsg;
				errMsg = "HtlMap rotateRightLeft Error thrown";
				throw std::exception(errMsg.c_str());
			}
		};

		void rotateRightNull(HtlTreeNode<TKey,TObj>* ptrNode)
		{


		};
		//!Update the height of the current node
		int updateHeight(HtlTreeNode<TKey,TObj>* ptrCurrNode)
		{
			if(!ptrCurrNode){return 0;};
			int intRootHeight;
			ptrCurrNode->heightNode(intRootHeight);
			return intRootHeight;
		};


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
				errMsg = "HtlMap Save Error thrown";
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
							insert(objKeyTemp,objValTemp);
						};
					};
				};
				return intReturn;
			}catch(...){
				std::string errMsg;
				errMsg = "HtlMap Load Error thrown";
				throw std::exception(errMsg.c_str());
				return -1;
			};
			return intReturn;

		};


	};//end HtlMap class definition


	//Htl1DVector MEMBER FUNCTION DECLARATIONS
};//end namespace HTL
#endif