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
**	usage, redistribution, and modification rights to HTL.
**
**  HTL is distributed in the hope that it will be useful,
**  but WITHOUT ANY WARRANTY; without even the implied warranty of
**  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
**  GNU Lesser General Public License for more details.
**
**  You should have received a copy of the GNU Lesser General Public License
**  along with HTL.  If not, see <http://www.gnu.org/licenses/>.
*/


//HTL COLLECTION MANAGER ACCESSOR MACROS
//MACROS ARE BAAAAADDD.
//THE PURPOSE OF THESE MACROS ARE TAKE THE PLACE OF AN MOC CODE GENERATOR
//AND GENERATE THE PASS THROUGH ACCESSOR FUNCTIONS FOR COMPOSITE AND AGGREGATE COLLECTION MANAGERS
//THERE ISN'T A CONCERN OF DEBUG TRACING BECAUSE THEY ARE JUST PASS THROUGH FUNCTIONS
//THEY ALSO FORCE THE USER TO HAVE A STANDARDIZED SET OF ACCESSOR FUNCTIONS FOR A GIVEN COLLECTION
//REGISTER THEIR SERIALIZABLE MEMBER VARIABLES

//COMPOSITE MANAGER COLLECTION ACCESSOR FUNCTIONS#####################################>>>
//get the pointer to an object by it's global unique identifier
#ifndef HTL_COLLECTIONACCESSORS_H
#define HTL_COLLECTIONACCESSORS_H

#include ".\HtlCompositeManager.h"
#include ".\HtlAggregateManager.h"

