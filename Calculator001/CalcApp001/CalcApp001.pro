#-------------------------------------------------
#
# Project created by QtCreator 2015-06-14T14:55:56
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = CalcApp001
TEMPLATE = app


SOURCES += main.cpp\
        widget.cpp

HEADERS  += widget.h

win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../CalcLib001/release/ -lCalcLib001
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../CalcLib001/debug/ -lCalcLib001
else:unix: LIBS += -L$$OUT_PWD/../CalcLib001/ -lCalcLib001

INCLUDEPATH += $$PWD/../CalcLib001
DEPENDPATH += $$PWD/../CalcLib001

win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../CalcLib001/release/libCalcLib001.a
else:win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../CalcLib001/debug/libCalcLib001.a
else:win32:!win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../CalcLib001/release/CalcLib001.lib
else:win32:!win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../CalcLib001/debug/CalcLib001.lib
else:unix: PRE_TARGETDEPS += $$OUT_PWD/../CalcLib001/libCalcLib001.a
