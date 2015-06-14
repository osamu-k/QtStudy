#-------------------------------------------------
#
# Project created by QtCreator 2015-06-14T15:58:02
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = CalcApp004
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp

HEADERS  += mainwindow.h

FORMS    += mainwindow.ui

win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../CalcLib004/release/ -lCalcLib004
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../CalcLib004/debug/ -lCalcLib004
else:unix: LIBS += -L$$OUT_PWD/../CalcLib004/ -lCalcLib004

INCLUDEPATH += $$PWD/../CalcLib004
DEPENDPATH += $$PWD/../CalcLib004

win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../CalcLib004/release/libCalcLib004.a
else:win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../CalcLib004/debug/libCalcLib004.a
else:win32:!win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../CalcLib004/release/CalcLib004.lib
else:win32:!win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../CalcLib004/debug/CalcLib004.lib
else:unix: PRE_TARGETDEPS += $$OUT_PWD/../CalcLib004/libCalcLib004.a
