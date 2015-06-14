#-------------------------------------------------
#
# Project created by QtCreator 2015-06-14T16:21:11
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = CalcApp005
TEMPLATE = app


SOURCES += main.cpp\
        widget.cpp

HEADERS  += widget.h

win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../CalcLib005/release/ -lCalcLib005
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../CalcLib005/debug/ -lCalcLib005
else:unix: LIBS += -L$$OUT_PWD/../CalcLib005/ -lCalcLib005

INCLUDEPATH += $$PWD/../CalcLib005
DEPENDPATH += $$PWD/../CalcLib005

win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../CalcLib005/release/libCalcLib005.a
else:win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../CalcLib005/debug/libCalcLib005.a
else:win32:!win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../CalcLib005/release/CalcLib005.lib
else:win32:!win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../CalcLib005/debug/CalcLib005.lib
else:unix: PRE_TARGETDEPS += $$OUT_PWD/../CalcLib005/libCalcLib005.a
