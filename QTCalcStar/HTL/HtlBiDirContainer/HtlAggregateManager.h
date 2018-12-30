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

#ifndef HTL_AGGREGATEMANAGER_H
#define HTL_AGGREGATEMANAGER_H	

#include "..\HtlObject\HtlObject.h"
#include "..\modHtlGUID.h"
#include "..\modHtlArchive.h"

#include ".\HtlObjectAggPtr.h"
#include "..\HtlThread\HtlSpinLock.h"
#include "..\HtlContainer\Htl1DVector.h"
namespace HTL
{
	typedef Htl1DVector< HtlObjectAggPtr, HTL_BASE> HtlObjectAggList;
	typedef Htl1DVector< HtlObjectAggPtr, HTL_BASE >::Iterator HtlObjectAggListIter;


	template<typename TObj, HtlObjectType TObjEnum>
	class HtlAggregateManager :
		public HtlObject
	{
	public:
		HtlAggregateManager(void);
		HtlAggregateManager(HtlObject * ptrParent);
		HtlAggregateManager(const HtlAggregateManager& rhs);
		HtlAggregateManager & operator = (const HtlAggregateManager & rhs);

		virtual ~HtlAggregateManager(void);

		//!Pointer to the parent object
		HTLMEMVAR_BYVAL_STYLE1(public, HtlObject*, ptrParent);

		//!This boolean flage is very important to the behaviour of the object.
		/*!It is a boolean flag that sets whether or not the container behaves as if it is the bi directional relationship primary object.
		In other words the object has the diamond on the UML diagram, then this flag should be set to true. If it doesn't have the 
		diamond, then it should be set to false
		*/
		HTLMEMVAR_BYVAL_STYLE1(public, bool, blnPrimary);

		//!This protected variable allows for locking the vector during a transaction to prevent circular referencing.
		//It is used in the Add / Remove controls
		HTLMEMVAR_BYVAL_STYLE1(private, bool, blnLocked);
		
		//!This is the unique string Link ID that is shared between the objects
		HTLMEMVAR_BYVAL_STYLE1(public, std::string, strLinkID);

		//PUBLIC MEMBER FUNCTIONS
		int DoesObjectExist(HtlGUID128 objGUID, bool & blnExistReturn, long & lngIndexReturn);

		//HTLOBJECT ACCESSOR METHODS///////////////////////////////////
		//get the pointer to an object by it's global unique identifier
		HtlObject * GetHtlObject(size_t lngIndex);
		HtlObject * GetHtlObject(HtlGUID128 objGUID);
		HtlObject * GetHtlObject(std::string strGUID);
		size_t GetObjectIndex(HtlGUID128 objGUID);
		size_t GetObjectIndex(std::string strGUID);
		int ClearObjCompPtr(HtlGUID128 objGUID);
		int ClearObjCompPtr(std::string strGUID);
		//element GUID accessing
		HtlGUID128 GetObjectGUID(size_t lngIndex);
		int GetAllObjectGUIDs(std::vector<HtlGUID128> & arrObjGUIDReturn);
		//element based indexing
		HtlObject * FirstHtlObject(void);
		HtlObject * LastHtlObject(void);
		//iterator based indexing
		HtlObjectAggListIter BeginHtlObject(void);
		HtlObjectAggListIter EndHtlObject(void);

		HtlObject * AtHtlObject(size_t lngIndex);
		size_t Size(void) const;
		//swaps two objects in the collection for sorting purposes
		int SwapObjects(size_t intA, size_t intB);

		//OBJECT POINTER BASED ACCESSORS///////////////////////
		//Get the pointer to an object by it's global unique identifier
		TObj* GetObject(HtlGUID128 objGUID);
		TObj* GetObject(std::string strGUID);
		TObj * First(void);
		TObj * Last(void);
		TObj * At(size_t lngIndex);
		HtlObjectAggPtr AtAggPtr(size_t lngIndex);

		//custom find objects methods
		HtlObjectAggListIter FindObject(HtlGUID128 objGUID);
		HtlObjectAggListIter FindObject(std::string strGUID);
		HtlObjectAggListIter FindObject(TObj * ptrObject);

		//OBJECT ADD METHODS////////////////////////////
		//! Adds an object to the Aggregate Object Member List
		int AddObject( TObj* ptrObjectTemp);
		//OBJECT REMOVE METHODS////////////////////////////
		//! Removes an object from the member list based on index
		int RemoveObject( size_t lngIndex);
		//! Removes an object from the member list based on the object's GUID
		int RemoveObject( HtlGUID128 objGUID);
		//! Removes an object from the member list based on the object's GUID
		int RemoveObject( std::string strGUID);
		//! Removes all objects from the member list
		int RemoveAllObjects (void);

		//BIDIRECTIONAL REMOVE TO AVOID CIRCULAR REFERENCING
		//! Removes an object from the member list based on the object's GUID
		int BiDirAddObject( HtlObject * ptrObj);
		//! Removes an object from the member list based on the object's GUID
		int BiDirRemoveObject( HtlObject * ptrObj);


		//! Sets the pointer of the object with the GUID to NULL but leaves the GUID and pointer in tact
		int ClearPointer( HtlGUID128 objGUID);
		//! Sets the pointer of the object with the GUID to NULL but leaves the GUID and pointer in tact
		int ClearAllPointers(void);

		//Virtual Inheritance Serialization Engines
		//SERIALIZATION FUNCTIONS///////////////////////////////////////
		//!Save member data to the current element node
		virtual int Save(HTL::HtlElement * ptrCurrNode, std::string strMemVarName, bool blnWithSubObjects);
		//!Load member data from the current element node
		virtual int Load(HTL::HtlElement * ptrCurrNode, std::string strMemVarName);
	private:

		//!THE COLLECTION OF HTLOBJECTS
		Htl1DVector< HtlObjectAggPtr ,HTL_BASE> m_arrPtrCollection;

	};//end class definition

