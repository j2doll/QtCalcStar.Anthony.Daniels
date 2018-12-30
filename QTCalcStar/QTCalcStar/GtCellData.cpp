/*
**	This file is part of the GT Core Library.
**  It is based on a merger of QT along with development of new classes.
**  License information is in the License.h file
**	This software was merged and developed by:
**	
**  Anthony Daniels

**
**  GT is free software: you can redistribute it and/or modify
**  it under the terms of the GNU Lesser General Public License as published by
**  the Free Software Foundation, either version 3 of the License, or
**  (at your option) any later version.
**
**  The United States of America Department of Defense has unlimited 
**	usage, redistribution, and modification rights to GT.
**
**  GT is distributed in the hope that it will be useful,
**  but WITHOUT ANY WARRANTY; without even the implied warranty of
**  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
**  GNU Lesser General Public License for more details.
**
**  You should have received a copy of the GNU Lesser General Public License
**  along with GT.  If not, see <http://www.gnu.org/licenses/>.
*/

#pragma once
#pragma warning(push)
#pragma warning (disable : 4005 ) /* macro redefinition */
#define HTL_DLLEXPORT
#pragma warning(pop)

#include ".\GtCellData.h"
#include "QTSpreadSheet.h"

namespace GT
{
	namespace GtCalc
	{

		//default constructor
		GtCellData::GtCellData(HtlBase* ptrParent)
         : QTableWidgetItem(), HtlBase()
		{
         m_objType = HTL_BASE;
			m_strType = "GtCellData";
			m_lngRow = 0;
			m_lngColumn = 0;
			//set flags
			m_blnEditable = true;
			m_blnVisible = false;

			m_objEvaluator.Set_ptrParent(this);
			m_objEvaluator.Set_ptrSheet(ptrParent);
		};
		//virtual destructor
		GtCellData::~GtCellData(void)
		{

		};

		GtCellData::GtCellData(GtCellData & rhs)
		{
         m_objType = HTL_BASE;
         m_strType = "GtCellData";
			this->m_strFormula = rhs.m_strFormula;
			this->m_strData = rhs.m_strData;
		};

		GtCellData & GtCellData::operator= (const GtCellData & rhs) 
      {
			if (this != &rhs)
			{
				this->m_strFormula = rhs.m_strFormula;
				this->m_strData = rhs.m_strData;
			}
			return *this;
		};

      GtCellData *GtCellData::clone() const
      {
         GtCellData *item = new GtCellData();
         *item = *this;
         return item;
      }

      QVariant GtCellData::data(int role) const
      {
         if (role == Qt::EditRole || role == Qt::StatusTipRole)
            return formula();

         if (role == Qt::DisplayRole)
            return display();

         return QTableWidgetItem::data(role);
      }

      void GtCellData::setData(int role, const QVariant &value)
      {
         m_strFormula = value.toString();
         QTableWidgetItem::setData(role, value);
         if (tableWidget())
            tableWidget()->viewport()->update();
      }

      QVariant GtCellData::display() const
      {
         return m_strData;
      }

      QString GtCellData::formula() const
      {
         return m_strFormula;
      }
      
		//!Evaluates the cell formula and replaces the displayed value
		int GtCellData::Evaluate(int serialnum)
		{
			int iRet;
			double dblCurrVal, dblNewVal;
			if (m_strFormula.size() <= 0) { return 0; };//safety check
			if (m_intSerial == serialnum)
			{
				//calculation already been here
				return -2;//circular logic detected.
			}
			//first time through
			m_intSerial = serialnum;
			if (m_strFormula[0] == '=')
			{
				dblCurrVal = (m_strData.toDouble());

				m_objEvaluator.Set_strExpression(m_strFormula.toStdString());
				iRet = m_objEvaluator.Evaluate();
				dblNewVal = m_objEvaluator.Get_dblCurrValue();
				char buf[24];
				sprintf(buf, "%lf", dblNewVal);

				this->m_strData = buf;

				if (abs(dblCurrVal - dblNewVal) > 0.001f)
				{
					return 2;//success, value changed
				}

			}else {
				//otherwise string or number
				this->m_strData = m_strFormula;
			}
			return 1;//success value constant
		};


		//Virtual Inheritance Serialization Engines
		//SERIALIZATION FUNCTIONS///////////////////////////////////////
		//!Save member data to the current element node
		int GtCellData::Save(HTL::HtlElement * ptrCurrNode, std::string strMemVarName, bool blnWithSubObjects)
		{
			if ((m_strFormula.size() <= 0) && (m_strData.size() <= 0))
			{
				//then this is a blank cell, do nothing
				return 0;
			}
			int intReturn = 0;
			//SAFETY CHECK //put at top of all Serialize Methods
			if (!ptrCurrNode) { return 0; };
			//CALL PARENT CLASS Serialize()
			/*...*/

			//Standard Member Variables
			//intReturn &= SetHtlMemVar<long, CPP_LONG>(ptrCurrNode, "m_lngRow", m_lngRow, false);
			//intReturn &= SetHtlMemVar<long, CPP_LONG>(ptrCurrNode, "m_lngColumn", m_lngColumn, false);
			//intReturn &= SetHtlMemVar<string, STL_STRING>(ptrCurrNode, "m_strFormula", m_strFormula, false);
			//intReturn &= SetHtlMemVar<string, STL_STRING>(ptrCurrNode, "m_strData", m_strData, false);
			//intReturn &= SetHtlMemVar<GtColor, HTL_BASE>(ptrCurrNode, "m_objColor", m_objColor, true);

			return 1;
		};
		//!Load member data from the current element node
		int GtCellData::Load(HTL::HtlElement * ptrCurrNode, std::string strMemVarName)
		{
			int intReturn = 0;
			//Standard Member Variables
			//intReturn &= GetHtlMemVar<long, CPP_LONG>(ptrCurrNode, "m_lngRow", m_lngRow);
			//intReturn &= GetHtlMemVar<long, CPP_LONG>(ptrCurrNode, "m_lngColumn", m_lngColumn);
			//intReturn &= GetHtlMemVar<string, STL_STRING>(ptrCurrNode, "m_strFormula", m_strFormula);
			//intReturn &= GetHtlMemVar<string, STL_STRING>(ptrCurrNode, "m_strData", m_strData);
			//intReturn &= GetHtlMemVar<GtColor, HTL_BASE>(ptrCurrNode, "m_objColor", m_objColor);

			//HtlNode nodeTemp;
			//nodeTemp.DecodeSpecialChars(m_strFormula);
			//nodeTemp.DecodeSpecialChars(m_strData);


			return intReturn;
		};



	};//end namespace GtGui

};//end namespace GT