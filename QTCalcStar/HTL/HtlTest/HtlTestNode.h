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
//HtlDB BASE Test NODE TYPE
#ifndef HTL_TESTNODE_H
#define HTL_TESTNODE_H

#include "..\modHtlGlobal.h"
#include "..\modHtlMacro.h"
#include "..\modHtlString.h"

//TEMPORARILY HAS STD::VECTOR UNTIL HTL vector1D class is written
#include <vector>
#include <string>
using namespace std;

//Htl BASE TYPE DEFINITION
//Htl Base is a minimalistic struct that allows for strong typing
namespace HTL
{

	class HTL_DLLAPI HtlTestNode
	{
	public:

		HtlTestNode();
		HtlTestNode(HtlTestNode* ptrParent);
		virtual ~HtlTestNode();
		//!pointer to the parent Node
		HTLMEMVAR_BYVAL_STYLE1(public, HtlTestNode*, ptrParentNode);
		//!String name of the node
		HTLMEMVAR_BYREF_STYLE1(public, std::string, strTestName);
		void Set_strNodeName(const char* ptrChar){m_strTestName = ptrChar;};
		//!String node name type
		HTLMEMVAR_BYREF_STYLE1(public, std::string, strTestDescription);
		void Set_strNodeType(const char* ptrChar){m_strTestDescription = ptrChar;};
		//!String node value (Variant as a string)
		HTLMEMVAR_BYREF_STYLE1(public, std::string, strResults);
		void Set_strValue(const char* ptrChar){m_strResults = ptrChar;};
		//!String node value (Variant as a string)
		HTLMEMVAR_BYVAL_STYLE1(public, int, intResultsCode);


		//!Sub Node Manipulation methods//////////////////////////////////
		HtlTestNode * addNode(std::string & strTestName);
		int deleteNode(std::string & strName);
		int deleteNode(size_t lngIndex);
		int deleteAllNodes(void);
		int sortNodes(void);

		size_t countNodes(void);
		bool hasNodes(void);
		bool doesNodeExist(std::string & strName);
		HtlTestNode * getNode(std::string &  strName);
		HtlTestNode * getNode(size_t lngIndex);
		HtlTestNode * atNode( size_t lngIndex);
		HtlTestNode * firstNode(size_t & lngCurrIndex);
		HtlTestNode * lastNode(size_t & lngCurrIndex);
		HtlTestNode * nextNode(size_t & lngCurrIndex);
		HtlTestNode * previousNode(size_t & lngCurrIndex);


		//Test Node virtual operations functions
		//!Performs Setup, PreProcess, Run, PostProcess, and Clear in sequence.
		int PerformTest(void);  
		//!  Setup the Test Objects
		virtual int SetupTest(void){return 0;};
		//!  Perform any test pre-processing
		virtual int PreProcessTest(void){return 0;};
		//! Run the actual test suite for this node.  CAN involve other sub test nodes
		virtual int RunTest(void){return 0;};
		virtual int PostProcessTest(void){return 0;};
		virtual int ClearTest(void){return 0;};

	protected: 
		//!Sub test nodes
		std::vector<HtlTestNode*> m_arrPtrNodes;


	};//end class definition

};//end Htl namespace
#endif