	//TEMPLATE FUNCTION DEFINITIONS
	template<typename TObj, HtlObjectType TObjEnum>
	HtlAggregateManager<TObj,TObjEnum>::HtlAggregateManager(void)
		: HtlObject()
	{
		m_strType = "HtlAggregateManager";
		m_objType = HTL_BASE;
		m_ptrParent = NULL;
		m_ptrOwner = NULL;
		m_blnPrimary = true;
		m_blnLocked = false;

		return;
	};

	template<typename TObj, HtlObjectType TObjEnum>
	HtlAggregateManager<TObj,TObjEnum>::HtlAggregateManager(HtlObject * ptrParent)
		: HtlObject
	{
		//HtlObject Initialization Section
		m_strType = "HtlAggregateManager";
		m_objType = HTL_BASE;
		m_ptrPrimary = true;
		m_blnLocked = false;
		if(ptrParent)
		{
			m_ptrParent = ptrParent;
		}else{
			m_ptrParent = NULL;
		};
		return;
	};

	template<typename TObj, HtlObjectType TObjEnum>
	HtlAggregateManager<TObj,TObjEnum>::HtlAggregateManager(const  HtlAggregateManager<TObj,TObjEnum> & rhs)
		: HtlObject(rhs)
	{
      try
      {
         //HtlObject Initialization Section
         m_strTypeName = "HtlAggregateManager";
         m_objType = HTL_BASE;
         m_ptrParent = rhs.Get_ptrParent();
         m_ptrPrimary = true;
         m_blnLocked = false;
         //HtlCollectionManager Initialization Section
         //go through objects and clone them
         DeleteAllObjects();
         TObj* ptrNewObj = NULL;
         size_t i, intNumObjects;
         intNumObjects = rhs.Size();
         for (i = 0; i < intNumObjects; i++)
         {
            ptrNewObj = CreateObject();
            if (ptrNewObj)
            {
               *(ptrNewObj) = *(rhs.At(i));
            };
         };

      }
      catch (...)
      {
         std::string errMsg;
         errMsg = "HtlAggregateManager Copy Constructor Error thrown";
         throw std::exception(errMsg.c_str());
      }

		return;
	};

	template<typename TObj, HtlObjectType TObjEnum>
	HtlAggregateManager<TObj,TObjEnum> & HtlAggregateManager<TObj,TObjEnum>::operator = (const HtlAggregateManager<TObj,TObjEnum> & rhs)
	{
      try
      {
         if (this != &rhs)
         {
            HtlObject::operator=(rhs);
            //HtlObject Initialization Section
            m_strTypeName = "HtlAggregateManager";
            m_objType = HTL_BASE;
            m_ptrParent = rhs.Get_ptrParent();
            m_ptrPrimary = true;
            m_blnTransactionLocked = false;
            //HtlCollectionManager Initialization Section
            //go through objects and clone them
            DeleteAllObjects();
            TObj* ptrNewObj = NULL;
            size_t i, intNumObjects;
            intNumObjects = rhs.Size();
            for (i = 0; i < intNumObjects; i++)
            {
               ptrNewObj = CreateObject();
               if (ptrNewObj)
               {
                  *(ptrNewObj) = *(rhs.At(i));
               };
            };
         };//end self assignment check

         return *this;
      }
      catch (...)
      {
         std::string errMsg;
         errMsg = "HtlAggregateManager Assignment Operator Error thrown";
         throw std::exception(errMsg.c_str());
      }
	};

	template<typename TObj, HtlObjectType TObjEnum>
	HtlAggregateManager<TObj,TObjEnum>::~HtlAggregateManager(void)
	{
		return;
	};

	template<typename TObj, HtlObjectType TObjEnum>
	int HtlAggregateManager<TObj,TObjEnum>::DoesObjectExist(HtlGUID128 objGUID, bool & blnExistReturn, long & lngIndexReturn)
	{
      try
      {
         long i, intUboundI;
         HtlObject * ptrCurrObj = NULL;
         HtlGUID128 objCurrGUID;
         intUboundI = m_arrPtrCollection.size();
         blnExistReturn = false;
         lngIndexReturn = -1;
         for (i = 0; i < intUboundI;i++)
         {
            ptrCurrObj = m_arrPtrCollection.at(i).GetObjPtr();
            if (ptrCurrObj)
            {
               objCurrGUID = ptrCurrObj->Get_objGUID();
               if (objCurrGUID == objGUID)
               {
                  //then we have found it
                  blnExistReturn = true;
                  lngIndexReturn = i;
                  return 1;
               }
            };//end valid object check
         }
         return 0;
      }
      catch (...)
      {
         std::string errMsg;
         errMsg = "HtlAggregateManager DoesObjectExist Error thrown";
         throw std::exception(errMsg.c_str());
      }
	};

	//Get the object pointer based on the index
	template<typename TObj, HtlObjectType TObjEnum>
	HtlObject * HtlAggregateManager<TObj,TObjEnum>::GetHtlObject(size_t lngIndex)
	{
		try{
			if((lngIndex >= 0)&&(lngIndex < m_arrPtrCollection.size()))
			{
				return (m_arrPtrCollection.at(lngIndex).GetObjPtr() );
			}else{
				return NULL;
			};
		}catch(...){
         std::string errMsg;
         errMsg = "HtlNode GetHtlObject Error thrown";
         throw std::exception(errMsg.c_str());
			return NULL;
		}
		return NULL;	
	};

