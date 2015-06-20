#-------------------------------------------------
#
# Project created by QtCreator 2015-06-20T20:51:36
#
#-------------------------------------------------

QT       += widgets testlib

TARGET = tst_calclib010test
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app


SOURCES += tst_calclib010test.cpp
DEFINES += SRCDIR=\\\"$$PWD/\\\"

win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../CalcLib010/release/ -lCalcLib010
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../CalcLib010/debug/ -lCalcLib010
else:unix: LIBS += -L$$OUT_PWD/../CalcLib010/ -lCalcLib010

INCLUDEPATH += $$PWD/../CalcLib010
DEPENDPATH += $$PWD/../CalcLib010

win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../CalcLib010/release/libCalcLib010.a
else:win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../CalcLib010/debug/libCalcLib010.a
else:win32:!win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../CalcLib010/release/CalcLib010.lib
else:win32:!win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../CalcLib010/debug/CalcLib010.lib
else:unix: PRE_TARGETDEPS += $$OUT_PWD/../CalcLib010/libCalcLib010.a
