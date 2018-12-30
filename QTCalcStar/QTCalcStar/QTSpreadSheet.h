/****************************************************************************
**
** Copyright (C) 2016 The Qt Company Ltd.
** Contact: https://www.qt.io/licensing/
**
** This file is part of the demonstration applications of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:BSD$
** Commercial License Usage
** Licensees holding valid commercial Qt licenses may use this file in
** accordance with the commercial license agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and The Qt Company. For licensing terms
** and conditions see https://www.qt.io/terms-conditions. For further
** information use the contact form at https://www.qt.io/contact-us.
**
** BSD License Usage
** Alternatively, you may use this file under the terms of the BSD license
** as follows:
**
** "Redistribution and use in source and binary forms, with or without
** modification, are permitted provided that the following conditions are
** met:
**   * Redistributions of source code must retain the above copyright
**     notice, this list of conditions and the following disclaimer.
**   * Redistributions in binary form must reproduce the above copyright
**     notice, this list of conditions and the following disclaimer in
**     the documentation and/or other materials provided with the
**     distribution.
**   * Neither the name of The Qt Company Ltd nor the names of its
**     contributors may be used to endorse or promote products derived
**     from this software without specific prior written permission.
**
**
** THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
** "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
** LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
** A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
** OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
** SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
** LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
** DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
** THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
** (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
** OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE."
**
** $QT_END_LICENSE$
**
****************************************************************************/


#ifndef SPREADSHEET_H
#define SPREADSHEET_H
#include "GtCellData.h"
#include <QWidget>
#include <modHtlMacro.h>
#include <modHtlBase.h>
#include <modHtlGUID.h>
#include <modHtlContainer.h>
using namespace HTL;

class QToolBar;
class QMenuBar;
class QAction;
class QLabel;
class QLineEdit;
class QToolBar;
class QTableWidgetItem;
class QTableWidget;

namespace GT
{
   namespace GtCalc
   {
      class GtCellData;
      typedef HtlTreeNode<Htl2DIndex, GtCellData*>* SheetNodeIter;


      class QTSpreadSheet : public QWidget, public HtlBase
      {
         Q_OBJECT

      public:

         QTSpreadSheet(QString strName, int rows = 50, int cols = 50, QWidget *parent = 0);

         HTLMEMVAR_BYREF_STYLE1(public, string, strType);
         HTLMEMVAR_BYREF_STYLE1(public, string, strName);
         HTLMEMVAR_BYREF_STYLE1(public, HtlGUID128, objGUID);

         public slots:
         void updateStatus(QTableWidgetItem *item);
         void updateColor(QTableWidgetItem *item);
         void updateLineEdit(QTableWidgetItem *item);
         void returnPressed();
         bool eventFilter(QObject *obj, QEvent *evt);
         void selectColor();
         void selectFont();
         void clear();
         void showAbout();
         void UpdateCalcSheet();
         void print();
         void OnResize(QSize & var);
          
         GtCellData* GetCellPtr(long row, long col);
         GtCellData* GetOrMakeCellPtr(long row, long col);
         //!Event handler for CTRL + C keystroke event
         void OnCopy();
         //!Event handler for CTRL + X keystroke event
         void OnCut();
         //!Event handler for CTRL + V keystroke event
         void OnPaste();
         //!Event handler for Delete keystroke event
         void OnDelete();
      protected:
         void setupContextMenu();
        

         void setupMenuBar();
         void createActions();
         void GetIndexRange(QModelIndexList & list, int & iLBRow, int & iLBCol, int & iUBRow, int & iUBCol);

         //!The Cell Collection
         HtlListMap<Htl2DIndex, HTL_BASE, GtCellData*, HTL_OBJECT_PTR> m_mapCells;

      private:

         QAction *colorAction;
         QAction *fontAction;
         QAction *firstSeparator;
         QAction *secondSeparator;
         QAction *clearAction;
         QAction *aboutSpreadSheet;
         QAction *exitAction;

         QAction *printAction;

         QLabel *cellLabel;
         QTableWidget *table;
         QLineEdit *formulaInput;
         QMenuBar * menuBar;
         QToolBar * toolBar;
         HWND m_winID;
      };

      void decode_pos(const QString &pos, int *row, int *col);
      QString encode_pos(int row, int col);
   }
}
#endif // SPREADSHEET_H