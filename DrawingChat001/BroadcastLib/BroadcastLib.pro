#-------------------------------------------------
#
# Project created by QtCreator 2015-05-10T15:01:11
#
#-------------------------------------------------

QT       += network

QT       -= gui

TARGET = BroadcastLib
TEMPLATE = lib
CONFIG += staticlib

QMAKE_CXXFLAGS += -std=c++11 -stdlib=libc++

SOURCES += \
    broadcastserver.cpp \
    broadcastclient.cpp \
    bytearraytransmitter.cpp

HEADERS += \
    broadcastserver.h \
    broadcastclient.h \
    bytearraytransmitter.h
unix {
    target.path = /usr/lib
    INSTALLS += target
}
