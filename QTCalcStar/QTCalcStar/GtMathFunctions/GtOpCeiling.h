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

#ifndef GtCalc_OP_Ceiling_H
#define GtCalc_OP_Ceiling_H

#include "..\GtOpBase.h"
#include "..\GtOpBaseFactory.h"
namespace GT
{
	namespace GtCalc
	{

		class GtOpCeiling : public GtOpBase
		{
		public:
			//!Default Constructor
			GtOpCeiling();
			//!Default Destructor
			~GtOpCeiling();

			//!Perform the operation on the stack
			virtual int OpEval(std::vector<GtRpnUnit> & arrObjCalcStack, bool & blnCalcSuccessful, int intCurrPos);

		};

		//OBJECT FACTORY REGISTRATION CODE
		static bool blnGtOpCeiling_Registered = GtCalc::GetOpBaseFactoryPtr()->Register<GtOpCeiling>("ceil");
		static bool blnGtOpCeiling3_Registered = GtCalc::GetOpBaseFactoryPtr()->Register<GtOpCeiling>("GtOpCeiling");
	}//end namespace
}//end namespace
#endif //GtCalc_OP_Ceiling_H
