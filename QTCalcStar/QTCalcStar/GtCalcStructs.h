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

#ifndef GtCalc_STRUCTS_H
#define GtCalc_STRUCTS_H

#include <modHtlLibRefs.h>
#include "GtCalcEnums.h"
namespace GT
{
	namespace GtCalc
	{

		struct HTL_DLLAPI GtVariable
		{
			//!the variable prose name
			std::string m_strVarName;
			//!the variable current Value
			double m_dblCurrVal;
		};


	}//end namespace GtCalc
}//end namespace GT
#endif // GtCalc_STRUCTS_H
