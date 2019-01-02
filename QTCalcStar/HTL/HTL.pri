# -------------------------------------------------
# HTL.pri
# -------------------------------------------------

# -------------------------------------------------
# HTL

INCLUDEPATH += .

HEADERS += \
modHtlArchive.h \
modHtlAtomic.h \
modHtlBase.h \
modHtlBiDirContainer.h \
modHtlContainer.h \
modHtlGlobal.h \
modHtlGUID.h \
modHtlLibRefs.h \
modHtlMacro.h \
modHtlMath.h \
modHtlObject.h \
modHtlRandNumGen.h \
modHtlSignalSlot.h \
modHtlString.h \
modHtlTest.h \
modHtlThread.h \
modHtlTime.h

# -------------------------------------------------
# HTL/HtlArchive

INCLUDEPATH += ./HtlArchive

HEADERS += \
HtlArchive/HtlAttribute.h \
HtlArchive/HtlComment.h \
HtlArchive/HtlDocument.h \
HtlArchive/HtlElement.h \
HtlArchive/HtlMemVar.h \
HtlArchive/HtlMemVar2.h \
HtlArchive/HtlMemVarItem.h \
HtlArchive/HtlNode.h \
HtlArchive/HtlProcess.h

SOURCES += \
HtlArchive/HtlAttribute.cpp \
HtlArchive/HtlComment.cpp \
HtlArchive/HtlDocument.cpp \
HtlArchive/HtlElement.cpp \
HtlArchive/HtlMemVar.cpp \
HtlArchive/HtlMemVar2.cpp \
HtlArchive/HtlMemVarItem.cpp \
HtlArchive/HtlNode.cpp \
HtlArchive/HtlProcess.cpp

# -------------------------------------------------
# HTL/HtlArchive/ArchBinary

INCLUDEPATH += ./HtlArchive/ArchBinary

HEADERS += \
HtlArchive/ArchBinary/HtlBinReader.h \
HtlArchive/ArchBinary/HtlBinStructs.h \
HtlArchive/ArchBinary/HtlBinWriter.h

SOURCES += \
HtlArchive/ArchBinary/HtlBinReader.cpp \
HtlArchive/ArchBinary/HtlBinStructs.cpp \
HtlArchive/ArchBinary/HtlBinWriter.cpp



