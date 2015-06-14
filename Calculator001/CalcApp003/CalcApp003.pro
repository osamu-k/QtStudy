#-------------------------------------------------
#
# Project created by QtCreator 2015-06-14T15:38:11
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = CalcApp003
TEMPLATE = app


SOURCES += main.cpp\
        widget.cpp

HEADERS  += widget.h

win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../CalcLib003/release/ -lCalcLib003
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../CalcLib003/debug/ -lCalcLib003
else:unix: LIBS += -L$$OUT_PWD/../CalcLib003/ -lCalcLib003

INCLUDEPATH += $$PWD/../CalcLib003
DEPENDPATH += $$PWD/../CalcLib003

win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../CalcLib003/release/libCalcLib003.a
else:win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../CalcLib003/debug/libCalcLib003.a
else:win32:!win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../CalcLib003/release/CalcLib003.lib
else:win32:!win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../CalcLib003/debug/CalcLib003.lib
else:unix: PRE_TARGETDEPS += $$OUT_PWD/../CalcLib003/libCalcLib003.a
