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

#include "GtCalcEnums.h"
namespace GT
{
	namespace GtCalc
	{

		std::string TokenTypeToString(GtTokenType objInput)
		{
			std::string strRet;

			if (objInput == NOOP) { return "NOOP"; };
			if (objInput == OPENPAREN) { return "OPENPAREN"; };
			if (objInput == OPENBRACKET) { return "OPENBRACKET"; };
			if (objInput == OPENBLOCK) { return "OPENBLOCK"; };
			if (objInput == CLOSEPAREN) { return "CLOSEPAREN"; };
			if (objInput == CLOSEBRACKET) { return "CLOSEBRACKET"; };
			if (objInput == CLOSEBLOCK) { return "CLOSEBLOCK"; };
			if (objInput == COMMA) { return "COMMA"; };
			if (objInput == NUMBER) { return "NUMBER"; };
			if (objInput == VAR) { return "VAR"; };
			if (objInput == ASSIGN) { return "ASSIGN"; };
			if (objInput == NEG) { return "NEG"; };
			if (objInput == ADD) { return "ADD"; };
			if (objInput == SUB) { return "SUB"; };
			if (objInput == MULT) { return "MULT"; };
			if (objInput == DIV) { return "DIV"; };
			if (objInput == POW) { return "POW"; };
			if (objInput == LT) { return "LT"; };
			if (objInput == GT) { return "GT"; };
			if (objInput == LTE) { return "LTE"; };
			if (objInput == GTE) { return "GTE"; };
			if (objInput == NEQ) { return "NEQ"; };
			if (objInput == EQ) { return "EQ"; };
			if (objInput == AND) { return "AND"; };
			if (objInput == OR) { return "OR"; };
			if (objInput == NOT) { return "NOT"; };
			if (objInput == FUNC) { return "FUNC"; };
			if (objInput == RANGE) { return "RANGE"; };
			if (objInput == SHEET) { return "SHEET"; };
			if (objInput == CELL) { return "CELL"; };
			return("nil");

		};






		bool GetNextNumberInt(std::string & strInput, int posStart, int & intLength, int & intReturn)
		{
			int j;
			char buf[256], output[256];
			memset(buf, '\0', sizeof(buf));
			memset(output, '\0', sizeof(output));

			int pos = posStart;

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
				intReturn = atoi(buf);
				intLength = 1;
				return true;
			}
			//more than one character in the array
			for (pos = posStart, j = 0; pos < (int)strInput.size(); pos++, j++)
			{

				if (isdigit(strInput.at(pos)) || strInput.at(pos) == '.')
				{
					buf[j] = strInput.at(pos);
				}
				else {
					break;
				}

			}
			intLength = j;
			intReturn = atoi(buf);
			return true;
		};

		//!Utility function that takes a string rowcol and gets the row and column indexes
		bool GetRowCol(std::string & strCell, int & iRow, int & iCol)
		{
			bool blnIsRowCol = false;
			int iposR, iposC, iLength;
			iposR = 0;
			if (strCell.size() <= 0) { iRow = -1; iCol = -1; return false; };//no string
			if ((strCell.at(iposR) == 'r') || (strCell.at(iposR) == 'R'))
			{
				//then good opener
			}else {
				iRow = -1; iCol = -1; return false;
			};//not a rowcol
			if (!(GetNextNumberInt(strCell, iposR + 1, iLength, iRow)))
			{
				iRow = -1; iCol = -1; return false;
			};//not a rowcol
			//then valid row;
			iposC = iposR + iLength + 1;
			if (strCell.size() > iposC + 1)
			{
				if ((strCell.at(iposC) == 'c') || (strCell.at(iposC) == 'C'))
				{
					//then good col header
				}
				else {
					iRow = -1; iCol = -1; return false;
				};//not a rowcol
				if (!(GetNextNumberInt(strCell, iposC + 1, iLength, iCol)))
				{
					iRow = -1; iCol = -1; return false;
				};//not a rowcol
			}
			else {
				iRow = -1; iCol = -1; return false;
			}

			//then valid row col
			return true;		
		};

	}//end namespace GtCalc
}//end namespace GT