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

#include ".\GtOpCount.h"
#include "..\GtCellData.h"
#include "..\QTSpreadSheet.h"
#include "..\GtSheetServer.h"

namespace GT
{
	namespace GtCalc
	{

		//!Default Constructor
		GtOpCount::GtOpCount() : GtOpBase()
		{
			m_intNumInputs = 4;
		};
		//!Default Destructor
		GtOpCount::~GtOpCount() {};

		int GtOpCount::GatherCells(std::vector<GtRpnUnit> & arrObjCalcStack, int intCurrPos)
		{
			GtSheetServer * ptrServer = NULL;
			QTSpreadSheet * ptrSheetGet = NULL;
			if (m_blnRemoteSheet)
			{
				string sheetname = arrObjCalcStack.at(intCurrPos - 3).m_strToken;

				ptrServer = GtSheetServer::GetServerPtr();
				if (ptrServer)
				{
					ptrSheetGet = ptrServer->GetSheetPtr(sheetname);
				}else {
					ptrSheetGet = dynamic_cast<QTSpreadSheet*>(m_ptrSheet);
				}
			}else {
				ptrSheetGet = dynamic_cast<QTSpreadSheet*>(m_ptrSheet);
			}

			if (!ptrSheetGet)
			{
				m_arrCells.clear();
				return 0;
			}

			int i, j;
			for (i = m_iRLow; i <= m_iRHigh; i++)
			{
				for (j = m_iCLow; j <= m_iCHigh; j++)
				{
					GtCellData * ptrCell = ptrSheetGet->GetCellPtr(i, j);
					if (ptrCell)
					{
						m_arrCells.push_back(ptrCell);
					}
				}
			}
				
			return 1;
		};
		bool GtOpCount::IsNumeric(string & strInput)
		{
			int j,intLength;
			char buf[256], output[256];
			memset(buf, '\0', sizeof(buf));
			memset(output, '\0', sizeof(output));

			int pos = 0;

			//if it's not a number, return false
			if (!isdigit(strInput.at(pos)) && strInput.at(pos) != '-' && strInput.at(pos) != '.')
				return false;

			//if the - don't follow by number, then it's not a number
			if (strInput.at(pos) == '-')
				if (!isdigit(strInput.at(pos + 1)))
					return false;
			buf[0] = strInput.at(pos);
			//if only one character long short circuit and quit out
			if (strInput.size() <= 1)
			{
				intLength = 1;
				return true;
			}
			//more than one character in the array
			for (pos = 0, j = 0; pos < (int)strInput.size(); pos++, j++)
			{

				if (isdigit(strInput.at(pos)) || strInput.at(pos) == '.')
				{
					buf[j] = strInput.at(pos);
				}
				else if( (strInput.at(pos) == '\r')||
					(strInput.at(pos) == '\t')|| (strInput.at(pos) == '\n') )
				{//ignore white space

				}else{
					return false;
				}

			}

			return true;

		};

		int GtOpCount::ValidOpInputs(std::vector<GtRpnUnit> & arrObjCalcStack, bool & blnValidInputs, int intCurrPos, int intNumInputs)
		{
			int i;
			blnValidInputs = true;
			GtRpnUnit * ptrUnit = NULL;
			try {
				//start at the current position - 1 and go back
				for (i = intCurrPos - 1; i >= intCurrPos - intNumInputs;i--)
				{
					ptrUnit = &(arrObjCalcStack.at(i));
					if ((ptrUnit->m_objTokenType == SHEET) || (ptrUnit->m_objTokenType == CELL))
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
		//!Perform the operation on the stack
		int GtOpCount::OpEval(std::vector<GtRpnUnit> & arrObjCalcStack, bool & blnCalcSuccessful, int intCurrPos)
		{
			//FUNCTION: pow(Number, numdecimal)
			//first determine if the necessary inputs are valid, if they are,
			//then get the input numbers and perform the calculation, Once the calculation is made
			//then replace the operation and input tokens with the output number token

			char chrOutput[256];
			memset(chrOutput, '\0', sizeof(chrOutput));
			blnCalcSuccessful = true;
			bool blnValid;
			double dblOutput;
			GtRpnUnit objOutput;

			try {

				if ((intCurrPos - 3) >= 0)
				{
					m_blnRemoteSheet = true;
					this->ValidOpInputs(arrObjCalcStack, blnValid, intCurrPos, 3);
				}else {
					m_blnRemoteSheet = false;
					this->ValidOpInputs(arrObjCalcStack, blnValid, intCurrPos, 2);
				}

					

				if (blnValid)
				{
					double m_dRLow, m_dCLow, m_dRHigh, m_dCHigh;
					std::string strSheet, strRCLow, strRCHigh;

					if (m_blnRemoteSheet)
					{
						this->GetOpString(&(arrObjCalcStack.at(intCurrPos - 1)), strRCHigh);
						GetRowCol(strRCHigh, m_iRHigh, m_iCHigh);
						this->GetOpString(&(arrObjCalcStack.at(intCurrPos - 2)), strRCLow);
						GetRowCol(strRCLow, m_iRLow, m_iCLow);
						this->GetOpString(&(arrObjCalcStack.at(intCurrPos - 3)), strSheet);
						QTSpreadSheet* ptrTarget = NULL;
						ptrTarget = GtSheetServer::GetServerPtr()->GetSheetPtr(strSheet);
						if (ptrTarget)
						{
							m_ptrSheet = ptrTarget;
						}
					}
					else {
						this->GetOpString(&(arrObjCalcStack.at(intCurrPos - 1)), strRCHigh);
						GetRowCol(strRCHigh, m_iRHigh, m_iCHigh);
						this->GetOpString(&(arrObjCalcStack.at(intCurrPos - 2)), strRCLow);
						GetRowCol(strRCLow, m_iRLow, m_iCLow);
					}

					//check for illegal indexes
					if (m_iRLow <= 0) { blnCalcSuccessful = false; return 0; };
					if (m_iCLow <= 0) { blnCalcSuccessful = false; return 0; };
					if (m_iRHigh <= 0) { blnCalcSuccessful = false; return 0; };
					if (m_iCHigh <= 0) { blnCalcSuccessful = false; return 0; };
					this->GatherCells(arrObjCalcStack, intCurrPos);

					int i, iNum, iResult;
					iResult = 0;
					iNum = m_arrCells.size();
					if (iNum > 0)
					{
						for (i = 0; i < iNum;i++)
						{
							GtCellData* ptrCell = m_arrCells.at(i);
							if (ptrCell)
							{
								if (IsNumeric(ptrCell->m_strData.toStdString()))
								{
									iResult++;
								}
							}
							
						}
					}else {
						blnCalcSuccessful = false;
						return 0;
					}


					objOutput.m_objTokenType = NUMBER;
					objOutput.m_dblToken = iResult;
					sprintf_s(chrOutput, "%f", iResult);
					objOutput.m_strToken = iResult;

					if (m_blnRemoteSheet)
					{
						this->ReplaceOp(arrObjCalcStack, intCurrPos - 3, intCurrPos, objOutput);
					}else {
						this->ReplaceOp(arrObjCalcStack, intCurrPos - 2, intCurrPos, objOutput);
					}
					
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