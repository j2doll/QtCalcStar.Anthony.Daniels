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

#ifndef HTL_DEBUGPRINTER_H
#define HTL_DEBUGPRINTER_H

#include "..\modHtlLibRefs.h"
#include "..\modHtlMacro.h"
//from iostream
//__PURE_APPDOMAIN_GLOBAL extern _CRTDATA2 istream cin;
//__PURE_APPDOMAIN_GLOBAL extern _CRTDATA2 ostream cout;

//from conio
//_Check_return_opt_ _CRTIMP int __cdecl _cprintf(_In_z_ _Printf_format_string_ const char * _Format, ...);
//_Check_return_opt_ _CRTIMP int __cdecl _cprintf_s(_In_z_ _Printf_format_string_ const char * _Format, ...);

#include <iostream>
#include <conio.h>
#include <string>
namespace HTL
{
	// MODIFIED 8.3.12 WAL to provide for LEAPS output
	class HTL_DLLAPI HtlDebugPrinter
	{
	public:
		HtlDebugPrinter(void);
		virtual ~HtlDebugPrinter(void);

		int DebugPrint(int intLevel,const char *fmt, ...);

		int DeleteDebugFile();

		void Disable(void);
		//!Debug print file name
		HTLMEMVAR_BYREF_STYLE1(public, std::string, strFileName);
		void Set_strFileName(const char* strName) { m_strFileName = strName; };
		//!boolean flag for printing to file
		HTLMEMVAR_BYVAL_STYLE1(public, bool, blnPrintToFile);
		//!boolean flag for printing to stream
		HTLMEMVAR_BYVAL_STYLE1(public, bool, blnPrintToStream);
		//!boolean flag for printing to text edit
		HTLMEMVAR_BYVAL_STYLE1(public, bool, blnPrintToTextEdit);
		//!sewtting the debug print level.  
		//Debug print levels print every statement AT OR BELOW the current level of the debug printer
		HTLMEMVAR_BYVAL_STYLE1(public, int, intPrintLevel);

	public:
		//protected write functions
		int DebugPrintToStream(const char *fmt, va_list args);
		int DebugPrintToFile(const char *fmt, va_list args);

	};//end class HtlDebugPrinter

	HTL_EXPORT void LocalDebugPrint(char * ptrFile, char * ptrMethod, const char * format, ...);

};
#endif
