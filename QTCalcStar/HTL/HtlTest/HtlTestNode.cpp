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
#pragma warning(push)
#pragma warning (disable : 4005 ) /* macro redefinition */
#define HTL_DLLEXPORT
#pragma warning(pop)

#include ".\HtlTestNode.h"
#include ".\HtlTestFactory.h"

#include <algorithm>

using namespace std;

namespace HTL
{

		HtlTestNode::HtlTestNode(void)
		{	
			m_ptrParentNode = NULL;
			return;
		};
		HtlTestNode::HtlTestNode(HtlTestNode* ptrParent)
		{
			m_ptrParentNode = NULL;
			if(ptrParent)
			{
				this->m_ptrParentNode = ptrParent;
			};
			return;
		};

		HtlTestNode::~HtlTestNode(void)
		{
			this->deleteAllNodes();
			return;
		};

	
		//!Add an attribute to the element
		HtlTestNode * HtlTestNode::addNode(std::string & strTestName)
		{
			try{
				HtlTestNode* ptrNewNode = HTL::CreateTestNode(strTestName);
				this->m_arrPtrNodes.push_back(ptrNewNode);
				return ptrNewNode;
			}catch(...){
				return NULL;
			};
		};

		//!Delete an attribute from the element by its name
		int HtlTestNode::deleteNode(std::string & strName)
		{
			size_t i, intNumNodes;
			std::string strCurrName;
			intNumNodes = m_arrPtrNodes.size();
			if(intNumNodes <= 0)
			{//no attributes to seTest
				return 0;
			}
			try{
				for(i = 0; i < intNumNodes; i++)
				{
					strCurrName = m_arrPtrNodes.at(i)->Get_strTestName();
					if(strName == strCurrName)
					{//then match found, delete it
						delete m_arrPtrNodes.at(i);
						m_arrPtrNodes.erase(m_arrPtrNodes.begin() + i);
						//successful deletion
						return 1;
					};
				};//end for loop through attributes
				//no match found return NULL
				return NULL;
			}catch(...){
				return -1;
			};
		};
		//!Delete an attribute from the element by its index
		int HtlTestNode::deleteNode(size_t lngIndex)
		{
			size_t intNumNodes;
			intNumNodes = m_arrPtrNodes.size();
			if(intNumNodes <= 0)
			{//no attributes to seTest
				return 0;
			};
			try{
				if((lngIndex >= 0)&&(lngIndex < intNumNodes))
				{
					delete m_arrPtrNodes.at(lngIndex);
					m_arrPtrNodes.erase(m_arrPtrNodes.begin() + lngIndex);
					//successful deletion
					return 1;
				};
				//nothing done
				return NULL;
			}catch(...){
				return -1;
			};
		};
		//!Delete All of the Element's sub-Elements

		int HtlTestNode::deleteAllNodes(void)
		{
			size_t i, intNumNodes;
			intNumNodes = m_arrPtrNodes.size();
			if(intNumNodes <= 0)
			{//no attributes to seTest
				return 0;
			}
			try{
				for(i = 0; i < intNumNodes; i++)
				{
					delete m_arrPtrNodes.at(i);
				};//end for loop through attributes	
				m_arrPtrNodes.clear();
				//successful deletion of all elements
				return 1;
			}catch(...){
				return -1;
			};
		};
		//!Sort the collection of Elements Alphabetically
		//Need this sort function isolated with precompiler #ifndef statement so it only gets referenced once
		bool sortNodesAscending(HtlTestNode * ptrA,HtlTestNode * ptrB)
		{
			//HtlTestNode HAS HtlTestNodeO INHERIHtlTestNode OR BE A XMLNode!!!!!!!!!!!!!!!!!!!!!!!
			HtlString strNameA, strNameB;
			strNameA = ptrA->Get_strTestName();
			strNameB = ptrB->Get_strTestName();
			//scan through the two strings and sort them alphabetically characterwise
			return (strNameA < strNameB);
		};

