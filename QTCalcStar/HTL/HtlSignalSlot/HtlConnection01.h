	
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

#ifndef HTL_CONNECTION01_H
#define HTL_CONNECTION01_H

#include "..\modHtlLibRefs.h"
#include ".\HtlSlot.h"

#include <vector>

using namespace std;


namespace HTL
{

	template <class arg1_type>
	class HtlConnection01Base
	{
	public:
		HtlConnection01Base(){};

		virtual ~HtlConnection01Base(){};
		//emit the signal, process the slot
		virtual void Emit(arg1_type a1){return;};

		virtual HtlHasSlots* Get_ptrObj(){return NULL;};

	};

	

	//!This is the connection class template for a 0 argument connection
	/*!
		This is the connection class template for a 0 argument connection.
		It is used with a HtlSignal00.h class
	*/

	template<class dest_type, class arg1_type>
	class HtlConnection01 : public HtlConnection01Base<arg1_type>
	{
	public:
		HtlConnection01() : HtlConnection01Base()
		{
			m_ptrObj = NULL;
			m_ptrMemFunc = NULL;
		}

		HtlConnection01(dest_type* pobject, void (dest_type::*pmemfun)(arg1_type))
		{
			m_ptrObj = pobject;
			m_ptrMemFunc = pmemfun;
		}
		
		virtual~HtlConnection01()
		{
			m_ptrObj = NULL;
			m_ptrMemFunc = NULL;
		}
		//!null check for object pointer
		bool IsNull(void){return (!m_ptrObj);};
		//!Emits the signal with the correct number of arguments
		virtual void Emit(arg1_type a1)
		{
			if(m_ptrObj)
			{
				(m_ptrObj->*m_ptrMemFunc)(a1);
			};
			return;
		};
		//!get the pointer to the object sending signal to.
		virtual HtlHasSlots* Get_ptrObj()
		{
			return dynamic_cast<HtlHasSlots*>(m_ptrObj);
		}

	public:
		//!pointer to the object
		dest_type* m_ptrObj;
		//!pointer to the member function
		void (dest_type::* m_ptrMemFunc)(arg1_type);
	};

};

#endif



//ORIGINAL SIG SLOT CODE
/*template<class arg1_type, class mt_policy>
class _connection_base1
{
public:
virtual has_slots<mt_policy>* getdest() const = 0;
virtual void emit(arg1_type) = 0;
virtual _connection_base1<arg1_type, mt_policy>* clone() = 0;
virtual _connection_base1<arg1_type, mt_policy>* duplicate(has_slots<mt_policy>* pnewdest) = 0;
};


template<class dest_type, class arg1_type, class mt_policy>
class _connection1 : public _connection_base1<arg1_type, mt_policy>
{
public:
_connection1()
{
pobject = NULL;
pmemfun = NULL;
}

_connection1(dest_type* pobject, void (dest_type::*pmemfun)(arg1_type))
{
m_pobject = pobject;
m_pmemfun = pmemfun;
}

virtual _connection_base1<arg1_type, mt_policy>* clone()
{
return new _connection1<dest_type, arg1_type, mt_policy>(*this);
}

virtual _connection_base1<arg1_type, mt_policy>* duplicate(has_slots<mt_policy>* pnewdest)
{
return new _connection1<dest_type, arg1_type, mt_policy>((dest_type *)pnewdest, m_pmemfun);
}

virtual void emit(arg1_type a1)
{
(m_pobject->*m_pmemfun)(a1);
}

virtual has_slots<mt_policy>* getdest() const
{
return m_pobject;
}

private:
dest_type* m_pobject;
void (dest_type::* m_pmemfun)(arg1_type);
};*/