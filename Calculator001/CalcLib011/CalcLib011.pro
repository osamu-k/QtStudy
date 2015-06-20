#-------------------------------------------------
#
# Project created by QtCreator 2015-06-20T21:51:25
#
#-------------------------------------------------

QT       += widgets

TARGET = CalcLib011
TEMPLATE = lib
CONFIG += staticlib

SOURCES += \
    calculator.cpp

HEADERS += \
    calculator.h \
    calcstate.h
unix {
    target.path = /usr/lib
    INSTALLS += target
}
