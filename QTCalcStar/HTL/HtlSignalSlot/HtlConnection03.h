	
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

#ifndef HTL_CONNECTION03_H
#define HTL_CONNECTION03_H

#include "..\modHtlLibRefs.h"
#include ".\HtlSlot.h"

#include <vector>

using namespace std;


namespace HTL
{

	template <class arg1_type, class arg2_type, class arg3_type>
	class HtlConnection03Base
	{
	public:
		HtlConnection03Base(){};

		virtual ~HtlConnection03Base(){};
		//emit the signal, process the slot
		virtual void Emit(arg1_type a1, arg2_type a2, arg3_type a3){return;};

		virtual HtlHasSlots* Get_ptrObj(){return NULL;};

	};

	

	//!This is the connection class template for a 0 argument connection
	/*!
		This is the connection class template for a 0 argument connection.
		It is used with a HtlSignal00.h class
	*/

	template<class dest_type, class arg1_type, class arg2_type, class arg3_type>
	class HtlConnection03 : public HtlConnection03Base<arg1_type, arg2_type, arg3_type>
	{
	public:
		HtlConnection03() : HtlConnection03Base()
		{
			m_ptrObj = NULL;
			m_ptrMemFunc = NULL;
		}

		HtlConnection03(dest_type* pobject, void (dest_type::*pmemfun)(arg1_type, arg2_type, arg3_type))
		{
			m_ptrObj = pobject;
			m_ptrMemFunc = pmemfun;
		}

		virtual~HtlConnection03()
		{
			m_ptrObj = NULL;
			m_ptrMemFunc = NULL;
		}
		//null check for object pointer
		bool IsNull(void){return (!m_ptrObj);};
		//!Emits the signal with the correct number of arguments
		virtual void Emit(arg1_type a1, arg2_type a2, arg3_type a3)
		{
			if(m_ptrObj)
			{
				(m_ptrObj->*m_ptrMemFunc)(a1, a2, a3);
			};
			return;
		};
		//!Get the object that the signal is sending to.
		virtual HtlHasSlots* Get_ptrObj()
		{
			return dynamic_cast<HtlHasSlots*>(m_ptrObj);
		}

	public:
		//!pointer to the object
		dest_type* m_ptrObj;
		//!pointer to the member function
		void (dest_type::* m_ptrMemFunc)(arg1_type, arg2_type, arg3_type);
	};

};

#endif