	//Get the pointer to an object by it's global unique identifier
	template<typename TObj, HtlObjectType TObjEnum>
   HtlObject * HtlAggregateManager<TObj, TObjEnum>::GetHtlObject(HtlGUID128 objGUID)
   {
      try
      {
         long i, intUboundI;
         HtlGUID128 objCurrGUID;
         intUboundI = m_arrPtrCollection.size();
         HtlObject* ptrObjReturn = NULL;
         HtlObject* ptrCurrObj = NULL;
         //CYCLE THROUGH THE COLLECTION TO FIND IT
         for (i = 0; i < intUboundI;i++)
         {
            ptrCurrObj = m_arrPtrCollection.at(i).GetObjPtr();
            if (ptrCurrObj)
            {
               objCurrGUID = ptrCurrObj->Get_objGUID();
               if (objCurrGUID == objGUID)
               {
                  //then we have found it
                  ptrObjReturn = m_arrPtrCollection.at(i).GetObjPtr();
               };
            };//end valid object check
         };
         return ptrObjReturn;
      }
      catch (...)
      {
         std::string errMsg;
         errMsg = "HtlAggregateManager GetHtlObject Error thrown";
         throw std::exception(errMsg.c_str());
      }

   };

	template<typename TObj, HtlObjectType TObjEnum>
	HtlObject * HtlAggregateManager<TObj,TObjEnum>::GetHtlObject(std::string strGUID)
	{		
      try
      {
         bool blnGUIDConvSuccess = false;
         long i, intUboundI;
         HtlObject* ptrCurrObj = NULL;
         HtlObject* ptrObjReturn = NULL;
         HtlGUID128 objCurrGUID, objGUID;
         blnGUIDConvSuccess = objGUID.fromStdString(strGUID);
         if (blnGUIDConvSuccess == false)
         {
            //bad GUID conversion
            return NULL;
         }

         intUboundI = m_arrPtrCollection.size();

         //CYCLE THROUGH THE COLLECTION TO FIND IT
         for (i = 0; i < intUboundI;i++)
         {
            ptrCurrObj = m_arrPtrCollection.at(i).GetObjPtr();
            if (ptrCurrObj)
            {
               objCurrGUID = ptrCurrObj->Get_objGUID();
               if (objCurrGUID == objGUID)
               {
                  //then we have found it
                  return ptrCurrObj;
               };
            };
         }

         return ptrObjReturn;
      }
      catch (...)
      {
         std::string errMsg;
         errMsg = "HtlAggregateManager GetHtlObject Error thrown";
         throw std::exception(errMsg.c_str());
      }
   };

	template<typename TObj, HtlObjectType TObjEnum>
	size_t HtlAggregateManager<TObj,TObjEnum>::GetObjectIndex(HtlGUID128 objGUID)
   {
      try
      {
         size_t i, intUboundI;
         HtlGUID128 objCurrGUID;
         HtlObject* ptrCurrObj = NULL;
         HtlObject* ptrObjReturn = NULL;
         //CYCLE THROUGH THE COLLECTION TO FIND IT
         intUboundI = m_arrPtrCollection.size();
         for (i = 0; i < intUboundI;i++)
         {
            ptrCurrObj = m_arrPtrCollection.at(i).GetObjPtr();
            if (ptrCurrObj)
            {
               objCurrGUID = ptrCurrObj->Get_objGUID();
               if (objCurrGUID == objGUID)
               {
                  //then we have found it
                  return i;
               };
            };
         }
         return -1;

      }
      catch (...)
      {
         std::string errMsg;
         errMsg = "HtlAggregateManager GetObjectIndex Error thrown";
         throw std::exception(errMsg.c_str());
      }

	};

	template<typename TObj, HtlObjectType TObjEnum>
	size_t HtlAggregateManager<TObj,TObjEnum>::GetObjectIndex(std::string strGUID)
	{
      try
      {
         bool blnGUIDConvSuccess = false;
         long i, intUboundI;
         HtlObject* ptrCurrObj = NULL;
         HtlObject* ptrObjReturn = NULL;
         HtlGUID128 objCurrGUID, objGUID;
         blnGUIDConvSuccess = objGUID.fromStdString(strGUID);
         if (blnGUIDConvSuccess == false)
         {
            //bad GUID conversion
            return NULL;
         }

         intUboundI = m_arrPtrCollection.size();

         //CYCLE THROUGH THE COLLECTION TO FIND IT
         for (i = 0; i < intUboundI;i++)
         {
            ptrCurrObj = m_arrPtrCollection.at(i).GetObjPtr();
            if (ptrCurrObj)
            {
               objCurrGUID = ptrCurrObj->Get_objGUID();
               if (objCurrGUID == objGUID)
               {
                  //then we have found it
                  return i;
               };
            };
         }
         return -1;
      }
      catch (...)
      {
         std::string errMsg;
         errMsg = "HtlAggregateManager GetObjectIndex Error thrown";
         throw std::exception(errMsg.c_str());
      }
   };

   template<typename TObj, HtlObjectType TObjEnum>
	int HtlAggregateManager<TObj,TObjEnum>::ClearObjCompPtr(HtlGUID128 objGUID)
	{
      try
      {
         long i, intUboundI;
         HtlGUID128 objCurrGUID;
         intUboundI = m_arrPtrCollection.size();
         HtlObject* ptrObjectReturn = NULL;
         HtlObject* ptrCurrObj = NULL;
         //CYCLE THROUGH THE COLLECTION TO FIND IT
         intUboundI = m_arrPtrCollection.size();
         for (i = 0; i < intUboundI;i++)
         {
            objCurrGUID = m_arrPtrCollection.at(i).m_objGUID;
            if (objCurrGUID == objGUID)
            {
               //then we have found it
               m_arrPtrCollection.at(i).SetObjPtr(NULL);
               return 1;
            };
         };
         return 0;

      }
      catch (...)
      {
         std::string errMsg;
         errMsg = "HtlAggregateManager ClearObjCompPtr Error thrown";
         throw std::exception(errMsg.c_str());
      }
	};

