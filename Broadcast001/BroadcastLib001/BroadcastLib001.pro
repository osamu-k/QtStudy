#-------------------------------------------------
#
# Project created by QtCreator 2015-05-10T15:01:11
#
#-------------------------------------------------

QT       += network

QT       -= gui

TARGET = BroadcastLib001
TEMPLATE = lib
CONFIG += staticlib

QMAKE_CXXFLAGS += -std=c++11 -stdlib=libc++

SOURCES += broadcastlib001.cpp \
    broadcastserver.cpp \
    broadcastclient.cpp

HEADERS += broadcastlib001.h \
    broadcastserver.h \
    broadcastclient.h
unix {
    target.path = /usr/lib
    INSTALLS += target
}
