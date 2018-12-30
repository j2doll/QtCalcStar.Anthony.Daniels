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

#ifndef HTL_1DVECTOR_H
#define HTL_1DVECTOR_H

#include ".\HtlContainer.h"
#include ".\HtlVectorNode.h"

namespace HTL
{

	//!Htl1DVector is a one dimensional container for objects
	/*!
		Htl1DVector is a one dimensional container for objects
		The constructor requires the class, and it's equivalent HtlObjectType enumeration
	*/
	template<typename TObj, HtlObjectType TObjEnum>
	class Htl1DVector : public HtlContainer<size_t,CPP_INT, TObj,TObjEnum>
	{
	public:
		typedef TObj & Reference;
		typedef const TObj & ConstReference;
		//HtlVector1D SUBCLASS DECLARATIONS////////////////////////////////////////
		//!HtlVector Iterator class
		class Iterator {
		public:
			TObj *i;

			typedef TObj Value;
			typedef TObj *Pointer;
			typedef TObj &Reference;
			typedef const TObj & ConstReference;
		
			inline Iterator() : i(0) {}
			inline Iterator(TObj *n) : i(n) {}
			inline Iterator(const Iterator &o): i(o.i){}
			inline TObj &operator*() const { return *i; }
			inline TObj *operator->() const { return i; }
			inline TObj &operator[](int j) const { return *(i + j); }
			inline bool operator==(const Iterator &o) const { return i == o.i; }
			inline bool operator!=(const Iterator &o) const { return i != o.i; }
			inline bool operator<(const Iterator& other) const { return i < other.i; }
			inline bool operator<=(const Iterator& other) const { return i <= other.i; }
			inline bool operator>(const Iterator& other) const { return i > other.i; }
			inline bool operator>=(const Iterator& other) const { return i >= other.i; }
			inline Iterator &operator++() { ++i; return *this; }
			inline Iterator operator++(int) { TObj *n = i; ++i; return n; }
			inline Iterator &operator--() { i--; return *this; }
			inline Iterator operator--(int) { TObj *n = i; i--; return n; }
			inline Iterator &operator+=(int j) { i+=j; return *this; }
			inline Iterator &operator-=(int j) { i-=j; return *this; }
			inline Iterator operator+(int j) const { return Iterator(i+j); }
			inline Iterator operator-(int j) const { return Iterator(i-j); }
			inline int operator-(Iterator j) const { return i - j.i; }
		};
		//!HtlVector Const Iterator class
		class ConstIterator {
		public:
			TObj *i;

			typedef TObj Value;
			typedef TObj *Pointer;
			typedef TObj &Reference;
			typedef const TObj & ConstReference;

			inline ConstIterator() : i(0) {}
			inline ConstIterator(TObj *n) : i(n) {}
			inline ConstIterator(const ConstIterator &o): i(o.i) {}
			inline explicit ConstIterator(const Iterator &o): i(o.i) {}
			inline const TObj &operator*() const { return *i; }
			inline const TObj *operator->() const { return i; }
			inline const TObj &operator[](int j) const { return *(i + j); }
			inline bool operator==(const ConstIterator &o) const { return i == o.i; }
			inline bool operator!=(const ConstIterator &o) const { return i != o.i; }
			inline bool operator<(const ConstIterator& other) const { return i < other.i; }
			inline bool operator<=(const ConstIterator& other) const { return i <= other.i; }
			inline bool operator>(const ConstIterator& other) const { return i > other.i; }
			inline bool operator>=(const ConstIterator& other) const { return i >= other.i; }
			inline ConstIterator &operator++() { ++i; return *this; }
			inline ConstIterator operator++(int) { TObj *n = i; ++i; return n; }
			inline ConstIterator &operator--() { i--; return *this; }
			inline ConstIterator operator--(int) { TObj *n = i; i--; return n; }
			inline ConstIterator &operator+=(int j) { i+=j; return *this; }
			inline ConstIterator &operator-=(int j) { i-=j; return *this; }
			inline ConstIterator operator+(int j) const { return ConstIterator(i+j); }
			inline ConstIterator operator-(int j) const { return ConstIterator(i-j); }
			inline int operator-(ConstIterator j) const { return i - j.i; }
		};
		//END HTLVECTOR1D SUBCLASS DEFINITIONS///////////////////////////////////////


