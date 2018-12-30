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

#ifndef GtCalc_TOKEN_H
#define GtCalc_TOKEN_H

#include "GtCalcStructs.h"

namespace GT
{
	namespace GtCalc
	{
      class QTSpreadSheet;

		struct HTL_DLLAPI GtToken
		{
		public:
			//!Default Constructor
			GtToken();
			//!Copy Constructor
			GtToken(const GtToken& rhs);
			//!Assignment Operator
			GtToken& operator= (const GtToken& rhs);
			//!Destructor
			~GtToken();
		public:
			//This is a thin class, so member variables are public like in a typical struct
			//!The token type of this RPN Unit
			GtTokenType m_objTokenType;
			//!operator presidence
			int m_intPresidence;
			//!The string representation of the token
			std::string m_strToken;
			//!token's associativity
			GtAssociativity m_objAssociativity;
			//!numeric version of token if applicable
			double m_dblToken;
			//!The row number of the cell
			long m_iRow;
			//!The column number of the cell
			long m_iCol;
         //!pointer to the sheet
         QTSpreadSheet * m_ptrSheet;
		};

	}//end namespace GtCalc
}//end namespace GT
#endif