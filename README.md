# QtCalcStar.codeproject

QtCalcStar is an adaptation of the GtCalc engine with a QT Spreadsheet interface. It is based on the QT Spreadsheet supplied from their website.

- Author: [Anthony Daniels](https://www.codeproject.com/Members/trident99)
- Email: AnthonyDaniels99@gmail.com
- Project page : https://www.codeproject.com/Tips/1226512/QtCalcStar-A-QT-Cplusplus-Spreadsheet-and-Workbook

## Introduction

QtCalcStar is an adaptation of the GtCalc engine with a QT Spreadsheet interface. It is based on the QT Spreadsheet supplied from their website.

- http://doc.qt.io/qt-5/qtwidgets-itemviews-spreadsheet-example.html
- https://www.codeproject.com/Articles/1162290/GtCalc-A-Cplusplus-Spreadsheet-Control-for-GT-Graphical-User-Interface-Library

As an engineer, I am constantly in need of embedding spreadsheet functionality into my applications. QtCalcStar is intended to provide the user a Microsoft Excel equivalent spreadsheet control and function evaluator. The function evaluator used in this library is derived from the CalcStar engine. The function set covers most of the major Excel math functions that operate on either individual cells or a range of cells. The functions provided are as given below.

## Basic Functions (Calcstar)

| Name           | Signature | Name                  | Signature |
|----------------|-----------|-----------------------|-----------|
| Add            | +         | Boolean And           | &&        |
| Subtract       | -         | Boolean Equal         | ==        |
| Multiply       | *         | Boolean Not           | !         |
| Divide         | /         | Boolean Not Equal     | !=        |
| ponential      | exp       | Boolean Or            | ||        |
| Power          | pow       | Greater Than          | >         |
| Natural Log    | ln        | Greater Than or Equal | >=        |
| Log2           | log2      | Less Than             | <         |
| Log10          | log10     | Less Than or Equal    | <=        |
| Absolute Value | abs       | Ceiling               | ceil      |
| Square Root    | sqrt      | Floor                 | floor     |
| Truncate       | trunc     |                       |           |

## Trigonometric Functions (CalcStar)

| Name        | Signature | Name            | Signature |
|-------------|-----------|-----------------|-----------|
| Sine        | sin       | Arc Sine        | asin      |
| Cosine      | cos       | Arc Cosine      | acos      |
| Tangent     | tan       | Arc Tangent     | atan      |
| Hyp Sine    | sinh      | Arc Hyp Sine    | asinh     |
| Hyp Cosine  | cosh      | Arc Hyp Cosine  | acosh     |
| Hyp Tangent | tanh      | Arc Hyp Tangent | atanh     |

## Additional Math Functions (Excel)

| Name      | Signature | Name          | Signature |
|-----------|-----------|---------------|-----------|
| Count     | count     | Odd           | odd       |
| Degrees   | deg       | PI            | pi        |
| E Number  | e         | Radians       | rad       |
| Even      | even      | RowCol (cell) | rc        |
| Factorial | fact      | Sign          | sign      |
| Maximum   | max       | St. Deviation | stdev     |
| Mean      | mean      | Sum           | sum       |
| Median    | median    | Variance      | var       |
| Minimum   | min       |               |           |
| Modulo    | mod       |               |           |

## Using QtCalcStar

Using QtCalcStar is very simple. In any application that uses QT as the user interface, insert the following code into the InitializeControls() method of the dialog that is intended as the parent of the spreadsheet. You set the control size and add it to the subwidget collection for that dialog.

- In header file (.h)
```h
private:
	Ui::QTCalcStarClass ui;
	QApplication * m_ptrApp;
	QTWorkbook * m_ptrWorkbook;
```

- In .cpp file
```cpp
m_ptrWorkbook = new QTWorkbook(ptrParentWidget);
m_ptrWorkbook->OnResizeAll();
m_ptrWorkbook->show();
```

QTWorkbook is the main object that contains a spreadsheet. A Workbook has a collection of QTSpreadSheets. The rows, columns, and cells are contained in maps that are index based. There are accessor functions for getting individual cells, or the user can use r#c# notation. The user can also access selected ranges of cells through the table Selection Model. Spreadsheet recalculation is done automatically whenever a cell edit is completed, but you can manually trigger a spreadsheet re-calc with the UpdateCalcSheet() method. When this method is triggered, the sheet cycles through the cells doing full tokenization, compilation, and evaluation of each cell. Each cell has its own GtFunctionEvaluator responsible for all calculations of that cell. The GtFunctionEvaluator is a modified version of the CSFunctionEvaluator from CalcStar. Modifications needed to be made to allow for evaluation of ranges of cells. Remember, CalcStar compiles infix notation equations into a RPN calculation stack for single pass evaluation.

## Equation Sytax

GtCalc is built on top of CalcStar. So any math function in CalcStar is valid. For more information on Calcstar, please refer to the following article:

https://www.codeproject.com/Tips/747223/CalcStar-A-Cplusplus-Math-Expression-Evaluator

If functions like sum refer to a range of cells, the syntax is sum(r1c1:r2c2). Single cell ranges are allowed but are the full range syntax (e.g., r1c1:r1c1). You can also use cell references directly in a function like Excel does. For example =r1c23 + r2c2 is a legal function. Referencing different pages would look like =sum(SheetName:r1c1:r15c1). Below is a screenshot of a multi spreadsheet test application provided.

![](QTCalcStar/Documentation/QTCalcStar%20Test%20Application%20GUI.jpg)

## License

- This article, along with any associated source code and files, is licensed under [The BSD License](http://www.opensource.org/licenses/bsd-license.php)

## About the Author

- [trident99](https://www.codeproject.com/Members/trident99)

## :construction: Modifing

- :warning: The current project is not be built. :yum:
- modifiing now :scream:
