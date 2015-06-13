#-------------------------------------------------
#
# Project created by QtCreator 2015-06-10T00:19:44
#
#-------------------------------------------------

QT       += network

QT       -= gui

TARGET = BroadcastLib002
TEMPLATE = lib
CONFIG += staticlib

SOURCES += \
    broadcaster.cpp \
    broadcasterimpl.cpp \
    broadcasterproxy.cpp \
    broadcasterstub.cpp \
    broadcastlib.cpp \
    broadcastserver.cpp \
    subscriber.cpp

HEADERS += \
    broadcaster.h \
    broadcasterimpl.h \
    broadcasterproxy.h \
    broadcasterstub.h \
    broadcastlib.h \
    broadcastserver.h \
    subscriber.h
unix {
    target.path = /usr/lib
    INSTALLS += target
}
