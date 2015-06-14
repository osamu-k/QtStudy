#-------------------------------------------------
#
# Project created by QtCreator 2015-06-14T18:03:59
#
#-------------------------------------------------

QT       += widgets

TARGET = CalcLib009
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
