#-------------------------------------------------
#
# Project created by QtCreator 2015-05-10T20:46:43
#
#-------------------------------------------------

QT       += network

QT       -= gui

TARGET = BroadcastLib002
TEMPLATE = lib
CONFIG += staticlib

SOURCES += broadcastlib002.cpp \
    broadcasterimpl.cpp \
    broadcasterstub.cpp \
    broadcasterproxy.cpp \
    broadcasterserver.cpp

HEADERS += broadcastlib002.h \
    broadcaster.h \
    broadcasterimpl.h \
    broadcasterstub.h \
    broadcasterproxy.h \
    broadcasterserver.h
unix {
    target.path = /usr/lib
    INSTALLS += target
}
