#-------------------------------------------------
#
# Project created by QtCreator 2015-06-14T14:50:16
#
#-------------------------------------------------

QT       += widgets

TARGET = CalcLib001
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
