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
#ifndef HTL_1DINDEX_H
#define HTL_1DINDEX_H
#include "..\modHtlLibRefs.h"
#include ".\HtlBase.h"

namespace HTL{


	//These are indexes for the various models
	//!One Dimensional Index for lists, vectors, etc.
	class HTL_DLLAPI Htl1DIndex : public HtlBase
	{
	public:
		//!Void Constructor
		Htl1DIndex();
		~Htl1DIndex();
		//!Operator Overloads
		bool operator==(const Htl1DIndex& ptrRHS); 

		bool operator!=(const Htl1DIndex& ptrRHS); 

		bool operator<=(const Htl1DIndex& ptrRHS); 

		bool operator>=(const Htl1DIndex& ptrRHS); 

		bool operator<(const Htl1DIndex& ptrRHS); 

		bool operator>(const Htl1DIndex& ptrRHS); 


		//!Clear the parent pointer
		void ClearParent(void);
		//!Clear the index
		void Clear(void);
		//!Zero the index
		void Zero(void);

		//Virtual Inheritance Serialization Engines
		//SERIALIZATION FUNCTIONS///////////////////////////////////////
		//!Save member data to the current element node
		virtual int Save(HTL::HtlElement * ptrCurrNode, std::string strMemVarName, bool blnWithSubObjects);
		//!Load member data from the current element node
		virtual int Load(HTL::HtlElement * ptrCurrNode, std::string strMemVarName);

	public:
		//Index row or X value
		long m_lngX;

		//Pointer to parent index
		Htl1DIndex * m_ptrParent;

	};//end Htl1DIndex class

};//end HTL namespace
#endif