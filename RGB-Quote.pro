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

    LIBS += -L"$$PWD/PDFWriter/Binaries" -lFreeType
    LIBS += -L"$$PWD/PDFWriter/Binaries" -llibTiff
    LIBS += -L"$$PWD/PDFWriter/Binaries" -lzlib
    LIBS += -L"$$PWD/PDFWriter/Binaries" -lpdfwriter
    LIBS += -L"$$PWD/PDFWriter/Binaries" -lLibJpeg
    CONFIG += static
}


SOURCES += main.cpp\
        mainwindow.cpp \
    prefdialog.cpp \
    cablecover.cpp \
    values.cpp \
    pdfgenerator.cpp

HEADERS  += \
    cablecover.hh \
    mainwindow.hh \
    pdfgenerator.hh \
    prefdialog.hh \
    values.hh


FORMS    += mainwindow.ui \
    prefdialog.ui \
    cablecover.ui



