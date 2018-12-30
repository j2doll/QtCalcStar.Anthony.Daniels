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

#ifndef HTL_TREENODE_H
#define HTL_TREENODE_H

#include "..\modHtlLibRefs.h"
#include "..\modHtlBase.h"
namespace HTL
{

	template<typename TKey, typename TObj>
	class HtlTreeNode
	{
	public:
		//!Count the number of elements, this is a recursive function
		HtlTreeNode(void)
		{
			//set to NULL STRING
			m_intLHS = 0;
			m_intRHS = 0;
			m_intBalance = 0;
			m_ptrParent = NULL;
			m_ptrLeft = NULL;
			m_ptrRight = NULL;
			m_ptrNext = NULL;
			m_ptrPrev = NULL;
			m_blnRoot = false;
			m_blnHead = false;
			m_blnEnd = false;
		};

		~HtlTreeNode(void)
		{
			this->setNull();
		};

		HtlTreeNode & operator=(HtlTreeNode & ptrRHS)
		{
			//safety check
			if(&ptrRHS == this){return *this;};
			//assignments
			m_objKey = ptrRHS.key();
			m_objData = ptrRHS.value();
			m_intLHS = ptrRHS.m_intLHS;
			m_intRHS = ptrRHS.m_intRHS;
			m_intBalance = ptrRHS.m_intBalance;
			m_ptrParent = ptrRHS.m_ptrParent;
			m_ptrLeft = ptrRHS.m_ptrLeft;
			m_ptrRight = ptrRHS.m_ptrRight;
			m_ptrNext = ptrRHS.m_ptrNext;
			m_ptrPrev = ptrRHS.m_ptrPrev;
			m_blnRoot = ptrRHS.m_blnRoot;
			m_blnHead = ptrRHS.m_blnHead;
			m_blnEnd = ptrRHS.m_blnEnd;
			return *this;
		}

		bool operator == (const HtlTreeNode & ptrRHS ){return (m_objKey == ptrRHS.m_objKey);};
		bool operator != (const HtlTreeNode & ptrRHS ){return (m_objKey != ptrRHS.m_objKey);};
		bool operator < (const HtlTreeNode & ptrRHS ){return (m_objKey < ptrRHS.m_objKey);};
		bool operator > (const HtlTreeNode & ptrRHS ){return (m_objKey > ptrRHS.m_objKey);};
		bool operator <= (const HtlTreeNode & ptrRHS ){return (m_objKey <= ptrRHS.m_objKey);};
		bool operator >= (const HtlTreeNode & ptrRHS ){return (m_objKey >= ptrRHS.m_objKey);};

		//this counts the elements in the tree
		size_t count(size_t & intCounter)
		{ 
			if(m_ptrRight)
			{
				m_ptrRight->count(intCounter);
			};
			if(m_ptrLeft)
			{
				m_ptrLeft->count(intCounter);
			};
			//for this node
			intCounter++;
			return intCounter;
		};
		//!count the height of the of the node
		void heightNode(int & intLevel)
		{
			heightLeft(m_intLHS);
			heightRight(m_intRHS);
			//for all nodes below
			intLevel = max<int>(m_intLHS,m_intRHS);
			//for this node
			this->m_intBalance = m_intLHS - m_intRHS;
			intLevel++;
		};

		bool isRoot(void)
		{
			if(!m_ptrParent)
			{
				m_blnRoot = true;
			}else{
				m_blnRoot = false;			
			};
		};
		bool isLeft(void)
		{
			if(m_ptrParent)
			{
				return (m_ptrParent->m_ptrLeft == this);
			}else{
				return false;
			};
		};
		bool isRight(void)
		{
			if(m_ptrParent)
			{
				return (m_ptrParent->m_ptrRight == this);
			}else{
				return false;
			};
		};

		void setNull(void)
		{	
			m_ptrParent = NULL;
			m_ptrRight = NULL;
			m_ptrLeft = NULL;
			m_ptrNext = NULL;
			m_ptrPrev = NULL;
			//memset(&m_objKey,0,sizeof(TKey));
			//memset(&m_objData,0,sizeof(TObj));
		};
		//!returns the key 
		TKey key(void){return m_objKey;};
		//!returns the payload value
		TObj value(void){return m_objData;};
		//sets the key
		void setKey(TKey & objVal){m_objKey = objVal;};
		//sets the value
		void setValue(TObj & objVal){m_objData = objVal;};

	private:
		//!gets the height of the left sub tree
		void HtlTreeNode::heightLeft(int & intLeft)
		{
			if(m_ptrLeft)
			{
				m_ptrLeft->heightNode(intLeft);
			}else{
				intLeft = 0;
			};
			return;

		};
		//!gets the height of the right sub tree
		void HtlTreeNode::heightRight(int & intRight)
		{
			if(m_ptrRight)
			{
				m_ptrRight->heightNode(intRight);
			}else{
				intRight = 0;
			};
			return;
		};


		//Public Member Variables
	public: 
		//!Size Left side of the sub tree
		int m_intLHS;
		//!Size Rignt side of the sub tree
		int m_intRHS;
		//!This is the AVL Tree node balance level
		//(if abs() > 1 the tree must be rebalanced)
		int m_intBalance;

		bool m_blnRoot;
		bool m_blnHead;
		bool m_blnEnd;

		//!Pointer to the PARENT node
		HtlTreeNode<TKey,TObj> * m_ptrParent;

		//!Pointer to the LEFT sub node
		HtlTreeNode<TKey,TObj> * m_ptrLeft;
		//!Pointer to the RIGHT sub node
		HtlTreeNode<TKey,TObj> * m_ptrRight;

		//!pointer to the NEXT node in vector form
		HtlTreeNode<TKey,TObj> * m_ptrNext;
		//!pointer to the PREVIOUS Node in the vector form
		HtlTreeNode<TKey,TObj> * m_ptrPrev;

		//!This node's Key
		TKey m_objKey;
		//IMPORTANT that this is last item to be declared BECAUSE C character array runs after this
		TObj m_objData;
	};

};//end namespace HTL
#endif

