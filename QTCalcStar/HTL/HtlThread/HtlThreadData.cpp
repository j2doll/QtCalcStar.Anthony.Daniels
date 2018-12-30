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

#include ".\HtlThreadData.h"


namespace HTL
{

	//compiler test
	template <>
	void enumToString<HtlPriority>(HtlPriority enumVal, std::string  & strReturn)
	{
		try{
			switch(enumVal)
			{
				//HTL CPLUSPLUS NATIVE TYPES
			case IdlePriority: {strReturn = "IdlePriority";  return; break;};
			case LowestPriority: {strReturn = "LowestPriority";  return; break;};
			case LowPriority: {strReturn = "LowPriority";  return; break;};
			case NormalPriority: {strReturn = "NormalPriority";  return; break;};
			case HighPriority: {strReturn = "HighPriority";  return; break;};
			case HighestPriority: {strReturn = "HighestPriority";  return; break;};
			case TimeCriticalPriority: {strReturn = "TimeCriticalPriority";  return; break;};
			case InheritPriority: {strReturn = "InheritPriority";  return; break;};
				//DEFUALT UNKNOWN
			default: {strReturn = "NormalPriority";  return; break;};

			};
		}catch(...){
			strReturn = "";
		};
		return;	

	};

	template <>
	void stringToEnum<HtlPriority>(std::string  & strVal, HtlPriority & enumValReturn)
	{
		try{
			if(strVal.empty()){enumValReturn = NormalPriority; return;};
			//check by comparison
			//HTL CPLUSPLUS NATIVE TYPES
			if(strVal == "IdlePriority"){enumValReturn = IdlePriority; return;};
			if(strVal == "LowestPriority"){enumValReturn = LowestPriority; return;};
			if(strVal == "LowPriority"){enumValReturn = LowPriority; return;};
			if(strVal == "NormalPriority"){enumValReturn = NormalPriority; return;};
			if(strVal == "HighPriority"){enumValReturn = HighPriority; return;};
			if(strVal == "HighestPriority"){enumValReturn = HighestPriority; return;};
			if(strVal == "TimeCriticalPriority"){enumValReturn = TimeCriticalPriority; return;};
			if(strVal == "InheritPriority"){enumValReturn = InheritPriority; return;};

			//DEFUALT UNKNOWN
			enumValReturn = NormalPriority;
			return;
		}catch(...){
			enumValReturn = NormalPriority;
			return;
		};

	};


	template <>
	void enumToString<HtlThreadState>(HtlThreadState enumVal, std::string  & strReturn)
	{
		try{
			switch(enumVal)
			{
				//HTL CPLUSPLUS NATIVE TYPES
			case ThreadCrash: {strReturn = "ThreadCrash";  return; break;};
			case ThreadTerminated: {strReturn = "ThreadTerminated";  return; break;};
			case ThreadStopped: {strReturn = "ThreadStopped";  return; break;};
			case ThreadPaused: {strReturn = "ThreadPaused";  return; break;};
			case ThreadWaiting: {strReturn = "ThreadWaiting";  return; break;};
			case ThreadRunning: {strReturn = "ThreadRunning";  return; break;};
			case ThreadFinished: {strReturn = "ThreadFinished";  return; break;};
			case ThreadExitedNormal: {strReturn = "ThreadExitedNormal";  return; break;};
				//DEFUALT UNKNOWN
			default: {strReturn = "ThreadStopped";  return; break;};

			};
		}catch(...){
			strReturn = "";
		};
		return;	

	};

	template <>
	void stringToEnum<HtlThreadState>(std::string  & strVal, HtlThreadState & enumValReturn)
	{
		try{
			if(strVal.empty()){enumValReturn = ThreadStopped; return;};
			//check by comparison
			//HTL CPLUSPLUS NATIVE TYPES
			if(strVal == "ThreadCrash"){enumValReturn = ThreadCrash; return;};
			if(strVal == "ThreadTerminated"){enumValReturn = ThreadTerminated; return;};
			if(strVal == "ThreadStopped"){enumValReturn = ThreadStopped; return;};
			if(strVal == "ThreadPaused"){enumValReturn = ThreadPaused; return;};
			if(strVal == "ThreadWaiting"){enumValReturn = ThreadWaiting; return;};
			if(strVal == "ThreadRunning"){enumValReturn = ThreadRunning; return;};
			if(strVal == "ThreadFinished"){enumValReturn = ThreadFinished; return;};
			if(strVal == "ThreadExitedNormal"){enumValReturn = ThreadExitedNormal; return;};

			//DEFUALT UNKNOWN
			enumValReturn = ThreadStopped;
			return;
		}catch(...){
			enumValReturn = ThreadStopped;
			return;
		};

	};




};//end HTL namespace