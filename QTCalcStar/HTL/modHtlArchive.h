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

#ifndef MOD_HTL_ARCHIVE_H
#define MOD_HTL_ARCHIVE_H
#include <string>
using namespace std;

#include ".\modHtlLibRefs.h"
#include ".\HtlArchive\HtlNode.h"
#include ".\HtlArchive\HtlAttribute.h"
#include ".\HtlArchive\HtlComment.h"
#include ".\HtlArchive\HtlProcess.h"
#include ".\HtlArchive\HtlElement.h"
#include ".\HtlArchive\HtlDocument.h"
#include ".\HtlArchive\HtlMemVarItem.h"
#include ".\HtlArchive\HtlMemVar.h"
#include ".\HtlArchive\HtlMemVar2.h"

//XML READERS AND WRITERS
#include ".\HtlArchive\ArchXML\HtlXMLReader.h"
#include ".\HtlArchive\ArchXML\HtlXMLWriter.h"

//XDL READERS AND WRITERS
#include ".\HtlArchive\ArchXDL\HtlXDLReader.h"
#include ".\HtlArchive\ArchXDL\HtlXDLWriter.h"

//JSON READERS AND WRITERS
#include ".\HtlArchive\ArchJSON\HtlJSONReader.h"
#include ".\HtlArchive\ArchJSON\HtlJSONWriter.h"

#endif //MOD_HTL_GLOBAL_H