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

#include ".\HtlElement.h"


using namespace HTL;

//PUBLIC CONSTRUCTORS & DESTRUCTOR/////////////////////////////
HtlElement::HtlElement(void)
: HtlNode()
{
	//HtlNode Initialization/////////////
	Set_objNodeType(ELEMENT);
	//HtlElement Initialization//////////
	m_intCurrAttributeIndex = NULL;
	m_intCurrElementIndex = NULL;
	m_blnRootNode = false;
	m_blnNullNode = false;
	return;
};
HtlElement::HtlElement(HtlNode * ptrParentNode)
: HtlNode(ptrParentNode)
{
	//HtlNode Initialization/////////////
	Set_objNodeType(ELEMENT);
	//HtlElement Initialization//////////
	m_intCurrAttributeIndex = NULL;
	m_intCurrElementIndex = NULL;
	m_blnRootNode = false;
	m_blnNullNode = false;
	return;
};
HtlElement::HtlElement(HtlElement & rhs)
{
	//self assignment check
	if(this == &rhs)
		return;
	//HtlNode Copy Construction
	HtlNode::HtlNode(rhs);
	//HtlElement Copy Construction
	m_intCurrAttributeIndex = 0;
	m_intCurrElementIndex = 0;
	m_blnRootNode = rhs.Get_blnRootNode();
	m_blnNullNode = rhs.Get_blnNullNode();
	return;
};
HtlElement::~HtlElement(void)
{
	Clear();
};

//PUBLIC OPERATOR OVERLOADS
HtlElement & HtlElement::operator = (HtlElement & rhs)
{	
	//self assignment check
	if(this == &rhs)
		return *this;
	//HtlNode Assignment Operation
	HtlNode::operator = (rhs);
	//HtlElement Assignment Operation
	m_intCurrAttributeIndex = 0;
	m_intCurrElementIndex = 0;
	m_blnRootNode = rhs.Get_blnRootNode();
	m_blnNullNode = rhs.Get_blnNullNode();
	return *this;
};


//PUBLIC MEMBER FUNCTIONS/////////////////////////////////////
void HtlElement::Clear(void)
{
	DeleteAllAttributes();
	DeleteAllSubElements();
	DeleteAllComments();
	DeleteAllProcesses();
};

//ATTRIBUTE COLLECTION ACCESSOR FUNCTIONS/////////////////////
//!Add an attribute to the element
HtlAttribute * HtlElement::AddAttribute(void)
{
	return AddNode<HtlAttribute>(m_arrPtrAttributes, this);
};

//!Add an attribute to the element
int HtlElement::AddAttribute(HtlAttribute * ptrAttrib)
{
	return AddNode<HtlAttribute>(m_arrPtrAttributes, this, ptrAttrib);
};

//!Delete an attribute from the element by its name
int HtlElement::DeleteAttribute(const std::string & strName)
{
	return DeleteNode<HtlAttribute>(m_arrPtrAttributes, strName);
};

//!Delete an attribute from the element by its index
int HtlElement::DeleteAttribute(size_t lngIndex)
{
	return DeleteNode<HtlAttribute>(m_arrPtrAttributes, lngIndex);
};

//!Delete All of the Element's Attributes
int HtlElement::DeleteAllAttributes(void)
{
	return DeleteAllNodes<HtlAttribute>(m_arrPtrAttributes);
};

//!Sort the collection of Attributes Alphabetically
int HtlElement::SortAttributes(void)
{
	return SortNodes<HtlAttribute>(m_arrPtrAttributes);
};

//!Size of the Attribute collection
long HtlElement::CountAttributes(void)
{
	return CountNodes<HtlAttribute>(m_arrPtrAttributes);
};

//!Boolean check to see if attribute collection is empty
bool HtlElement::HasAttributes(void)
{
	return HasNodes<HtlAttribute>(m_arrPtrAttributes);
};

//!Does Attribute Exist check by it's name
bool HtlElement::DoesAttributeExist(const std::string & strName)
{
	return DoesNodeExist<HtlAttribute>(m_arrPtrAttributes, strName);
};

//!Get the pointer to the first Attribute
HtlAttribute * HtlElement::FirstAttribute(void)
{
	return FirstNode<HtlAttribute>(m_arrPtrAttributes, m_intCurrAttributeIndex);
};

