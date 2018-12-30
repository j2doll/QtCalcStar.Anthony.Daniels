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

#ifndef GT_CELL_DATA_H
#define GT_CELL_DATA_H

#include "GtFunctionEvaluator.h"
#include <QTableWidgetItem>
#include <QColor>
#include <modHtlMacro.h>
#include <modHtlBase.h>
using namespace HTL;

namespace GT
{

	namespace GtCalc
	{

      class QTSpreadSheet;

		class HTL_DLLAPI GtCellData : public QTableWidgetItem, public HtlBase
		{
		public:
			//!Parent set constructor
			GtCellData(HtlBase* ptrParent = NULL);
         GtCellData *clone() const override;

         QVariant data(int role) const override;
         void setData(int role, const QVariant &value) override;
         QVariant display() const;

         QString formula() const;
			GtCellData(GtCellData & rhs);
			//!Virtual destructor
			virtual ~GtCellData(void);

			GtCellData & operator= (const GtCellData & rhs);
			//MEMBER VARIABLES////////////////////////

			//!The boolean flag for is the cell editable
			bool m_blnEditable;
			//!The boolean flag for is the cell editable
			bool m_blnVisible;
			//GEOMETRY
			//!The row of the cell
			long m_lngRow;
			//!The column of the cell
			long m_lngColumn;
			//!String to contain the cell formula
		   QString m_strFormula;
			//!String to contain the displayed data
			QString m_strData;
			//!pointer to the parent sheet
			QTSpreadSheet* m_ptrSheet;
			////!the visible rect for drawing
			//GtRectI m_objFrame;
			////!the color of the cell
			QColor m_objColor;
			//!The function evaluator for the cell.
			GtFunctionEvaluator m_objEvaluator;

			//evaluate the cell
			int Evaluate(int serialnum);
			//SERIALIZATION FUNCTIONS///////////////////////////////////////
			//!Save member data to the current element node
			virtual int Save(HTL::HtlElement * ptrCurrNode, std::string strMemVarName, bool blnWithSubObjects);
			//!Load member data from the current element node
			virtual int Load(HTL::HtlElement * ptrCurrNode, std::string strMemVarName);
		protected:
			int m_intSerial;
			//!boolean flag for editing
			bool m_blnModifyCell;


		};//end HtlBase class definition

	}//end namespace GtCore
}//end namespace GT
#endif //GT_OBJECT_H