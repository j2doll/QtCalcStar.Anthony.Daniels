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

#include ".\GtOpBoolAnd.h"

namespace GT
{
	namespace GtCalc
	{

		//!Default Constructor
		GtOpBoolAnd::GtOpBoolAnd() : GtOpBase()
		{
			m_intNumInputs = 2;
		};
		//!Default Destructor
		GtOpBoolAnd::~GtOpBoolAnd() {};

		//!Perform the operation on the stack
		int GtOpBoolAnd::OpEval(std::vector<GtRpnUnit> & arrObjCalcStack, bool & blnCalcSuccessful, int intCurrPos)
		{
			//FUNCTION: logical and (A AND B)
			//first determine if the necessary inputs are valid, if they are,
			//then get the input numbers and perform the calculation, Once the calculation is made
			//then replace the operation and input tokens with the output number token

			char chrOutput[256];
			for (int i = 0; i < 256; chrOutput[i++] = '\0');
			blnCalcSuccessful = true;
			bool blnValid;
			double dblOutput;
			GtRpnUnit objOutput;

			try {
				this->ValidOpInputs(arrObjCalcStack, blnValid, intCurrPos, 2);

				if (blnValid)
				{
					//then valid inputs, perform the sin calculation
					//then replace the sin calculation results with the single number
					double dblNum1, dblNum2;
					this->GetOpNumber(&(arrObjCalcStack.at(intCurrPos - 1)), dblNum2);
					this->GetOpNumber(&(arrObjCalcStack.at(intCurrPos - 2)), dblNum1);

					if ((dblNum1 == 1) && (dblNum2 == 1))
					{
						dblOutput = 1;
					}
					else {
						dblOutput = 0;
					}

					objOutput.m_objTokenType = NUMBER;
					objOutput.m_dblToken = dblOutput;
					sprintf_s(chrOutput, "%f", dblOutput);
					objOutput.m_strToken = chrOutput;

					this->ReplaceOp(arrObjCalcStack, intCurrPos - 2, intCurrPos, objOutput);
					blnCalcSuccessful = true;
					return 1;

				}
				else {
					blnCalcSuccessful = false;
					return 0;
				}
			}
			catch (...) {
				blnCalcSuccessful = false;
				return -1;
			}//end try catch

		};

	}//end namespace
}//end namespace