	template<typename TObj, HtlObjectType TObjEnum>
	int HtlAggregateManager<TObj,TObjEnum>::ClearObjCompPtr(std::string strGUID)
	{
      try
      {
         bool blnGUIDConvSuccess = false;
         long i, intUboundI;
         HtlObject* ptrCurrObj = NULL;
         HtlObject* ptrObjReturn = NULL;
         HtlGUID128 objCurrGUID, objGUID;
         blnGUIDConvSuccess = objGUID.fromStdString(strGUID);
         if (blnGUIDConvSuccess == false)
         {
            //bad GUID conversion
            return NULL;
         }
         intUboundI = m_arrPtrCollection.size();
         //CYCLE THROUGH THE COLLECTION TO FIND IT
         for (i = 0; i < intUboundI;i++)
         {
            objCurrGUID = m_arrPtrCollection.at(i).m_objGUID;
            if (objCurrGUID == objGUID)
            {
               //then we have found it
               m_arrPtrCollection.at(i).SetObjPtr(NULL);
               return 1;
            };
         };
         return 0;
      }
      catch (...)
      {
         std::string errMsg;
         errMsg = "HtlAggregateManager ClearObjCompPtr Error thrown";
         throw std::exception(errMsg.c_str());
      }
	};



	//ELEMENT GUID ACCESSING METHODS
	////////////////////////////////////////////////////////////////////////////
	template<typename TObj, HtlObjectType TObjEnum>
	HtlGUID128 HtlAggregateManager<TObj,TObjEnum>::GetObjectGUID(size_t lngIndex)
   {
      try
      {
         size_t intUboundI;
         HtlGUID128 objCurrGUID;
         intUboundI = m_arrPtrCollection.size();
         if ((lngIndex >= 0) && (lngIndex < intUboundI))
         {
            m_arrPtrCollection.at(lngIndex).GetObjPtr();
            HtlObjectAggPtr ptrCurr = m_arrPtrCollection.at(lngIndex);
            if (ptrCurr.m_ptrObject)
            {
               return ptrCurr->Get_objGUID();
            }
            else {
               HtlGUID128 objNull;
               objNull.setNull();
               return objNull;
            }
         }
         else {
            HtlGUID128 objNull;
            objNull.setNull();
            return objNull;
         };

      }
      catch (...)
      {
         std::string errMsg;
         errMsg = "HtlAggregateManager GetObjectGUID Error thrown";
         throw std::exception(errMsg.c_str());
      }

   };

	template<typename TObj, HtlObjectType TObjEnum>
	int HtlAggregateManager<TObj,TObjEnum>::GetAllObjectGUIDs(std::vector<HtlGUID128> & arrObjGUIDReturn)
	{
      try
      {
         arrObjGUIDReturn.clear();
         long i, intUboundI;
         HtlGUID128 objCurrGUID;
         intUboundI = m_arrPtrCollection.size();
         if (intUboundI <= 0)
         {
            //nothing in collection
            return 0;
         };
         //CYCLE THROUGH THE COLLECTION TO FIND IT
         for (i = 0; i < intUboundI;i++)
         {
            m_arrPtrCollection.at(i).GetObjPtr();
            if (m_arrPtrCollection.at(i).m_ptrObject)
            {
               objCurrGUID = m_arrPtrCollection.at(i)->Get_objGUID();
               arrObjGUIDReturn.push_back(objCurrGUID);
            }
         }
         return 1;

      }
      catch (...)
      {
         std::string errMsg;
         errMsg = "HtlAggregateManager GetObjectGUID Error thrown";
         throw std::exception(errMsg.c_str());
      }
   };

	//element based indexing
	template<typename TObj, HtlObjectType TObjEnum>
	HtlObject * HtlAggregateManager<TObj,TObjEnum>::FirstHtlObject(void)
	{
		try{
			return (m_arrPtrCollection.front().GetObjPtr() );
		}catch(...){
         std::string errMsg;
         errMsg = "HtlAggregateManager FirstHtlObject Error thrown";
         throw std::exception(errMsg.c_str());
			return NULL;
		};
	};

	template<typename TObj, HtlObjectType TObjEnum>
	HtlObject * HtlAggregateManager<TObj,TObjEnum>::LastHtlObject(void)
	{
		try{
			return (m_arrPtrCollection.back().GetDBPtr() );
		}catch(...){
         std::string errMsg;
         errMsg = "HtlAggregateManager LastHtlObject Error thrown";
         throw std::exception(errMsg.c_str());
			return NULL;
		};
	};

	//iterator based indexing
	template<typename TObj, HtlObjectType TObjEnum>
	HtlObjectAggListIter HtlAggregateManager<TObj,TObjEnum>::BeginHtlObject(void)
	{
		try{
			return (m_arrPtrCollection.begin() );
		}catch(...){
         std::string errMsg;
         errMsg = "HtlAggregateManager BeginHtlObject Error thrown";
         throw std::exception(errMsg.c_str());
			return (m_arrPtrCollection.end() );
		};
	};

	template<typename TObj, HtlObjectType TObjEnum>
	HtlObjectAggListIter HtlAggregateManager<TObj,TObjEnum>::EndHtlObject(void)
	{
		try{
			return (m_arrPtrCollection.end() );
		}catch(...){
         std::string errMsg;
         errMsg = "HtlAggregateManager EndHtlObject Error thrown";
         throw std::exception(errMsg.c_str());
			return (m_arrPtrCollection.end() );
		};
	};

	template<typename TObj, HtlObjectType TObjEnum>
	HtlObject* HtlAggregateManager<TObj,TObjEnum>::AtHtlObject(size_t lngIndex)
	{
		ORS_SAFEMETHOD(ORSDBObject* );
		try{
			if((lngIndex > 0)&&(lngIndex < m_arrPtrCollection.size()))
			{
				return (m_arrPtrCollection.at(lngIndex).GetObjPtr() );
			}else{
				return NULL;
			}
		}catch(...){
         std::string errMsg;
         errMsg = "HtlAggregateManager AtHtlObject Error thrown";
         throw std::exception(errMsg.c_str());
			return NULL;
		}
	};

	template<typename TObj, HtlObjectType TObjEnum>
	size_t HtlAggregateManager<TObj,TObjEnum>::Size(void) const
	{
		try{
			return (m_arrPtrCollection.size());
		}catch(...){
         std::string errMsg;
         errMsg = "HtlAggregateManager Size Error thrown";
         throw std::exception(errMsg.c_str());
			return 0;
		}
	};

