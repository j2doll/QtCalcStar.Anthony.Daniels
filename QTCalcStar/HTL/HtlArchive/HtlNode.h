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
#ifndef HtlNODE_H
#define HtlNODE_H
#include <string>
#include <vector>
#include <algorithm>
#include "..\modHtlMacro.h"
#include "..\modHtlBase.h"
#include "..\modHtlString.h"
namespace HTL{

	class HTL_DLLAPI HtlIndex3D;

	//!This is the archive tree structure base class.
	/*!
		This is the archive tree structure base class.  ALL node types inherit from this class.
		This file also includes template functions for the container manipulation.
	*/
	class HTL_DLLAPI HtlNode
	{
	public:

		//PUBLIC CONSTRUCTORS & DESTRUCTOR/////////////////////////////
		HtlNode(void);
		HtlNode(HtlNode * ptrParentNode);
		HtlNode(HtlNode & rhs);
		virtual ~HtlNode(void);
		//PUBLIC OPERATOR OVERLOADS
		HtlNode & operator = (HtlNode & rhs);

		//!Pointer to the parent node of the object
		HTLMEMVAR_BYVAL_STYLE1(public, HtlNode *, ptrParentNode);

		//!Enumerated flag indicating what type of archive node this is
		HTLMEMVAR_BYVAL_STYLE1(public, HtlArchNodeType, objNodeType);
		//!3D tree index of the archive node (row = x, col = y, level = z)
		HTLMEMVAR_BYVAL_STYLE1(public, Htl3DIndex, objIndex);

		//!Set the row of the nodes index
		void Set_intRow(long lngRow);
		//!Set the column of the nodes index
		void Set_intColumn(long lngCol);
		//!Set the level or page of the nodes index
		void Set_intLevel(long lngLevel);
		
		//!Get the row of the nodes index
		long Get_intRow(void);
		//!Get the column of the nodes index
		long Get_intColumn(void);
		//!Get the level or page of the nodes index
		long Get_intLevel(void);
		//!String Name of the Archive Node
		HTLMEMVAR_BYVAL_STYLE1(public, std::string, strName);

		//!String Value of the Archive Node
		//DECLARED INDIVIDUALLY BECAUSED SPECIALIZED ACCESSORS ARE REQUIRED
		//HTLMEMVAR_BYVAL_STYLE1(public, std::string, strValue);

		//!Enumerated flag indicating what type of HTL object this is
		HTLMEMVAR_BYVAL_STYLE1(public, HtlObjectType, objType);
		

		//PUBLIC MEMBER FUNCTIONS////////////////////////////////////
		//While the base storage is a string (m_strValue)
		//The following conveinience Functions are added to facilitate base type inputs
		//From a best practice standpoint it is not recommended to store vectors as attributes.
		//Store Vectors, and Arrays as collections of element.

		//!Set and Get for Node Value
		void Set_strValue(const std::string & strValue);
		void Set_strValue(const char * ptrCharString);
		void Set_strValue(bool blnVal);
		void Set_strValue(short shrtVal);
		void Set_strValue(unsigned short ushrtVal);
		void Set_strValue(int intVal);
		void Set_strValue(unsigned int uint);
		void Set_strValue(long lngVal);
		void Set_strValue(unsigned long ulngVal);
		void Set_strValue(float sngVal);
		void Set_strValue(double dblVal);
		void Set_strValue(char chrVal);
		void Set_strValue(unsigned char uchrVal);

		//!Set and Get for Node Value
		std::string Get_strValue(void);
		void Get_strValue(bool & blnValReturn);
		void Get_strValue(short & shrtValReturn);
		void Get_strValue(unsigned short & ushrtValReturn);
		void Get_strValue(int & intValReturn);
		void Get_strValue(unsigned int & uintValReturn);
		void Get_strValue(long & lngValReturn);
		void Get_strValue(unsigned long & ulngValReturn);
		void Get_strValue(float & sngValReturn);
		void Get_strValue(double & dblValReturn);
		void Get_strValue(char & chrValReturn);
		void Get_strValue(unsigned char & uchrValReturn);
		void Get_strValue(std::string & strValReturn);
		void Get_strValueDecode(std::string & strValReturn);
		//!Encoding special characters to Htl compatible format
		void EncodeSpecialChars(std::string & strToEncode);
		//!Decode special characters from Htl compatible format;
		void DecodeSpecialChars(std::string & strToDecode);
		//virtual std::string Get_strValue(bool blnWithFormatting){std::string strOut; return strOut;};
	protected:
		//!The string value of the node
		std::string m_strValue;


	};//end class HtlNode description


