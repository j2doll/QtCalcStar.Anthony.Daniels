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
#define HTL_DLLEXPORT

#include ".\GtOpAssign.h"

namespace GT
{
	namespace GtCalc
	{
		//Default Constructor
		GtOpAssign::GtOpAssign() : GtOpBase()
		{
			m_intNumInputs = 2;
		};
		//!Default Destructor
		GtOpAssign::~GtOpAssign() {};

		//!Perform the operation on the stack
		int GtOpAssign::OpEval(std::vector<GtRpnUnit> & arrObjCalcStack, bool & blnCalcSuccessful, int intCurrPos)
		{
			//FUNCTION: Assignes B to A (A = B)
			//first determine if the necessary inputs are valid, if they are,
			//then get the input numbers and perform the calculation, Once the calculation is made
			//then replace the operation and input tokens with the output number token

			char chrOutput[256];
			memset(chrOutput, '\0', 256);

			blnCalcSuccessful = true;
			bool blnValid;
			double dblOutput;
			GtRpnUnit objOutput;

			try {
				this->ValidOpInputs(arrObjCalcStack, blnValid, intCurrPos, m_intNumInputs);

				if (blnValid)
				{
					//then valid inputs, perform the sin calculation
					//then replace the sin calculation results with the single number
					double dblNum1, dblNum2;
					this->GetOpNumber(&(arrObjCalcStack.at(intCurrPos - 1)), dblNum2);
					this->GetOpNumber(&(arrObjCalcStack.at(intCurrPos - 2)), dblNum1);

					dblOutput = dblNum2;
					this->SetOpNumber(&(arrObjCalcStack.at(intCurrPos - 2)), dblOutput);
					objOutput.m_objTokenType = NUMBER;
					objOutput.m_dblToken = dblOutput;
					sprintf_s(chrOutput, "%f", dblOutput);
					objOutput.m_strToken = chrOutput;

					this->ReplaceOp(arrObjCalcStack, intCurrPos - 2, intCurrPos, objOutput);
					blnCalcSuccessful = true;
					return 1;

				}
				else {
					//check for single number assign
					this->ValidOpInputs(arrObjCalcStack, blnValid, intCurrPos, 1);

					if (blnValid)
					{

						//then valid inputs, perform the sin calculation
						//then replace the sin calculation results with the single number
						double dblNum1, dblNum2;
						this->GetOpNumber(&(arrObjCalcStack.at(intCurrPos - 1)), dblNum2);
						dblOutput = dblNum2;

						objOutput.m_objTokenType = NUMBER;
						objOutput.m_dblToken = dblOutput;
						sprintf_s(chrOutput, "%f", dblOutput);
						objOutput.m_strToken = chrOutput;

						this->ReplaceOp(arrObjCalcStack, intCurrPos - 1, intCurrPos, objOutput);
						blnCalcSuccessful = true;
						return 1;

					}
					//otherwise fail
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
}//end namespace GT