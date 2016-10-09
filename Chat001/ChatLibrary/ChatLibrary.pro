#-------------------------------------------------
#
# Project created by QtCreator 2016-10-09T22:21:16
#
#-------------------------------------------------

QT       -= gui

TARGET = ChatLibrary
TEMPLATE = lib
CONFIG += staticlib

DEFINES += CHATLIBRARY_LIBRARY

SOURCES += chatlibrary.cpp \
    messagebuffer.cpp

HEADERS += chatlibrary.h\
        chatlibrary_global.h \
    messagebuffer.h

unix {
    target.path = /usr/lib
    INSTALLS += target
}
