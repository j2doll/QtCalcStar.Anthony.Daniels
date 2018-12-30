/*
**	This file is part of the GtCalc Function Evaluator library.
**  License information is in the GtLicense.h file.
**	This software was developed by:
**	
**  Anthony Daniels (copyright 2014)
** AnthonyDaniels99@gmail.com
**
**  GtCalc is free software: you can redistribute it and/or modify
**  it under the terms of the GNU Lesser General Public License as published by
**  the Free Software Foundation, either version 3 of the License, or
**  (at your option) any later version.
**
**
**  GtCalc is distributed in the hope that it will be useful,
**  but WITHOUT ANY WARRANTY; without even the implied warranty of
**  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
**  GNU Lesser General Public License for more details.
**
**  You should have received a copy of the GNU Lesser General Public License
**  along with GtCalc.  If not, see <http://www.gnu.org/licenses/>.
*/
#pragma once

#ifndef GtCalc_OP_ADD_H
#define GtCalc_OP_ADD_H

#include "..\GtOpBase.h"
#include "..\GtOpBaseFactory.h"
namespace GT
{
	namespace GtCalc
	{

		class GtOpAdd : public GtOpBase
		{
		public:
			//!Default Constructor
			GtOpAdd();
			//!Default Destructor
			~GtOpAdd();

			//!Perform the operation on the stack
			virtual int OpEval(std::vector<GtRpnUnit> & arrObjCalcStack, bool & blnCalcSuccessful, int intCurrPos);

		};

		//OBJECT FACTORY REGISTRATION CODE
		static bool blnGtOpAdd_Registered = GtCalc::GetOpBaseFactoryPtr()->Register<GtOpAdd>("+");
		static bool blnGtOpAdd2_Registered = GtCalc::GetOpBaseFactoryPtr()->Register<GtOpAdd>("ADD");
		static bool blnGtOpAdd3_Registered = GtCalc::GetOpBaseFactoryPtr()->Register<GtOpAdd>("GtOpAdd");
	}//end namespace
}//end namespace
#endif //GtCalc_OP_ADD_H
