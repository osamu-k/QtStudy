#-------------------------------------------------
#
# Project created by QtCreator 2015-06-03T06:17:38
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = ExprApp3
TEMPLATE = app


SOURCES += main.cpp\
    mainwidget.cpp \
    treeviewer.cpp \
    visualtree.cpp

HEADERS  += \
    mainwidget.h \
    treeviewer.h \
    visualtree.h

win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../ExprLibCpp3/release/ -lExprLibCpp3
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../ExprLibCpp3/debug/ -lExprLibCpp3
else:unix: LIBS += -L$$OUT_PWD/../ExprLibCpp3/ -lExprLibCpp3

INCLUDEPATH += $$PWD/../ExprLibCpp3
DEPENDPATH += $$PWD/../ExprLibCpp3

win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../ExprLibCpp3/release/libExprLibCpp3.a
else:win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../ExprLibCpp3/debug/libExprLibCpp3.a
else:win32:!win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../ExprLibCpp3/release/ExprLibCpp3.lib
else:win32:!win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../ExprLibCpp3/debug/ExprLibCpp3.lib
else:unix: PRE_TARGETDEPS += $$OUT_PWD/../ExprLibCpp3/libExprLibCpp3.a
