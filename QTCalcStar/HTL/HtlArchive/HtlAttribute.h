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
#ifndef HtlATTRIBUTE_H
#define HtlATTRIBUTE_H

#include ".\HtlNode.h"

namespace HTL{


	//!HtlAttribute is a name value pair node for storing property information of an HtlElement.
	class HTL_DLLAPI HtlAttribute : 
		public HtlNode
		{
		public:

			//PUBLIC CONSTRUCTORS & DESTRUCTOR/////////////////////////////
			//!Void Constructor
			HtlAttribute(void);
			//!Constructor with parent node passed in to manually set the parent node
			HtlAttribute(HtlNode * ptrParentNode);
			//!Copy Constructor
			HtlAttribute(HtlAttribute & rhs);
			//!Virtual Destructor
			virtual ~HtlAttribute(void);
			//PUBLIC OPERATOR OVERLOADS
			//!Assignment Operator Overload
			HtlAttribute & operator = (HtlAttribute & rhs);
			
		private:

		};//end class HtlAttribute;

};//end namespace HtlStar
#endif //HtlATTRIBUTE_H