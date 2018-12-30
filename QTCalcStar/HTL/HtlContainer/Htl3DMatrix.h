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

#ifndef HTL_3DMATRIX_H
#define HTL_3DMATRIX_H

#include ".\HtlMap.h"

namespace HTL
{
		//!HtlMatrix3D is a container for storing three dimensional matrix of data.
	/*!
	HtlMatrix3D is a container for storing three dimensional matrix of data.  HtlMatrix3D
	is like other array containers in that it can store two dimensional data. HOWEVER, HtlMatrix3D
	is inherits from HtlMap.  IT IS NOT a vector of vectors of vectors winged data structure. IT IS A MAP.
	The HtlIndex3D is the key for the items in the array map.  Going to a map data structure
	provides two unique advantages.  It has linear time item access and it is not all elements
	of the array need to be store, only the ones that have data are stored.  This makes it a very
	compact representation of sparce matrices and other 3d array.
	*/
		template<typename TObj, HtlObjectType TSubObj>
		class Htl3DMatrix : HtlMap<Htl3DIndex,HTL_BASE,TObj,TSubObj>
		{
			//typedef qptrdiff difference_type;
			typedef TObj Value;
			typedef TObj *Pointer;
			typedef TObj &Reference;
			typedef const TObj & ConstReference;
			//HtlVector1D SUBCLASS DECLARATIONS////////////////////////////////////////
			//END HTLVECTOR1D SUBCLASS DEFINITIONS///////////////////////////////////////


			//HtlVector1D CLASS DEFINITION/////////////////////////////////////////
		public:

			//!Default Constructor
			Htl3DMatrix() : HtlMap()
			{
				m_objType = HTL_CONTAINER;
				m_strType = "Htl3DMatrix";
				m_itemType = TSubObj;
				m_chrNull = '\0';
				m_objHead.setNull();
				m_objEnd.setNull();
			};

			//!Virtual Destructor
			virtual ~Htl3DMatrix(void)
			{
				clear();
			};

		};
};
#endif