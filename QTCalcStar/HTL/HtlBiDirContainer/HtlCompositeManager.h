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

#ifndef HTL_COMPOSITEMANAGER_H
#define HTL_COMPOSITEMANAGER_H	

#include "..\HtlObject\HtlObject.h"
#include "..\modHtlGUID.h"
#include "..\modHtlArchive.h"

#include ".\HtlObjectCompPtr.h"
#include "..\HtlThread\HtlSpinLock.h"

namespace HTL
{
	typedef  Htl1DVector< HtlObjectCompPtr, HTL_BASE > HtlObjectCompList;
	typedef  Htl1DVector< HtlObjectCompPtr, HTL_BASE >::Iterator HtlObjectCompListIter;

	template<typename TObj, HtlObjectType TObjEnum>
	class HtlCompositeManager :
		public HtlObject
	{
	public:
		HtlCompositeManager(void);
		HtlCompositeManager(HtlObject * ptrParent);
		HtlCompositeManager(const HtlCompositeManager& rhs);
		HtlCompositeManager & operator = (const HtlCompositeManager & rhs);

		virtual ~HtlCompositeManager(void);

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
		HtlObjectCompListIter BeginHtlObject(void);
		HtlObjectCompListIter EndHtlObject(void);

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

		//custom find objects methods
		HtlObjectCompListIter FindObject(HtlGUID128 objGUID);
		HtlObjectCompListIter FindObject(std::string strGUID);
		HtlObjectCompListIter FindObject(TObj * ptrObject);

		//OBJECT CREATION METHODS////////////////////////////
		//!Creates a new object to add to the object collection
		int CreateObject( TObj* ptrObjectTemp);
		//!Creates a new object to add to the object collection
		TObj* CreateObject(void);

		//OBJECT DELETION METHODS////////////////////////////
		//!Deletes and destroys an object from the object collection based on the lngIndex
		int DeleteObject( long lngIndex);
		//!Deletes and destroys an object from the object collection based on the object GUID
		int DeleteObject( HtlGUID128 objGUID);
		//!Deletes and destroys an object from the object collection based on the object GUID
		int DeleteObject( std::string strGUID);
		//!Deletes and destroys all of the objects from the object collection
		int DeleteAllObjects(void);

		//Virtual Inheritance Serialization Engines
		//SERIALIZATION FUNCTIONS///////////////////////////////////////
		//!Save member data to the current element node
		virtual int Save(HTL::HtlElement * ptrCurrNode, std::string strMemVarName, bool blnWithSubObjects);
		//!Load member data from the current element node
		virtual int Load(HTL::HtlElement * ptrCurrNode, std::string strMemVarName);


	private:

		//!THE COLLECTION OF HTLOBJECTS
		Htl1DVector< HtlObjectCompPtr ,HTL_BASE> m_arrPtrCollection;

	};//end class definition

	//TEMPLATE FUNCTION DEFINITIONS
	template<typename TObj, HtlObjectType TObjEnum>
	HtlCompositeManager<TObj,TObjEnum>::HtlCompositeManager(void)
		: HtlObject()
	{
		m_strType = "HtlCompositeManager";
		m_objType = HTL_BASE;
		m_ptrParent = NULL;
		m_ptrOwner = NULL;
		m_blnPrimary = true;
		m_blnLocked = false;

		return;
	};

