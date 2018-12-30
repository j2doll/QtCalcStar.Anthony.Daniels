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
#ifndef HtlELEMENT_H
#define HtlELEMENT_H

#include ".\HtlNode.h"
#include ".\HtlAttribute.h"
#include ".\HtlComment.h"
#include ".\HtlProcess.h"

namespace HTL{
			//!HtlElement is the primary node in the generic serializable tree structure that HTL incorporates.
			/*!
			HtlElement is the primary node in the generic serializable tree structure that HTL incorporates.
			HtlElement owns a collection of Attributes, Comments, Processes and Sub Elements.
			HtlElement is directly based on the XML counterpart and provides the user with a generic tree
			structure for object persistance.
			*/
	class HTL_DLLAPI HtlElement : 
		public HtlNode
		{
		public:

			//PUBLIC CONSTRUCTORS & DESTRUCTOR/////////////////////////////
			//!Void constructor
			HtlElement(void);
			//!Constructor with parent node passed in to manually set the parent node
			HtlElement(HtlNode * ptrParentNode);
			//!Copy Constructor
			HtlElement(HtlElement & rhs);
			//!Virtual Destructor
			virtual ~HtlElement(void);
			//PUBLIC OPERATOR OVERLOADS///////////////////////////////////
			HtlElement & operator = (HtlElement & rhs);

			void Clear(void);
			//ATTRIBUTE COLLECTION ACCESSOR FUNCTIONS/////////////////////
			//!Add an attribute to the element
			HtlAttribute * AddAttribute(void);
			//!Add an attribute to the element
			int AddAttribute(HtlAttribute * ptrAttrib);
			//!Delete an attribute from the element by its name
			int DeleteAttribute(const std::string & strName);
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
			bool DoesAttributeExist(const std::string & strName);
			//!Get the pointer to the first Attribute
			HtlAttribute * FirstAttribute(void);
			//!Get the pointer to the last Attribute
			HtlAttribute * LastAttribute(void);
			//!Get the pointer to the next Attribute
			HtlAttribute * NextAttribute(void);
			//!Get the pointer to the previous Attribute
			HtlAttribute * PreviousAttribute(void);
			//!Get the pointer to the Attribute by it's name
			HtlAttribute * GetAttribute(const std::string & strName);
			//!Get the pointer to the Attribute by it's index
			HtlAttribute * GetAttribute(size_t lngIndex);
			//!Get the pointer to the Attribute by it's index
			HtlAttribute * AtAttribute(size_t lngIndex);

			//COMMENT COLLECTION ACCESSOR FUNCTIONS/////////////////////
			//!Add an Comment to the element
			HtlComment * AddComment(void);
			//!Add an Comment to the element
			int AddComment(HtlComment * ptrAttrib);
			//!Delete an Comment from the element by its name
			int DeleteComment(const std::string & strName);
			//!Delete an Comment from the element by its index
			int DeleteComment(size_t lngIndex);
			//!Delete All of the Element's Comments
			int DeleteAllComments(void);
			//!Sort the collection of Comments Alphabetically
			int SortComments(void);
			//!Size of the Comment collection
			long CountComments(void);
			//!Boolean check to see if Comment collection is empty
			bool HasComments(void);
			//!Does Comment Exist check by it's name
			bool DoesCommentExist(const std::string & strName);
			//!Get the pointer to the first Comment
			HtlComment * FirstComment(void);
			//!Get the pointer to the last Comment
			HtlComment * LastComment(void);
			//!Get the pointer to the next Comment
			HtlComment * NextComment(void);
			//!Get the pointer to the previous Comment
			HtlComment * PreviousComment(void);
			//!Get the pointer to the Comment by it's name
			HtlComment * GetComment(const std::string & strName);
			//!Get the pointer to the Comment by it's index
			HtlComment * GetComment(size_t lngIndex);
			//!Get the pointer to the Comment by it's index
			HtlComment * AtComment(size_t lngIndex);

			//COMMENT COLLECTION ACCESSOR FUNCTIONS/////////////////////
			//!Add an Process to the element
			HtlProcess * AddProcess(void);
			//!Add an Process to the element
			int AddProcess(HtlProcess * ptrAttrib);
			//!Delete an Process from the element by its name
			int DeleteProcess(const std::string & strName);
			//!Delete an Process from the element by its index
			int DeleteProcess(size_t lngIndex);
			//!Delete All of the Element's Processs
			int DeleteAllProcesses(void);
			//!Sort the collection of Processs Alphabetically
			int SortProcesses(void);
			//!Size of the Process collection
			long CountProcesses(void);
			//!Boolean check to see if Process collection is empty
			bool HasProcesses(void);
			//!Does Process Exist check by it's name
			bool DoesProcessExist(const std::string & strName);
			//!Get the pointer to the first Process
			HtlProcess * FirstProcess(void);
			//!Get the pointer to the last Process
			HtlProcess * LastProcess(void);
			//!Get the pointer to the next Process
			HtlProcess * NextProcess(void);
			//!Get the pointer to the previous Process
			HtlProcess * PreviousProcess(void);
			//!Get the pointer to the Process by it's name
			HtlProcess * GetProcess(const std::string & strName);
			//!Get the pointer to the Process by it's index
			HtlProcess * GetProcess(size_t lngIndex);
			//!Get the pointer to the Process by it's index
			HtlProcess * AtProcess(size_t lngIndex);

			//SUB-ELEMENT COLLECTION ACCESSOR FUNCTIONS//////////////////////
			//!Add an attribute to the element
			HtlElement *  AddSubElement(void);
			//!Add an attribute to the element
			int AddSubElement(HtlElement * ptrAttrib);
			//!Delete an attribute from the element by its name
			int DeleteSubElement(const std::string & strName);
			//!Delete an attribute from the element by its index
			int DeleteSubElement(size_t lngIndex);
			//!Delete All of the Element's sub-Elements
			int DeleteAllSubElements(void);
			//!Sort the collection of Elements Alphabetically
			int SortSubElements(void);
			//!Size of the Element collection
			long CountSubElements(void);
			//!Boolean check to see if attribute collection is empty
			bool HasSubElements(void);
			//!Does Element Exist check by it's name
			bool DoesSubElementExist(const std::string & strName);
			//!Get the pointer to the first Element
			HtlElement * FirstSubElement(void);
			//!Get the pointer to the last Element
			HtlElement * LastSubElement(void);
			//!Get the pointer to the next Element
			HtlElement * NextSubElement(void);
			//!Get the pointer to the previous Element
			HtlElement * PreviousSubElement(void);
			//!Get the pointer to the Element by it's name
			HtlElement * GetSubElement(const std::string & strName);
			//!Get the pointer to the Element by it's index
			HtlElement * GetSubElement(size_t lngIndex);
			//!Get the pointer to the Element by it's index
			HtlElement * AtSubElement(size_t lngIndex);

			//!Sets the root node flag
			void Set_blnRootNode(bool blnIsRootNode);
			//!Gets the root node flag value
			bool Get_blnRootNode(void) const;
			//!Indicates whether or not this element is the root node
			bool IsRootNode(void);

			//!Sets the null node flag
			void Set_blnNullNode(bool blnIsNullNode);
			//!Gets the null node flag value
			bool Get_blnNullNode(void) const;
			//!Indicates whether or not this element is the null node
			bool IsNullNode(void);

			//!Update the indexes
			int UpdateIndexes(void);

			//Htl SERIALIZATION AND DE-SERIALIZATION METHODS///////////
			//!Expand the Htl string value of the element
			//virtual int LoadNodeTree(const std::string & strInput, HtlElementIndex & objCurrElementIndex);
			//virtual int LoadNodeTree(std::istream & strStreamInput);
			//virtual int LoadNodeTree(std::ifstream & strStreamInput);
			
			//virtual int SaveNodeTree(std::string & strOutput,bool blnWithFormatting);
			//virtual int SaveNodeTree(std::ostream & strStreamOut,bool blnWithFormatting);
			//virtual int SaveNodeTree(std::ofstream & strStreamOut,bool blnWithFormatting);
			//virtual std::string Get_strValue(bool blnWithFormatting);

		protected:
			//!The vector collection of the attributes for this element
			std::vector<HtlAttribute* > m_arrPtrAttributes;
			//!The vector collection of the comments for this element
			std::vector<HtlComment* > m_arrPtrComments;
			//!The vector collection of the attributes for this element
			std::vector<HtlProcess* > m_arrPtrProcesses;
			//!The vector collection of sub elements for this element
			std::vector<HtlElement* > m_arrPtrSubElements;
			//pointer to the currently selected Attribute
			size_t m_intCurrAttributeIndex;
			//pointer to the currently selected Comment
			size_t m_intCurrCommentIndex;
			//pointer to the currently selected Process
			size_t m_intCurrProcessIndex;
			//pointer to the currently selected element
			size_t m_intCurrElementIndex;
			//!boolean flag for indicating that this element is the root node element, used for auto indexing
			bool m_blnRootNode;

			bool m_blnNullNode;


		};//end class HtlElement;

		//TEMPLATE FUNCTION DEFINITIONS


};//end namespace HtlStar
#endif