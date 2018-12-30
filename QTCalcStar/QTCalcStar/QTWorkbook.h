#pragma once
#ifndef QT_WORKBOOK_H
#define QT_WORKBOOK_H

#include <modHtlBase.h>
using namespace HTL;

#include <QWidget>
#include <QMenuBar>
#include "ui_QTWorkbook.h"


namespace GT
{
   namespace GtCalc
   {

      class QTSpreadSheet;

      class QTWorkbook : public QWidget, public HtlBase
      {
         Q_OBJECT

      public:
         QTWorkbook(QWidget *parent = Q_NULLPTR);
         ~QTWorkbook();



      protected:
         virtual void SetupMenus(void);
         virtual void SetupControls(void);

      public:
         int CountSheets(void);
         QTSpreadSheet *  GetSheet(int index);
         QTSpreadSheet *  GetSheet(QString  strName);

         void SheetAdd(QString strName);
         void SheetDelete(QString strName);
         void SheetDeleteALL(QString strName);

         public slots:
         void OnSheetAdd(void);
         void OnSheetDelete(void);
         void OnSheetDeleteALL(void);
         void OnResizeAll(void);

      private:
         Ui::QTWorkbook ui;
         QMenuBar * m_ptrWorkbookMenu;
         QAction * m_ptrSheetAdd;
         QAction * m_ptrSheetDelete;
         QAction * m_ptrSheetDeleteALL;
      };

   };//end namespace GtCalc

};//end namespace GT

#endif