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

#ifndef HTL_BASE_H
#define HTL_BASE_H

#include "..\modHtlGlobal.h"

//#include ".\HtlNameValuePair.h"

namespace HTL
{
	class HtlElement;
	//Htl BASE TYPE DEFINITION
	//!Htl Base is a minimalistic base object that allows for serialization using the HTL system.
	
	/*! That allows for strong typing of base types with an enumerated type flag.*/
	class HTL_DLLAPI HtlBase
	{
	public:
		//!Default Constructor
		HtlBase();
		//!Default Constructor
		HtlBase(const HtlBase& rhs);
		//!Virtual Destructor
		virtual ~HtlBase(void);

		//PUBLIC OPERATOR OVERLOADS
		HtlBase & operator = (const HtlBase & rhs);
		//collection of fields

		//!Get the ENUMERATED Object Type
		HtlObjectType Get_objType(void)
		{
			if(!this){return HtlUnknownType;};
			return m_objType;
		};

		//!Get the ENUMERATED Object Type as a string
		std::string Get_strType(void)
		{
			return m_strType;
		};

		void Set_strType(std::string & strType)
		{
			m_strType = strType;
		}
		//!Enable SafeCall System
		inline void EnableSafeCall(void)
		{
			m_blnSafeCallEnabled = true;
		};
		//!Disable SafeCall System
		inline void DisableSafeCall(void)
		{
			m_blnSafeCallEnabled = false;
		};		
		//Virtual Inheritance Serialization Engines
		//SERIALIZATION FUNCTIONS///////////////////////////////////////
		//!Save member data to the current element node
		virtual int Save(HTL::HtlElement * ptrCurrNode, std::string strMemVarName, bool blnWithSubObjects);
		//!Load member data from the current element node
		virtual int Load(HTL::HtlElement * ptrCurrNode, std::string strMemVarName);


	protected:
		//!String type class name
		std::string m_strType;
		//!enumerated base type
		HtlObjectType m_objType;
		//!static boolean flag for enabling SafeCall Methods 
		bool m_blnSafeCallEnabled;

	};//end HtlBase class definition


};//end namspace Htl

#endif//HtlBASE_H


