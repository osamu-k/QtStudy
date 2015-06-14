#-------------------------------------------------
#
# Project created by QtCreator 2015-06-14T15:20:18
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = CalcApp002
TEMPLATE = app


SOURCES += main.cpp\
        widget.cpp

HEADERS  += widget.h

win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../CalcLib002/release/ -lCalcLib002
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../CalcLib002/debug/ -lCalcLib002
else:unix: LIBS += -L$$OUT_PWD/../CalcLib002/ -lCalcLib002

INCLUDEPATH += $$PWD/../CalcLib002
DEPENDPATH += $$PWD/../CalcLib002

win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../CalcLib002/release/libCalcLib002.a
else:win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../CalcLib002/debug/libCalcLib002.a
else:win32:!win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../CalcLib002/release/CalcLib002.lib
else:win32:!win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../CalcLib002/debug/CalcLib002.lib
else:unix: PRE_TARGETDEPS += $$OUT_PWD/../CalcLib002/libCalcLib002.a