	//swaps two objects in the collection for sorting purposes
	template<typename TObj, HtlObjectType TObjEnum>
	int HtlAggregateManager<TObj,TObjEnum>::SwapObjects(size_t intA, size_t intB)
	{
      try
      {
         size_t intSize = m_arrPtrCollection.size();
         //safety check indexes
         if ((intA < 0) || (intA >= intSize)) { return -1; };
         if ((intB < 0) || (intB >= intSize)) { return -1; };

         HtlObjectAggPtr ptrTemp;
         ptrTemp = m_arrPtrCollection.at(intA);
         m_arrPtrCollection.at(intA) = m_arrPtrCollection.at(intB);
         m_arrPtrCollection.at(intB) = ptrTemp;
         return 1;
      }
      catch (...)
      {
         std::string errMsg;
         errMsg = "HtlAggregateManager Size Error thrown";
         throw std::exception(errMsg.c_str());
         return 0;
      }
	};

	//OBJECT POINTER BASED ACCESSORS///////////////////////
	//Get the pointer to an object by it's global unique identifier
	template<typename TObj, HtlObjectType TObjEnum>
	TObj* HtlAggregateManager<TObj,TObjEnum>::GetObject(HtlGUID128 objGUID)
	{
      try
      {
         size_t i, intUboundI;
         HtlGUID128 objCurrGUID;
         intUboundI = m_arrPtrCollection.size();
         TObj* ptrObjReturn = NULL;
         //CYCLE THROUGH THE COLLECTION TO FIND IT
         for (i = 0; i < intUboundI;i++)
         {
            objCurrGUID = m_arrPtrCollection.at(i)->Get_objGUID();

            if (objCurrGUID == objGUID)
            {
               //then we have found it
               ptrObjReturn = (dynamic_cast<TObj*>(m_arrPtrCollection.at(i).GetObjPtr()));
            }
         }

         return ptrObjReturn;
      }
      catch (...)
      {
         std::string errMsg;
         errMsg = "HtlAggregateManager GetObject thrown";
         throw std::exception(errMsg.c_str());
         return 0;
      }
   };

	template<typename TObj, HtlObjectType TObjEnum>
	TObj* HtlAggregateManager<TObj,TObjEnum>::GetObject(std::string strGUID)
	{	
      try
      {
         bool blnGUIDConvSuccess = false;
         size_t i, intUboundI;
         HtlGUID128 objCurrGUID, objGUID;
         blnGUIDConvSuccess = objGUID.fromStdString(strGUID);
         if (blnGUIDConvSuccess == false)
         {	//bad GUID conversion
            return NULL;
         }

         intUboundI = m_arrPtrCollection.size();
         TObj* ptrObjReturn = NULL;
         //CYCLE THROUGH THE COLLECTION TO FIND IT
         for (i = 0; i < intUboundI;i++)
         {
            objCurrGUID = m_arrPtrCollection.at(i)->Get_objGUID();

            if (objCurrGUID == objGUID)
            {
               //then we have found it
               ptrObjReturn = (dynamic_cast<TObj*>(m_arrPtrCollection.at(i).GetObjPtr()));
            }
         }

         return ptrObjReturn;
      }
      catch (...)
      {
         std::string errMsg;
         errMsg = "HtlAggregateManager GetObject thrown";
         throw std::exception(errMsg.c_str());
         return 0;
      }
   };


	template<typename TObj, HtlObjectType TObjEnum>
	TObj * HtlAggregateManager<TObj,TObjEnum>::First(void)
	{

		try{
			HtlObjectAggPtr ptrObjTemp;
			ptrObjTemp = m_arrPtrCollection.front();
			return (dynamic_cast<TObj*>(ptrObjTemp.GetObjPtr() ) );
		}catch(...){
         std::string errMsg;
         errMsg = "HtlAggregateManager First thrown";
         throw std::exception(errMsg.c_str());
			return NULL;
		}
	};

	template<typename TObj, HtlObjectType TObjEnum>
	TObj * HtlAggregateManager<TObj,TObjEnum>::Last(void)
	{
		try{
			HtlObjectAggPtr ptrObjTemp;
			ptrObjTemp = m_arrPtrCollection.back();
			return (dynamic_cast<TObj*>(ptrObjTemp.GetObjPtr() ) );
		}catch(...){
         std::string errMsg;
         errMsg = "HtlAggregateManager Last Error thrown";
         throw std::exception(errMsg.c_str());
			return NULL;
		}
	};

	template<typename TObj, HtlObjectType TObjEnum>
	TObj * HtlAggregateManager<TObj,TObjEnum>::At(size_t lngIndex)
	{

		try{
			if((lngIndex >= 0)&&(lngIndex < m_arrPtrCollection.size()))
			{
				HtlObjectAggPtr ptrTemp = m_arrPtrCollection.at(lngIndex);
				std::string strGUID = ptrTemp.m_objGUID.toStdString();
				//debugging code
				TObj* ptrItem = dynamic_cast<TObj*>(ptrTemp.GetObjPtr());
				if(ptrItem)
				{
					HtlGUID128 objGUID2 = ptrItem->Get_objGUID();
					std::string strGUID2 = objGUID2.toStdString();
				}
				return ptrItem;
			}else{
				//illegal index
				return NULL;
			};
		}catch(...){
         std::string errMsg;
         errMsg = "HtlAggregateManager At Error thrown";
         throw std::exception(errMsg.c_str());
			return NULL;
		}
	};

	template<typename TObj, HtlObjectType TObjEnum>
	HtlObjectAggPtr HtlAggregateManager<TObj,TObjEnum>::AtAggPtr(size_t lngIndex)
	{
		HtlObjectAggPtr ptrRet;
		try{	
			if((lngIndex >= 0)&&(lngIndex < m_arrPtrCollection.size()))
			{
				ptrRet = m_arrPtrCollection.at(lngIndex);
			}
			return ptrRet;
		}catch(...){
         std::string errMsg;
         errMsg = "HtlAggregateManager AtAggPtr Error thrown";
         throw std::exception(errMsg.c_str());
			return ptrRet;
		}
	};