namespace HTL{


//###############################################################################>>
#ifndef HTL_DECL_INDEX_ACCESSORS
#define HTL_DECL_INDEX_ACCESSORS(TName,TClass,PtrCollManager) \
	/*!COLLECTION BASE MANAGER INDEX ACCESSORS FOR ##TName/////////////////////////*/ \
	/*!Gets the Object Index based on the objGUID passed in*/ \
	long Get##TName##_ObjectIndex(HtlGUID128 objGUID); \
	/*!Gets the Object Index based on the strGUID passed in*/ \
	long Get##TName##_ObjectIndex(std::string strGUID); \
	/*!Gets the Count or Size of the collection*/ \
	size_t Count_##TName##s(void) const; \
	/*!Gets the GUID based on the lngIndex passed in*/ \
	HtlGUID128 Get##TName##_GUID(size_t lngIndex); \
	/*!Gets All of the GUID Indexes and puts them into a vector*/ \
	int GetAll##TName##_GUIDs(std::vector<HtlGUID128> & arrObjGUIDReturn); \
	/*END ISA_DECL_INDEX_ACCESSORS MACRO*/
#endif //ISA_DECL_INDEX_ACCESSORS

#ifndef HTL_GEN_INDEX_ACCESSORS
#define HTL_GEN_INDEX_ACCESSORS(TSelfClass,TName,TClass,PtrCollManager) \
	/*!COLLECTION BASE MANAGER INDEX ACCESSORS FOR ##TName/////////////////////////*/ \
	/*!Gets the Object Index based on the objGUID passed in*/ \
	long TSelfClass::Get##TName##_ObjectIndex(HtlGUID128 objGUID) \
	{ \
	return PtrCollManager->GetObjectIndex(objGUID); \
	}; \
	/*!Gets the Object Index based on the strGUID passed in*/ \
	long TSelfClass::Get##TName##_ObjectIndex(std::string strGUID) \
	{ \
	return PtrCollManager->GetObjectIndex(strGUID); \
	}; \
	/*!Gets the Count or Size of the collection*/ \
	size_t TSelfClass::Count_##TName##s(void) const \
	{ \
	return PtrCollManager->Size(); \
	}; \
	/*!Gets the GUID based on the lngIndex passed in*/ \
	HtlGUID128 TSelfClass::Get##TName##_GUID(size_t lngIndex) \
	{ \
	return PtrCollManager->GetObjectGUID(lngIndex); \
	}; \
	/*!Gets All of the GUID Indexes and puts them into a vector*/ \
	int TSelfClass::GetAll##TName##_GUIDs(std::vector<HtlGUID128> & arrObjGUIDReturn) \
	{ \
	return PtrCollManager->GetAllObjectGUIDs(arrObjGUIDReturn); \
	}; \
	/*END ISA_GEN_INDEX_ACCESSORS MACRO*/
#endif //ISA_GEN_INDEX_ACCESSORS



//###############################################################################>>
#ifndef HTL_DECL_HTLOBJECT_ACCESSORS
#define HTL_DECL_HTLOBJECT_ACCESSORS(TName,TClass,PtrCollManager) \
	/*!HtlObject ELEMENT ACCESSOR METHODS for ##TName////////////////////*/ \
	/*! Gets a HtlObject pointer for the lngIndex specified*/ \
	HtlObject * Get##TName##_HtlObject(size_t lngIndex); \
	/*! Gets a HtlObject pointer for the objGUID specified*/ \
	HtlObject * Get##TName##_HtlObject(HtlGUID128 objGUID); \
	/*! Gets a HtlObject pointer for the strGUID specified*/ \
	HtlObject * Get##TName##_HtlObject(std::string strGUID); \
	/*! Gets the HtlObject pointer at the specified lngIndex*/ \
	HtlObject * At##TName##_HtlObject(size_t lngIndex) const; \
	/*END ISA_DECL_DBOBJECT_ACCESSORS MACRO*/
#endif //ISA_DECL_DBOBJECT_ACCESSORS

#ifndef HTL_GEN_HTLOBJECT_ACCESSORS
#define HTL_GEN_HTLOBJECT_ACCESSORS(TSelfClass,TName,TClass,PtrCollManager) \
	/*!HtlObject ELEMENT ACCESSOR METHODS for ##TName////////////////////*/ \
	/*! Gets a HtlObject pointer for the lngIndex specified*/ \
	HtlObject * TSelfClass::Get##TName##_HtlObject(size_t lngIndex) \
	{ \
		return PtrCollManager->GetHtlObject(lngIndex); \
	}; \
	/*! Gets a HtlObject pointer for the objGUID specified*/ \
	HtlObject * TSelfClass::Get##TName##_HtlObject(HtlGUID128 objGUID) \
	{ \
		return PtrCollManager->GetHtlObject(objGUID); \
	}; \
	/*! Gets a HtlObject pointer for the strGUID specified*/ \
	HtlObject * TSelfClass::Get##TName##_HtlObject(std::string strGUID) \
	{ \
		return PtrCollManager->GetHtlObject(strGUID); \
	}; \
	/*! Gets the HtlObject pointer at the specified lngIndex*/ \
	HtlObject * TSelfClass::At##TName##_HtlObject(size_t lngIndex) const \
	{ \
		return PtrCollManager->AtDBObject(lngIndex); \
	}; \
	/*END ISA_GEN_DBOBJECT_ACCESSORS MACRO*/
#endif //ISA_GEN_DBOBJECT_ACCESSORS
	
//###############################################################################>>
#ifndef HTL_DECL_ITEM_ACCESSORS
#define HTL_DECL_ITEM_ACCESSORS(TName,TClass,PtrCollManager) \
	/*!TEMPLATE COLLECTION ELEMENT ACCESSOR METHODS for ##TName////////////////////*/ \
	/*! Gets the ##TClass pointer at the specified objGUID*/ \
	TClass* Get##TName(HtlGUID128 objGUID); \
	/*! Gets the ##TClass pointer at the specified strGUID*/ \
	TClass* Get##TName(std::string strGUID); \
	/*! Gets the First ##TClass pointer in the collection*/ \
	TClass* First##TName(void); \
	/*! Gets the Last ##TClass pointer in the collection*/ \
	TClass* Last##TName(void); \
	/*! Gets the ##TClass pointer at the specified lngIndex*/ \
	TClass* At##TName(long lngIndex); \
	/*END ISA_DECL_ITEM_ACCESSORS MACRO*/
#endif //ISA_DECL_ITEM_ACCESSORS

#ifndef HTL_GEN_ITEM_ACCESSORS
#define HTL_GEN_ITEM_ACCESSORS(TSelfClass,TName,TClass,PtrCollManager) \
	/*!TEMPLATE COLLECTION ELEMENT ACCESSOR METHODS for ##TName////////////////////*/ \
	/*! Gets the ##TClass pointer at the specified objGUID*/ \
	TClass* TSelfClass::Get##TName(HtlGUID128 objGUID) \
	{ \
		return PtrCollManager->GetObject(objGUID); \
	}; \
	/*! Gets the ##TClass pointer at the specified strGUID*/ \
	TClass* TSelfClass::Get##TName(std::string strGUID) \
	{ \
		return PtrCollManager->GetObject(strGUID); \
	}; \
	/*! Gets the First ##TClass pointer in the collection*/ \
	TClass* TSelfClass::First##TName(void)\
	{ \
		return PtrCollManager->First(); \
	}; \
	/*! Gets the Last ##TClass pointer in the collection*/ \
	TClass* TSelfClass::Last##TName(void) \
	{ \
		return PtrCollManager->Last(); \
	}; \
	/*! Gets the ##TClass pointer at the specified lngIndex*/ \
	TClass* TSelfClass::At##TName(long lngIndex) \
	{ \
		return PtrCollManager->At(lngIndex); \
	}; \
	/*END ISA_GEN_ITEM_ACCESSORS MACRO*/
#endif //ISA_GEN_ITEM_ACCESSORS

//###############################################################################>>
#ifndef HTL_DECL_COMPOSITE_ACCESSORS
#define HTL_DECL_COMPOSITE_ACCESSORS(TName,TClass,PtrCollManager) \
	/*##TName OBJECT CREATION METHODS//////////////////////////*/ \
	/*!Creates a new ##TName object to add to the object collection*/ \
	int Create##TName(TClass* ptrObjectTemp); \
	/*!Creates a new ##TName object to add to the object collection*/ \
	TClass* Create##TName(void); \
	/*##TName OBJECT DELETION METHODS//////////////////////////*/ \
	/*!Deletes and destroys an object from the object collection based on the lngIndex*/ \
	int Delete##TName( size_t lngIndex); \
	/*!Deletes and destroys an object from the object collection based on the object GUID*/ \
	int Delete##TName( HtlGUID128 objGUID); \
	/*!Deletes and destroys an object from the object collection based on the object GUID*/ \
	int Delete##TName( std::string strGUID); \
	/*!Deletes and destroys all of the objects from the object collection*/ \
	int DeleteAll##TName##s(void); \
	/*END ISA_DECL_COMPOSITE_ACCESSORS MACRO*/
#endif //ISA_DECL_COMPOSITE_ACCESSORS


#ifndef HTL_GEN_COMPOSITE_ACCESSORS
#define HTL_GEN_COMPOSITE_ACCESSORS(TSelfClass,TName,TClass,PtrCollManager) \
	/*##TName OBJECT CREATION METHODS//////////////////////////*/ \
	/*!Creates a new ##TName object to add to the object collection*/ \
	int TSelfClass::Create##TName(TClass* ptrObjectTemp) \
	{ \
		return PtrCollManager->CreateObject(ptrObjectTemp); \
	}; \
	/*!Creates a new ##TName object to add to the object collection*/ \
	TClass* TSelfClass::Create##TName(void) \
	{ \
		return PtrCollManager->CreateObject(); \
	}; \
	/*##TName OBJECT DELETION METHODS//////////////////////////*/ \
	/*!Deletes and destroys an object from the object collection based on the lngIndex*/ \
	int TSelfClass::Delete##TName( size_t lngIndex) \
	{ \
		return PtrCollManager->DeleteObject(lngIndex); \
	}; \
	/*!Deletes and destroys an object from the object collection based on the object GUID*/ \
	int TSelfClass::Delete##TName( HtlGUID128 objGUID) \
	{ \
		return PtrCollManager->DeleteObject(objGUID); \
	}; \
	/*!Deletes and destroys an object from the object collection based on the object GUID*/ \
	int TSelfClass::Delete##TName( std::string strGUID) \
	{ \
		return PtrCollManager->DeleteObject(strGUID); \
	}; \
	/*!Deletes and destroys all of the objects from the object collection*/ \
	int TSelfClass::DeleteAll##TName##s(void) \
	{ \
		return PtrCollManager->DeleteAllObjects(); \
	}; \
	/*END ISA_GEN_COMPOSITE_ACCESSORS MACRO*/
#endif //ISA_GEN_COMPOSITE_ACCESSORS

//###############################################################################>>
#ifndef HTL_DECL_AGGREGATE_ACCESSORS
#define HTL_DECL_AGGREGATE_ACCESSORS(TName,TClass,PtrCollManager) \
	/*##TName OBJECT ADDITION METHODS//////////////////////////*/ \
	/*! Adds an object to the Aggregate Object Member List*/ \
	int Add##TName(TClass* ptrObjectTemp); \
	/*##TName OBJECT REMOVAL METHODS//////////////////////////*/ \
	/*! Removes an object from the member list based on index*/ \
	int Remove##TName(size_t lngIndex); \
	/*! Removes an object from the member list based on the object's GUID*/ \
	int Remove##TName(HtlGUID128 objGUID); \
	/*! Removes an object from the member list based on the object's GUID*/ \
	int Remove##TName(std::string strGUID); \
	/*! Removes all objects from the member list*/ \
	int RemoveAll##TName##s(void); \
	/*! Bi Directional Add an object to the Aggregate Object Member List*/ \
	int BiDirAdd##TName(TClass* ptrObjectTemp); \
	/*! Bi Directional Remove an object to the Aggregate Object Member List*/ \
	int BiDirRemove##TName(TClass* ptrObjectTemp); \
	/*END ISA_DECL_AGGREGATE_ACCESSORS MACRO*/
#endif//ISA_DECL_AGGREGATE_ACCESSORS


#ifndef HTL_GEN_AGGREGATE_ACCESSORS
#define HTL_GEN_AGGREGATE_ACCESSORS(TSelfClass,TName,TClass,PtrCollManager) \
	/*##TName OBJECT ADDITION METHODS//////////////////////////*/ \
	/*! Adds an object to the Aggregate Object Member List*/ \
	int TSelfClass::Add##TName(TClass* ptrObjectTemp) \
	{ \
		return PtrCollManager->AddObject(ptrObjectTemp); \
	}; \
	/*##TName OBJECT REMOVAL METHODS//////////////////////////*/ \
	/*! Removes an object from the member list based on index*/ \
	int TSelfClass::Remove##TName(size_t lngIndex) \
	{ \
		return PtrCollManager->RemoveObject(lngIndex); \
	}; \
	/*! Removes an object from the member list based on the object's GUID*/ \
	int TSelfClass::Remove##TName(HtlGUID128 objGUID) \
	{ \
		return PtrCollManager->RemoveObject(objGUID); \
	}; \
	/*! Removes an object from the member list based on the object's GUID*/ \
	int TSelfClass::Remove##TName(std::string strGUID) \
	{ \
		return PtrCollManager->RemoveObject(strGUID); \
	}; \
	/*! Removes all objects from the member list*/ \
	int TSelfClass::RemoveAll##TName##s(void) \
	{ \
		return PtrCollManager->RemoveAllObjects(); \
	}; \
	/*! Bi Directional Adds an object to the Aggregate Object Member List*/ \
	int TSelfClass::BiDirAdd##TName(TClass* ptrObjectTemp) \
	{ \
		return PtrCollManager->BiDirAddObject(ptrObjectTemp); \
	}; \
	/*! Bi Directional Adds an object to the Aggregate Object Member List*/ \
	int TSelfClass::BiDirRemove##TName(TClass* ptrObjectTemp) \
	{ \
		return PtrCollManager->BiDirRemoveObject(ptrObjectTemp); \
	}; \
	/*END ISA_GEN_AGGREGATE_ACCESSORS MACRO*/
#endif//ISA_GEN_AGGREGATE_ACCESSORS


};//end namespace HTL
#endif //HTL_COLLECTIONACCESSORS_H