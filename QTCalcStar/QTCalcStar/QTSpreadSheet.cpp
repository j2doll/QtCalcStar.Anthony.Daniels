
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
#define HTL_DLLEXPORT
#include <QKeyEvent>

#include <QtWidgets>
#if defined(QT_PRINTSUPPORT_LIB)
#include <QtPrintSupport/qtprintsupportglobal.h>
#if QT_CONFIG(printdialog)
#include <QPrinter>
#include <QPrintDialog>
#endif
#if QT_CONFIG(printpreviewdialog)
#include <QPrintPreviewDialog>
#endif
#endif
#include "GtSheetServer.h"
#include "QTSpreadSheet.h"
#include "QTSpreadSheetDelegate.h"
#include "GtCellData.h"
#include "QTPrintView.h"

namespace GT
{
   namespace GtCalc
   {

      QTSpreadSheet::QTSpreadSheet(QString strName, int rows, int cols, QWidget *parent)
         : QWidget(parent)
      {
         m_strName = strName.toStdString();
         m_objGUID.newID();
         GtSheetServer::GetServerPtr()->RegisterSheet(this);

         toolBar = new QToolBar(this);
         toolBar->move(0, 25);
         formulaInput = new QLineEdit(this);
         formulaInput->setMinimumSize(500, 0);
         cellLabel = new QLabel(toolBar);
         cellLabel->setMinimumSize(40, 0);
         cellLabel->setText("Fx:");

         toolBar->addWidget(cellLabel);
         toolBar->addWidget(formulaInput);
         toolBar->show();

         table = new QTableWidget(rows, cols, this);
         table->move(0, 50);
         QSize parentSize = parent->size();
         parentSize.setHeight(parentSize.height() - 50);
         parentSize.setWidth(parentSize.width() - 25);
         table->resize(parentSize);
         table->setSizeAdjustPolicy(QTableWidget::AdjustToContents);
         table->setHorizontalScrollBarPolicy(Qt::ScrollBarPolicy::ScrollBarAsNeeded);
         table->setVerticalScrollBarPolicy(Qt::ScrollBarPolicy::ScrollBarAsNeeded);




         table->setItemPrototype(table->item(rows - 1, cols - 1));
         table->setItemDelegate(new QTSpreadSheetDelegate());

         createActions();
         updateColor(0);
         setupMenuBar();
         
         setupContextMenu();
         //statusBar();
         connect(table, &QTableWidget::currentItemChanged,
            this, &QTSpreadSheet::updateStatus);
         connect(table, &QTableWidget::currentItemChanged,
            this, &QTSpreadSheet::updateColor);
         connect(table, &QTableWidget::currentItemChanged,
            this, &QTSpreadSheet::updateLineEdit);
         connect(table, &QTableWidget::itemChanged,
            this, &QTSpreadSheet::updateStatus);
         connect(formulaInput, &QLineEdit::returnPressed, this, &QTSpreadSheet::returnPressed);
         connect(table, &QTableWidget::itemChanged,
            this, &QTSpreadSheet::updateLineEdit);

         setWindowTitle(tr("QTSpreadSheet"));

         table->installEventFilter(this);


      }

      void QTSpreadSheet::createActions()
      {
         fontAction = new QAction(tr("Font..."), this);
         fontAction->setShortcut(Qt::CTRL | Qt::Key_F);
         connect(fontAction, &QAction::triggered, this, &QTSpreadSheet::selectFont);

         colorAction = new QAction(QPixmap(16, 16), tr("Background &Color..."), this);
         connect(colorAction, &QAction::triggered, this, &QTSpreadSheet::selectColor);

         clearAction = new QAction(tr("Clear"), this);
         clearAction->setShortcut(Qt::Key_Delete);
         connect(clearAction, &QAction::triggered, this, &QTSpreadSheet::clear);

         aboutSpreadSheet = new QAction(tr("About QTSpreadSheet"), this);
         connect(aboutSpreadSheet, &QAction::triggered, this, &QTSpreadSheet::showAbout);

         exitAction = new QAction(tr("E&xit"), this);
         connect(exitAction, &QAction::triggered, qApp, &QCoreApplication::quit);

         printAction = new QAction(tr("&Print"), this);
         connect(printAction, &QAction::triggered, this, &QTSpreadSheet::print);

         firstSeparator = new QAction(this);
         firstSeparator->setSeparator(true);

         secondSeparator = new QAction(this);
         secondSeparator->setSeparator(true);
      }

