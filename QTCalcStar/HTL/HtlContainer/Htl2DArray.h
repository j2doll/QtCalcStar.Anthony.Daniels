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

#ifndef HTL_2DARRAY_H
#define HTL_2DARRAY_H

#include ".\HtlMap.h"

namespace HTL
{
	//!HtlArray2D is a container for storing two dimensional array of data.
	/*!
	HtlArray2D is a container for storing two dimensional array of data.  HtlArray2D
	is like other array containers in that it can store two dimensional data. HOWEVER, HtlArray2D
	is inherits from HtlMap.  IT IS NOT a vector of vectors winged data structure. IT IS A MAP.
	The HtlIndex2D is the key for the items in the array map.  Going to a map data structure
	provides two unique advantages.  It has linear time item access and it is not all elements
	of the array need to be store, only the ones that have data are stored.  This makes it a very
	compact representation of sparce matrices and other 2d array.
	*/
		template<typename TObj, HtlObjectType TObjEnum>
		class Htl2DArray : public HtlMap<Htl2DIndex,HTL_BASE,TObj,TObjEnum>
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
			Htl2DArray() : HtlMap()
			{
				m_objType = HTL_CONTAINER;
				m_strType = "Htl2DArray";
				m_itemType = TObjEnum;
				m_chrNull = '\0';
			};

			//!Virtual Destructor
			virtual ~Htl2DArray(void)
			{
				clear();
			};

			//!Less Than Parameter 1 Less Than Parameter 2 Utility Value
			HTLMEMVAR_BYREF_STYLE1(public, TObj, objDefault);

			TObj AtIndex(Htl2DIndex & index)
			{
				try
				{
					HtlTreeNode<Htl2DIndex, TObj> * ptrItem = NULL;
					ptrItem = HtlMap::findList(index);
					if (ptrItem)
					{
						return ptrItem->value();
					};
					//otherwise return default value
					return m_objDefault;
				}
				catch (...)
				{
					std::string errMsg;
					errMsg = "Htl2DArray AtIndex Error thrown";
					throw std::exception(errMsg.c_str());
				}
			};

			void SetValue(int intP1, int intP2, TObj & varVal)
			{
				try
				{
					Htl2DIndex index;
					index.m_lngX = intP1;
					index.m_lngY = intP2;
					HtlMap::insert(index, varVal);
				}
				catch (...)
				{
					std::string errMsg;
					errMsg = "Htl2DArray SetValue Error thrown";
					throw std::exception(errMsg.c_str());
				}
			};

			void GetParam1Range(int & intP1LowerBound, int & intP1UpperBound)
			{
				try
				{
					if (size() <= 0)
					{
						intP1LowerBound = 0;
						intP1UpperBound = 0;
					}
					size_t i;
					Htl2DIndex index = this->atkey(0);
					intP1LowerBound = index.m_lngX;
					intP1UpperBound = index.m_lngX;
					for (i = 0; i < m_intSize; i++)
					{
						index = this->atkey(i);
						if (index.m_lngX < intP1LowerBound) { intP1LowerBound = index.m_lngX; };
						if (index.m_lngX > intP1UpperBound) { intP1UpperBound = index.m_lngX; };
					}
					return;
				}
				catch (...)
				{
					std::string errMsg;
					errMsg = "Htl2DArray GetParam1Range Error thrown";
					throw std::exception(errMsg.c_str());
				}
			};

			void GetParam2Range(int & intP2LowerBound, int & intP2UpperBound)
			{
				try
				{
					if (size() <= 0)
					{
						intP2LowerBound = 0;
						intP2UpperBound = 0;
					}
					size_t i;
					Htl2DIndex index = this->atkey(0);
					intP2LowerBound = index.m_lngY;
					intP2UpperBound = index.m_lngY;
					for (i = 0; i < m_intSize; i++)
					{
						index = this->atkey(i);
						if (index.m_lngY < intP2LowerBound) { intP2LowerBound = index.m_lngY; };
						if (index.m_lngY > intP2UpperBound) { intP2UpperBound = index.m_lngY; };
					}
					return;
				}
				catch (...)
				{
					std::string errMsg;
					errMsg = "Htl2DArray GetParam2Range Error thrown";
					throw std::exception(errMsg.c_str());
				}
			};

		};
};
#endif