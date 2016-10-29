#-------------------------------------------------
#
# Project created by QtCreator 2016-10-29T22:28:08
#
#-------------------------------------------------

QT       -= gui

TARGET = ChatLib
TEMPLATE = lib
CONFIG += staticlib

SOURCES += \
    chatclient.cpp

HEADERS += \
    chatclient.h
unix {
    target.path = /usr/lib
    INSTALLS += target
}