	template<typename TObj, HtlObjectType TObjEnum>
	HtlCompositeManager<TObj,TObjEnum>::HtlCompositeManager(HtlObject * ptrParent)
		: HtlObject
	{
		//HtlObject Initialization Section
		m_strType = "HtlCompositeManager";
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
	HtlCompositeManager<TObj,TObjEnum>::HtlCompositeManager(const  HtlCompositeManager<TObj,TObjEnum> & rhs)
		: HtlObject(rhs)
	{
      try
      {
         //HtlObject Initialization Section
         m_strTypeName = "HtlCompositeManager";
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

         return;
      }
      catch (...)
      {
         std::string errMsg;
         errMsg = "HtlCompositeManager Copy Constructor Error thrown";
         throw std::exception(errMsg.c_str());
         return -1;
      };
	};

	template<typename TObj, HtlObjectType TObjEnum>
	HtlCompositeManager<TObj,TObjEnum> & HtlCompositeManager<TObj,TObjEnum>::operator = (const HtlCompositeManager<TObj,TObjEnum> & rhs)
	{
      try
      {
         if (this != &rhs)
         {
            HtlObject::operator=(rhs);
            //HtlObject Initialization Section
            m_strTypeName = "HtlCompositeManager";
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
         errMsg = "HtlCompositeManager Assignment Operator Error thrown";
         throw std::exception(errMsg.c_str());
         return -1;
      };
	};

	template<typename TObj, HtlObjectType TObjEnum>
	HtlCompositeManager<TObj,TObjEnum>::~HtlCompositeManager(void)
	{
		return;
	};

	template<typename TObj, HtlObjectType TObjEnum>
	int HtlCompositeManager<TObj,TObjEnum>::DoesObjectExist(HtlGUID128 objGUID, bool & blnExistReturn, long & lngIndexReturn)
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
         errMsg = "HtlCompositeManager DoesObjectExist Error thrown";
         throw std::exception(errMsg.c_str());
         return -1;
      };
   };

   //Get the object pointer based on the index
	template<typename TObj, HtlObjectType TObjEnum>
	HtlObject * HtlCompositeManager<TObj,TObjEnum>::GetHtlObject(size_t lngIndex)
	{
		try
      {
			if((lngIndex >= 0)&&(lngIndex < m_arrPtrCollection.size()))
			{
				return (m_arrPtrCollection.at(lngIndex).GetObjPtr() );
			}else{
				return NULL;
			};
      }
      catch (...)
      {
         std::string errMsg;
         errMsg = "HtlCompositeManager GetHtlObject Error thrown";
         throw std::exception(errMsg.c_str());
         return NULL;
      };
		return NULL;	
	};

