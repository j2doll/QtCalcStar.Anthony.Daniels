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
#define HTL_DLLEXPORT

#include <GtBasicControls\GtButton.h>
#include <GtBasicControls\GtLabel.h>
#include <GtBasicControls\GtTabBar.h>
#include <GtBasicControls\GtTabPage.h>

#include <GtTextView\GtSimpleTextEdit.h>
#include <GtWinForms\GtColorDialog.h>
#include ".\GtCellData.h"
#include ".\GtCalcCell.h"
#include ".\GtSheetRow.h"
#include ".\GtSheetColumn.h"
#include ".\QTSpreadSheet.h"

#include ".\GtCellProperties.h"



namespace GT
{
	namespace GtCalc
	{
		//default constructor
		GtCellProperties::GtCellProperties(GtObject* ptrParent)
			: GtDialog(ptrParent)
		{
			m_strType = "GtCellProperties";
			m_ptrCell = NULL;
			m_ptrSheet = NULL;

			GtRectI rectNew;
			rectNew.xMin = 0;
			rectNew.xMax = 300;
			rectNew.yMin = 0;
			rectNew.yMax = 300;
			this->Set_objFrame(rectNew);
			this->m_blnDrawFrameText = false;
			this->Set_objBackBrush(GtBrush(GtColor(100, 150, 255)));
			this->InitializeDialog();

			this->PostPaint();
			
		};
		//virtual destructor
		GtCellProperties::~GtCellProperties(void)
		{
			this->DeleteAllSubWidgets();
		};

		void GtCellProperties::InitializeControls(void)
		{

			std::string strTemp;
			GtRectI rectNew;


			m_lblRowHeight = new GtLabel(this);
			rectNew.xMin = 25; rectNew.xMax = 100; rectNew.yMin = 25; rectNew.yMax = 50;
			m_lblRowHeight->Set_objFrame(rectNew);
			strTemp = "Row Height";
			m_lblRowHeight->Set_strText(strTemp);
			this->AddSubWidget(m_lblRowHeight);

			m_txtRowHeight = new GtSimpleTextEdit(this);
			rectNew.xMin = 125; rectNew.xMax = 200; rectNew.yMin = 25; rectNew.yMax = 50;
			m_txtRowHeight->Set_objFrame(rectNew);
			strTemp = "25";
			m_txtRowHeight->Set_strText(strTemp);
			this->AddSubWidget(m_txtRowHeight);

			m_lblColWidth = new GtLabel(this);
			rectNew.xMin = 25; rectNew.xMax = 100; rectNew.yMin = 75; rectNew.yMax = 100;
			m_lblColWidth->Set_objFrame(rectNew);
			strTemp = "Col Width";
			m_lblColWidth->Set_strText(strTemp);
			this->AddSubWidget(m_lblColWidth);

			m_txtColWidth = new GtSimpleTextEdit(this);
			rectNew.xMin = 125; rectNew.xMax = 200; rectNew.yMin = 75; rectNew.yMax = 100;
			m_txtColWidth->Set_objFrame(rectNew);
			strTemp = "50";
			m_txtColWidth->Set_strText(strTemp);
			this->AddSubWidget(m_txtColWidth);

			m_frmColor = new GtFrame(this);
			rectNew.xMin = 25; rectNew.xMax = 100; rectNew.yMin = 125; rectNew.yMax = 150;
			m_frmColor->Set_objFrame(rectNew);
			m_frmColor->Set_blnDrawFrameText(false);
			this->AddSubWidget(m_frmColor);

			m_cmdChangeColor = new GtButton(this);
			rectNew.xMin = 125; rectNew.xMax = 200; rectNew.yMin = 125; rectNew.yMax = 150;
			m_cmdChangeColor->Set_objFrame(rectNew);
			strTemp = "Color";
			m_cmdChangeColor->Set_strText(strTemp);
			this->AddSubWidget(m_cmdChangeColor);

			m_cmdOK = new GtButton(this);
			rectNew.xMin = 25; rectNew.xMax = 100; rectNew.yMin = 175; rectNew.yMax = 200;
			m_cmdOK->Set_objFrame(rectNew);
			strTemp = "OK";
			m_cmdOK->Set_strText(strTemp);
			this->AddSubWidget(m_cmdOK);

			m_cmdCancel = new GtButton(this);
			rectNew.xMin = 125; rectNew.xMax = 200; rectNew.yMin = 175; rectNew.yMax = 200;
			m_cmdCancel->Set_objFrame(rectNew);
			strTemp = "CANCEL";
			m_cmdCancel->Set_strText(strTemp);
			this->AddSubWidget(m_cmdCancel);

			return;
		};

