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
#ifndef HTL_STRUCTS_H
#define HTL_STRUCTS_H
#include "..\modHtlLibRefs.h"

namespace HTL{


	//!Element index for archiving
	struct HTL_DLLAPI HtlElementIndex
	{
	public:

		HtlElementIndex()
		{
			//initialize the values to an invalid index
			Reset();
		};

		inline void Reset(void){
			m_intOpenTagStartPos = 0;
			m_intTagLength = 0;
			m_intOpenTagEndPos = 0;
			m_intSubElementStartPos = 0;
			m_intCloseTagStartPos = 0;
			m_intCloseTagEndPos = 0;
		};

		size_t m_intOpenTagStartPos;
		size_t m_intTagLength;
		size_t m_intOpenTagEndPos;
		size_t m_intSubElementStartPos;
		size_t m_intCloseTagStartPos;
		size_t m_intCloseTagEndPos;
	};

};//end HTL namespace
#endif