	//NODE COLLECTION ACCESSOR TEMPLATE FUNCTIONS//////////////////////
	//!Add an attribute to the element
	template<typename T /*= HtlNode*/>
	T * AddNode(std::vector<T*> & arrPtrNodeCollection, HtlNode * ptrParent)
	{
		try{
			T* ptrNewNode = new T(ptrParent);
			arrPtrNodeCollection.push_back(ptrNewNode);
			return ptrNewNode;
		}catch(...){
         std::string errMsg;
         errMsg = "HtlNode AddNode Error thrown";
         throw std::exception(errMsg.c_str());
			return NULL;
		};
	};
	//!Add an attribute to the element
	template<typename T /*= HtlNode*/>
	int AddNode(std::vector<T*> & arrPtrNodeCollection, HtlNode * ptrParent, T * ptrObject)
	{
		try{
			if(ptrObject)
			{
				ptrObject->Set_ptrParentNode(ptrParent);
				arrPtrNodeCollection.push_back(ptrObject);
				return 1;
			}else{
				return 0;
			}
		}catch(...){
         std::string errMsg;
         errMsg = "HtlNode AddNode Error thrown";
         throw std::exception(errMsg.c_str());
			return NULL;
		};
	};
	//!Delete an attribute from the element by its name
	template<typename T /*= HtlNode*/>
	int DeleteNode(std::vector<T*> & arrPtrNodeCollection, const std::string & strName)
	{
		size_t i, intNumNodes;
		intNumNodes = arrPtrNodeCollection.size();
		if(intNumNodes <= 0)
		{//no attributes to search
			return 0;
		}
		try{
			std::string strNameTest;
			for(i = 0; i < intNumNodes; i++)
			{
				strNameTest = arrPtrNodeCollection.at(i)->Get_strName();
				if(HtlStringAlg::IsStringEqual(strNameTest, strName))
				{//then match found, delete it
					delete arrPtrNodeCollection.at(i);
					arrPtrNodeCollection.erase(arrPtrNodeCollection.begin() + i);
					//successful deletion
					return 1;
				};
			};//end for loop through attributes
			strNameTest.clear();
			//no match found return NULL
			return NULL;
		}catch(...){
         std::string errMsg;
         errMsg = "HtlNode DeleteNode Error thrown";
         throw std::exception(errMsg.c_str());
			return -1;
		};
	};
	//!Delete an attribute from the element by its index
	template<typename T /*= HtlNode*/>
	int DeleteNode(std::vector<T*> & arrPtrNodeCollection, size_t lngIndex)
	{
		size_t intNumNodes;
		std::string strCurrTagName;
		intNumNodes = arrPtrNodeCollection.size();
		if(intNumNodes <= 0)
		{//no attributes to search
			return 0;
		};
		try{
			if((lngIndex >= 0)&&(lngIndex < intNumNodes))
			{
				delete arrPtrNodeCollection.at(lngIndex);
				arrPtrNodeCollection.erase(arrPtrNodeCollection.begin() + lngIndex);
				//successful deletion
				return 1;
			};
			//nothing done
			return NULL;
		}catch(...){
         std::string errMsg;
         errMsg = "HtlNode DeleteNode Error thrown";
         throw std::exception(errMsg.c_str());
			return -1;
		};
	};
	//!Delete All of the Element's sub-Elements
	template<typename T /*= HtlNode*/>
	int DeleteAllNodes(std::vector<T*> & arrPtrNodeCollection)
	{
		size_t i, intNumNodes;
		std::string strCurrTagName;
		intNumNodes = arrPtrNodeCollection.size();
		if(intNumNodes <= 0)
		{//no attributes to search
			return 0;
		}
		try{
			for(i = 0; i < intNumNodes; i++)
			{
				delete arrPtrNodeCollection.at(i);
			};//end for loop through attributes	
			arrPtrNodeCollection.clear();
			//successful deletion of all elements
			return 1;
		}catch(...){
         std::string errMsg;
         errMsg = "HtlNode DeleteAllNodes Error thrown";
         throw std::exception(errMsg.c_str());
			return -1;
		};
	};
	//!Sort the collection of Elements Alphabetically
	//Need this sort function isolated with precompiler #ifndef statement so it only gets referenced once
	template<typename T /*= HtlNode*/>
	bool SortNodesAscending(T * ptrA,T * ptrB)
	{
		//T HAS TO INHERIT OR BE A HtlNode!!!!!!!!!!!!!!!!!!!!!!!
		std::string strNameA, strNameB;
		std::string::iterator iterA, iterB;
		strNameA = ptrA->Get_strName();
		strNameB = ptrB->Get_strName();
		//scan through the two strings and sort them alphabetically characterwise
		for( iterA = strNameA.begin(), iterB = strNameB.begin();( (iterA != strNameA.end()) && (iterB != strNameB.end()) ); ++iterA, ++iterB )
		{
			if( tolower( *iterA ) < tolower( *iterB ) )
				return true;
			else if( tolower( *iterA ) > tolower( *iterB ) )
				return false;
		};
		if( strNameA.size() < strNameB.size() )
		{
			return true;
		}else{
			return false;
		};
	};

