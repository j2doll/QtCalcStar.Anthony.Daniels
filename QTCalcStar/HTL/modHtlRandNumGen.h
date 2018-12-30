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

#ifndef MOD_HTL_RANDNUMGEN_H
#define MOD_HTL_RANDNUMGEN_H

#include ".\HtlRandNumGen\HtlRandNumGen.h"
#include ".\HtlRandNumGen\HtlRandNumDist.h"
//Random Number Generators
#include ".\HtlRandNumGen\RandNumGenerators\HtlLCGenerator.h"
#include ".\HtlRandNumGen\RandNumGenerators\HtlMLCGenerator.h"
#include ".\HtlRandNumGen\RandNumGenerators\HtlMersenneGenerator.h"
//Random Distributions
#include ".\HtlRandNumGen\RandDistGenerators\HtlExponential.h"
#include ".\HtlRandNumGen\RandDistGenerators\HtlGamma.h"
#include ".\HtlRandNumGen\RandDistGenerators\HtlGaussian.h"
#include ".\HtlRandNumGen\RandDistGenerators\HtlPoisson.h"
#include ".\HtlRandNumGen\RandDistGenerators\HtlUniform.h"

#endif //MOD_HTL_GLOBAL_H