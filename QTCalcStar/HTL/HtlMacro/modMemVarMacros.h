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



/*
	STATEMENT ON MACROS
	THE ONLY MACROS ALLOWED WITHIN HTL ARE FOR THREE PURPOSES:
	1) GENERATION OF SIMPLE ACCESSOR FUNCTIONS FOR MEMBER VARIABLES
	2) FORCING A NAMING CONVENTION FOR A FUNCTION PROTOTYPE
	3) TO TRIGGER A META OBJECT COMPILER ROUTINE

	NO OTHER MACROS ARE ALLOWED FOR ANY OTHER PURPOSES IN HTL.
	THEY IN GENERAL ARE A BAD PROGRAMMING PRACTICE.
	THEY PRODUCE CODE THAT IS NOT TRACEABLE.
*/


#ifndef MODMEMVARMACROS_H
#define MODMEMVARMACROS_H


/*
HTL Member Variable STYLE 1 EXAMPLE
HTLMEMVAR_BYVAL_STYLE1(public,float,sngHeight)
creates...

public:
void Set_sngHeight(float varVal)
{
	this->m_sngHeight = varVal;
	return;
};
float Get_sngHeight(void)
{
	return this->m_sngHeight;
};
protected:
	float m_sngHeight;
*/

#ifndef HTL_CPPNATIVE_MEMVAR
#define HTL_CPPNATIVE_MEMVAR(Type, TName) \
protected:\
	Type m_##TName; \
public:\
	inline Type Get_##TName() const{return m_##TName;}; \
	inline void Set_##TName( Type TName ){m_##TName = TName ; };
#endif


////MACROS TO GENERATE ACCESSOR FUNCTIONS FOR SIMPLE MEMBER VARIABLES///////////////////
//#ifndef HTL_MEMVAR_BYVAL
//#define HTL_MEMVAR_BYVAL(Type, TName) \
//protected:\
//	Type m_##TName; \
//public:\
//	inline Type Get_##TName() const{return m_##TName;}; \
//	inline void Set_##TName( Type TName ){m_##TName = TName ; };
//#endif
//
//#ifndef QTL_MEMVAR_BYREF
//#define QTL_MEMVAR_BYREF(Type, TName) \
//protected:\
//	Type m_##TName; \
//public:\
//	inline Type Get_##TName() const{return m_##TName;}; \
//	inline void Set_##TName( Type & TName ){m_##TName = TName ; };
//#endif
/////////////////////////////////////////////////////////////////////////////////////////



#ifndef HTLMEMVAR_BYVAL_STYLE1
#define HTLMEMVAR_BYVAL_STYLE1(access, varType, varName) \
protected: \
	varType m_##varName; \
access :\
	/*HTL Member Variable Accessor Set Function*/ \
	void Set_##varName( varType varVal) \
	{ \
		this->m_##varName = varVal; \
		return ; \
	}; \
	/*HTL Member Variable Accessor Get Function*/ \
	varType Get_##varName(void) const\
	{ \
		return this->m_##varName; \
	}; \

#endif

#ifndef HTLMEMVAR_BYREF_STYLE1
#define HTLMEMVAR_BYREF_STYLE1(access, varType, varName) \
protected: \
	varType m_##varName; \
access :\
	/*HTL Member Variable Accessor Set Function*/ \
	void Set_##varName( varType & varVal) \
	{ \
		this->m_##varName = varVal; \
		return ; \
	}; \
	/*HTL Member Variable Accessor Get Function*/ \
	varType Get_##varName(void) const\
	{ \
		return this->m_##varName; \
	}; \

#endif



#ifndef HTLOBJ_MEMVAR_BYVAL_STYLE1
#define HTLOBJ_MEMVAR_BYVAL_STYLE1(access, varType, varName) \
protected: \
	varType m_##varName; \
access :\
	/*HTL Member Variable Accessor Set Function*/ \
	void Set_##varName( varType varVal) \
	{ \
		this->m_##varName = varVal; \
		this->m_blnChanged = true; \
		return ; \
	}; \
	/*HTL Member Variable Accessor Get Function*/ \
	varType Get_##varName(void) \
	{ \
		return this->m_##varName; \
	}; \

#endif

#ifndef HTLOBJ_MEMVAR_BYREF_STYLE1
#define HTLOBJ_MEMVAR_BYREF_STYLE1(access, varType, varName) \
protected: \
	varType m_##varName; \
access :\
	/*HTL Member Variable Accessor Set Function*/ \
	void Set_##varName( varType & varVal) \
	{ \
		this->m_##varName = varVal; \
		this->m_blnChanged = true; \
		return ; \
	}; \
	/*HTL Member Variable Accessor Get Function*/ \
	varType Get_##varName(void) \
	{ \
		return this->m_##varName; \
	}; \

#endif









/*
HTL Member Variable STYLE 2 EXAMPLE
HTLMEMVAR_BYVAL_STYLE1(public,float,sngHeight)
creates...

public:
void Set_sngHeight(float varVal)
{
	this->m_sngHeight = varVal;
	return;
};
float sngHeight(void)
{
	return this->m_sngHeight;
};
protected:
	float m_sngHeight;
*/

#define HTLMEMVAR_BYVAL_STYLE2(access, varType, varName) access:\
	/*HTL Member Variable Accessor Set Function*/ \
	void Set_##varName( varType varVal) \
	{ \
		this->m_##varName = varVal; \
		return ; \
	}; \
	/*HTL Member Variable Accessor Get Function*/ \
	varType varName(void) \
	{ \
		return this->m_##varName; \
	}; \
protected: \
	varType m_##varName; \


#define HTLMEMVAR_BYREF_STYLE2(access, varType, varName) access:\
	/*HTL Member Variable Accessor Set Function*/ \
	void Set_##varName( varType & varVal) \
	{ \
		this->m_##varName = varVal; \
		return ; \
	}; \
	/*HTL Member Variable Accessor Get Function*/ \
	varType varName(void) \
	{ \
		return this->m_##varName; \
	}; \
protected: \
	varType m_##varName; \



#endif