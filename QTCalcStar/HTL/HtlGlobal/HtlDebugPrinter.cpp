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

#include ".\HtlDebugPrinter.h"


using namespace std;
namespace HTL
{

	bool fexists(const char *filename)
	{
		ifstream ifile(filename);
		return bool(ifile);
	}

	HtlDebugPrinter::HtlDebugPrinter(void)
	{
		//debug printer file name
		m_strFileName = "DEBUGPRINTER.txt";
		//boolean flag for printing to file
		m_blnPrintToFile = false;
		//boolean flag to the STD LIB COut Stream;
		m_blnPrintToStream = true;

		m_blnPrintToTextEdit = false;
		m_intPrintLevel = 3;
	};

	HtlDebugPrinter::~HtlDebugPrinter(void)
	{
		m_strFileName.clear();
	};

	int HtlDebugPrinter::DebugPrint(int intLevel, const char *format, ...)
	{
		//set up to read the extra arguments
		int intReturn;
		try{
			if(intLevel > m_intPrintLevel)
			{
				//don't print, level of detail to high for current setting
				return 0;
			};

			va_list args;
			va_start( args, format );
			intReturn &= DebugPrintToStream(format,args);
			intReturn &= DebugPrintToFile(format,args);
			va_end(args);
			return intReturn;
		}catch(...){
			return -1;
		}
		return 0;
	};

	int HtlDebugPrinter::DebugPrintToStream(const char *format, va_list args)
	{
		int intReturn = 0;
		try{
			//va_start( args, format );
			//OUTPUT STREAM SECTION
			if(m_blnPrintToStream)
			{//print to the std output stream
				intReturn = vprintf(format, args);
			}
			//va_end(args);
			return intReturn;
		}catch(...){
			return -1;
		};
		return 0;
	};

	int HtlDebugPrinter::DebugPrintToFile(const char *format, va_list args)
	{
		int intReturn = 0;
		try{
			//va_start( args, format );

			if(m_blnPrintToFile)
				//FILE OUTPUT SECTION
			{//print to the file...
				//Open the output file to append to it
				FILE *stream;
				std::string strFile = m_strFileName.c_str();
				if(fexists(strFile.c_str()))
				{
					//stream = fopen( m_strPrintFileName.c_str(),"w"); //We want this one to overwrite
					stream = fopen(  strFile.c_str() ,"a");//a for appending to existing file
				}else{
					stream = fopen(  strFile.c_str() ,"w");//We want this one to overwrite
				}
				intReturn = vfprintf( stream, format, args );
				fclose(stream);
			};
			//va_end(args);
			return intReturn;
		}catch(...){
			return -1;
		};
		return 0;
	};
		
	
	void HtlDebugPrinter::Disable(void)
	{
		m_blnPrintToFile = false;
		m_blnPrintToStream = false;
		m_blnPrintToTextEdit = false;		
	};

	int HtlDebugPrinter::DeleteDebugFile()
	{
		try
		{
			const char * filename = m_strFileName.c_str();
			if(fexists(filename))
			{
				std::remove(filename);
			}
		}catch(...){
			return -1;
		};
		return 1;
	};

	void LocalDebugPrint(char * ptrFile, char * ptrMethod, const char * format, ...)
	{

		HtlDebugPrinter objLocal;
		objLocal.Set_strFileName(ptrFile);
		objLocal.Set_blnPrintToFile(true);

		va_list args;
		va_start(args, format);
		objLocal.DebugPrintToFile(format, args);
		va_end(args);

	};


};//end namespace HTL