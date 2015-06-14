#-------------------------------------------------
#
# Project created by QtCreator 2015-06-14T17:49:16
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = CalcApp008
TEMPLATE = app


SOURCES += main.cpp\
        widget.cpp

HEADERS  += widget.h

win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../CalcLib008/release/ -lCalcLib008
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../CalcLib008/debug/ -lCalcLib008
else:unix: LIBS += -L$$OUT_PWD/../CalcLib008/ -lCalcLib008

INCLUDEPATH += $$PWD/../CalcLib008
DEPENDPATH += $$PWD/../CalcLib008

win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../CalcLib008/release/libCalcLib008.a
else:win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../CalcLib008/debug/libCalcLib008.a
else:win32:!win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../CalcLib008/release/CalcLib008.lib
else:win32:!win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../CalcLib008/debug/CalcLib008.lib
else:unix: PRE_TARGETDEPS += $$OUT_PWD/../CalcLib008/libCalcLib008.a