		void GtCellProperties::InitializeActions(void)
		{
			if (m_cmdOK)
			{
				m_cmdOK->Clicked.SlotConnect(this, &GtCellProperties::OnOK_Clicked);
			};
			if (m_cmdCancel)
			{
				m_cmdCancel->Clicked.SlotConnect(this, &GtCellProperties::OnCancel_Clicked);
			};
			if (m_cmdChangeColor)
			{
				m_cmdChangeColor->Clicked.SlotConnect(this, &GtCellProperties::OnChangeColor_Clicked);
			};
			return;
		};


		void GtCellProperties::OnOK_Clicked(void)
		{
			if (!m_ptrCell) { return; };//safety check
			if (!m_ptrSheet) { return; };//safety check

			long iRow, jCol, rowHeight,colWidth;
			rowHeight = 25;//default
			colWidth = 50;//default
			iRow = m_ptrCell->m_lngRow;
			jCol = m_ptrCell->m_lngColumn;
			if(m_txtRowHeight)
				rowHeight = atoi(m_txtRowHeight->GetTextString().c_str());

			if (m_txtColWidth)
				colWidth = atoi(m_txtColWidth->GetTextString().c_str());
			GtSheetColumn* ptrCol = m_ptrSheet->GetColumnPtr(jCol);
			if (ptrCol)
			{
				ptrCol->Set_intWidth(colWidth);
			}
			GtSheetRow* ptrRow = m_ptrSheet->GetRowPtr(iRow);
			if (ptrRow)
			{
				ptrRow->Set_intHeight(rowHeight);
			}

			m_ptrCell->m_objColor = m_frmColor->Get_objBackBrush().Get_objColor();

			m_ptrSheet->PostPaint();
			this->Accept();
		};

		void GtCellProperties::OnCancel_Clicked(void)
		{
			this->Reject();
		};

		void GtCellProperties::OnChangeColor_Clicked(void)
		{
			if (!m_ptrCell) { return; };//safety check
			GtColorDialog dlgColor;
			dlgColor.Set_ptrParent(NULL);
			dlgColor.Set_blnModal(true);

			if (dlgColor.Exec())
			{
				GtColor objSel = dlgColor.Get_objSelColor();
				if (m_frmColor)
				{
					m_frmColor->Set_objBackBrush(GtBrush(objSel));
				}
			}
		};

		void GtCellProperties::OnUpdateData(void)
		{
			if (!m_ptrCell) { return; };//safety check
			if (!m_ptrSheet) { return; };//safety check
			char buf[16];
			long iRow, jCol, rowHeight, colWidth;
			
			iRow = m_ptrCell->m_lngRow;
			jCol = m_ptrCell->m_lngColumn;

			GtSheetRow* ptrRow = m_ptrSheet->GetRowPtr(iRow);
			if (ptrRow)
			{
				rowHeight = ptrRow->Get_intHeight();
				if (m_txtRowHeight)
				{
					sprintf(buf, "%d", rowHeight);
					m_txtRowHeight->SetTextString(buf);
				}
			}
			
			GtSheetColumn* ptrCol = m_ptrSheet->GetColumnPtr(jCol);
			if (ptrCol)
			{
				colWidth = ptrCol->Get_intWidth();
				if (m_txtColWidth)
				{
					sprintf(buf, "%d", colWidth);
					m_txtColWidth->SetTextString(buf);
				}
			}
			if (m_frmColor)
			{
				m_frmColor->Set_objBackBrush(GtBrush(m_ptrCell->m_objColor));
			}
			
		};

	}//end namespace
}//end namespace
