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
#ifndef HTL_3DINDEX_H
#define HTL_3DINDEX_H
#include "..\modHtlLibRefs.h"
#include ".\HtlBase.h"

namespace HTL{

	//!Three Dimensional Index for tables and treeviews
	class HTL_DLLAPI Htl3DIndex : public HtlBase
	{
	public:
		Htl3DIndex();
		~Htl3DIndex();
		//!Htl3DIndex equal operator
		bool operator==(const Htl3DIndex& ptrRHS); 

		bool operator!=(const Htl3DIndex& ptrRHS); 

		bool operator<=(const Htl3DIndex& ptrRHS);

		bool operator>=(const Htl3DIndex& ptrRHS); 

		bool operator<(const Htl3DIndex& ptrRHS); 

		bool operator>(const Htl3DIndex& ptrRHS); 

		//!Clear the parent pointer
		void ClearParent(void);
		//!Clear the index
		void Clear(void);
		//!Zero the index
		void Zero(void);

		//Virtual Inheritance Serialization Engines
		//SERIALIZATION FUNCTIONS///////////////////////////////////////
		//Save member data to the current element node
		virtual int Save(HTL::HtlElement * ptrCurrNode, std::string strMemVarName, bool blnWithSubObjects);
		//Load member data from the current element node
		virtual int Load(HTL::HtlElement * ptrCurrNode, std::string strMemVarName);

	public:
		//index row or X value
		long m_lngX;
		//index column or Y value
		long m_lngY;
		//index level, page, or Z value
		long m_lngZ;
		//pointer to parent index
		Htl3DIndex * m_ptrParent;
	};//end 


};//end HTL namespace

#endif
