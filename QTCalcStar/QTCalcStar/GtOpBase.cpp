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

#include "GtOpBase.h"
#include "GtRpnUnit.h"
#include "GtCellData.h"
#include "QTSpreadSheet.h"

namespace GT
{
	namespace GtCalc
	{
		//!Default Constructor
		GtOpBase::GtOpBase()
		{
			m_intNumInputs = 1;
			m_ptrSheet = NULL;
		};
		//!Default Destructor
		GtOpBase::~GtOpBase()
		{
			return;
		}
		//!This function determines if the required preceeding operations are valid numbers or variables
		int GtOpBase::ValidOpInputs(std::vector<GtRpnUnit> & arrObjCalcStack, bool & blnValidInputs, int intCurrPos, int intNumInputs)
		{
			int i;
			blnValidInputs = true;
			GtRpnUnit * ptrUnit = NULL;
			try {
				//start at the current position - 1 and go back
				for (i = intCurrPos - 1; i >= intCurrPos - intNumInputs;i--)
				{
					ptrUnit = &(arrObjCalcStack.at(i));
					if ((ptrUnit->m_objTokenType == NUMBER) || 
						(ptrUnit->m_objTokenType == VAR) ||
						(ptrUnit->m_objTokenType == CELL) )
					{
						//valid input do nothing
					}
					else {
						//invalid input
						blnValidInputs = false;
					}
				}
				return 1;
			}
			catch (...) {
				//encountered an error probably
				blnValidInputs = false;
				return -1;
			}
		};

		int GtOpBase::ReplaceOp(std::vector<GtRpnUnit> & arrObjCalcStack, int intStartPos, int intEndPos, GtRpnUnit objNumberUnit)
		{
			try {
				////erase the calculation tokens
				//arrObjCalcStack.erase(arrObjCalcStack.begin() + intStartPos,arrObjCalcStack.begin() + intEndPos);
				////write the replacement number token
				//arrObjCalcStack.insert(arrObjCalcStack.begin() + intStartPos,objNumberUnit);
				////the above method should have worked but erase has lost its mind in the STL

				//CLEAN SLATE REPLACE METHOD
				std::vector<GtRpnUnit>::iterator iter;

				std::vector<GtRpnUnit> arrObjNewStack;

				//copy up to the current operation
				for (size_t i = 0; i < (intStartPos); i++)
				{
					arrObjNewStack.push_back(arrObjCalcStack.at(i));
				};
				//put in the replacement for the operation
				arrObjNewStack.push_back(objNumberUnit);
				//put in the remainder of the unyet used stack
				if ((intEndPos + 1) < arrObjCalcStack.size())
				{
					for ((iter = arrObjCalcStack.begin() + intEndPos + 1); iter != arrObjCalcStack.end(); ++iter)
					{
						arrObjNewStack.push_back((*iter));
					}
				};
				//assign new stack
				arrObjCalcStack.clear();
				arrObjCalcStack = arrObjNewStack;

				return 1;
			}
			catch (...) {
				return -1;
			}
		};
		//!This function takes in an RPN Unit and returns the numeric value for the unit if it is a NUMBER OR VAR, 
		//return's NULL if it doesn't recognize the operation type
		int GtOpBase::GetOpNumber(GtRpnUnit * ptrUnit, double & dblReturn)
		{
			if (ptrUnit->m_objTokenType == NUMBER)
			{
				//return the numeric value of the token
				dblReturn = ptrUnit->m_dblToken;
				return 1;
			}
			else if (ptrUnit->m_objTokenType == VAR) {
				//check to see if the pointer has been set
				if (ptrUnit->m_ptrDblVarData != NULL)
				{
					dblReturn = *(ptrUnit->m_ptrDblVarData);
					return 1;
				}
				else {
					dblReturn = 0;
					return -1;
				}
			}else if (ptrUnit->m_objTokenType == CELL) {
				//check to see if the pointer has been set
				if (ptrUnit->m_ptrSheet != NULL)
				{
					int iRow, jCol;
					GetRowCol(ptrUnit->m_strToken, iRow, jCol);
					GtCellData * ptrCell = ptrUnit->m_ptrSheet->GetCellPtr(iRow, jCol);
					if (ptrCell)
					{
						dblReturn = (ptrCell->m_strData.toDouble());
						return 1;
					}
					else {
						dblReturn = 0;
						return -1;
					}

				}
				else {
					dblReturn = 0;
					return -1;
				}
			}
			else {
				//unknown token type for numeric output
				dblReturn = 0;
				return -1;
			}
		};

		//!Gets the string for the current operational unit
		int GtOpBase::GetOpString(GtRpnUnit * ptrUnit, std::string & strReturn)
		{
			if (ptrUnit)
			{
				//return the numeric value of the token
				strReturn = ptrUnit->m_strToken;
				return 1;
			}
		};

		//return's NULL if it doesn't recognize the operation type
		int GtOpBase::SetOpNumber(GtRpnUnit * ptrUnit, double & dblReturn)
		{
			if (ptrUnit->m_objTokenType == NUMBER)
			{
				//return the numeric value of the token
				ptrUnit->m_dblToken = dblReturn;
				return 1;
			}
			else if (ptrUnit->m_objTokenType == VAR) {
				//check to see if the pointer has been set
				if (ptrUnit->m_ptrDblVarData != NULL)
				{
					*(ptrUnit->m_ptrDblVarData) = dblReturn;
					return 1;
				}
				else {
					return -1;
				}
			}
			else {
				//unknown token type for numeric output
				dblReturn = 0;
				return -1;
			}
		};

	}//end namespace GtCalc
}//end namespace GT