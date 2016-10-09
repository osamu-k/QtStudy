#-------------------------------------------------
#
# Project created by QtCreator 2016-10-10T00:30:29
#
#-------------------------------------------------

QT       += core gui websockets

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = ChatClientWS
TEMPLATE = app


SOURCES += main.cpp\
        chatclientwswidget.cpp \
    chatclientws.cpp

HEADERS  += chatclientwswidget.h \
    chatclientws.h

CONFIG += mobility
MOBILITY = 