//!Get the pointer to the last Attribute
HtlAttribute * HtlElement::LastAttribute(void)
{
	return LastNode<HtlAttribute>(m_arrPtrAttributes, m_intCurrAttributeIndex);
};

//!Get the pointer to the next Attribute
HtlAttribute * HtlElement::NextAttribute(void)
{
	return NextNode<HtlAttribute>(m_arrPtrAttributes, m_intCurrAttributeIndex);
};

//!Get the pointer to the previous Attribute
HtlAttribute * HtlElement::PreviousAttribute(void)
{
	return PreviousNode<HtlAttribute>(m_arrPtrAttributes, m_intCurrAttributeIndex);
};

//!Get the pointer to the Attribute by it's name
HtlAttribute * HtlElement::GetAttribute(const std::string & strName)
{
	return GetNode<HtlAttribute>(m_arrPtrAttributes, strName);
};
//!Get the pointer to the Attribute by it's index
HtlAttribute * HtlElement::GetAttribute(size_t lngIndex)
{
	return GetNode<HtlAttribute>(m_arrPtrAttributes, lngIndex);
};
//!Get the pointer to the Attribute by it's index
HtlAttribute * HtlElement::AtAttribute(size_t lngIndex)
{
	return GetNode<HtlAttribute>(m_arrPtrAttributes, lngIndex);
};
//COMMENT COLLECTION ACCESSOR FUNCTIONS/////////////////////
//!Add an Comment to the element
HtlComment * HtlElement::AddComment(void)
{
	return AddNode<HtlComment>(m_arrPtrComments, this);
};

//!Add an Comment to the element
int HtlElement::AddComment(HtlComment * ptrAttrib)
{
	return AddNode<HtlComment>(m_arrPtrComments, this, ptrAttrib);
};

//!Delete an Comment from the element by its name
int HtlElement::DeleteComment(const std::string & strName)
{
	return DeleteNode<HtlComment>(m_arrPtrComments, strName);
};

//!Delete an Comment from the element by its index
int HtlElement::DeleteComment(size_t lngIndex)
{
	return DeleteNode<HtlComment>(m_arrPtrComments, lngIndex);
};

//!Delete All of the Element's Comments
int HtlElement::DeleteAllComments(void)
{
	return DeleteAllNodes<HtlComment>(m_arrPtrComments);
};

//!Sort the collection of Comments Alphabetically
int HtlElement::SortComments(void)
{
	return SortNodes<HtlComment>(m_arrPtrComments);
};

//!Size of the Comment collection
long HtlElement::CountComments(void)
{
	return CountNodes<HtlComment>(m_arrPtrComments);
};

//!Boolean check to see if Comment collection is empty
bool HtlElement::HasComments(void)
{
	return HasNodes<HtlComment>(m_arrPtrComments);
};

//!Does Comment Exist check by it's name
bool HtlElement::DoesCommentExist(const std::string & strName)
{
	return DoesNodeExist<HtlComment>(m_arrPtrComments, strName);
};

//!Get the pointer to the first Comment
HtlComment * HtlElement::FirstComment(void)
{
	return FirstNode<HtlComment>(m_arrPtrComments, m_intCurrCommentIndex);
};

//!Get the pointer to the last Comment
HtlComment * HtlElement::LastComment(void)
{
	return LastNode<HtlComment>(m_arrPtrComments, m_intCurrCommentIndex);
};

//!Get the pointer to the next Comment
HtlComment * HtlElement::NextComment(void)
{
	return NextNode<HtlComment>(m_arrPtrComments, m_intCurrCommentIndex);
};

//!Get the pointer to the previous Comment
HtlComment * HtlElement::PreviousComment(void)
{
	return PreviousNode<HtlComment>(m_arrPtrComments, m_intCurrCommentIndex);
};

//!Get the pointer to the Comment by it's name
HtlComment * HtlElement::GetComment(const std::string & strName)
{
	return GetNode<HtlComment>(m_arrPtrComments, strName);
};

//!Get the pointer to the Comment by it's index
HtlComment * HtlElement::GetComment(size_t lngIndex)
{
	return GetNode<HtlComment>(m_arrPtrComments, lngIndex);
};

