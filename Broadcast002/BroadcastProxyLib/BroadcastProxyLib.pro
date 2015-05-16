#-------------------------------------------------
#
# Project created by QtCreator 2015-05-14T23:48:58
#
#-------------------------------------------------

QT       += network

QT       -= gui

TARGET = BroadcastProxyLib
TEMPLATE = lib
CONFIG += staticlib

SOURCES += broadcastproxylib.cpp

HEADERS += broadcastproxylib.h
unix {
    target.path = /usr/lib
    INSTALLS += target
}
