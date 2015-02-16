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

win32
{
    INCLUDEPATH += C:\Users\mygnu\Documents\GitHub\PDFWriter\Headers\FreeType
    INCLUDEPATH += C:\Users\mygnu\Documents\GitHub\PDFWriter\Headers\LibTiff
    INCLUDEPATH += C:\Users\mygnu\Documents\GitHub\PDFWriter\Headers\ZLib
    INCLUDEPATH += C:\Users\mygnu\Documents\GitHub\PDFWriter\Headers\PDFWriter

    LIBS += -LC:\Users\mygnu\Documents\GitHub\PDFWriter\Binaries\x64\Release -lFreeType
    LIBS += -LC:\Users\mygnu\Documents\GitHub\PDFWriter\Binaries\x64\Release -llibTiff
    LIBS += -LC:\Users\mygnu\Documents\GitHub\PDFWriter\Binaries\x64\Release -lpdfwriter
    LIBS += -LC:\Users\mygnu\Documents\GitHub\PDFWriter\Binaries\x64\Release -lzlib

}


SOURCES += main.cpp\
        mainwindow.cpp \
    prefdialog.cpp \
    cablecover.cpp \
    values.cpp \
    pdfgenerator.cpp

HEADERS  += mainwindow.h \
    prefdialog.h \
    cablecover.h \
    values.h \
    pdfgenerator.h


FORMS    += mainwindow.ui \
    prefdialog.ui \
    cablecover.ui

DISTFILES +=

