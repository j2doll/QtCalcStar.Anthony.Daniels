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
#define HTL_DLLEXPORT

#include ".\GtOpRange.h"
namespace GT
{
	namespace GtCalc
	{

		//!Default Constructor
		GtOpRange::GtOpRange() : GtOpBase()
		{
			m_intNumInputs = 2;
		};
		//!Default Destructor
		GtOpRange::~GtOpRange() {};

		//!Perform the operation on the stack
		int GtOpRange::OpEval(std::vector<GtRpnUnit> & arrObjCalcStack, bool & blnCalcSuccessful, int intCurrPos)
		{
			return 0;

		};

	}//end namespace
}//end namespace