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

#ifndef STL_VECTOR_H
#define STL_VECTOR_H
#include <vector>
using namespace std;

#include ".\HtlContainer.h"

namespace HTL
{

	//!StlVector is a one dimensional container for objects
	/*!
		StlVector is a one dimensional container for objects
		The constructor requires the class, and it's equivalent HtlObjectType enumeration
	*/
	template<typename TObj, HtlObjectType TObjEnum>
	class StlVector : public HtlContainer<size_t,CPP_INT, TObj,TObjEnum>
	{
	protected:
		//!The wrapped vector
		std::vector<TObj> m_vect;
		

	public:
		
		typedef typename std::vector<TObj>::iterator StlIterator;
		//!Void constructor
		StlVector() : HtlContainer()
		{
			m_strType = "StlVector";
			m_objType = STL_CONTAINER;
			m_strType = "StlVector";
			m_itemType = TObjEnum;
		};

		//!Virtual Destructor
		virtual ~StlVector(void)
		{ 
			m_vect.clear();
		};

		//TEMPLATE MEMBER VARIABLE DECLARATION AND DEFINITION//////////////////////////////////
		//!Assignment Operator
		StlVector<TObj, TObjEnum> & operator=(StlVector<TObj, TObjEnum>& ptrRHS)
		{
			try
			{
				//safety check
				if (this == &ptrRHS)
					return *this;

				m_objType = STL_CONTAINER;
				m_itemType = TObjEnum;
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
				errMsg = "StlVector Assignment Operator Error thrown";
				throw std::exception(errMsg.c_str());
			}
		};

		inline void push_back(const TObj &t) 
		{ 
			try
			{
				HtlGUID128 objNullID;
				objNullID.newID();
				m_objLock.lock(objNullID);

				m_vect.push_back(t);

				m_objLock.unlock(objNullID);
			}
			catch (...)
			{
				std::string errMsg;
				errMsg = "StlVector push_back Error thrown";
				throw std::exception(errMsg.c_str());
			}
		};

		void pop_back() 
		{ 
			try
			{
				HtlGUID128 objNullID;
				objNullID.newID();
				m_objLock.lock(objNullID);

				m_vect.pop_back();

				m_objLock.unlock(objNullID);
			}
			catch (...)
			{
				std::string errMsg;
				errMsg = "StlVector pop_back Error thrown";
				throw std::exception(errMsg.c_str());
			}
		};
	
		//!HTL Container Analyzers
		//!Returns the length of the vector minus the null terminator (\0)
		virtual size_t size(void) const
		{
			return m_vect.size();
		};
		
		//!Returns the length of the vector minus the null terminator (\0)
		virtual size_t count(void) const
		{
			return m_vect.size();
		};

		//!Forces a recount of the length of the string minus the null terminator (\0)
		virtual void recount(void)
		{
			m_vect.size();
			return;
		};

		//!Is the Container Empty
		virtual bool isEmpty(void) const
		{

			if (m_vect.size() <= 0)
			{return true;}else{return false;};

			return true;
		};
		//!What is the Current Capacity of the container
		virtual size_t capacity(void) const
		{//
			return m_vect.size();
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

				m_vect.clear();

				m_objLock.unlock(objNullID);

				return;
			}
			catch (...)
			{
				std::string errMsg;
				errMsg = "StlVector clear Error thrown";
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
			m_vect.reserve(size);	//TO BE ADDED
		};


		//!Item accessor function
		StlIterator begin(void)
		{
			return m_vect.begin();
		};
		StlIterator end(void)
		{
			return m_vect.end();
		};

		virtual TObj & at(size_t i)
		{
			return m_vect.at(i);
		};
		//!Item accessor function
		virtual TObj & operator[](size_t i)
		{
			return m_vect.at(i);
		};

		//!Insert single object N times
		void insert(StlIterator before, const TObj &t)
		{
			try
			{
				//safety checks
				HtlGUID128 objNullID;
				objNullID.newID();
				m_objLock.lock(objNullID);

				m_vect.insert(t);

				m_objLock.unlock(objNullID);

				return m_ptrData->m_arrObj + intOffset;
			}
			catch (...)
			{
				std::string errMsg;
				errMsg = "StlVector insert Error thrown";
				throw std::exception(errMsg.c_str());
			}
		}

		//!Erase single object at iterator location
		StlIterator erase(size_t index)
		{
			try
			{
				vector<TObj>::iterator itNext;
				HtlGUID128 objNullID;
				objNullID.newID();

				if ((index >= 0) || (index < this->size()))
				{
					m_objLock.lock(objNullID);
					StlIterator iter = m_vect.begin();
					size_t i = 0;
					//shift the old cells to the left
					while ((iter != m_vect.end()) && (i != index))
					{
						++iter;
						i++;
					};
					if (i == index)
					{
						itNext = m_vect.erase(iter);
					}

					//unlock container
					m_objLock.unlock(objNullID);
				}

				//return the leading edge
				return itNext;
			}
			catch (...)
			{
				std::string errMsg;
				errMsg = "StlVector erase Error thrown";
				throw std::exception(errMsg.c_str());
			}
		};


		//!Erase single object at iterator location
		StlIterator erase(StlIterator abegin)
		{
			try
			{
				vector<TObj>::iterator itNext;
				HtlGUID128 objNullID;
				objNullID.newID();
				m_objLock.lock(objNullID);
				//shift the old cells to the left
				itNext = m_vect.erase(abegin);
				//unlock container
				m_objLock.unlock(objNullID);
				//return the leading edge
				return itNext;
			}
			catch (...)
			{
				std::string errMsg;
				errMsg = "StlVector erase Error thrown";
				throw std::exception(errMsg.c_str());
			}
		};
		//!Erase objects from begin to end iterators
		StlIterator erase(StlIterator abegin, StlIterator aend)
		{
			try
			{
				int i;
				if (!m_ptrData) { return NULL; };
				int intOffset = int(abegin - m_ptrData->m_arrObj);
				int intSpan = int(aend - abegin);
				vector::iterator itNext;
				HtlGUID128 objNullID;
				objNullID.newID();
				m_objLock.lock(objNullID);
				TObj objTemp = t;//temp copy for duplication

				itNext = m_vect.erase(abegin, aend);

				//unlock container
				m_objLock.unlock(objNullID);
				//return the leading edge
				return  m_ptrData->m_arrTObj + intOffset;
			}
			catch (...)
			{
				std::string errMsg;
				errMsg = "StlVector erase Error thrown";
				throw std::exception(errMsg.c_str());
			}
		}


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
			StlIterator iter;
			HtlElement * ptrNewElement = NULL;

			i = 0;
			//CALL PARENT CLASS SERIALIZATION FIRST
			if(ptrCurrNode)
			{
				//Serialize Local Sub objects if blnWithSubObjects flag is set to TRUE-------------------->

				//get the number of elements
				intNumItems = size();
				//set the elements to XML
				for (iter = m_vect.begin(); iter != m_vect.end(); ++iter)
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
			errMsg = "StlVector Save Error thrown";
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
						bool blnIsPointer = HTL::IsPointer<TObj>();
						HtlBaseCreator<TObj> objInit;
						objInit.Create(strItemTypeName,objTemp);
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
			errMsg = "StlVector Load Error thrown";
			throw std::exception(errMsg.c_str());
			return -1;
		};
		return intReturn;

	};



	};//end StlVector class definition

};//end namspace Htl

#endif//HtlBASE_H


