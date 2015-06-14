#-------------------------------------------------
#
# Project created by QtCreator 2015-06-14T15:27:58
#
#-------------------------------------------------

QT       += widgets

TARGET = CalcLib003
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
