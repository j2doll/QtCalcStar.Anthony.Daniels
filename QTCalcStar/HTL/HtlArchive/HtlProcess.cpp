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

#include ".\HtlProcess.h"

using namespace HTL;

//PUBLIC CONSTRUCTORS & DESTRUCTOR/////////////////////////////
HtlProcess::HtlProcess(void)
: HtlNode()
{
		//HtlNode Initialization/////////////
	Set_objNodeType(PROCESS);
		m_intCurrAttributeIndex = NULL;
	return;
};

HtlProcess::HtlProcess(HtlNode * ptrParentNode)
: HtlNode(ptrParentNode)
{
		//HtlNode Initialization/////////////
	Set_objNodeType(PROCESS);
		m_intCurrAttributeIndex = NULL;
	return;
};

HtlProcess::HtlProcess(HtlProcess & rhs)
{
	//self assignment check
	if(this == &rhs)
		return;
	//HtlNode Copy Construction
	HtlNode::HtlNode(rhs);
	//HtlProcess Copy Construction
		m_intCurrAttributeIndex = NULL;

	return;
};

HtlProcess::~HtlProcess(void)
{
	Clear();
};

//PUBLIC OPERATOR OVERLOADS
HtlProcess & HtlProcess::operator = (HtlProcess & rhs)
{	
	//self assignment check
	if(this == &rhs)
		return *this;
	//HtlNode Assignment Operation
	HtlNode::operator = (rhs);
	//HtlProcess Assignment Operation
	m_intCurrAttributeIndex = NULL;
	return *this;
};

//PUBLIC MEMBER FUNCTIONS/////////////////////////////////////
void HtlProcess::Clear(void)
{
	DeleteAllAttributes();
};

//ATTRIBUTE COLLECTION ACCESSOR FUNCTIONS/////////////////////
//!Add an attribute to the element
HtlAttribute * HtlProcess::AddAttribute(void)
{
	return AddNode<HtlAttribute>(m_arrPtrAttributes, this);
};

//!Add an attribute to the element
int HtlProcess::AddAttribute(HtlAttribute * ptrAttrib)
{
	return AddNode<HtlAttribute>(m_arrPtrAttributes, this, ptrAttrib);
};

//!Delete an attribute from the element by its name
int HtlProcess::DeleteAttribute(std::string strName)
{
	return DeleteNode<HtlAttribute>(m_arrPtrAttributes, strName);
};

//!Delete an attribute from the element by its index
int HtlProcess::DeleteAttribute(size_t lngIndex)
{
	return DeleteNode<HtlAttribute>(m_arrPtrAttributes, lngIndex);
};

//!Delete All of the Element's Attributes
int HtlProcess::DeleteAllAttributes(void)
{
	return DeleteAllNodes<HtlAttribute>(m_arrPtrAttributes);
};

//!Sort the collection of Attributes Alphabetically
int HtlProcess::SortAttributes(void)
{
	return SortNodes<HtlAttribute>(m_arrPtrAttributes);
};

//!Size of the Attribute collection
long HtlProcess::CountAttributes(void)
{
	return CountNodes<HtlAttribute>(m_arrPtrAttributes);
};

//!Boolean check to see if attribute collection is empty
bool HtlProcess::HasAttributes(void)
{
	return HasNodes<HtlAttribute>(m_arrPtrAttributes);
};

//!Does Attribute Exist check by it's name
bool HtlProcess::DoesAttributeExist(std::string strName)
{
	return DoesNodeExist<HtlAttribute>(m_arrPtrAttributes, strName);
};

//!Get the pointer to the first Attribute
HtlAttribute * HtlProcess::FirstAttribute(void)
{
	return FirstNode<HtlAttribute>(m_arrPtrAttributes, m_intCurrAttributeIndex);
};

//!Get the pointer to the last Attribute
HtlAttribute * HtlProcess::LastAttribute(void)
{
	return LastNode<HtlAttribute>(m_arrPtrAttributes, m_intCurrAttributeIndex);
};

//!Get the pointer to the next Attribute
HtlAttribute * HtlProcess::NextAttribute(void)
{
	return NextNode<HtlAttribute>(m_arrPtrAttributes, m_intCurrAttributeIndex);
};

//!Get the pointer to the previous Attribute
HtlAttribute * HtlProcess::PreviousAttribute(void)
{
	return PreviousNode<HtlAttribute>(m_arrPtrAttributes, m_intCurrAttributeIndex);
};

//!Get the pointer to the Attribute by it's name
HtlAttribute * HtlProcess::GetAttribute(std::string strName)
{
	return GetNode<HtlAttribute>(m_arrPtrAttributes, strName);
};

//!Get the pointer to the Attribute by it's index
HtlAttribute * HtlProcess::GetAttribute(size_t lngIndex)
{
	return GetNode<HtlAttribute>(m_arrPtrAttributes, lngIndex);
};