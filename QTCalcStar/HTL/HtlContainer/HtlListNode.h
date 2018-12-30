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

#ifndef HTL_LISTNODE_H
#define HTL_LISTNODE_H

#include "..\modHtlLibRefs.h"

namespace HTL
{
	template< typename TObj>
	class HtlListNode
	{
	public:
		HtlListNode(void)
		{
			//set to NULL STRING
			m_ptrNext = 0;
			m_ptrPrev = 0;
			memset(&m_data,0,sizeof(TObj));
		};
		virtual ~HtlListNode(void)
		{
			//set to NULL STRING
			m_ptrNext = 0;
			m_ptrPrev = 0;
			memset(&m_data,0,sizeof(TObj));
		}

		void set_value(TObj & obj){m_data = obj;};
		TObj* get_value(void){return &m_data;};
	public:
		//!pointer to the NEXT node in vector form
		HtlListNode * m_ptrNext;
		//!pointer to the PREVIOUS Node in the vector form
		HtlListNode * m_ptrPrev;
		//!pointer to the head character
		//IMPORTANT that this is last item to be declared BECAUSE C character array runs after this
		TObj m_data;
	};

};

#endif