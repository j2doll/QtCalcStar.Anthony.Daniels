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
#pragma warning(push)
#pragma warning (disable : 4005 ) /* macro redefinition */
#define HTL_DLLEXPORT
#pragma warning(pop)

#include ".\HtlTestFactory.h"


namespace HTL
{
	//HTL_DLLAPI ORSObjectFactory ORSDB::m_objORSFactory;

	//retrieves a string vector of all of the classes in the factory
	std::vector<std::string> HtlTestFactory::GetAllTestNames(void)
	{
		std::vector<std::string> arrStrNames;
		HtlFactory<HtlTestNode>::FactoryIter iter;
		for(iter = m_ptrObjectConstructorMap.begin();
			iter != m_ptrObjectConstructorMap.end(); ++iter)
		{
			
			arrStrNames.push_back(iter->first);
		};
		return arrStrNames;
	};
	//retrieves a subset of the classes in factory that contain strName in the class name
	std::vector<std::string> HtlTestFactory::SearchTestNames(std::string strName)
	{
		std::vector<std::string> arrStrNames;
		std::string strTemp;

		HtlFactory<HtlTestNode>::FactoryIter iter;
		for(iter = m_ptrObjectConstructorMap.begin();
			iter != m_ptrObjectConstructorMap.end(); ++iter)
		{
			if(iter->first.find(strName) != string::npos)
			{
				arrStrNames.push_back(iter->first);
			};
		};
		strTemp.clear();
		return arrStrNames;
	};

	HtlTestFactory * GetTestFactoryPtr(void)
	{
		static HtlTestFactory m_objHtlTestFactory;
		return &(m_objHtlTestFactory);
	};

	HtlTestNode * CreateTestNode(std::string strTestName)
	{
		return GetTestFactoryPtr()->Create(strTestName);
	};

	HtlTestNode * CreateTestNode(const char * ptrName)
	{
		std::string strName = ptrName;
		return GetTestFactoryPtr()->Create(strName);
	};




};