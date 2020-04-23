# ----------------------------------------------------
# This file is generated by the Qt Visual Studio Add-in.
# ------------------------------------------------------

TEMPLATE = app
TARGET = CCLook
DESTDIR = ../Win32/Release
QT += core gui xmlpatterns opengl widgets
CONFIG += release
DEFINES += QT_LARGEFILE_SUPPORT QT_DLL QT_OPENGL_LIB QT_XMLPATTERNS_LIB
INCLUDEPATH += ./GeneratedFiles \
    . \
    ./GeneratedFiles/Release
LIBS += -lopengl32 \
    -lglu32
DEPENDPATH += .
MOC_DIR += ./GeneratedFiles/release
OBJECTS_DIR += release
UI_DIR += ./GeneratedFiles
RCC_DIR += ./GeneratedFiles
TRANSLATIONS += cclook_zh.ts
#win32:RC_FILE = CCLook.rc
HEADERS += ./globaldefines.h \
    ./cclook.h \
    ./qcclstat.h \
    ./qaboutdlg.h \
    ./qcclookscore.h \
    ./qcclooktimebar.h \
    ./qcclooktext.h \
    ./qcclookline.h \
    ./qcclscene.h \
    ./qcclookitem.h \
    ./qscoredlg.h \
    ./resource.h
SOURCES += ./cclook.cpp \
    ./main.cpp \
    ./qaboutdlg.cpp \
    ./qcclookitem.cpp \
    ./qcclookline.cpp \
    ./qcclookscore.cpp \
    ./qcclooktext.cpp \
    ./qcclooktimebar.cpp \
    ./qcclscene.cpp \
    ./qcclstat.cpp \
    ./qscoredlg.cpp
FORMS += ./cclook.ui \
    ./qaboutdlg.ui \
    ./qscoredlg.ui
TRANSLATIONS += ./cclook_zh.ts
RESOURCES += \
    resouce.qrc