		//HtlVector1D CLASS DEFINITION/////////////////////////////////////////
	public:

		//!Void constructor
		Htl1DVector() : HtlContainer()
		{
			m_ptrData = &m_objSharedNull;
			m_objType = HTL_CONTAINER;
			m_strType = "Htl1DVector";
			m_itemType = TObjEnum;
			m_chrNull = '\0';
		};

		//!Virtual Destructor
		virtual ~Htl1DVector(void){};
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

		inline Iterator begin() { return m_ptrData->m_arrObj; };
		inline ConstIterator beginConst() const { return m_ptrData->m_arrObj; };
		inline Iterator end() { return m_ptrData->m_arrObj + m_ptrData->m_intSize; };
		inline ConstIterator endConst() const { return m_ptrData->m_arrObj + m_ptrData->m_intSize; };

		inline Reference front() { return m_ptrData->m_arrObj[0]; };
		inline ConstReference front() const { return m_ptrData->m_arrObj[0]; };
		inline Reference back() {return m_ptrData->m_arrObj[(m_ptrData->m_intSize - 1)]; };
		inline ConstReference back() const { return m_ptrData->m_arrObj[(m_ptrData->m_intSize - 1)]; };

		inline void push_back(const TObj &t) { append(t); };
		inline void push_front(const TObj &t) { prepend(t); };
		void pop_back() { if(!isEmpty()){erase(end()-1);};};
		void pop_front() { if(!isEmpty()){ erase(begin());};};

	protected:
		//!Static shared NULL object for when vector is empty 
		HtlVectorNode<TObj> m_objSharedNull;
		//!character null for NULL typing
		char m_chrNull;
		//!THIS IS THE POINTER TO THE ACTUAL VECTOR DATA THAT IS BEING MANAGED
		HtlVectorNode<TObj> * m_ptrData;

	private:
		//!This grows the string by int units
		//void grow(size_t intSize);
		//!This shrinks the string by int spaces, or completely if intSize > intCurrentSize
		//void shrink(size_t intSize);

		//TEMPLATE MEMBER VARIABLE DECLARATION AND DEFINITION//////////////////////////////////
	public:
			//!Assignment Operator
			Htl1DVector<TObj, TObjEnum> & operator=(Htl1DVector<TObj, TObjEnum>& ptrRHS)
			{
				try
				{
					//safety check
					if (!m_ptrData) { return *this; };

					//clear existing characters
					clear();
					//assign the new character
					for (size_t i = 0; i < ptrRHS.size(); i++)
					{
						push_back(ptrRHS.at(i));
					};
					return *this;
				}
				catch (...)
				{
					std::string errMsg;
					errMsg = "Htl1DVector assignement operator Error thrown";
					throw std::exception(errMsg.c_str());
				}
			};
		
		
		//!HTL Container Analyzers
		//!Returns the length of the vector minus the null terminator (\0)
		virtual size_t size(void) const
		{
			if(!m_ptrData)
			{
				return 0;
			};
			return m_ptrData->m_intSize;
		};
		
		//!Returns the length of the vector minus the null terminator (\0)
		virtual size_t count(void) const
		{
			if(!m_ptrData){return 0;};
			return m_ptrData->m_intSize;
		};


		//!Is the Container Empty
		virtual bool isEmpty(void) const
		{
			//safety check
			if(!m_ptrData){return true;};

			if(m_ptrData->m_intSize <= 0)
			{return true;}else{return false;};

			return true;
		};
		//!What is the Current Capacity of the container
		virtual size_t capacity(void) const
		{//
			//safety check
			if(!m_ptrData){return 0;};

			return m_ptrData->m_intAlloc;

		};

