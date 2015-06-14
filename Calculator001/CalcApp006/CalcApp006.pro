#-------------------------------------------------
#
# Project created by QtCreator 2015-06-14T16:44:31
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = CalcApp006
TEMPLATE = app


SOURCES += main.cpp\
        widget.cpp

HEADERS  += widget.h

win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../CalcLib006/release/ -lCalcLib006
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../CalcLib006/debug/ -lCalcLib006
else:unix: LIBS += -L$$OUT_PWD/../CalcLib006/ -lCalcLib006

INCLUDEPATH += $$PWD/../CalcLib006
DEPENDPATH += $$PWD/../CalcLib006

win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../CalcLib006/release/libCalcLib006.a
else:win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../CalcLib006/debug/libCalcLib006.a
else:win32:!win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../CalcLib006/release/CalcLib006.lib
else:win32:!win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../CalcLib006/debug/CalcLib006.lib
else:unix: PRE_TARGETDEPS += $$OUT_PWD/../CalcLib006/libCalcLib006.a
