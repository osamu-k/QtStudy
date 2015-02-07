#-------------------------------------------------
#
# Project created by QtCreator 2015-01-18T09:24:17
#
#-------------------------------------------------

QT       += core gui network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Drawing01
TEMPLATE = app


SOURCES += main.cpp\
        drawingpad.cpp \
    canvas.cpp \
    shape.cpp \
    polyline.cpp \
    colorselector.cpp \
    widthselector.cpp \
    listener.cpp \
    serversocket.cpp \
    bytearraysocket.cpp

HEADERS  += drawingpad.h \
    canvas.h \
    shape.h \
    polyline.h \
    colorselector.h \
    widthselector.h \
    listener.h \
    serversocket.h \
    bytearraysocket.h

DISTFILES += \
    license.txt