		int HtlTestNode::sortNodes(void)
		{
			try{
				std::sort(m_arrPtrNodes.begin(),m_arrPtrNodes.end(),sortNodesAscending);
				return 1;
			}catch(...){
				return -1;
			};
		};
		//!Size of the Element collection
		size_t HtlTestNode::countNodes(void)
		{
			return m_arrPtrNodes.size();
		};
		//!Boolean check to see if attribute collection is empty
		bool HtlTestNode::hasNodes(void)
		{
			size_t intNumNodes;
			intNumNodes = m_arrPtrNodes.size();
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
		bool HtlTestNode::doesNodeExist(std::string & strName)
		{
			size_t i, intNumNodes;
			std::string strCurrName;
			intNumNodes = m_arrPtrNodes.size();
			if(intNumNodes <= 0)
			{//no attributes to seTest
				return false;
			}
			try{
				for(i = 0; i < intNumNodes; i++)
				{
					strCurrName = m_arrPtrNodes.at(i)->Get_strTestName();
					if(strName == strCurrName)
					{//then match found, delete it
						return true;
					};
				};//end for loop through attributes
				//no match found return NULL
				return false;
			}catch(...){
				return false;
			};
		};


		//!Get the pointer to the Element by it's name
		HtlTestNode * HtlTestNode::getNode(std::string & strName)
		{
			size_t i, intNumNodes;
			std::string strCurrName;
			intNumNodes = m_arrPtrNodes.size();
			if(intNumNodes <= 0)
			{//no attributes to seTest
				return NULL;
			}
			try{
				for(i = 0; i < intNumNodes; i++)
				{
					strCurrName = m_arrPtrNodes.at(i)->Get_strTestName();
					if(strName == strCurrName)
					{//then match found, delete it
						return m_arrPtrNodes.at(i);
					};
				};//end for loop through attributes
				//no match found return NULL
				return NULL;
			}catch(...){
				return NULL;
			};
		};

		//!Get the pointer to the Element by it's index
		HtlTestNode * HtlTestNode::getNode( size_t lngIndex)
		{
			size_t intNumNodes;
			intNumNodes = m_arrPtrNodes.size();
			if(intNumNodes <= 0)
			{//no attributes to seTest
				return 0;
			};
			try{
				if((lngIndex >= 0)&&(lngIndex < intNumNodes))
				{
					//valid index
					return m_arrPtrNodes.at(lngIndex);
				};
				//nothing done
				return NULL;
			}catch(...){
				return NULL;
			};
		};
		//!Get the pointer to the Element by it's index
		HtlTestNode * HtlTestNode::atNode( size_t lngIndex)
		{
			size_t intNumNodes;
			intNumNodes = m_arrPtrNodes.size();
			if(intNumNodes <= 0)
			{//no nodes to seTest
				return 0;
			};
			try{
				if((lngIndex >= 0)&&(lngIndex < intNumNodes))
				{
					//valid index
					return m_arrPtrNodes.at(lngIndex);
				};
				//nothing done
				return NULL;
			}catch(...){
				return NULL;
			};
		};

		//!Get the pointer to the first Element
		HtlTestNode * HtlTestNode::firstNode(size_t & lngCurrIndex)
		{
			size_t intNumNodes;
			intNumNodes = m_arrPtrNodes.size();
			if(intNumNodes <= 0)
			{//no attributes to seTest
				lngCurrIndex = -1;
				return NULL;
			};
			//has attributes return the first one
			lngCurrIndex = 0;
			return m_arrPtrNodes.front();
		};
		//!Get the pointer to the last Element
		HtlTestNode * HtlTestNode::lastNode(size_t & lngCurrIndex)
		{
			size_t intNumNodes;
			intNumNodes = m_arrPtrNodes.size();
			if(intNumNodes <= 0)
			{//no attributes to seTest
				lngCurrIndex = -1;
				return NULL;
			};
			//has attributes return the first one
			lngCurrIndex = m_arrPtrNodes.size() - 1;
			return m_arrPtrNodes.back();
		};
		//!Get the pointer to the next Element
		HtlTestNode * HtlTestNode::nextNode(size_t & lngCurrIndex)
		{
			size_t intNumNodes;
			intNumNodes = m_arrPtrNodes.size();
			if(intNumNodes <= 0)
			{//no attributes to seTest
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
					return m_arrPtrNodes.front();
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
						return m_arrPtrNodes.at(lngCurrIndex);
					}else{
						//not a legal index quit gracefully;
						lngCurrIndex = 0;
						return NULL;
					};
				};
			}catch(...){
				return NULL;
			};

		};
		//!Get the pointer to the previous Element
		HtlTestNode * HtlTestNode::previousNode(size_t & lngCurrIndex)
		{
			size_t intNumNodes;
			intNumNodes = m_arrPtrNodes.size();
			if(intNumNodes <= 0)
			{//no attributes to seTest
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
					return m_arrPtrNodes.front();
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
						return m_arrPtrNodes.at(lngCurrIndex);
					}else{
						//not a legal index quit gracefully;
						lngCurrIndex = 0;
						return NULL;
					};
				};
			}catch(...){
				return NULL;
			};
		};

		int HtlTestNode::PerformTest(void)
		{
			try{
				int intReturn = 1;
				std::cout << "Performing Test..." << this->m_strTestName.c_str() << "\n";
				//setup
				intReturn = this->SetupTest();
				//!  Perform any test pre-processing
				intReturn = this->PreProcessTest();
				//! Run the actual test suite for this node.  CAN involve other sub test nodes
				intReturn = this->RunTest();

				//run all sub nodes/////////////////////
				size_t i, intNumNodes;
				intNumNodes = this->countNodes();
				for(i = 0; i < intNumNodes;i++)
				{		
					std::cout << "\tSubNode...\n";
					//run that registered sub node
					if (this->atNode(i))
					{
						intReturn = this->atNode(i)->PerformTest();
					}
					
				};
				///////////////////////////////////////

				//post process
				intReturn = this->PostProcessTest();
				//clean up
				intReturn = this->ClearTest();

			

			return intReturn;
						}catch(...){
				return -1;
			};
		};  
		
};//end namespace HTL