#-------------------------------------------------
#
# Project created by QtCreator 2015-06-14T17:08:46
#
#-------------------------------------------------

QT       += widgets

TARGET = CalcLib007
TEMPLATE = lib
CONFIG += staticlib

SOURCES += \
    calculator.cpp

HEADERS += \
    calculator.h
unix {
    target.path = /usr/lib
    INSTALLS += target
}