//!Get the pointer to the Comment by it's index
HtlComment * HtlElement::AtComment(size_t lngIndex)
{
	return GetNode<HtlComment>(m_arrPtrComments, lngIndex);
};

//PROCESS COLLECTION ACCESSOR FUNCTIONS/////////////////////
//!Add an Process to the element
HtlProcess * HtlElement::AddProcess(void)
{
	return AddNode<HtlProcess>(m_arrPtrProcesses, this);
};

//!Add an Process to the element
int HtlElement::AddProcess(HtlProcess * ptrAttrib)
{
	return AddNode<HtlProcess>(m_arrPtrProcesses, this, ptrAttrib);
};

//!Delete an Process from the element by its name
int HtlElement::DeleteProcess(const std::string & strName)
{
	return DeleteNode<HtlProcess>(m_arrPtrProcesses, strName);
};

//!Delete an Process from the element by its index
int HtlElement::DeleteProcess(size_t lngIndex)
{
	return DeleteNode<HtlProcess>(m_arrPtrProcesses, lngIndex);
};

//!Delete All of the Element's Processes
int HtlElement::DeleteAllProcesses(void)
{
	return DeleteAllNodes<HtlProcess>(m_arrPtrProcesses);
};

//!Sort the collection of Processes Alphabetically
int HtlElement::SortProcesses(void)
{
	return SortNodes<HtlProcess>(m_arrPtrProcesses);
};

//!Size of the Process collection
long HtlElement::CountProcesses(void)
{
	return CountNodes<HtlProcess>(m_arrPtrProcesses);
};

//!Boolean check to see if Process collection is empty
bool HtlElement::HasProcesses(void)
{
	return HasNodes<HtlProcess>(m_arrPtrProcesses);
};

//!Does Process Exist check by it's name
bool HtlElement::DoesProcessExist(const std::string & strName)
{
	return DoesNodeExist<HtlProcess>(m_arrPtrProcesses, strName);
};

//!Get the pointer to the first Process
HtlProcess * HtlElement::FirstProcess(void)
{
	return FirstNode<HtlProcess>(m_arrPtrProcesses, m_intCurrProcessIndex);
};

//!Get the pointer to the last Process
HtlProcess * HtlElement::LastProcess(void)
{
	return LastNode<HtlProcess>(m_arrPtrProcesses, m_intCurrProcessIndex);
};

//!Get the pointer to the next Process
HtlProcess * HtlElement::NextProcess(void)
{
	return NextNode<HtlProcess>(m_arrPtrProcesses, m_intCurrProcessIndex);
};

//!Get the pointer to the previous Process
HtlProcess * HtlElement::PreviousProcess(void)
{
	return PreviousNode<HtlProcess>(m_arrPtrProcesses, m_intCurrProcessIndex);
};

//!Get the pointer to the Process by it's name
HtlProcess * HtlElement::GetProcess(const std::string & strName)
{
	return GetNode<HtlProcess>(m_arrPtrProcesses, strName);
};

//!Get the pointer to the Process by it's index
HtlProcess * HtlElement::GetProcess(size_t lngIndex)
{
	return GetNode<HtlProcess>(m_arrPtrProcesses, lngIndex);
};

//!Get the pointer to the Process by it's index
HtlProcess * HtlElement::AtProcess(size_t lngIndex)
{
	return GetNode<HtlProcess>(m_arrPtrProcesses, lngIndex);
};

//SUB - ELEMENT COLLECTION ACCESSOR FUNCTIONS//////////////////////
//!Add an attribute to the element
HtlElement * HtlElement::AddSubElement(void)
{
	return AddNode<HtlElement>(m_arrPtrSubElements, this);
};

//!Add an attribute to the element
int HtlElement::AddSubElement(HtlElement * ptrElement)
{
	return AddNode<HtlElement>(m_arrPtrSubElements, this, ptrElement);
};

//!Delete an attribute from the element by its name
int HtlElement::DeleteSubElement(const std::string & strName)
{
	return DeleteNode<HtlElement>(m_arrPtrSubElements, strName);
};

