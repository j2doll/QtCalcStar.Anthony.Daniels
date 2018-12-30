#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_QTCalcStar.h"
class QApplication;

namespace GT
{
   namespace GtCalc
   {
      class QTWorkbook;

      class QTCalcStar : public QMainWindow
      {
         Q_OBJECT

      public:
         QTCalcStar(QWidget *parent = Q_NULLPTR);
         void SetAppPtr(QApplication* ptrApp);

         public slots:
         void OnAppExit(void);
         void resizeEvent(QResizeEvent* event);

      private:
         Ui::QTCalcStarClass ui;
         QApplication * m_ptrApp;
         QTWorkbook * m_ptrWorkbook;
      };

   }//end namespace GtCalc
}//end namespace GT