		//!Clears the container
		virtual void clear(void)
		{
			try
			{
				if (!m_ptrData) { return; };
				//lock the container before modifying it
				HtlGUID128 objNullID;
				objNullID.newID();
				m_objLock.lock(objNullID);

				if ((m_ptrData) && (m_ptrData != &m_objSharedNull))
				{
					//fill('\0');
					qMemFree(m_ptrData);
					m_ptrData = &m_objSharedNull;
				};
				m_objLock.unlock(objNullID);

				return;
			}
			catch (...)
			{
				std::string errMsg;
				errMsg = "Htl1DVector clear Error thrown";
				throw std::exception(errMsg.c_str());
			}
		};

		//!Vector resizing related methods
		virtual void resize(int size)
		{
			return;//TO BE ADDED
		};

		virtual void reserve(int size)
		{
			return;	//TO BE ADDED
		};

		//!Access to the actual data pointers
		virtual TObj *Get_ptrData()
		{
			if(m_ptrData)
			{
				m_ptrData->m_arrObj;
			}else{
				return NULL;
			};
			return NULL;
		};

		//!Item accessor function
		virtual	const TObj & at(size_t i) const
		{
			try
			{
				if (!m_ptrData) { return m_objNull; };
				if (i < m_ptrData->m_intSize)
				{
					return m_ptrData->m_arrObj[i];
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
				errMsg = "Htl1DVector at Error thrown";
				throw std::exception(errMsg.c_str());
			}
		};
		//!Item accessor function
		virtual TObj & at(size_t i)
		{
			try
			{
				if (!m_ptrData) { return m_objNull; };
				if (i < m_ptrData->m_intSize)
				{
					return m_ptrData->m_arrObj[i];
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
				errMsg = "Htl1DVector at Error thrown";
				throw std::exception(errMsg.c_str());
			}
		};
		//!Item accessor function
		virtual const TObj & operator[](size_t i) const
		{
			try
			{
				if (!m_ptrData) { return m_objNull; };
				if (i < m_ptrData->m_intSize)
				{
					return m_ptrData->m_arrObj[i];
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
				errMsg = "Htl1DVector at Error thrown";
				throw std::exception(errMsg.c_str());
			}
		};
		//!Item accessor function
		virtual TObj & operator[](size_t i)
		{
			try
			{
				if (!m_ptrData) { return m_objNull; };
				if (i < m_ptrData->m_intSize)
				{
					return m_ptrData->m_arrObj[i];
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
				errMsg = "Htl1DVector at Error thrown";
				throw std::exception(errMsg.c_str());
			}
		};
		//!Append single object
		void append(const TObj& ptrRHS)
		{
			try
			{
				//safety checks
				if ((!m_ptrData) || (m_ptrData == &m_objSharedNull))
				{
					m_ptrData = new HtlVectorNode<TObj>();
				};
				HtlGUID128 objNullID;
				objNullID.newID();
				m_objLock.lock(objNullID);
				//otherwise append to existing string
				size_t intOldSize = m_ptrData->m_intSize;
				//safe to append TObjacter
				if (m_ptrData->m_intSize == 0)
				{//first element, already there

					if (TypeInfo<TObj>::isComplex)
					{
						new (m_ptrData->m_arrObj) TObj(ptrRHS);
					}
					else {
						TObj * ptrLoc = &m_ptrData->m_arrObj[intOldSize];
						memcpy(ptrLoc, &ptrRHS, sizeof(TObj));
					};
					m_ptrData->m_intSize++;
				}
				else {
					//need to grow first
					this->grow(1);//m_intSize incremented in grow
					if (TypeInfo<TObj>::isComplex)
					{
						new (m_ptrData->m_arrObj + intOldSize) TObj(ptrRHS);
					}
					else {
						TObj * ptrLoc = &m_ptrData->m_arrObj[intOldSize];
						memcpy(ptrLoc, &ptrRHS, sizeof(TObj));
					};
				};
				//append the TObjacter
				//perform the memory copying of the incoming string

				m_objLock.unlock(objNullID);
				return;
			}
			catch (...)
			{
				std::string errMsg;
				errMsg = "Htl1DVector append Error thrown";
				throw std::exception(errMsg.c_str());
			}
		};
		//!Prepend single object
		void prepend(const TObj& ptrRHS)
		{
			try
			{
				//safety checks
				if ((!m_ptrData) || (m_ptrData == &m_objSharedNull))
				{
					//nothing there yet, append new item
					append(ptrRHS);
					return;
				};
				//safe to proceed
				//duplicate to buffer
				HtlGUID128 objNullID;
				objNullID.newID();
				m_objLock.lock(objNullID);


				size_t intOldSize = m_ptrData->m_intSize;
				TObj * ptrBuf = NULL;
				ptrBuf = (TObj*)qMemAlloc(intOldSize * sizeof(TObj));

				memcpy(ptrBuf, m_ptrData->m_arrObj, intOldSize * sizeof(TObj));

				//valid prepend grow the string to accomodate
				grow(1);

				if (TypeInfo<TObj>::isComplex)
				{
					new (m_ptrData->m_arrObj)TObj(ptrRHS);
				}
				else {
					//prepend and copy back string
					TObj* ptrLoc1 = &m_ptrData->m_arrObj[0];
					memcpy(ptrLoc1, &ptrRHS, sizeof(TObj));
				};
				//append old string
				TObj* ptrLoc2 = &m_ptrData->m_arrObj[1];
				memcpy(ptrLoc2, ptrBuf, intOldSize * sizeof(TObj));
				//clean up memory
				qMemFree(ptrBuf);
				ptrBuf = NULL;

				m_objLock.unlock(objNullID);

				return;
			}
			catch (...)
			{
				std::string errMsg;
				errMsg = "Htl1DVector prepend Error thrown";
				throw std::exception(errMsg.c_str());
			}
		};

		//!Insert single object N times
		Iterator insert(Iterator before, size_t n, const TObj &t)	
		{
			try
			{
				//safety checks
				if (!m_ptrData) { return NULL; };
				if (n <= 0) { return m_ptrData->m_arrObj; };
				int intOffset = int(before - m_ptrData->m_arrObj);

				HtlGUID128 objNullID;
				objNullID.newID();
				m_objLock.lock(objNullID);

				TObj objTemp = t;//temp copy for duplication
				//grow the vector at the tail
				grow(n);
				//shift the old cells to the right
				for (size_t i = (m_ptrData->m_intSize - 1); i >= (intOffset + n); --i)
				{
					TObj* ptrLocDest = &(m_ptrData->m_arrObj[i]);
					TObj* ptrLocSource = &(m_ptrData->m_arrObj[i - n]);

					/*if(HTL::TypeInfo<TObj>::isComplex)
					{
						ptrLocDest->~TObj();
					};*/
					//shift to the left

					memcpy(ptrLocDest, ptrLocSource, sizeof(TObj));
				};
				//insert the new cells
				for (size_t i = intOffset; i < (intOffset + n); i++)
				{
					if (TypeInfo<TObj>::isComplex)
					{
						new (m_ptrData->m_arrObj + i) TObj(objTemp);
					}
					else {
						memcpy(&(m_ptrData->m_arrObj[i]), &objTemp, sizeof(TObj));
					};
				};

				m_objLock.unlock(objNullID);

				return m_ptrData->m_arrObj + intOffset;

			}
			catch (...)
			{
				std::string errMsg;
				errMsg = "Htl1DVector insert Error thrown";
				throw std::exception(errMsg.c_str());
			}

		}
		//!Erase single object at iterator location
		Iterator erase(Iterator abegin)
		{
			try
			{
				if (!m_ptrData) { return NULL; };
				int intOffset = int(abegin - m_ptrData->m_arrObj);
				int intSpan = 1;

				HtlGUID128 objNullID;
				objNullID.newID();
				m_objLock.lock(objNullID);
				//shift the old cells to the left
				for (size_t i = (intOffset + intSpan); i < m_ptrData->m_intSize; i++)
				{
					TObj* ptrLocDest = &(m_ptrData->m_arrObj[i - intSpan]);
					TObj* ptrLocSource = &(m_ptrData->m_arrObj[i]);

					if (HTL::TypeInfo<TObj>::isComplex)
					{
						ptrLocDest->~TObj();
					};
					//shift to the left

					memcpy(ptrLocDest, ptrLocSource, sizeof(TObj));
				};
				//shrink to the new size
				shrink(intSpan);
				//unlock container
				m_objLock.unlock(objNullID);
				//return the leading edge
				return  m_ptrData->m_arrObj + intOffset;
			}
			catch (...)
			{
				std::string errMsg;
				errMsg = "Htl1DVector erase Error thrown";
				throw std::exception(errMsg.c_str());
			}
		};
		//!Erase objects from begin to end iterators
		Iterator erase(Iterator abegin, Iterator aend)
		{
			try
			{
				int i;
				if (!m_ptrData) { return NULL; };
				int intOffset = int(abegin - m_ptrData->m_arrObj);
				int intSpan = int(aend - abegin);

				HtlGUID128 objNullID;
				objNullID.newID();
				m_objLock.lock(objNullID);
				TObj objTemp = t;//temp copy for duplication
				//shift the old cells to the left
				for (int i = (intOffset + intSpan); i < m_ptrData->m_intSize; i++)
				{
					TObj* ptrLocDest = &(m_ptrData->m_arrObj[i - intSpan]);
					TObj* ptrLocSource = &(m_ptrData->m_arrObj[i]);

					if (HTL::TypeInfo<TObj>::isComplex)
					{
						ptrLocDest->~TObj();
					};
					//shift to the left

					memcpy(ptrLocDest, ptrLocSource, sizeof(TObj));
				};
				//shrink to the new size
				shrink(intSpan);
				//unlock container
				m_objLock.unlock(objNullID);
				//return the leading edge
				return  m_ptrData->m_arrTObj + intOffset;
			}
			catch (...)
			{
				std::string errMsg;
				errMsg = "Htl1DVector erase Error thrown";
				throw std::exception(errMsg.c_str());
			}
		}

	private:
		//!Grow the memory to accommodate objects for size + intSize
		void grow(size_t intSize)
		{
			try
			{
				//safety checks
				if (!m_ptrData) { return; };

				size_t intOldSize, intNewSize, intCurrEnd, intNewEnd;
				intCurrEnd = m_ptrData->m_intSize;
				intOldSize = sizeof(HtlVectorNode<TObj>) + ((m_ptrData->m_intSize - 1) * sizeof(TObj));
				intNewSize = intOldSize + (intSize * sizeof(TObj));//ADD TO THE EXISTING
				//This constructor takes the incoming text and
				//appends it to the current string
				if (intOldSize <= 0)
				{
					//no TObjacters, nothing to do...
					//return gracefully
					m_ptrData = &m_objSharedNull;
					memset(&m_objSharedNull.m_arrObj[0], 0, sizeof(TObj));

					return;
				}
				else {
					//reserve the memory
					//qMemReAllocAligned(void *oldptr, size_t newsize, size_t oldsize, size_t alignment)
					m_ptrData = (HtlVectorNode<TObj>*) qMemReAlloc(m_ptrData, intNewSize);

					//set the container sizes
					m_ptrData->m_intSize = intCurrEnd + intSize;
					m_ptrData->m_intAlloc = m_ptrData->m_intSize;

					//set the NULL terminator for the string
					intNewEnd = intCurrEnd + intSize;
					//memset(&m_ptrData->m_arrObj[intNewEnd],'\0',1);

					return;
				};

				return;
			}
			catch (...)
			{
				std::string errMsg;
				errMsg = "Htl1DVector grow Error thrown";
				throw std::exception(errMsg.c_str());
			}
		};
		//!Shrink the memory to accommodate objects for size - intSize
		void shrink(size_t intSize)
		{
			try
			{
				//safety checks
				if (!m_ptrData) { return; };

				size_t intOldSize, intNewSize, intCurrEnd, intNewEnd;
				intCurrEnd = m_ptrData->m_intSize;
				//safety check. If requested shrink is greater than current size, alloc a zero size string
				if (intSize > intCurrEnd)
				{
					intNewSize = sizeof(HtlVectorNode<TObj>);
					m_ptrData = (HtlVectorNode<TObj>*) qMemReAlloc(m_ptrData, intNewSize);
					return;
				};
				//otherwise perform shrink

				intOldSize = sizeof(HtlVectorNode<TObj>) + ((m_ptrData->m_intSize) * sizeof(TObj));
				intNewSize = intOldSize - (intSize * sizeof(TObj));//SUBTRACT FROM EXISTING
				intNewEnd = intCurrEnd - intSize;
				//This constructor takes the incoming text and
				//appends it to the current string
				if ((!m_ptrData) || (intOldSize <= 0)) {
					//no TObjacters, nothing to do...
					//return gracefully
					m_ptrData = &m_objSharedNull;
					memset(&m_objSharedNull.m_arrObj[0], 0, sizeof(TObj));


					return;
				}
				else {
					//reserve the memory

					//clean up the tail before the reallocation
					TObj *it = m_ptrData->m_arrObj + intCurrEnd;
					TObj* itBegin = m_ptrData->m_arrObj + intNewEnd;
					if (HTL::TypeInfo<TObj>::isComplex)
					{
						while (it != itBegin)
						{
							--it;
							it->~TObj();
						};
					};
					//qMemReAllocAligned(void *oldptr, size_t newsize, size_t oldsize, size_t alignment)
					m_ptrData = (HtlVectorNode<TObj>*) qMemReAlloc(m_ptrData, intNewSize);

					//set the container sizes
					m_ptrData->m_intSize = intNewEnd;
					m_ptrData->m_intAlloc = m_ptrData->m_intSize;
					memset(&m_ptrData->m_arrObj[intNewEnd], '\0', sizeof(TObj));
					return;
				};
				return;
			}
			catch (...)
			{
				std::string errMsg;
				errMsg = "Htl1DVector shrink Error thrown";
				throw std::exception(errMsg.c_str());
			}
		};


	public:
	//Virtual Inheritance Serialization Engines
	//SERIALIZATION ACCESSOR MACRO///////////////////////////////////////
	//!Save Vector information and item sub element information to the HTL archive tree structure
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
			int intReturn = 1;
			size_t i, intNumItems;
			char chrBuf[256];
			std::string strIndexName;
			Iterator iter;
			HtlElement * ptrNewElement = NULL;

			i = 0;
			//CALL PARENT CLASS SERIALIZATION FIRST
			if(ptrCurrNode)
			{
				//Serialize Local Sub objects if blnWithSubObjects flag is set to TRUE-------------------->

				//get the number of elements
				intNumItems = size();
				//set the elements to XML
				for(iter = begin(); iter != end();++iter)
				{				
					itoa(i,chrBuf,10);
					strIndexName = "IT_";
					strIndexName += chrBuf;
					TObj objVal = (*iter);
					//SOME FUNCTION FOR SETTING THE XML ITEM REGARDLESS OF TYPE
					HTL::SetHtlMemVar<TObj,TObjEnum>(ptrCurrNode,strIndexName,objVal,blnWithSubObjects);
					++i;
				};
			};//end valid new node check
			return 1;
		}catch(...){
			std::string errMsg;
			errMsg = "Htl1DVector Save Error thrown";
			throw std::exception(errMsg.c_str());
			return -1;
		};

		return intReturn;

	};
	//!Load Vector information and item sub element information from the HTL archive tree structure
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
				resize(intNumItems);
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
			errMsg = "Htl1DVector Load Error thrown";
			throw std::exception(errMsg.c_str());
			return -1;
		};
		return intReturn;

	};



	};//end Htl1DVector class definition

};//end namspace Htl

#endif//HtlBASE_H


