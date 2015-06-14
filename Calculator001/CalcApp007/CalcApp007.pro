#-------------------------------------------------
#
# Project created by QtCreator 2015-06-14T17:11:17
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = CalcApp007
TEMPLATE = app


SOURCES += main.cpp\
        widget.cpp

HEADERS  += widget.h

win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../CalcLib007/release/ -lCalcLib007
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../CalcLib007/debug/ -lCalcLib007
else:unix: LIBS += -L$$OUT_PWD/../CalcLib007/ -lCalcLib007

INCLUDEPATH += $$PWD/../CalcLib007
DEPENDPATH += $$PWD/../CalcLib007

win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../CalcLib007/release/libCalcLib007.a
else:win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../CalcLib007/debug/libCalcLib007.a
else:win32:!win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../CalcLib007/release/CalcLib007.lib
else:win32:!win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../CalcLib007/debug/CalcLib007.lib
else:unix: PRE_TARGETDEPS += $$OUT_PWD/../CalcLib007/libCalcLib007.a
