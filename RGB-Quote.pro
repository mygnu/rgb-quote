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


SOURCES += main.cpp\
        mainwindow.cpp \
    prefdialog.cpp \
    cablecover.cpp \
    values.cpp

HEADERS  += mainwindow.h \
    prefdialog.h \
    cablecover.h \
    values.h


FORMS    += mainwindow.ui \
    prefdialog.ui \
    cablecover.ui

DISTFILES += \
    settings.conf