	//custom find objects methods
	template<typename TObj, HtlObjectType TObjEnum>
	HtlObjectAggListIter HtlAggregateManager<TObj,TObjEnum>::FindObject(HtlGUID128 objGUID)
	{
      try
      {
         HtlObjectAggListIter iter;
         //safety code
         if (m_arrPtrCollection.size() <= 0) { return m_arrPtrCollection.end(); };
         //otherwise safe to proceed
         for (iter = m_arrPtrCollection.begin();iter != m_arrPtrCollection.end();++iter)
         {
            HtlObject* ptrCurr = iter->GetObjPtr();
            if (ptrCurr)
            {
               if (objGUID == ptrCurr->Get_objGUID())
               {
                  //then match found
                  return iter;
               }
            }
         };
         //no match found, return end iterator
         return m_arrPtrCollection.end();
      }
      catch (...)
      {
         std::string errMsg;
         errMsg = "HtlAggregateManager FindObject Error thrown";
         throw std::exception(errMsg.c_str());
         return NULL;
      }
	};

	template<typename TObj, HtlObjectType TObjEnum>
	HtlObjectAggListIter HtlAggregateManager<TObj,TObjEnum>::FindObject(std::string strGUID)
	{
      try
      {
         bool blnGUIDConvSuccess = false;
         size_t i, intUboundI;
         HtlObjectAggListIter iter;
         HtlGUID128 objCurrGUID, objGUID;
         blnGUIDConvSuccess = objGUID.fromStdString(strGUID);
         if (blnGUIDConvSuccess == false)
         {	//bad GUID conversion
            return m_arrPtrCollection.end();
         }
         //safety code
         if (m_arrPtrCollection.size() <= 0) { return m_arrPtrCollection.end(); };
         //otherwise safe to proceed
         for (iter = m_arrPtrCollection.begin();iter != m_arrPtrCollection.end();++iter)
         {
            HtlObject* ptrCurr = iter->GetObjPtr();
            if (ptrCurr)
            {
               if (objGUID == ptrCurr->Get_objGUID())
               {
                  //then match found
                  return iter;
               }
            }
         }
         //no match found, return end iterator
         return m_arrPtrCollection.end();
      }
      catch (...)
      {
         std::string errMsg;
         errMsg = "HtlAggregateManager FindObject Error thrown";
         throw std::exception(errMsg.c_str());
         return NULL;
      }
	};
	
	template<typename TObj, HtlObjectType TObjEnum>
	HtlObjectAggListIter HtlAggregateManager<TObj,TObjEnum>::FindObject(TObj * ptrObject)
	{
      try
      {
         TObj * ptrTemp = NULL;
         HtlObject * ptrHtlTemp = NULL;
         HtlObjectAggListIter iter;
         //safety code
         int intSize = m_arrPtrCollection.size();
         if (intSize <= 0) { return m_arrPtrCollection.end(); };
         //otherwise safe to proceed

         for (iter = m_arrPtrCollection.begin();iter != m_arrPtrCollection.end();++iter)
         {
            ptrTemp = NULL;
            ptrHtlTemp = (*iter).GetObjPtr();
            try {
               ptrTemp = dynamic_cast<TObj*>(ptrHtlTemp);
            }
            catch (...) {
               //error in type cast
               try {
                  //sync pointer and try again
                  (*iter).SyncObjPtr();
                  ptrHtlTemp = (*iter).GetObjPtr();
                  ptrTemp = dynamic_cast<TObj*>(ptrHtlTemp);
               }
               catch (...) {
                  //failed move on...
                  ptrTemp = NULL;
               };
            };
            if (ptrObject == ptrTemp)
            {
               //then match found
               return iter;
            };
         };
         //no match found, return end iterator
         return m_arrPtrCollection.end();
      }
      catch (...)
      {
         std::string errMsg;
         errMsg = "HtlAggregateManager FindObject Error thrown";
         throw std::exception(errMsg.c_str());
         return NULL;
      }
   };

	//OBJECT ADD METHODS////////////////////////////
	//! Adds an object to the Aggregate Object Member List
	template<typename TObj, HtlObjectType TObjEnum>
	int HtlAggregateManager<TObj,TObjEnum>::AddObject( TObj* ptrObjectTemp)
   {
      try
      {
         //First See if the object already exists in the collection, if so, then skip it
         HtlObjectAggListIter iterFind;

         iterFind = FindObject(ptrObjectTemp);
         if (iterFind != m_arrPtrCollection.end())
         {
            //then match found, quit out gracefully
            return 0;
         }
         else {
            //no match found
            //Add the object, then add the bi-directional pointer with the object

            if (m_ptrOwner)
            {
               m_ptrOwner->SetChanged();
            }

            HtlObjectAggPtr ptrTemp;
            ptrTemp.SetObjPtr(ptrObjectTemp);
            m_arrPtrCollection.push_back(ptrTemp);
            ptrObjectTemp->AddBiDirPtr(Get_ptrParent(), m_strLinkID);
            return 1;
         };
         return 1;
      }
      catch (...)
      {
         std::string errMsg;
         errMsg = "HtlAggregateManager AddObject Error thrown";
         throw std::exception(errMsg.c_str());
         return NULL;
      }
   };

