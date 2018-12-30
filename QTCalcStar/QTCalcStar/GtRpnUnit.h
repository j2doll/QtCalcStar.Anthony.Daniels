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

#ifndef GtCalc_RPNUNIT_H
#define GtCalc_RPNUNIT_H

#include "GtToken.h"

namespace GT
{
	namespace GtCalc
	{

		class GtOpBase;
		class QTSpreadSheet;

		struct GtRpnUnit : public GtToken
		{
		public:
			//!Default Constructor
			GtRpnUnit();
			//!Copy Constructor
			GtRpnUnit(const GtRpnUnit& rhs);
			//!Assignment Operator
			GtRpnUnit& operator= (const GtRpnUnit& rhs);
			//!Destructor
			~GtRpnUnit();
			//Create the OpBase from the factory
			void CreateOpBase(void);
			//!Delete the ObBase
			void DeleteOpBase(void);

		public:
			//Inherits from structToken
			double * m_ptrDblVarData;
			//!The variable is initialized flag
			bool m_blnVarLinked;
			//!The variable is Externally Linked
			bool m_blnExternal;
			//!pointer to the operater
			GtOpBase* m_ptrOpEval;


		};


	}//end namespace GtCalc
}//end namespace GT

#endif //GtCalc_RPNUNIT_H
