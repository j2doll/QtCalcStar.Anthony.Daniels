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

#ifndef GtCalc_ENUMS_H
#define GtCalc_ENUMS_H

#include "GtCalcLibRefs.h"
#include <modHtlLibRefs.h>
namespace GT
{
	namespace GtCalc
	{

		enum HTL_DLLAPI GtAssociativity
		{
			NON_ASSOCIATIVE = 0,
			LEFT_ASSOCIATIVE = 1,
			RIGHT_ASSOCIATIVE = 2
		};

		enum HTL_DLLAPI GtTrigType
		{
			REG,
			ARC,
			HYP,
			AHYP
		};

		enum HTL_DLLAPI GtTokenType
		{	//IMPORTANT NOTE!!! these operators are in order of operation prescedence
			//THE HIGHER THE NUMBER THE HIGHER THE PRESCEDENCE
			//DO NOT CHANGE THIS ORDERING, HARDCODING IS USED BASED ON ENUMERATED TYPES
			//
			NOOP = -1,
			OPENPAREN = 0,
			OPENBRACKET,
			OPENBLOCK,
			CLOSEPAREN,
			CLOSEBRACKET,
			CLOSEBLOCK,
			COMMA,
			RANGE,
			LT,
			GT,
			LTE,
			GTE,
			NEQ,
			EQ,
			AND,
			OR,
			NOT,
			SUB,
			ADD,
			DIV,
			MULT,
			POW,
			NEG,
			ASSIGN,
			CELL,
			SHEET,
			NUMBER,
			VAR,
			FUNC
		};

#define PRES_NOOP  -1,
#define PRES_OPENPAREN  1 
#define PRES_OPENBRACKET 1
#define PRES_OPENBLOCK 1
#define PRES_CLOSEPAREN 1
#define PRES_CLOSEBRACKET 1
#define PRES_CLOSEBLOCK 1
#define PRES_COMMA 1
#define PRES_RANGE 1
#define PRES_LT 4
#define PRES_GT 4
#define PRES_LTE 4
#define PRES_GTE 4
#define PRES_NEQ 4
#define PRES_EQ 4
#define PRES_AND 4
#define PRES_OR 4
#define PRES_NOT 4
#define PRES_SUB 6
#define PRES_ADD 6
#define PRES_DIV 8
#define PRES_MULT 8
#define PRES_POW 9
#define PRES_NEG 10
#define PRES_ASSIGN 2
#define PRES_NUMBER 14
#define PRES_VAR 14
#define PRES_SHEET 14
#define PRES_CELL 14
#define PRES_FUNC 16

		//MISCELLANEOUS PUBLIC DATA FUNCTIONS
		//Converts the token type to a string for output
		HTL_DLLAPI std::string TokenTypeToString(GtTokenType objInput);

		//!Utility function that takes a string rowcol and gets the row and column indexes
		bool GetRowCol(std::string & strCell, int & iRow, int & iCol);

	}//end namespace GtCalc
}//end namespace GT
#endif // GtCalc_ENUMS_H


