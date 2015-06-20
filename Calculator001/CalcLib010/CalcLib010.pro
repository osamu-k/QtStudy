#-------------------------------------------------
#
# Project created by QtCreator 2015-06-18T00:26:27
#
#-------------------------------------------------

QT       += widgets

TARGET = CalcLib010
TEMPLATE = lib
CONFIG += staticlib

SOURCES += \
    calculator.cpp

HEADERS +=\
    calculator.h

unix {
    target.path = /usr/lib
    INSTALLS += target
}
