#-------------------------------------------------
#
# Project created by QtCreator 2015-06-14T16:40:14
#
#-------------------------------------------------

QT       += widgets

TARGET = CalcLib006
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