	//OBJECT REMOVE METHODS////////////////////////////
	//! Removes an object from the member list based on indes lngIndexToRemove
	template<typename TObj, HtlObjectType TObjEnum>
	int HtlAggregateManager<TObj,TObjEnum>::RemoveObject( size_t lngIndex)
	{
      try
      {
         //First See if the object already exists in the collection
         size_t i, intUboundI;
         bool blnObjectExists = false;

         intUboundI = m_arrPtrCollection.size();
         if ((lngIndex >= 0) && (lngIndex < intUboundI))
         {
            HtlObject * ptrObjTemp = this->Get_ptrParent();
            if (!ptrObjTemp) { return 0; };
            HtlGUID128 objGUIDToRemove = ptrObjTemp->Get_objGUID();
            //remove the remote pointer
            TObj * ptrObjItem = this->At(lngIndex);
            if (!ptrObjItem) { return 0; };
            ptrObjItem->RemoveBiDirPtr(ptrObjTemp, m_strLinkID);
            //remove the item here
            m_arrPtrCollection.erase(m_arrPtrCollection.begin() + lngIndex);

            if (m_ptrOwner)
            {
               m_ptrOwner->SetChanged();
            }

            return 1;
         }
         else {
            //no match found
            return 0;
         };
         return 1;
      }
      catch (...)
      {
         std::string errMsg;
         errMsg = "HtlAggregateManager RemoveObject Error thrown";
         throw std::exception(errMsg.c_str());
         return NULL;
      }
   };

	//! Removes an object from the member list based on the objects GUID
	template<typename TObj, HtlObjectType TObjEnum>
	int HtlAggregateManager<TObj,TObjEnum>::RemoveObject( HtlGUID128 objGUID)
	{
      try
      {
         HtlObjectAggListIter iter = this->FindObject(objGUID);
         if (iter == m_arrPtrCollection.end()) { return 0; };

         HtlObject * ptrObjTemp = this->Get_ptrParent();
         if (!ptrObjTemp) { return 0; };
         HtlGUID128 objGUIDToRemove = ptrObjTemp->Get_objGUID();
         //remove the remote pointer
         TObj * ptrObjItem = dynamic_cast<TObj*>(iter->GetObjPtr());
         if (!ptrObjItem) { return 0; };
         ptrObjItem->RemoveBiDirPtr(ptrObjTemp, m_strLinkID);
         //remove the item here
         m_arrPtrCollection.erase(iter);

         if (m_ptrOwner)
         {
            m_ptrOwner->SetChanged();
         }
         return 1;
      }
      catch (...)
      {
         std::string errMsg;
         errMsg = "HtlAggregateManager RemoveObject Error thrown";
         throw std::exception(errMsg.c_str());
         return NULL;
      }
	};

	//! Removes an object from the member list based on the objects GUID
	template<typename TObj, HtlObjectType TObjEnum>
	int HtlAggregateManager<TObj,TObjEnum>::RemoveObject( std::string strGUID)
   {
      try
      {
         HtlObjectAggListIter iter = this->FindObject(strGUID);
         if (iter == m_arrPtrCollection.end()) { return 0; };

         HtlObject * ptrObjTemp = this->Get_ptrParent();
         if (!ptrObjTemp) { return 0; };
         HtlGUID128 objGUIDToRemove = ptrObjTemp->Get_objGUID();
         //remove the remote pointer
         TObj * ptrObjItem = dynamic_cast<TObj*>(iter->GetObjPtr());
         if (!ptrObjItem) { return 0; };
         ptrObjItem->RemoveBiDirPtr(ptrObjTemp, m_strLinkID);
         //remove the item here
         m_arrPtrCollection.erase(iter);

         if (m_ptrOwner)
         {
            m_ptrOwner->SetChanged();
         }
         return 1;
      }
      catch (...)
      {
         std::string errMsg;
         errMsg = "HtlAggregateManager RemoveObject Error thrown";
         throw std::exception(errMsg.c_str());
         return NULL;
      }
   };

	//! Removes all objects from the member list
	template<typename TObj, HtlObjectType TObjEnum>
	int HtlAggregateManager<TObj,TObjEnum>::RemoveAllObjects (void)
	{
      try
      {
         //First See if the object already exists in the collection, if so, then skip it
         size_t i, intUboundI;
         intUboundI = m_arrPtrCollection.size();
         //cycle through the collection removing links
         HtlObject * ptrObjTemp = this->Get_ptrParent();
         if (!ptrObjTemp) { return 0; };
         HtlGUID128 objGUIDToRemove = ptrObjTemp->Get_objGUID();

         for (i = 0; i < intUboundI;i++)
         {
            //remove the remote pointer
            TObj * ptrObjItem = this->At(i);
            if (!ptrObjItem) { return 0; };
            ptrObjItem->RemoveBiDirPtr(ptrObjTemp, m_strLinkID);
         };
         //clear the link collection
         m_arrPtrCollection.clear();

         if (m_ptrOwner)
         {
            m_ptrOwner->SetChanged();
         }
         //no match found
         return 1;

      }
      catch (...)
      {
         std::string errMsg;
         errMsg = "HtlAggregateManager RemoveAllObjects Error thrown";
         throw std::exception(errMsg.c_str());
         return NULL;
      }

	};



	//BIDIRECTIONAL REMOVE TO AVOID CIRCULAR REFERENCING
	//! Adds an object from the member list based on the objects GUID
	template<typename TObj, HtlObjectType TObjEnum>
	int HtlAggregateManager<TObj,TObjEnum>::BiDirAddObject( HtlObject * ptrObj)
	{
      try
      {

         //First See if the object already exists in the collection, if so, then skip it
         HtlObjectAggListIter iterFind;

         iterFind = FindObject(ptrObj->Get_objGUID());
         if (iterFind != m_arrPtrCollection.end())
         {
            //then match found, quit out gracefully
            return 0;
         }
         else {
            //no match found
            //Add the object, then add the bi-directional pointer with the object
            HtlObjectAggPtr ptrTemp;
            ptrTemp.SetObjPtr(ptrObj);
            m_arrPtrCollection.push_back(ptrTemp);

            if (m_ptrOwner)
            {
               m_ptrOwner->SetChanged();
            }
            //no recursive call
            return 1;
         };
         return 1;
      }
      catch (...)
      {
         std::string errMsg;
         errMsg = "HtlAggregateManager BiDirAddObject Error thrown";
         throw std::exception(errMsg.c_str());
         return NULL;
      }
	};


