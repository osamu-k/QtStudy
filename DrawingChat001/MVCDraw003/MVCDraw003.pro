#-------------------------------------------------
#
# Project created by QtCreator 2015-06-07T20:57:46
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = MVCDraw003
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    drawingpad.cpp \
    freehandmaker.cpp \
    linewidthdialog.cpp \
    rectanglemaker.cpp \
    shapemaker.cpp \
    model/drawingsettings.cpp \
    model/freehand.cpp \
    model/freehandfactory.cpp \
    model/rectangle.cpp \
    model/rectanglefactory.cpp \
    model/shape.cpp \
    model/shapefactory.cpp \
    model/shapespace.cpp \
    model/shapevisitor.cpp \
    view/drawvisitor.cpp

HEADERS  += mainwindow.h \
    drawingpad.h \
    freehandmaker.h \
    linewidthdialog.h \
    rectanglemaker.h \
    shapemaker.h \
    model/drawingsettings.h \
    model/freehand.h \
    model/freehandfactory.h \
    model/rectangle.h \
    model/rectanglefactory.h \
    model/shape.h \
    model/shapefactory.h \
    model/shapespace.h \
    model/shapevisitor.h \
    view/drawvisitor.h

INCLUDEPATH += . \
    model \
    view