	//Get the pointer to an object by it's global unique identifier
	template<typename TObj, HtlObjectType TObjEnum>
	HtlObject * HtlCompositeManager<TObj,TObjEnum>::GetHtlObject(HtlGUID128 objGUID)
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
         errMsg = "HtlCompositeManager GetHtlObject Error thrown";
         throw std::exception(errMsg.c_str());
         return NULL;
      };
	};

	template<typename TObj, HtlObjectType TObjEnum>
	HtlObject * HtlCompositeManager<TObj,TObjEnum>::GetHtlObject(std::string strGUID)
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
         errMsg = "HtlCompositeManager GetHtlObject Error thrown";
         throw std::exception(errMsg.c_str());
         return NULL;
      };
	};

	template<typename TObj, HtlObjectType TObjEnum>
	size_t HtlCompositeManager<TObj,TObjEnum>::GetObjectIndex(HtlGUID128 objGUID)
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
         errMsg = "HtlCompositeManager GetObjectIndex Error thrown";
         throw std::exception(errMsg.c_str());
         return NULL;
      };
	};

	template<typename TObj, HtlObjectType TObjEnum>
	size_t HtlCompositeManager<TObj,TObjEnum>::GetObjectIndex(std::string strGUID)
	{
      try
      {

         bool blnGUIDConvSuccess = false;
         size_t i, intUboundI;
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
         errMsg = "HtlCompositeManager GetObjectIndex Error thrown";
         throw std::exception(errMsg.c_str());
         return NULL;
      };
	};

	template<typename TObj, HtlObjectType TObjEnum>
	int HtlCompositeManager<TObj,TObjEnum>::ClearObjCompPtr(HtlGUID128 objGUID)
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
         errMsg = "HtlCompositeManager ClearObjCompPtr Error thrown";
         throw std::exception(errMsg.c_str());
         return NULL;
      };
   };

	template<typename TObj, HtlObjectType TObjEnum>
	int HtlCompositeManager<TObj,TObjEnum>::ClearObjCompPtr(std::string strGUID)
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
         errMsg = "HtlCompositeManager ClearObjCompPtr Error thrown";
         throw std::exception(errMsg.c_str());
         return NULL;
      };
	};



	//ELEMENT GUID ACCESSING METHODS
	////////////////////////////////////////////////////////////////////////////
	template<typename TObj, HtlObjectType TObjEnum>
	HtlGUID128 HtlCompositeManager<TObj,TObjEnum>::GetObjectGUID(size_t lngIndex)
   {
      try
      {
         size_t intUboundI;
         intUboundI = m_arrPtrCollection.size();
         if ((lngIndex >= 0) && (lngIndex < intUboundI))
         {
            return m_arrPtrCollection.at(lngIndex)->Get_objGUID();
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
         errMsg = "HtlCompositeManager GetObjectGUID Error thrown";
         throw std::exception(errMsg.c_str());
         return NULL;
      };
	};

	template<typename TObj, HtlObjectType TObjEnum>
	int HtlCompositeManager<TObj,TObjEnum>::GetAllObjectGUIDs(std::vector<HtlGUID128> & arrObjGUIDReturn)
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
            objCurrGUID = m_arrPtrCollection.at(i)->Get_objGUID();
            arrObjGUIDReturn.push_back(objCurrGUID);
         }
         return 1;
      }
      catch (...)
      {
         std::string errMsg;
         errMsg = "HtlCompositeManager GetAllObjectGUIDs Error thrown";
         throw std::exception(errMsg.c_str());
         return NULL;
      };
	};

	//element based indexing
	template<typename TObj, HtlObjectType TObjEnum>
	HtlObject * HtlCompositeManager<TObj,TObjEnum>::FirstHtlObject(void)
	{
		try{
			return (m_arrPtrCollection.front().GetObjPtr() );
		}catch(...){
         std::string errMsg;
         errMsg = "HtlCompositeManager FirstHtlObject Error thrown";
         throw std::exception(errMsg.c_str());
			return NULL;
		};
	};

	template<typename TObj, HtlObjectType TObjEnum>
	HtlObject * HtlCompositeManager<TObj,TObjEnum>::LastHtlObject(void)
	{
		try{
			return (m_arrPtrCollection.back().GetDBPtr() );
		}catch(...){
         std::string errMsg;
         errMsg = "HtlCompositeManager LastHtlObject Error thrown";
         throw std::exception(errMsg.c_str());
			return NULL;
		};
	};

	//iterator based indexing
	template<typename TObj, HtlObjectType TObjEnum>
	HtlObjectCompListIter HtlCompositeManager<TObj,TObjEnum>::BeginHtlObject(void)
	{
		try{
			return (m_arrPtrCollection.begin() );
		}catch(...){
         std::string errMsg;
         errMsg = "HtlCompositeManager BeginHtlObject Error thrown";
         throw std::exception(errMsg.c_str());
			return (m_arrPtrCollection.end() );
		};
	};

	template<typename TObj, HtlObjectType TObjEnum>
	HtlObjectCompListIter HtlCompositeManager<TObj,TObjEnum>::EndHtlObject(void)
	{
		try{
			return (m_arrPtrCollection.end() );
		}catch(...){
         std::string errMsg;
         errMsg = "HtlCompositeManager EndHtlObject Error thrown";
         throw std::exception(errMsg.c_str());
			return (m_arrPtrCollection.end() );
		};
	};

	template<typename TObj, HtlObjectType TObjEnum>
	HtlObject* HtlCompositeManager<TObj,TObjEnum>::AtHtlObject(size_t lngIndex)
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
         errMsg = "HtlCompositeManager AtHtlObject Error thrown";
         throw std::exception(errMsg.c_str());
			return NULL;
		}
	};

	template<typename TObj, HtlObjectType TObjEnum>
	size_t HtlCompositeManager<TObj,TObjEnum>::Size(void) const
	{
		try{
			return (m_arrPtrCollection.size());
		}catch(...){
         std::string errMsg;
         errMsg = "HtlCompositeManager Size Error thrown";
         throw std::exception(errMsg.c_str());
			return 0;
		}
	};

	//swaps two objects in the collection for sorting purposes
	template<typename TObj, HtlObjectType TObjEnum>
	int HtlCompositeManager<TObj,TObjEnum>::SwapObjects(size_t intA, size_t intB)
	{
      try
      {
         size_t intSize = m_arrPtrCollection.size();
         //safety check indexes
         if ((intA < 0) || (intA >= intSize)) { return -1; };
         if ((intB < 0) || (intB >= intSize)) { return -1; };

         HtlObjectCompPtr ptrTemp;
         ptrTemp = m_arrPtrCollection.at(intA);
         m_arrPtrCollection.at(intA) = m_arrPtrCollection.at(intB);
         m_arrPtrCollection.at(intB) = ptrTemp;
         return 1;
      }
      catch (...)
      {
         std::string errMsg;
         errMsg = "HtlCompositeManager SwapObjects Error thrown";
         throw std::exception(errMsg.c_str());
         return 0;
      }
	};

	//OBJECT POINTER BASED ACCESSORS///////////////////////
	//Get the pointer to an object by it's global unique identifier
	template<typename TObj, HtlObjectType TObjEnum>
	TObj* HtlCompositeManager<TObj,TObjEnum>::GetObject(HtlGUID128 objGUID)
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
         errMsg = "HtlCompositeManager GetObject Error thrown";
         throw std::exception(errMsg.c_str());
         return 0;
      }
   };

	template<typename TObj, HtlObjectType TObjEnum>
	TObj* HtlCompositeManager<TObj,TObjEnum>::GetObject(std::string strGUID)
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
         errMsg = "HtlCompositeManager GetObject Error thrown";
         throw std::exception(errMsg.c_str());
         return 0;
      }
	};


	template<typename TObj, HtlObjectType TObjEnum>
	TObj * HtlCompositeManager<TObj,TObjEnum>::First(void)
	{

		try{
			HtlObjectCompPtr ptrObjTemp;
			ptrObjTemp = m_arrPtrCollection.front();
			return (dynamic_cast<TObj*>(ptrObjTemp.GetObjPtr() ) );
		}catch(...){
         std::string errMsg;
         errMsg = "HtlCompositeManager First Error thrown";
         throw std::exception(errMsg.c_str());
			return NULL;
		}
	};

	template<typename TObj, HtlObjectType TObjEnum>
	TObj * HtlCompositeManager<TObj,TObjEnum>::Last(void)
	{
		try{
			HtlObjectCompPtr ptrObjTemp;
			ptrObjTemp = m_arrPtrCollection.back();
			return (dynamic_cast<TObj*>(ptrObjTemp.GetObjPtr() ) );
		}catch(...){
         std::string errMsg;
         errMsg = "HtlCompositeManager Last Error thrown";
         throw std::exception(errMsg.c_str());
			return NULL;
		}
	};

	template<typename TObj, HtlObjectType TObjEnum>
	TObj * HtlCompositeManager<TObj,TObjEnum>::At(size_t lngIndex)
	{

		try{
			if((lngIndex >= 0)&&(lngIndex < m_arrPtrCollection.size()))
			{
				HtlObjectCompPtr ptrTemp = m_arrPtrCollection.at(lngIndex);
				return (dynamic_cast<TObj*>(ptrTemp.GetObjPtr()) );
			}else{
				//illegal index
				return NULL;
			};
		}catch(...){
         std::string errMsg;
         errMsg = "HtlCompositeManager At Error thrown";
         throw std::exception(errMsg.c_str());
			return NULL;
		}
	};

	//custom find objects methods
	template<typename TObj, HtlObjectType TObjEnum>
	HtlObjectCompListIter HtlCompositeManager<TObj,TObjEnum>::FindObject(HtlGUID128 objGUID)
   {
      try
      {
         HtlObjectCompListIter iter;
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
         errMsg = "HtlCompositeManager FindObject Error thrown";
         throw std::exception(errMsg.c_str());
         return NULL;
      }
	};

	template<typename TObj, HtlObjectType TObjEnum>
	HtlObjectCompListIter HtlCompositeManager<TObj,TObjEnum>::FindObject(std::string strGUID)
	{
      try
      {
         bool blnGUIDConvSuccess = false;
         size_t i, intUboundI;
         HtlObjectCompListIter iter;
         HtlGUID128 objCurrGUID, objGUID;
         blnGUIDConvSuccess = objGUID.fromStdString(strGUID);
         if (blnGUIDConvSuccess == false)
         {	//bad GUID conversion
            return NULL;
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
         errMsg = "HtlCompositeManager FindObject Error thrown";
         throw std::exception(errMsg.c_str());
         return NULL;
      }
   };
	
	template<typename TObj, HtlObjectType TObjEnum>
	HtlObjectCompListIter HtlCompositeManager<TObj,TObjEnum>::FindObject(TObj * ptrObject)
	{
      try
      {
         TObj * ptrTemp = NULL;
         HtlObject * ptrHtlTemp = NULL;
         HtlObjectCompListIter iter;
         //safety code
         if (m_arrPtrCollection.size() <= 0) { return m_arrPtrCollection.end(); };
         //otherwise safe to proceed

         for (iter = m_arrPtrCollection.begin();iter != m_arrPtrCollection.end();++iter)
         {
            ptrTemp = NULL;
            ptrHtlTemp = (*iter).GetObjPtr();
            try {
               ptrTemp = dynamic_cast<TObj*>(ptrOrsTemp);
            }
            catch (...) {
               //error in type cast
               try {
                  //sync pointer and try again
                  (*iter).SyncObjPtr();
                  ptrOrsTemp = (*iter).GetObjPtr();
                  ptrTemp = dynamic_cast<TObj*>(ptrOrsTemp);
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
         errMsg = "HtlCompositeManager FindObject Error thrown";
         throw std::exception(errMsg.c_str());
         return NULL;
      }
   };

	//OBJECT CREATION METHODS//////////////////////////////////////////
	//!Creates a new object to add to the object collection
	template<typename TObj, HtlObjectType TObjEnum>
	int HtlCompositeManager<TObj,TObjEnum>::CreateObject( TObj* ptrObjectTemp)
	{
      try
      {
         //push it onto the vector of objects in the collection
         //NOTE ASSUMES T is a subclass of HtlObject
         HtlObjectCompPtr ptrTemp;
         ptrTemp.SetObjPtr(ptrObjectTemp);

         m_arrPtrCollection.push_back(ptrTemp);

         //register the bi directional pointer with the objects parent class
         ptrObjectTemp->Set_ptrParent(this);
         ptrObjectTemp->Set_ptrOwner(Get_ptrParent());

         if (m_ptrOwner)
         {
            m_ptrOwner->SetChanged();
         }

         return 1;
      }
      catch (...)
      {
         std::string errMsg;
         errMsg = "HtlCompositeManager CreateObject Error thrown";
         throw std::exception(errMsg.c_str());
         return NULL;
      }
	};

	//!Creates a new object to add to the object collection
	template<typename TObj, HtlObjectType TObjEnum>
	TObj* HtlCompositeManager<TObj,TObjEnum>::CreateObject(void)
   {
      try
      {
         //push it onto the vector of objects in the collection
         //NOTE ASSUMES T is a subclass of HtlObject

         TObj* ptrObjectTemp = new TObj();
         HtlObjectCompPtr ptrTemp;
         ptrTemp.SetObjPtr(ptrObjectTemp);

         m_arrPtrCollection.push_back(ptrTemp);

         //register the bi directional pointer with the objects parent class
         ptrObjectTemp->Set_ptrParent(this);
         ptrObjectTemp->Set_ptrOwner(Get_ptrParent());

         if (m_ptrOwner)
         {
            m_ptrOwner->SetChanged();
         }
         return ptrObjectTemp;
      }
      catch (...)
      {
         std::string errMsg;
         errMsg = "HtlCompositeManager CreateObject Error thrown";
         throw std::exception(errMsg.c_str());
         return NULL;
      }
   };


	//OBJECT DELETION FUNCTIONS////////////////////////////
	//!Deletes and destroys an object from the object collection based on the lngIndex
	template<typename TObj, HtlObjectType TObjEnum>
	int HtlCompositeManager<TObj,TObjEnum>::DeleteObject( long lngIndex)
	{
      try
      {
         unsigned int intUboundI;
         intUboundI = m_arrPtrCollection.size();
         if ((lngIndex < 0) || (lngIndex >= intUboundI))
         {
            //then index illegal
            return -1;
         }
         else {// safe to proceed
            HtlObject* pObject = m_arrPtrCollection.at(lngIndex).GetObjPtr();
            delete pObject;
            pObject = NULL;
            m_arrPtrCollection.erase(m_arrPtrCollection.begin() + lngIndex);

            if (m_ptrOwner)
            {
               m_ptrOwner->SetChanged();
            }
            return 1;
         }
      }
      catch (...)
      {
         std::string errMsg;
         errMsg = "HtlCompositeManager DeleteObject Error thrown";
         throw std::exception(errMsg.c_str());
         return NULL;
      }
	};
	//!Deletes and destroys an object from the object collection based on the object GUID
	template<typename TObj, HtlObjectType TObjEnum>
	int HtlCompositeManager<TObj,TObjEnum>::DeleteObject( HtlGUID128 objGUID)
	{
      try
      {
         //NEED TO ADD A HASH MAP TO THIS TO MAKE SEARCHING FASTER
         HtlObject * ptrCurrObj = NULL;
         size_t i, intUboundI, intIndexSelected;
         HtlGUID128 objCurrGUID;
         intUboundI = m_arrPtrCollection.size();
         //set pessimistic to illegal index
         intIndexSelected = -1;

         for (i = 0; i < intUboundI; i++)
         {
            ptrCurrObj = m_arrPtrCollection.at(i).GetObjPtr();
            if (ptrCurrObj)
            {
               objCurrGUID = ptrCurrObj->Get_objGUID();
               if (objCurrGUID == objGUID)
               {//match found
                  intIndexSelected = i;
                  TObj* pObject = this->At(intIndexSelected);
                  delete pObject;
                  pObject = NULL;
                  m_arrPtrCollection.erase(m_arrPtrCollection.begin() + intIndexSelected);

                  if (m_ptrOwner)
                  {
                     m_ptrOwner->SetChanged();
                  }
                  return 1;
               };//end if GUID match check
            };
         };//end for loop through objects
         return 0;
      }
      catch (...)
      {
         std::string errMsg;
         errMsg = "HtlCompositeManager DeleteObject Error thrown";
         throw std::exception(errMsg.c_str());
         return NULL;
      }
	};
	//!Deletes and destroys an object from the object collection based on the object GUID
	template<typename TObj, HtlObjectType TObjEnum>
	int HtlCompositeManager<TObj,TObjEnum>::DeleteObject( std::string strGUID)
	{
      try
      {
         //NEED TO ADD A HASH MAP TO THIS TO MAKE SEARCHING FASTER
         HtlObject * ptrCurrObj = NULL;
         bool blnGUIDConvSuccess = false;
         size_t i, intUboundI, intIndexSelected;
         HtlGUID128 objCurrGUID, objGUID;
         blnGUIDConvSuccess = objGUID.fromStdString(strGUID);
         if (blnGUIDConvSuccess == false)
         {	//bad GUID conversion
            return -1;
         }
         intUboundI = m_arrPtrCollection.size();
         //set pessimistic to illegal index
         intIndexSelected = -1;

         for (i = 0; i < intUboundI; i++)
         {
            ptrCurrObj = m_arrPtrCollection.at(i).GetObjPtr();
            if (ptrCurrObj)
            {
               objCurrGUID = m_arrPtrCollection.at(i)->Get_objGUID();
               if (objCurrGUID == objGUID)
               {//match found
                  intIndexSelected = i;
                  TObj* pObject = this->At(intIndexSelected);
                  delete pObject;
                  pObject = NULL;
                  m_arrPtrCollection.erase(m_arrPtrCollection.begin() + intIndexSelected);

                  if (m_ptrOwner)
                  {
                     m_ptrOwner->SetChanged();
                  }
                  return 1;
               };//end if GUID match check
            };
         };//end for loop through objects
         return 0;
      }
      catch (...)
      {
         std::string errMsg;
         errMsg = "HtlCompositeManager DeleteObject Error thrown";
         throw std::exception(errMsg.c_str());
         return NULL;
      }
   };
   //!Deletes and destroys all of the objects from the object collection
	template<typename TObj, HtlObjectType TObjEnum>
	int HtlCompositeManager<TObj,TObjEnum>::DeleteAllObjects (void)
	{
      try
      {
         //NEED TO ADD A HASH MAP TO THIS TO MAKE SEARCHING FASTER
         size_t i, intUboundI;
         intUboundI = m_arrPtrCollection.size();
         //set pessimistic to illegal index

         for (i = 0; i < intUboundI; i++)
         {
            TObj* pObject = this->At(i);
            delete pObject;
            pObject = 0;
         }
         m_arrPtrCollection.clear();

         if (m_ptrOwner)
         {
            m_ptrOwner->SetChanged();
         }
         return 1;
      }
      catch (...)
      {
         std::string errMsg;
         errMsg = "HtlCompositeManager DeleteAllObjects Error thrown";
         throw std::exception(errMsg.c_str());
         return NULL;
      }
	};

	//Virtual Inheritance Serialization Engines
	//SERIALIZATION ACCESSOR MACRO///////////////////////////////////////
	//!Save Vector information and item sub element information to the HTL archive tree structure
	template<typename TObj, HtlObjectType TObjEnum>
	int HtlCompositeManager<TObj,TObjEnum>::Save(HTL::HtlElement * ptrCurrNode, std::string strMemVarName, bool blnWithSubObjects)
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
			HtlObjectCompListIter iter;
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
					HtlObjectCompPtr objVal = (*iter);
					//SOME FUNCTION FOR SETTING THE XML ITEM REGARDLESS OF TYPE
					HTL::SetHtlMemVar<HtlObjectCompPtr,HTL_BASE>(ptrCurrNode,strIndexName,objVal,blnWithSubObjects);
					++i;
				};
			};//end valid new node check
			return 1;
		}catch(...){
         std::string errMsg;
         errMsg = "HtlCompositeManager Save Error thrown";
         throw std::exception(errMsg.c_str());
			return -1;
		};

		return intReturn;

	};
	//!Load Vector information and item sub element information from the HTL archive tree structure
	template<typename TObj, HtlObjectType TObjEnum>
	int HtlCompositeManager<TObj,TObjEnum>::Load(HTL::HtlElement * ptrCurrNode, std::string strMemVarName)
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
						//create the object
						HtlObjectCompPtr objTemp;

						TObj* ptrObjectTemp = new TObj();
						objTemp.m_ptrObject = ptrObjectTemp;
						//then use object factory to create the item since the item is currently NULL
						//HTL::CreateObject<T,TSubObj>(strItemTypeName,objTemp);
						//take the newly created object and de-serialize it with the XML data
						intTemp = HTL::GetHtlMemVar<HtlObjectCompPtr,HTL_BASE>(ptrCurrNode,strIndexName,objTemp);
						if(intTemp < 0){intReturn = -1;};
						m_arrPtrCollection.push_back(objTemp);
					};
				};
			};
			return intReturn;
		}catch(...){
         std::string errMsg;
         errMsg = "HtlCompositeManager Load Error thrown";
         throw std::exception(errMsg.c_str());
			return -1;
		};
		return intReturn;

	};


};//end namespace HTL

#endif // HTL_COMPOSITEMANAGER_H