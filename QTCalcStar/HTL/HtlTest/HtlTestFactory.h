/*
**	This file is part of the Hpc Template Library (Htl or HTL).
**  It is based on a merger of QT, STL, and SigSlots along with development of new classes.
**  License information is in the HtlLicense.h file
**	This software was merged and developed by:
**	
**  Anthony Daniels
**	QT, STL, SigSlots
**
**  HTL is free software: you can redistribute it and/or modify
**  it under the terms of the GNU Lesser General Public License as published by
**  the Free Software Foundation, either version 3 of the License, or
**  (at your option) any later version.
**
**  The United States of America Department of Defense has unlimited 
**	usage, redistribution, and modification rights to HtlStar.
**
**  HTL is distributed in the hope that it will be useful,
**  but WITHOUT ANY WARRANTY; without even the implied warranty of
**  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
**  GNU Lesser General Public License for more details.
**
**  You should have received a copy of the GNU Lesser General Public License
**  along with HTL.  If not, see <http://www.gnu.org/licenses/>.
*/
#pragma once
#ifndef HTL_TESTFACTORY_H
#define HTL_TESTFACTORY_H

#include "..\modHtlBase.h"
#include ".\HtlTestNode.h"

using namespace std;

namespace HTL {

	class HTL_DLLAPI HtlTestFactory : 
		public HtlFactory<HtlTestNode> 
		{
		public:

			//retrieves a string vector of all of the classes in the factory
			std::vector<std::string> GetAllTestNames(void);
			//retrieves a subset of the classes in factory that contain strName in the class name
			std::vector<std::string> SearchTestNames(std::string strName);

		};//end ORSDBObjectFactory class definition

	//extern ORS_DLLAPI m_objHtlTestFactory m_objHtlTestFactory;


	HTL_DLLAPI HtlTestFactory * GetTestFactoryPtr(void);

	HTL_DLLAPI HtlTestNode * CreateTestNode(std::string strTestName);

	HTL_DLLAPI HtlTestNode * CreateTestNode(const char * ptrName);

};//end namespace HTL

#endif//HTL_TESTFACTORY_H