   //! Removes an object from the member list based on the objects GUID
   template<typename TObj, HtlObjectType TObjEnum>
   int HtlAggregateManager<TObj, TObjEnum>::BiDirRemoveObject(HtlObject * ptrObj)
   {
      try
      {
         HtlObjectAggListIter iter = this->FindObject(ptrObj->Get_objGUID());
         if (iter == m_arrPtrCollection.end()) { return 0; };

         //remove the remote pointer
         TObj * ptrObjItem = dynamic_cast<TObj*>(iter->GetObjPtr());
         if (!ptrObjItem) { return 0; };
         //remove the item here
         m_arrPtrCollection.erase(iter);

         if (m_ptrOwner)
         {
            m_ptrOwner->SetChanged();
         }

         return 1;
      }
      catch (...)
      {
         std::string errMsg;
         errMsg = "HtlAggregateManager BiDirRemoveObject Error thrown";
         throw std::exception(errMsg.c_str());
         return NULL;
      }
	};


	//custom find objects methods
	template<typename TObj, HtlObjectType TObjEnum>
	int HtlAggregateManager<TObj,TObjEnum>::ClearPointer(HtlGUID128 objGUID)
   {
      try
      {
         //First See if the object already exists in the collection
         HtlObjectAggListIter iter = this->FindObject(objGUID);
         if (iter == m_arrPtrCollection.end()) { return 0; };

         iter->SetObjPtr(NULL);
         //no match found
         return 0;
      }
      catch (...)
      {
         std::string errMsg;
         errMsg = "HtlAggregateManager ClearPointer Error thrown";
         throw std::exception(errMsg.c_str());
         return NULL;
      }

	};

	//custom find objects methods
	template<typename TObj, HtlObjectType TObjEnum>
   int HtlAggregateManager<TObj, TObjEnum>::ClearAllPointers(void)
   {
      try
      {
         //First See if the object already exists in the collection, if so, then skip it
         HtlObjectAggListIter iter;
         //cycle through the collection removing links
         for (iter = m_arrPtrCollection.begin(); iter != m_arrPtrCollection.end(); ++iter)
         {
            iter->SetObjPtr(NULL);
         }
         //no match found
         return 1;
      }
      catch (...)
      {
         std::string errMsg;
         errMsg = "HtlAggregateManager ClearPointer Error thrown";
         throw std::exception(errMsg.c_str());
         return NULL;
      }
   };


	//Virtual Inheritance Serialization Engines
	//SERIALIZATION ACCESSOR MACRO///////////////////////////////////////
	//!Save Vector information and item sub element information to the HTL archive tree structure
	template<typename TObj, HtlObjectType TObjEnum>
	int HtlAggregateManager<TObj,TObjEnum>::Save(HTL::HtlElement * ptrCurrNode, std::string strMemVarName, bool blnWithSubObjects)
	{

		int intReturn = 0;
		//SAFETY CHECK //put at top of all Serialize Methods
		if(!ptrCurrNode){return 0;};
		//CALL PARENT CLASS Serialize()
		/*...*/
		HtlBase::Save(ptrCurrNode, strMemVarName, blnWithSubObjects);
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
			HtlObjectAggListIter iter;
			HtlElement * ptrNewElement = NULL;

			i = 0;
			//CALL PARENT CLASS SERIALIZATION FIRST
			if(ptrCurrNode)
			{
				//Serialize Local Sub objects if blnWithSubObjects flag is set to TRUE-------------------->

				//get the number of elements
				intNumItems = m_arrPtrCollection.size();
				//set the elements to XML
				for(iter = m_arrPtrCollection.begin(); iter != m_arrPtrCollection.end();++iter)
				{				
					itoa(i,chrBuf,10);
					strIndexName = "IT_";
					strIndexName += chrBuf;
					HtlObjectAggPtr objVal = (*iter);
					//SOME FUNCTION FOR SETTING THE XML ITEM REGARDLESS OF TYPE
					HTL::SetHtlMemVar<HtlObjectAggPtr,HTL_BASE>(ptrCurrNode,strIndexName,objVal,blnWithSubObjects);
					++i;
				};
			};//end valid new node check
			return 1;
		}catch(...){
         std::string errMsg;
         errMsg = "HtlAggregateManager Save Error thrown";
         throw std::exception(errMsg.c_str());
			return -1;
		};

		return intReturn;

	};
	//!Load Vector information and item sub element information from the HTL archive tree structure
	template<typename TObj, HtlObjectType TObjEnum>
	int HtlAggregateManager<TObj,TObjEnum>::Load(HTL::HtlElement * ptrCurrNode, std::string strMemVarName)
	{

		int intReturn = 0;
		//SAFETY CHECK //put at top of all Serialize Methods
		if(!ptrCurrNode){return 0;};
		//CALL PARENT CLASS Serialize()
		/*...*/
		HtlBase::Load(ptrCurrNode,strMemVarName);
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
			if(m_arrPtrCollection.size() != intNumItems)
			{
				m_arrPtrCollection.resize(intNumItems);
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
						
						HtlObjectAggPtr objTemp;
						//then use object factory to create the item since the item is currently NULL
						//HTL::CreateObject<T,TSubObj>(strItemTypeName,objTemp);
						//take the newly created object and de-serialize it with the XML data
						intTemp = HTL::GetHtlMemVar<HtlObjectAggPtr,HTL_BASE>(ptrCurrNode,strIndexName,objTemp);
						if(intTemp < 0){intReturn = -1;};
						m_arrPtrCollection.push_back(objTemp);
					};
				};
			};
			return intReturn;
		}catch(...){
         std::string errMsg;
         errMsg = "HtlAggregateManager Load Error thrown";
         throw std::exception(errMsg.c_str());
			return -1;
		};
		return intReturn;

	};





};//end namespace HTL

#endif // HTL_AGGREGATEMANAGER_H