	template<typename T /*= HtlNode*/>
	int SortNodes(std::vector<T*> & arrPtrNodeCollection)
	{
		try{
			std::sort(arrPtrNodeCollection.begin(),arrPtrNodeCollection.end(),SortNodesAscending<T>);
			return 1;
		}catch(...){
         std::string errMsg;
         errMsg = "HtlNode SortNodes Error thrown";
         throw std::exception(errMsg.c_str());
			return -1;
		};
	};
	//!Size of the Element collection
	template<class T /*= HtlNode*/>
	long CountNodes(std::vector<T*> & arrPtrNodeCollection)
	{
		return arrPtrNodeCollection.size();
	};
	//!Boolean check to see if attribute collection is empty
	template<typename T /*= HtlNode*/>
	bool HasNodes(std::vector<T*> & arrPtrNodeCollection)
	{
		size_t intNumNodes;
		std::string strCurrTagName;
		intNumNodes = arrPtrNodeCollection.size();
		if(intNumNodes > 0)
		{
			//has attributes
			return true;
		}else{
			//does not have attributes
			return false;
		};
	};
	//!Does Element Exist check by it's name
	template<typename T /*= HtlNode*/>
	bool DoesNodeExist(std::vector<T*> & arrPtrNodeCollection,const std::string & strName)
	{
		size_t i, intNumNodes;
		intNumNodes = arrPtrNodeCollection.size();
		if(intNumNodes <= 0)
		{//no attributes to search
			return false;
		}
		try{
			for(i = 0; i < intNumNodes; i++)
			{
				std::string strNameTest = arrPtrNodeCollection.at(i)->Get_strName();
				if(HtlStringAlg::IsStringEqual(strNameTest, strName))
				{//then match found, delete it
					return true;
				};
			};//end for loop through attributes
			//no match found return NULL
			return false;
		}catch(...){
         std::string errMsg;
         errMsg = "HtlNode DoesNodeExist Error thrown";
         throw std::exception(errMsg.c_str());
			return false;
		};
	};
	//!Get the pointer to the first Element
	template<typename T /*= HtlNode*/>
	T * FirstNode(std::vector<T*> & arrPtrNodeCollection, size_t & lngCurrIndex)
	{
		size_t intNumNodes;
		std::string strCurrTagName;
		intNumNodes = arrPtrNodeCollection.size();
		if(intNumNodes <= 0)
		{//no attributes to search
			lngCurrIndex = -1;
			return NULL;
		};
		//has attributes return the first one
		lngCurrIndex = 0;
		return arrPtrNodeCollection.front();
	};
	//!Get the pointer to the last Element
	template<typename T /*= HtlNode*/>
	T * LastNode(std::vector<T*> & arrPtrNodeCollection, size_t & lngCurrIndex)
	{
		size_t intNumNodes;
		std::string strCurrTagName;
		intNumNodes = arrPtrNodeCollection.size();
		if(intNumNodes <= 0)
		{//no attributes to search
			lngCurrIndex = -1;
			return NULL;
		};
		//has attributes return the first one
		lngCurrIndex = arrPtrNodeCollection.size() - 1;
		return arrPtrNodeCollection.back();
	};
	//!Get the pointer to the next Element
	template<typename T /*= HtlNode*/>
	T * NextNode(std::vector<T*> & arrPtrNodeCollection, size_t & lngCurrIndex)
	{
		size_t intNumNodes;
		std::string strCurrTagName;
		intNumNodes = arrPtrNodeCollection.size();
		if(intNumNodes <= 0)
		{//no attributes to search
			return false;
		};
		//if the current attribute has not been set yet go the first,
		//otherwise go to the next,
		//if end of vector reached return NULL
		try{
			if(lngCurrIndex < 0)
			{
				//then hasn't been set wyet
				lngCurrIndex = 0;
				return arrPtrNodeCollection.front();
			}else if(lngCurrIndex >= intNumNodes){
				//then at the end of the vector, there is no next, reset to zero and return NULL
				lngCurrIndex = 0;
				return NULL;
			}else{
				//legal index in vector increment it
				++lngCurrIndex;
				//check for legal new index
				if((lngCurrIndex >= 0)&&(lngCurrIndex<intNumNodes))
				{
					return arrPtrNodeCollection.at(lngCurrIndex);
				}else{
					//not a legal index quit gracefully;
					lngCurrIndex = 0;
					return NULL;
				};
			};
		}catch(...){
         std::string errMsg;
         errMsg = "HtlNode NextNode Error thrown";
         throw std::exception(errMsg.c_str());
			return NULL;
		};

	};
	//!Get the pointer to the previous Element
	template<typename T /*= HtlNode*/>
	T * PreviousNode(std::vector<T*> & arrPtrNodeCollection, size_t & lngCurrIndex)
	{
		size_t intNumNodes;
		std::string strCurrTagName;
		intNumNodes = arrPtrNodeCollection.size();
		if(intNumNodes <= 0)
		{//no attributes to search
			return false;
		};
		//if the current attribute has not been set yet go the first,
		//otherwise go to the next,
		//if end of vector reached return NULL
		try{
			if(lngCurrIndex < 0)
			{
				//then hasn't been set wyet
				lngCurrIndex = 0;
				return arrPtrNodeCollection.front();
			}else if(lngCurrIndex >= intNumNodes){
				//then at the end of the vector, there is no next, reset to zero and return NULL
				lngCurrIndex = 0;
				return NULL;
			}else{
				//legal index in vector increment it
				--lngCurrIndex;
				//check for legal new index
				if((lngCurrIndex >= 0)&&(lngCurrIndex<intNumNodes))
				{
					return arrPtrNodeCollection.at(lngCurrIndex);
				}else{
					//not a legal index quit gracefully;
					lngCurrIndex = 0;
					return NULL;
				};
			};
		}catch(...){
         std::string errMsg;
         errMsg = "HtlNode PreviousNode Error thrown";
         throw std::exception(errMsg.c_str());
			return NULL;
		};
	};
	//!Get the pointer to the Element by it's name
	template<typename T /*= HtlNode*/>
	T * GetNode(std::vector<T*> & arrPtrNodeCollection, const std::string & strName)
	{
		size_t i, intNumNodes;

		intNumNodes = arrPtrNodeCollection.size();
		if(intNumNodes <= 0)
		{//no attributes to search
			return NULL;
		}
		try{
			std::string strNameTest;
			for(i = 0; i < intNumNodes; i++)
			{
				strNameTest = arrPtrNodeCollection.at(i)->Get_strName();
				if(HtlStringAlg::IsStringEqual(strNameTest, strName))
				{//then match found, delete it
					return arrPtrNodeCollection.at(i);
				};
			};//end for loop through attributes
			strNameTest.clear();
			//no match found return NULL
			return NULL;
		}catch(...){
         std::string errMsg;
         errMsg = "HtlNode GetNode Error thrown";
         throw std::exception(errMsg.c_str());
			return NULL;
		};
	};
	//!Get the pointer to the Element by it's index
	template<typename T /*= HtlNode*/>
	T * GetNode(std::vector<T*> & arrPtrNodeCollection, size_t lngIndex)
	{
		size_t intNumNodes;
		std::string strCurrTagName;
		intNumNodes = arrPtrNodeCollection.size();
		if(intNumNodes <= 0)
		{//no attributes to search
			return 0;
		};
		try{
			if((lngIndex >= 0)&&(lngIndex < intNumNodes))
			{
				//valid index
				return arrPtrNodeCollection.at(lngIndex);
			};
			//nothing done
			return NULL;
		}catch(...){
         std::string errMsg;
         errMsg = "HtlNode GetNode Error thrown";
         throw std::exception(errMsg.c_str());
			return NULL;
		};
	};



};//end namespace HtlLite
#endif