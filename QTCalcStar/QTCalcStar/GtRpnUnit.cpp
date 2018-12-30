
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

#include "GtRpnUnit.h"
#include "GtOpBase.h"
#include "GtOpBaseFactory.h"
#include "GtCellData.h"
#include "QTSpreadSheet.h"

namespace GT
{
	namespace GtCalc
	{
		GtRpnUnit::GtRpnUnit() : GtToken()
		{
			//Inherits from structToken
			m_ptrDblVarData = NULL;
			//!The variable is initialized flag
			m_blnVarLinked = false;
			//!The variable is Externally Linked
			m_blnExternal = false;
			//!Pointer to the opbase
			m_ptrOpEval = NULL;


		};

		GtRpnUnit::GtRpnUnit(const GtRpnUnit& rhs)
			: GtToken(rhs)
		{
			m_ptrDblVarData = rhs.m_ptrDblVarData;
			m_blnVarLinked = rhs.m_blnVarLinked;
			m_blnExternal = rhs.m_blnExternal;

			//DO NOT COPY THE m_ptrOpEval
			//!Pointer to the opbase
			m_ptrOpEval = NULL;

		};

		GtRpnUnit& GtRpnUnit::operator= (const GtRpnUnit& rhs)
		{
			if (this != &rhs)
			{
            GtToken::operator=(rhs);
				m_ptrDblVarData = rhs.m_ptrDblVarData;
				m_blnVarLinked = rhs.m_blnVarLinked;
				m_blnExternal = rhs.m_blnExternal;
				m_ptrSheet = rhs.m_ptrSheet;


				//DO NOT COPY THE m_ptrOpEval
				//!Pointer to the opbase
				m_ptrOpEval = NULL;
			}
			return *this;
		}

		GtRpnUnit::~GtRpnUnit()
		{
			this->DeleteOpBase();
		};

		//Create the OpBase from the factory
		void GtRpnUnit::CreateOpBase(void)
		{
			if (m_ptrOpEval)
			{
				delete m_ptrOpEval;
				m_ptrOpEval = NULL;
			};
			m_ptrOpEval = GetOpBaseFactoryPtr()->Create(m_strToken);
			if (m_ptrOpEval)
			{
				m_ptrOpEval->m_ptrSheet = dynamic_cast<QTSpreadSheet*>(m_ptrSheet);
			}
			
		};
		//!Delete the ObBase
		void GtRpnUnit::DeleteOpBase(void)
		{
			if (m_ptrOpEval)
			{
				delete m_ptrOpEval;
				m_ptrOpEval = NULL;
			};
		};

	}//end namespace GtCalc
}//end namespace GT