      void QTSpreadSheet::setupMenuBar()
      {
         menuBar = new QMenuBar(this);
         menuBar->move(0, 0);
         QMenu *fileMenu = menuBar->addMenu(tr("&File"));
         fileMenu->addAction(printAction);
         fileMenu->addAction(exitAction);

         QMenu *cellMenu = menuBar->addMenu(tr("&Cell"));
         cellMenu->addSeparator();
         cellMenu->addAction(colorAction);
         cellMenu->addAction(fontAction);

         menuBar->addSeparator();

         QMenu *aboutMenu = menuBar->addMenu(tr("&Help"));
         aboutMenu->addAction(aboutSpreadSheet);
      }

      void QTSpreadSheet::updateStatus(QTableWidgetItem *item)
      {
         //if (item && item == table->currentItem()) {
         //    statusBar()->showMessage(item->data(Qt::StatusTipRole).toString(), 1000);
         //    cellLabel->setText(tr("Cell: (%1)").arg(encode_pos(table->row(item), table->column(item))));
         //}
      }

      //!Get the pointer to the cell at location
      GtCellData* QTSpreadSheet::GetCellPtr(long row, long col)
      {
         Htl2DIndex key; key.m_lngX = row; key.m_lngY = col;

         SheetNodeIter iter = m_mapCells.find(key);
         if (iter)
         { //then doesn't already exist, create it
            return iter->value();
         }

         return NULL;
      };

      GtCellData* QTSpreadSheet::GetOrMakeCellPtr(long row, long col)
      {
         Htl2DIndex key; key.m_lngX = row; key.m_lngY = col;

         SheetNodeIter iter = m_mapCells.find(key);
         if (iter)
         { //then doesn't already exist, create it
            return iter->value();
         }
         else {
            GtCellData * ptrNew = new GtCellData(this);
            ptrNew->m_strFormula = "";
            Htl2DIndex index; index.m_lngX = row ; index.m_lngY = col ;
            ptrNew->m_ptrSheet = this;
            m_mapCells.insert(index, ptrNew);
            table->setItem(row - 1, col - 1, ptrNew);
            return ptrNew;
         }

         return NULL;
      };



      void QTSpreadSheet::updateColor(QTableWidgetItem *item)
      {
         QPixmap pix(16, 16);
         QColor col;
         if (item)
            col = item->backgroundColor();
         if (!col.isValid())
            col = palette().base().color();

         QPainter pt(&pix);
         pt.fillRect(0, 0, 16, 16, col);

         QColor lighter = col.light();
         pt.setPen(lighter);
         QPoint lightFrame[] = { QPoint(0, 15), QPoint(0, 0), QPoint(15, 0) };
         pt.drawPolyline(lightFrame, 3);

         pt.setPen(col.dark());
         QPoint darkFrame[] = { QPoint(1, 15), QPoint(15, 15), QPoint(15, 1) };
         pt.drawPolyline(darkFrame, 3);

         pt.end();

         colorAction->setIcon(pix);
      }

      void QTSpreadSheet::updateLineEdit(QTableWidgetItem *item)
      {
         if (item != table->currentItem())
            return;
         if (item)
            formulaInput->setText(item->data(Qt::EditRole).toString());
         else
            formulaInput->clear();
      }

      void QTSpreadSheet::returnPressed()
      {
         QString text = formulaInput->text();
         int row = table->currentRow();
         int col = table->currentColumn();
         GtCellData *item = dynamic_cast<GtCellData*>(table->item(row, col));
         if (!item)
         {
            GtCellData * ptrNew = new GtCellData(this);
            ptrNew->m_strFormula = text;
            Htl2DIndex index; index.m_lngX = row+1; index.m_lngY = col+1;
            ptrNew->m_ptrSheet = this;
            m_mapCells.insert(index, ptrNew);
            table->setItem(row, col, ptrNew);


            if (text.size() <= 0)
            {
               ptrNew->m_strData = text;
            }
            else {
               ptrNew->Evaluate(rand());
            }

         }
         else
         {
            item->setData(Qt::EditRole, text);
            if (text.size() <= 0)
            {
               item->m_strData = text;
            }
            else {
               item->Evaluate(rand());
            }
         }
         
         this->UpdateCalcSheet();

         table->viewport()->update();
      }

      void QTSpreadSheet::selectColor()
      {
         QTableWidgetItem *item = table->currentItem();
         QColor col = item ? item->backgroundColor() : table->palette().base().color();
         col = QColorDialog::getColor(col, this);
         if (!col.isValid())
            return;

         QList<QTableWidgetItem*> selected = table->selectedItems();
         if (selected.count() == 0)
            return;

         foreach(QTableWidgetItem *i, selected)
         {
            GtCellData * ptrCurr = dynamic_cast<GtCellData*>(i);
                      
            if (ptrCurr)
            {
               QString strTemp = ptrCurr->m_strFormula;
               ptrCurr->setBackgroundColor(col);
               ptrCurr->m_strFormula = strTemp;
            }
         }

         updateColor(table->currentItem());
      }

