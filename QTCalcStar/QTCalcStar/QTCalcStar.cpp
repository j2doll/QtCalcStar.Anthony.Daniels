
#define HTL_DLLEXPORT
#include "QTCalcStar.h"
#include "GtCellData.h"
#include "QTWorkbook.h"
#include "QTSpreadSheet.h"
#include <QResizeEvent>
#include <QApplication>
using namespace GT::GtCalc;
namespace GT
{
   namespace GtCalc
   {


      QTCalcStar::QTCalcStar(QWidget *parent)
         : QMainWindow(parent)
      {
         ui.setupUi(this);
         m_ptrWorkbook = new QTWorkbook(ui.centralWidget);
         m_ptrWorkbook->OnResizeAll();
         m_ptrWorkbook->show();

         connect(ui.actionExit, SIGNAL(triggered()), this, SLOT(OnAppExit()));

      }


      void QTCalcStar::SetAppPtr(QApplication* ptrApp)
      {
         m_ptrApp = ptrApp;
      };


      void QTCalcStar::OnAppExit(void)
      {
         if (m_ptrApp)
         {
            m_ptrApp->quit();
         }

      };

      void QTCalcStar::resizeEvent(QResizeEvent* event)
      {
         QMainWindow::resizeEvent(event);
         // Your code here.
         QSize sz0 = event->size();
         sz0.setHeight(sz0.height() - 25);
         sz0.setWidth(sz0.width() - 25);
         m_ptrWorkbook->resize(sz0);

         m_ptrWorkbook->OnResizeAll();


      }

   }//end namespace GtCalc
}//end namespace GT