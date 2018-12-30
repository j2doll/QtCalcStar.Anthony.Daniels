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

#ifndef GtCalc_OPBASE_H
#define GtCalc_OPBASE_H

#include "GtRpnUnit.h"


namespace GT
{
	namespace GtCalc
	{
      class QTSpreadSheet;

		class GtOpBase
		{
		public:
			//!Default Constructor
			GtOpBase();
			//!Default Destructor
			~GtOpBase();
		public:
			//!Perform the operation on the stack
			virtual int OpEval(std::vector<GtRpnUnit> & arrObjCalcStack, bool & blnCalcSuccessful, int intCurrPos) = 0;
			//!Makes sure the inputs to the Calculation Operation are Valid
			virtual int ValidOpInputs(std::vector<GtRpnUnit> & arrObjCalcStack, bool & blnValidInputs, int intCurrPos, int intNumInputs);
			//!Replace the operation and input tokens with the output NUMBER token
			int ReplaceOp(std::vector<GtRpnUnit> & arrObjCalcStack, int intStartPos, int intEndPos, GtRpnUnit objNumberUnit);
			//!Gets the number for the current operational unit
			int GetOpNumber(GtRpnUnit * ptrUnit, double & dblReturn);
			//!Gets the string for the current operational unit
			int GetOpString(GtRpnUnit * ptrUnit, std::string & strReturn);
			//!Sets the number for the current operational unit
			int SetOpNumber(GtRpnUnit * ptrUnit, double & dblReturn);
		public:
			int m_intNumInputs;

			QTSpreadSheet* m_ptrSheet;
		};

	}//end namespace GtCalc
}//end namespace GT
#endif