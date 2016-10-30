#-------------------------------------------------
#
# Project created by QtCreator 2016-10-29T22:28:08
#
#-------------------------------------------------

QT       -= gui
QT += network

TARGET = ChatLib
TEMPLATE = lib
CONFIG += staticlib

SOURCES += \
    chatclient.cpp \
    chatserver.cpp

HEADERS += \
    chatclient.h \
    chatserver.h
unix {
    target.path = /usr/lib
    INSTALLS += target
}
