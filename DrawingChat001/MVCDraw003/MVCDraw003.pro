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
    linewidthdialog.cpp \
    model/drawingsettings.cpp \
    model/freehand.cpp \
    model/freehandfactory.cpp \
    model/rectangle.cpp \
    model/rectanglefactory.cpp \
    model/shape.cpp \
    model/shapefactory.cpp \
    model/shapespace.cpp \
    model/shapevisitor.cpp \
    view/drawvisitor.cpp \
    controller/drawingcontroller.cpp \
    view/drawingview.cpp \
    controller/freehandmaker.cpp \
    controller/rectanglemaker.cpp \
    controller/shapemaker.cpp

HEADERS  += mainwindow.h \
    linewidthdialog.h \
    model/drawingsettings.h \
    model/freehand.h \
    model/freehandfactory.h \
    model/rectangle.h \
    model/rectanglefactory.h \
    model/shape.h \
    model/shapefactory.h \
    model/shapespace.h \
    model/shapevisitor.h \
    view/drawvisitor.h \
    controller/drawingcontroller.h \
    view/drawingview.h \
    controller/freehandmaker.h \
    controller/rectanglemaker.h \
    controller/shapemaker.h

INCLUDEPATH += . \
    controller \
    model \
    view

