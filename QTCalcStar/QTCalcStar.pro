# ----------------------------------------------------
# QTCalcStar.pro
# ----------------------------------------------------

TEMPLATE = app
TARGET = QTCalcStar

QT += core xml gui widgets printsupport

# DEFINES += WIN64 QT_DLL QT_WIDGETS_LIB QT_XML_LIB QT_PRINTSUPPORT_LIB
# DEFINES += WIN32 QT_DLL QT_WIDGETS_LIB QT_XML_LIB QT_PRINTSUPPORT_LIB

# CONFIG += debug
# DESTDIR = ../Win32/Debug

# ----------------------------------------------------

# INCLUDEPATH += \
# ./HTL

# LIBS += \
# -L"$(OutDir)" \
# -lHTLV20Debug

# DEPENDPATH += .
# MOC_DIR += ./GeneratedFiles/$(ConfigurationName)
# OBJECTS_DIR += debug
# UI_DIR += ./GeneratedFiles
# RCC_DIR += ./GeneratedFiles

# ----------------------------------------------------

include(QTCalcStar.pri)

