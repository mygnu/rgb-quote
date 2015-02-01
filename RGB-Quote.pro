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
    baseitem.cpp \
    prefdialog.cpp \
    cablecover.cpp \

HEADERS  += mainwindow.h \
    baseitem.h \
    prefdialog.h \
    cablecover.h \
    jsoncons/json.hpp \
    jsoncons/json1.hpp \
    jsoncons/json2.hpp \
    jsoncons/json_deserializer.hpp \
    jsoncons/json_exception.hpp \
    jsoncons/json_filter.hpp \
    jsoncons/json_input_handler.hpp \
    jsoncons/json_output_handler.hpp \
    jsoncons/json_reader.hpp \
    jsoncons/json_serializer.hpp \
    jsoncons/json_structures.hpp \
    jsoncons/json_type_traits.hpp \
    jsoncons/jsoncons.hpp \
    jsoncons/jsoncons_config.hpp \
    jsoncons/output_format.hpp \
    jsoncons/parse_error_handler.hpp

FORMS    += mainwindow.ui \
    prefdialog.ui \
    cablecover.ui
