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
#ifndef HtlDOCUMENT_H
#define HtlDOCUMENT_H

#include ".\HtlElement.h"

namespace HTL{
	//!HtlDocument is the capstone document object that is based on an HtlElement class.
	class HTL_DLLAPI HtlDocument : 
		public HtlElement
		{
		public:

			//PUBLIC CONSTRUCTORS & DESTRUCTOR/////////////////////////////
			//!Void Constructor
			HtlDocument(void);
			//!Constructor with parent node passed in to manually set the parent node
			HtlDocument(HtlNode * ptrParentNode);
			//!Copy Constructor
			HtlDocument(HtlDocument & rhs);
			virtual ~HtlDocument(void);
			//PUBLIC OPERATOR OVERLOADS
			//!Assignment Operator
			HtlDocument & operator = (HtlDocument & rhs);

			//!Set and Get for Include Prologue
			void Set_blnIncludePrologue(bool blnIncludePrologue);
			//!Get Include Prologue
			bool Get_blnIncludePrologue(void) const;

			//!Set Document Htl Version Number
			void Set_strVersion(std::string strVersion);
			//!Get Document Htl Version Number
			std::string Get_strVersion(void) const;

			//!Set Document Encoding 
			void Set_strEncoding(std::string strEncoding);
			//!Get Document Encoding
			std::string Get_strEncoding(void) const;

			//!Set Include Standalone
			void Set_blnStandalone(bool blnStandalone);
			//!Get Include Standalone
			bool Get_blnStandalone(void) const;

			//!Set Include Document Type Statement
			void Set_blnIncludeDocType(bool m_blnIncludeDocType);
			//!Get Include Document Type Statement
			bool Get_blnIncludeDocType(void) const;

			//!Set Document Type Statement 
			void Set_strDocType(std::string strDocType);
			//!Get Document Type Statement 
			std::string Get_strDocType(void) const;


			//Htl SERIALIZATION AND DE-SERIALIZATION METHODS///////////
			//!Load the XML Tree from the INPUT string or stream
			virtual int LoadHtlTree(std::string & strInput);
			//!Load the XML Tree from the string or stream
			virtual int LoadHtlTree(std::istream & strStreamInput);
			//!Load the XML Tree from the string or stream
			virtual int LoadHtlTree(std::ifstream & strStreamInput);

			//!Save the XML Tree to the OUTPUT string or stream
			virtual int SaveHtlTree(std::string & strOutput,bool blnWithFormatting);
			//!Save the XML Tree to the OUTPUT string or stream
			virtual int SaveHtlTree(std::ostream & strStreamOut,bool blnWithFormatting);
			//!Save the XML Tree to the OUTPUT string or stream
			virtual int SaveHtlTree(std::ofstream & strStreamOut,bool blnWithFormatting);
			//virtual std::string Get_strValue(bool blnWithFormatting);

		private:
			//!Htl Document Prolog Properties included in output
			bool m_blnIncludePrologue;
			//!Htl Prolog string version number for the 
			std::string m_strVersion;
			//!Htl Prolog string encoding format for the 
			std::string m_strEncoding;
			//!Htl Prolog standalone mode
			std::string m_strStandalone;
			//!Htl Document Type Format Tag included in output
			bool m_blnIncludeDocType;
			//!Htl Document Type Format Tag 
			std::string m_strDocType;

		};//end HtlDocument class definition

};//end HtlStar Namespace
#endif