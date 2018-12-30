#define HTL_DLLEXPORT

#include "QTWorkbook.h"
#include "GtCellData.h"
#include "QTSpreadSheet.h"

namespace GT
{
   namespace GtCalc
   {

      QTWorkbook::QTWorkbook(QWidget *parent)
         : QWidget(parent)
      {
         ui.setupUi(this);
         setWindowFlags(Qt::FramelessWindowHint);

         this->SetupMenus();
         this->SetupControls();

      };

      QTWorkbook::~QTWorkbook()
      {

      };


      void QTWorkbook::SetupMenus(void)
      {
         m_ptrWorkbookMenu = new QMenuBar(this);
         m_ptrWorkbookMenu->move(5, 5);

         QMenu * ptrSheetMenu = new QMenu(m_ptrWorkbookMenu);
         ptrSheetMenu->setTitle("Workbook");
         m_ptrWorkbookMenu->addMenu(ptrSheetMenu);

         m_ptrSheetAdd = new QAction("Add Sheet", ptrSheetMenu);
         ptrSheetMenu->addAction(m_ptrSheetAdd);
         connect(m_ptrSheetAdd, SIGNAL(triggered()), this, SLOT(OnSheetAdd()));

         m_ptrSheetDelete = new QAction("Delete Sheet", ptrSheetMenu);
         ptrSheetMenu->addAction(m_ptrSheetDelete);
         connect(m_ptrSheetDelete, SIGNAL(triggered()), this, SLOT(OnSheetDelete()));

         m_ptrSheetDeleteALL = new QAction("Delete ALL Sheets", ptrSheetMenu);
         ptrSheetMenu->addAction(m_ptrSheetDeleteALL);
         connect(m_ptrSheetDeleteALL, SIGNAL(triggered()), this, SLOT(OnSheetDeleteALL()));

      };

      void QTWorkbook::SetupControls(void)
      {
         QTSpreadSheet * ptrNewSheet = new QTSpreadSheet("Sheet01", 50, 50, ui.tabWorkSheets);
         ui.tabWorkSheets->addTab(ptrNewSheet, "Sheet01");
      };

      int QTWorkbook::CountSheets(void)
      {
         return ui.tabWorkSheets->count();
      };


      QTSpreadSheet *  QTWorkbook::GetSheet(int index)
      {
         if ((index >= 0) && (index < ui.tabWorkSheets->count()))
            return dynamic_cast<QTSpreadSheet *>(ui.tabWorkSheets->widget(index));
         else
            return NULL;
      };
      QTSpreadSheet *  QTWorkbook::GetSheet(QString  strName)
      {
         int numSheets = ui.tabWorkSheets->count();
         for (int i = 0; i < numSheets;i++)
         {
            QWidget * ptrCurr = ui.tabWorkSheets->widget(i);
            QString strTitle = ptrCurr->objectName();
            if (strName == strTitle)
            {
               return dynamic_cast<QTSpreadSheet *>(ui.tabWorkSheets->widget(i));
            }
         }
         return NULL;
      };

      void QTWorkbook::SheetAdd(QString strName)
      {
         QTSpreadSheet * ptrNewSheet = new QTSpreadSheet(strName, 50, 50, ui.tabWorkSheets);
         ui.tabWorkSheets->addTab(ptrNewSheet, strName);

      };

      void QTWorkbook::SheetDelete(QString strName)
      {
         int numSheets = ui.tabWorkSheets->count();
         for (int i = 0; i < numSheets;i++)
         {
            QWidget * ptrCurr = ui.tabWorkSheets->widget(i);
            QString strTitle = ptrCurr->objectName();
            if (strName == strTitle)
            {
               ui.tabWorkSheets->removeTab(i);
            }
         }
         return;
      };

      void QTWorkbook::SheetDeleteALL(QString strName)
      {
         int numSheets = ui.tabWorkSheets->count();
         for (int i = 0; i < numSheets;i++)
         {
            ui.tabWorkSheets->removeTab(0);
         }
         return;
      };

      void QTWorkbook::OnSheetAdd(void)
      {
         int numSheets = ui.tabWorkSheets->count();
         QString strName = "Sheet" + QString::number(numSheets);

         QTSpreadSheet * ptrNewSheet = new QTSpreadSheet(strName, 50, 50, ui.tabWorkSheets);
         ui.tabWorkSheets->addTab(ptrNewSheet, strName);

      };

      void QTWorkbook::OnSheetDelete(void)
      {
         int index = ui.tabWorkSheets->currentIndex();
         ui.tabWorkSheets->removeTab(index);
      };

      void QTWorkbook::OnSheetDeleteALL(void)
      {
         int numSheets = ui.tabWorkSheets->count();
         for (int i = 0; i < numSheets;i++)
         {
            ui.tabWorkSheets->removeTab(0);
         }
         return;
      };

      void QTWorkbook::OnResizeAll(void)
      {
         QSize sz0 = this->size();
         sz0.setHeight(sz0.height() - 60);
         sz0.setWidth(sz0.width() - 5);
         ui.tabWorkSheets->resize(sz0);
         int numSheets = this->CountSheets();
         for (int i = 0; i < numSheets; i++)
         {

            QTSpreadSheet * ptrCurr = this->GetSheet(i);
            if (ptrCurr)
            {
               ptrCurr->OnResize(sz0);
            }
         }

      };

   };//end namespace GtCalc

};//end namespace GT