//!Delete an attribute from the element by its index
int HtlElement::DeleteSubElement(size_t lngIndex)
{
	return DeleteNode<HtlElement>(m_arrPtrSubElements, lngIndex);
};

//!Delete All of the Element's sub-Elements
int HtlElement::DeleteAllSubElements(void)
{
	return DeleteAllNodes<HtlElement>(m_arrPtrSubElements);
};

//!Sort the collection of Elements Alphabetically
int HtlElement::SortSubElements(void)
{
	return SortNodes<HtlElement>(m_arrPtrSubElements);
};

//!Size of the Element collection
long HtlElement::CountSubElements(void)
{
	return CountNodes<HtlElement>(m_arrPtrSubElements);
};

//!Boolean check to see if attribute collection is empty
bool HtlElement::HasSubElements(void)
{
	return HasNodes<HtlElement>(m_arrPtrSubElements);
};

//!Does Element Exist check by it's name
bool HtlElement::DoesSubElementExist(const std::string & strName)
{
	return DoesNodeExist<HtlElement>(m_arrPtrSubElements, strName);
};

//!Get the pointer to the first Element
HtlElement * HtlElement::FirstSubElement(void)
{
	return FirstNode<HtlElement>(m_arrPtrSubElements, m_intCurrElementIndex);
};

//!Get the pointer to the last Element
HtlElement * HtlElement::LastSubElement(void)
{
	return LastNode<HtlElement>(m_arrPtrSubElements, m_intCurrElementIndex);
};

//!Get the pointer to the next Element
HtlElement * HtlElement::NextSubElement(void)
{
	return NextNode<HtlElement>(m_arrPtrSubElements, m_intCurrElementIndex);
};

//!Get the pointer to the previous Element
HtlElement * HtlElement::PreviousSubElement(void)
{
	return PreviousNode<HtlElement>(m_arrPtrSubElements, m_intCurrElementIndex);
};

//!Get the pointer to the Element by it's name
HtlElement * HtlElement::GetSubElement(const std::string & strName)
{
	return GetNode<HtlElement>(m_arrPtrSubElements, strName);
};

//!Get the pointer to the Element by it's index
HtlElement * HtlElement::GetSubElement(size_t lngIndex)
{
	return GetNode<HtlElement>(m_arrPtrSubElements, lngIndex);
};

//!Get the pointer to the Element by it's index
HtlElement * HtlElement::AtSubElement(size_t lngIndex)
{
	return GetNode<HtlElement>(m_arrPtrSubElements, lngIndex);
};

//!Sets the root node flag
void HtlElement::Set_blnRootNode(bool blnIsRootNode)
{
	m_blnRootNode = blnIsRootNode;
	return;
};

//!Gets the root node flag value
bool HtlElement::Get_blnRootNode(void) const
{
	return m_blnRootNode;
};

//!Indicates whether or not this element is the root node
bool HtlElement::IsRootNode(void)
{
	return m_blnRootNode;
};

//!Sets the null node flag
void HtlElement::Set_blnNullNode(bool blnIsNullNode)
{
	m_blnNullNode = blnIsNullNode;
	return;
};

//!Gets the null node flag value
bool HtlElement::Get_blnNullNode(void) const
{
	return m_blnNullNode;
};

//!Indicates whether or not this element is the null node
bool HtlElement::IsNullNode(void)
{
	return m_blnNullNode;
};

//!Update the indexes
int HtlElement::UpdateIndexes(void)
{
	int i, intNumAttributes,j,intNumSubElements;
	intNumAttributes = m_arrPtrAttributes.size();
	if(m_blnRootNode)
	{
		Set_intLevel(0);
	}
	for(i = 0; i < intNumAttributes; i++)
	{
		m_arrPtrAttributes.at(i)->Set_intLevel(Get_intLevel());
		m_arrPtrAttributes.at(i)->Set_intRow(i);
	};
	intNumSubElements = m_arrPtrSubElements.size();
	for(j = 0; j < intNumSubElements;j++)
	{
		m_arrPtrSubElements.at(j)->Set_intLevel(Get_intLevel() + 1);
		m_arrPtrSubElements.at(j)->Set_intRow(j);
		m_arrPtrSubElements.at(j)->UpdateIndexes();
	};
	return 1;
};