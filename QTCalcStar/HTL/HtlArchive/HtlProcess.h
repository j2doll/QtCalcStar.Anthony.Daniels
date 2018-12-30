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
#ifndef HtlPROCESS_H
#define HtlPROCESS_H

#include ".\HtlNode.h"
#include ".\HtlAttribute.h"

namespace HTL{
	//!This is the archive tree process node.
	/*!
		This is the archive tree process node. Process nodes usually store procedures or code blocks to be interpreted.
	*/
	class HTL_DLLAPI HtlProcess : 
		public HtlNode
		{
		public:

			//PUBLIC CONSTRUCTORS & DESTRUCTOR/////////////////////////////
			//!Void Constructor
			HtlProcess(void);
			//!Constructor with parent node passed in to manually set the parent node
			HtlProcess(HtlNode * ptrParentNode);
			//!Copy Constructor
			HtlProcess(HtlProcess & rhs);
			//!Virtual Destructor
			virtual ~HtlProcess(void);
			//PUBLIC OPERATOR OVERLOADS
			//!Assignment Operator Overload
			HtlProcess & operator = (HtlProcess & rhs);

			void Clear(void);
			//ATTRIBUTE COLLECTION ACCESSOR FUNCTIONS/////////////////////
			//!Add an attribute to the element
			HtlAttribute * AddAttribute(void);
			//!Add an attribute to the element
			int AddAttribute(HtlAttribute * ptrAttrib);
			//!Delete an attribute from the element by its name
			int DeleteAttribute(std::string strName);
			//!Delete an attribute from the element by its index
			int DeleteAttribute(size_t lngIndex);
			//!Delete All of the Element's Attributes
			int DeleteAllAttributes(void);
			//!Sort the collection of Attributes Alphabetically
			int SortAttributes(void);
			//!Size of the Attribute collection
			long CountAttributes(void);
			//!Boolean check to see if attribute collection is empty
			bool HasAttributes(void);
			//!Does Attribute Exist check by it's name
			bool DoesAttributeExist(std::string strName);
			//!Get the pointer to the first Attribute
			HtlAttribute * FirstAttribute(void);
			//!Get the pointer to the last Attribute
			HtlAttribute * LastAttribute(void);
			//!Get the pointer to the next Attribute
			HtlAttribute * NextAttribute(void);
			//!Get the pointer to the previous Attribute
			HtlAttribute * PreviousAttribute(void);
			//!Get the pointer to the Attribute by it's name
			HtlAttribute * GetAttribute(std::string strName);
			//!Get the pointer to the Attribute by it's index
			HtlAttribute * GetAttribute(size_t lngIndex);		
		protected:
			//!The vector collection of the attributes for this element
			std::vector<HtlAttribute* > m_arrPtrAttributes;
			//pointer to the currently selected Attribute
			size_t m_intCurrAttributeIndex;
		};//end class HtlProcess;

};//end namespace HtlStar
#endif //HtlPROCESS_H