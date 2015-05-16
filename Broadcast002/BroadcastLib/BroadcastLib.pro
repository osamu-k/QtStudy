#-------------------------------------------------
#
# Project created by QtCreator 2015-05-12T00:01:21
#
#-------------------------------------------------

QT       += network

QT       -= gui

TARGET = BroadcastLib
TEMPLATE = lib
CONFIG += staticlib

SOURCES += broadcastlib.cpp \
    broadcaster.cpp \
    subscriber.cpp \
    broadcasterimpl.cpp \
    broadcastserver.cpp \
    broadcasterstub.cpp \
    broadcasterproxy.cpp

HEADERS += broadcastlib.h \
    broadcaster.h \
    subscriber.h \
    broadcasterimpl.h \
    broadcastserver.h \
    broadcasterstub.h \
    broadcasterproxy.h
unix {
    target.path = /usr/lib
    INSTALLS += target
}
