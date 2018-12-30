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
#ifndef GtCalc_OPBASEFACTORY_H
#define GtCalc_OPBASEFACTORY_H

#include <modHtlBase.h>
#include ".\GtOpBase.h"
using namespace HTL;
using namespace std;

namespace GT
{
	namespace GtCalc {

		class HTL_DLLAPI GtOpBaseFactory :
			public HtlFactory<GtOpBase>
		{
		public:

			//retrieves a string vector of all of the classes in the factory
			std::vector<std::string> GetAllOperNames(void);
			//retrieves a subset of the classes in factory that contain strName in the class name
			std::vector<std::string> SearchOperNames(std::string strName);

		};//end ORSDBObjectFactory class definition


		HTL_DLLAPI GtOpBaseFactory * GetOpBaseFactoryPtr(void);

		HTL_DLLAPI GtOpBase * CreateOpBase(std::string strName);

		HTL_DLLAPI GtOpBase * CreateOpBase(const char * ptrName);

	}//end namespace GtCalc
}//end namespace GT
#endif//GtCalc_OPBASEFACTORY_H
