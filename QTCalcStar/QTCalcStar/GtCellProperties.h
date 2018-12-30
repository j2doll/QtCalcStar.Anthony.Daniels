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

#ifndef GT_CELL_PROPERTIES_H
#define GT_CELL_PROPERTIES_H

#include <GtWinforms\GtDialog.h>

namespace GT
{
	namespace GtGui
	{
		class GtMultiTextEdit;
		class GtSimpleTextEdit;
		class GtLabel;
		class GtButton;
	};

	namespace GtCalc
	{
		class GtCellData;
		class QTSpreadSheet;

		class HTL_DLLAPI GtCellProperties : public GtDialog
		{
		public:
			//!Parent set constructor
			GtCellProperties(GtObject* ptrParent = NULL);
			//!Virtual destructor
			virtual ~GtCellProperties(void);

			//MEMBER VARIABLES////////////////////////

			//SIGNALS/////////////////////////////////
		public:

			//MEMBER FUNCTIONS////////////////////////
		public:
			//!Initialize the Controls
			virtual void InitializeControls(void);
			virtual void InitializeActions(void);

			void OnOK_Clicked(void);
			void OnCancel_Clicked(void);
			void OnChangeColor_Clicked(void);

			//!the calculator object
			HTLMEMVAR_BYVAL_STYLE1(public, GtCellData*, ptrCell);
			//!the calculator object
			HTLMEMVAR_BYVAL_STYLE1(public, QTSpreadSheet*, ptrSheet);

			void OnUpdateData(void);
		protected:
			GtLabel* m_lblRowHeight;
			GtLabel* m_lblColWidth;

			GtSimpleTextEdit * m_txtRowHeight;
			GtSimpleTextEdit * m_txtColWidth;

			GtFrame * m_frmColor;
			GtButton * m_cmdChangeColor;

			GtButton * m_cmdOK;
			GtButton * m_cmdCancel;

		};//end HtlBase class definition
	}//end namespace
}//end namespace


#endif //GT_MAIN_WINDOW_H