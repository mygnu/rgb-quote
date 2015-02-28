#-------------------------------------------------
#
# Project created by QtCreator 2015-01-28T18:36:22
#
#-------------------------------------------------

QT       += core gui
CONFIG += c++11

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = RGB-Quote
TEMPLATE = app


win32 {
    INCLUDEPATH += "$$PWD/PDFWriter/Headers/FreeType"
    INCLUDEPATH += "$$PWD/PDFWriter/Headers/LibTiff"
    INCLUDEPATH += "$$PWD/PDFWriter/Headers/LibJpeg"
    INCLUDEPATH += "$$PWD/PDFWriter/Headers/ZLib"
    INCLUDEPATH += "$$PWD/PDFWriter/Headers/PDFWriter"

    CONFIG( debug, debug|release ) {
    # debug
    LIBS += -L"$$PWD/PDFWriter/debug" -lFreeType
    LIBS += -L"$$PWD/PDFWriter/debug" -llibTiff
    LIBS += -L"$$PWD/PDFWriter/debug" -lzlib
    LIBS += -L"$$PWD/PDFWriter/debug" -lpdfwriter
    LIBS += -L"$$PWD/PDFWriter/debug" -lLibJpeg
} else {
    # release#
    LIBS += -L"$$PWD/PDFWriter/release" -lFreeType
    LIBS += -L"$$PWD/PDFWriter/release" -llibTiff
    LIBS += -L"$$PWD/PDFWriter/release" -lzlib
    LIBS += -L"$$PWD/PDFWriter/release" -lpdfwriter
    LIBS += -L"$$PWD/PDFWriter/release" -lLibJpeg
    }
}


SOURCES += main.cpp\
        mainwindow.cpp \
    cablecover.cpp \
    pdfgenerator.cpp \
    ccprefdialog.cpp \
    ccvalues.cpp

HEADERS  += \
    cablecover.hh \
    mainwindow.hh \
    pdfgenerator.hh \
    ccprefdialog.hh \
    ccvalues.hh


FORMS    += mainwindow.ui \
    cablecover.ui \
    ccprefdialog.ui

RC_FILE = icon.rc



