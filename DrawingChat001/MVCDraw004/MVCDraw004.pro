#-------------------------------------------------
#
# Project created by QtCreator 2015-06-09T00:01:56
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = MVCDraw004
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    controller/drawingcontroller.cpp \
    controller/freehandmaker.cpp \
    controller/rectanglemaker.cpp \
    controller/shapemaker.cpp \
    model/drawingsettings.cpp \
    model/freehand.cpp \
    model/freehandfactory.cpp \
    model/rectangle.cpp \
    model/rectanglefactory.cpp \
    model/shape.cpp \
    model/shapefactory.cpp \
    model/shapespace.cpp \
    model/shapevisitor.cpp \
    view/drawingview.cpp \
    view/drawvisitor.cpp \
    linewidthdialog.cpp \
    view/scrollview.cpp

HEADERS  += mainwindow.h \
    controller/drawingcontroller.h \
    controller/freehandmaker.h \
    controller/rectanglemaker.h \
    controller/shapemaker.h \
    model/drawingsettings.h \
    model/freehand.h \
    model/freehandfactory.h \
    model/rectangle.h \
    model/rectanglefactory.h \
    model/shape.h \
    model/shapefactory.h \
    model/shapespace.h \
    model/shapevisitor.h \
    view/drawingview.h \
    view/drawvisitor.h \
    linewidthdialog.h \
    view/scrollview.h

INCLUDEPATH += . \
    controller \
    model \
    view
