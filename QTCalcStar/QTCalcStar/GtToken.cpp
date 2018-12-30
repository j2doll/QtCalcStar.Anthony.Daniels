
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

#include "GtToken.h"
#include "GtCellData.h"
#include "QTSpreadSheet.h"

namespace GT
{
	namespace GtCalc
	{
		GtToken::GtToken()
		{
			m_objTokenType = NOOP;
			m_objAssociativity = NON_ASSOCIATIVE;
			m_strToken = "nil";
			m_dblToken = 0.0;
			m_intPresidence = 0;
         m_ptrSheet = NULL;
		};

		GtToken::GtToken(const GtToken& rhs)
			: m_objTokenType(rhs.m_objTokenType)
			, m_objAssociativity(rhs.m_objAssociativity)
			, m_strToken(rhs.m_strToken)
			, m_dblToken(rhs.m_dblToken)
			, m_intPresidence(rhs.m_intPresidence)
         , m_ptrSheet(rhs.m_ptrSheet)
		{
		};

		GtToken& GtToken::operator= (const GtToken& rhs)
		{
			if (this != &rhs)
			{
				m_objTokenType = rhs.m_objTokenType;
				m_intPresidence = rhs.m_intPresidence;
				m_objAssociativity = rhs.m_objAssociativity;
				m_strToken = rhs.m_strToken;
				m_dblToken = rhs.m_dblToken;
            m_ptrSheet = rhs.m_ptrSheet;
			}
			return *this;
		}

		GtToken::~GtToken()
		{
			m_strToken.clear();
		};


	}//end namespace GtCalc
}//end namespace GT