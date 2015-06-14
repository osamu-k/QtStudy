#-------------------------------------------------
#
# Project created by QtCreator 2015-06-14T17:45:40
#
#-------------------------------------------------

QT       += widgets

TARGET = CalcLib008
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