      void QTSpreadSheet::selectFont()
      {
         QList<QTableWidgetItem*> selected = table->selectedItems();
         if (selected.count() == 0)
            return;

         bool ok = false;
         QFont fnt = QFontDialog::getFont(&ok, font(), this);

         if (!ok)
            return;
         foreach(QTableWidgetItem *i, selected) {
            if (i)
               i->setFont(fnt);
         }
      }


      void QTSpreadSheet::clear()
      {
         foreach(QTableWidgetItem *i, table->selectedItems())
            i->setText("");
      }

      void QTSpreadSheet::setupContextMenu()
      {

         addAction(firstSeparator);
         addAction(colorAction);
         addAction(fontAction);
         addAction(secondSeparator);
         addAction(clearAction);
         setContextMenuPolicy(Qt::ActionsContextMenu);
      }


      const char *htmlText =
         "<HTML>"
         "<p><b>This demo shows use of <c>QTableWidget</c> with custom handling for"
         " individual cells.</b></p>"
         "<p>Using a customized table item we make it possible to have dynamic"
         " output in different cells. The content that is implemented for this"
         " particular demo is:"
         "<ul>"
         "<li>Adding two cells.</li>"
         "<li>Subtracting one cell from another.</li>"
         "<li>Multiplying two cells.</li>"
         "<li>Dividing one cell with another.</li>"
         "<li>Summing the contents of an arbitrary number of cells.</li>"
         "</HTML>";

      void QTSpreadSheet::showAbout()
      {
         QMessageBox::about(this, "About QTSpreadSheet", htmlText);
      }

      void decode_pos(const QString &pos, int *row, int *col)
      {
         if (pos.isEmpty()) {
            *col = -1;
            *row = -1;
         }
         else {
            *col = pos.at(0).toLatin1() - 'A';
            *row = pos.right(pos.size() - 1).toInt() - 1;
         }
      }

      QString encode_pos(int row, int col)
      {
         return QString(col + 'A') + QString::number(row + 1);
      }

      void QTSpreadSheet::print()
      {
#if QT_CONFIG(printpreviewdialog)
         QPrinter printer(QPrinter::ScreenResolution);
         QPrintPreviewDialog dlg(&printer);
         QTPrintView view;
         view.setModel(table->model());
         connect(&dlg, &QPrintPreviewDialog::paintRequested, &view, &QTPrintView::print);
         dlg.exec();
#endif
      }

      void QTSpreadSheet::OnResize(QSize & var)
      {
         QSize parentSize;
         parentSize.setHeight(var.height() - 75);
         parentSize.setWidth(var.width() - 25);
         table->resize(parentSize);
      };

      bool QTSpreadSheet::eventFilter(QObject *obj, QEvent *evt)
      {
         if (evt->type() == QEvent::KeyPress)
         {
            QKeyEvent *keyEvent = static_cast<QKeyEvent *>(evt);
            int key = keyEvent->key();
            if ((key == Qt::Key_Return)||(key == Qt::Key_Enter))
            {
               this->returnPressed();
            }
            else if ((keyEvent->modifiers().testFlag(Qt::ControlModifier)) && (key == Qt::Key_C))
            {
               this->OnCopy();
            }
            else if ((keyEvent->modifiers().testFlag(Qt::ControlModifier)) && (key == Qt::Key_X))
            {
               this->OnCut();
            }
            else if ((keyEvent->modifiers().testFlag(Qt::ControlModifier)) && (key == Qt::Key_V))
            {
               this->OnPaste();
            }
            else if ((keyEvent->modifiers().testFlag(Qt::ControlModifier)) && (key == Qt::Key_Delete))
            {
               this->OnDelete();
            }
            else
            {
               return false;
            }
            return true;
         }
         else
         {
            return QObject::eventFilter(obj, evt);
         }
      }
      void QTSpreadSheet::UpdateCalcSheet()
      {
         bool blnCellChanged = false;
         int maxIter = 50;
         int iter = 0;
         do 
         {
            blnCellChanged = false;
            int numCells = m_mapCells.size();
            for (int i = 0; i < numCells;i++)
            {
               GtCellData* ptrCurr = m_mapCells.at(i);
               double dblCurrVal = (ptrCurr->m_strData.toDouble());
               ptrCurr->Evaluate(rand());
               double dblNextVal = (ptrCurr->m_strData.toDouble());
               if (dblCurrVal != dblNextVal)
               {
                  blnCellChanged = true;
               }
            }
            iter++;
         } while ((blnCellChanged == true) && (iter < maxIter));

      };

      void QTSpreadSheet::GetIndexRange(QModelIndexList & list, int & iLBRow, int & iLBCol, int & iUBRow, int & iUBCol)
      {
         iLBRow = -1;iLBCol = -1;iUBRow = -1;iUBCol = -1;


         int numIdxs = list.size();
         for (int i = 0; i < numIdxs;i++)
         {
            if (i == 0)
            {
               iLBRow = list.at(i).row();
               iLBCol = list.at(i).column();
               iUBRow = list.at(i).row();
               iUBCol = list.at(i).column();
            }

            if (list.at(i).row() < iLBRow) 
            {
               iLBRow = list.at(i).row();
            }
            if (list.at(i).row() > iUBRow)
            {
               iUBRow = list.at(i).row();
            }
            if (list.at(i).column() < iLBCol)
            {
               iLBCol = list.at(i).column();
            }
            if (list.at(i).column() > iUBCol)
            {
               iUBCol = list.at(i).column();
            }

         }

      };

      //!Event handler for CTRL + C keystroke event
      void QTSpreadSheet::OnCopy()
      {
         string strCopy;
         HGLOBAL hglbCopy;
         LPTSTR lpstrCopy;

         
         m_winID = (HWND)winId();
         if (!OpenClipboard(m_winID))
         {//couldn't open clipboard
            return;
         }
         EmptyClipboard();
         QItemSelectionModel * ptrSelection = table->selectionModel();
         QModelIndexList arrIndexes = ptrSelection->selectedIndexes();
         int iLBRow, iLBCol, iUBRow, iUBCol;
         GetIndexRange(arrIndexes, iLBRow, iLBCol, iUBRow, iUBCol);


         if ((iLBRow == iUBRow)&&(iLBCol == iUBCol))
         {//single cell selected
            GtCellData * pULCell = this->GetCellPtr(iLBRow+1, iLBCol+1);
            if (pULCell)
            {
               strCopy = pULCell->m_strData.toStdString();
            }

         }
         else {
       
            for (int i = iLBRow; i <= iUBRow; i++)
            {
               for (int j = iLBCol; j <= iUBCol; j++)
               {
                  GtCellData *pCurr = this->GetCellPtr(i+1, j+1);
                  if (pCurr)
                  {
                     strCopy += pCurr->m_strData.toStdString();
                  } else {
                     strCopy += "0.0";
                  }
                  if (j != iUBCol)
                     strCopy += "\t";
               };//end loop cols
               if (i != iUBRow)
                  strCopy += "\n";
            };//end loop rows

         };
         strCopy += "\n";
         hglbCopy = GlobalAlloc(GMEM_MOVEABLE, (strCopy.size()) * sizeof(TCHAR));
         if (!hglbCopy) { CloseClipboard(); return; }
         lpstrCopy = (LPTSTR)GlobalLock(hglbCopy);
         memcpy(lpstrCopy, strCopy.c_str(), strCopy.size());
         lpstrCopy[strCopy.size()] = 0;
         GlobalUnlock(hglbCopy);
         SetClipboardData(CF_TEXT, (LPTSTR)lpstrCopy);
         CloseClipboard();
         return;
      };
      //!Event handler for CTRL + X keystroke event
      void QTSpreadSheet::OnCut()
      {
         //first copy
         this->OnCopy();
         //then cut
         string strNull;
         QItemSelectionModel * ptrSelection = table->selectionModel();
         QModelIndexList arrIndexes = ptrSelection->selectedIndexes();
         int iLBRow, iLBCol, iUBRow, iUBCol;
         GetIndexRange(arrIndexes, iLBRow, iLBCol, iUBRow, iUBCol);

         if ((iLBRow == iUBRow) && (iLBCol == iUBCol))
         {//single cell selected
            GtCellData * pULCell = this->GetCellPtr(iLBRow+1, iLBCol+1);
            if (pULCell)
            {
               pULCell->m_strFormula = "";
               pULCell->m_strData = "";
            }
         }
         else {

            for (int i = iLBRow; i <= iUBRow; i++)
            {
               for (int j = iLBCol; j <= iUBCol; j++)
               {
                  GtCellData *pCurr = this->GetCellPtr(i+1, j+1);
                  if (pCurr)
                  {
                     pCurr->m_strFormula = "";
                     pCurr->m_strData = "";
                  }                
               };//end loop cols
            };//end loop rows
         };

         this->UpdateCalcSheet();
         return;

      };
      //!Event handler for CTRL + V keystroke event
      void QTSpreadSheet::OnPaste()
      {
         //safety check
         HGLOBAL hglbPaste;
         LPTSTR lpstrPaste;

         m_winID = (HWND)winId();
         if (!OpenClipboard(m_winID))
         {//couldn't open clipboard
            return;
         }
         if (!IsClipboardFormatAvailable(CF_TEXT)) { return; }
         hglbPaste = GetClipboardData(CF_TEXT);
         if (hglbPaste != NULL)
         {
            lpstrPaste = (LPTSTR)GlobalLock(hglbPaste);
            if (lpstrPaste != NULL)
            {
               //replace text
               bool blnMultiCell = false;
               std::string strBegin, strEnd;
               std::string strNew = (char*)(lpstrPaste);
               GtCellData *pCurr = NULL;
               int iCurrRow, iCurrCol, m, iSubStrA, iSubStrB;
               iSubStrA = 0;
               iSubStrB = 0;

               QItemSelectionModel * ptrSelection = table->selectionModel();
               QModelIndexList arrIndexes = ptrSelection->selectedIndexes();
               int iLBRow, iLBCol, iUBRow, iUBCol;
               GetIndexRange(arrIndexes, iLBRow, iLBCol, iUBRow, iUBCol);

               GtCellData * pULCell = this->GetOrMakeCellPtr(iLBRow+1, iLBCol+1);
               if (!pULCell)
               {
                  return;
               }
               iCurrRow = iLBRow; iCurrCol = iLBCol;
               for (m = 0; m < strNew.size(); m++)
               {
                  if (strNew[m] == '\t')
                  {
                     iSubStrB = m;
                     pCurr = this->GetOrMakeCellPtr(iCurrRow + 1, iCurrCol + 1);
                     //then column
                     if (pCurr)
                     {
                        string strCell = strNew.substr(iSubStrA, (iSubStrB - iSubStrA));
                        pCurr->m_strFormula = (strCell.c_str());
                        iSubStrA = m + 1;
                        iSubStrB = m + 1;
                        blnMultiCell = true;
                     }
                     iCurrCol++;
                  }//end tab
                  if (strNew[m] == '\n')
                  {
                     iSubStrB = m;
                     pCurr = this->GetOrMakeCellPtr(iCurrRow + 1, iCurrCol + 1);
                     //then column
                     if (pCurr)
                     {
                        string strCell = strNew.substr(iSubStrA, (iSubStrB - iSubStrA));
                        pCurr->m_strFormula = (strCell.c_str());
                        iSubStrA = m + 1;
                        iSubStrB = m + 1;
                        blnMultiCell = true;
                     }
                     iCurrRow++;
                     iCurrCol = iLBCol;
                  }//end return
                   //see if end of string

               }//end for loop through strNew
                //if only a single cell with no carriage returns
               if (blnMultiCell == false)
               {
                  pCurr = this->GetOrMakeCellPtr(iCurrRow + 1, iCurrCol + 1);
                  //then column
                  if (pCurr)
                  {
                     pCurr->m_strFormula = (strNew.c_str());
                  }
               }
            }//end string check
            GlobalUnlock(hglbPaste);
         }
         CloseClipboard();

         this->UpdateCalcSheet();
      };

      //!Event handler for CTRL + DELETE keystroke event
      void QTSpreadSheet::OnDelete()
      {
         //then cut
         string strNull;

         QItemSelectionModel * ptrSelection = table->selectionModel();
         QModelIndexList arrIndexes = ptrSelection->selectedIndexes();
         int iLBRow, iLBCol, iUBRow, iUBCol;
         GetIndexRange(arrIndexes, iLBRow, iLBCol, iUBRow, iUBCol);

         if ((iLBRow == iUBRow) && (iLBCol == iUBCol))
         {//single cell selected
            GtCellData * pULCell = this->GetCellPtr(iLBRow+1, iLBCol+1);
            if (pULCell)
            {
               pULCell->m_strFormula = "";
               pULCell->m_strData = "";
            }
         }
         else {

            for (int i = iLBRow; i <= iUBRow; i++)
            {
               for (int j = iLBCol; j <= iUBCol; j++)
               {
                  GtCellData *pCurr = this->GetCellPtr(i+1, j+1);
                  if (pCurr)
                  {
                     pCurr->m_strFormula = "";
                     pCurr->m_strData = "";                     
                  }

               };//end loop cols

            };//end loop rows

         };
         return;

      };


   };//end namespace GtCalc

};//end namespace GT