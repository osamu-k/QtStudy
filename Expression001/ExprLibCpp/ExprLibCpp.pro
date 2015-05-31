#-------------------------------------------------
#
# Project created by QtCreator 2015-05-24T00:40:30
#
#-------------------------------------------------

QT       -= core gui

TARGET = ExprLibCpp
TEMPLATE = lib
CONFIG += staticlib

SOURCES += \
    evaluator.cpp \
    node.cpp \
    parser.cpp \
    tokenizer.cpp \
    interpreter.cpp

HEADERS += \
    evaluator.h \
    node.h \
    nodevisitor.h \
    parser.h \
    token.h \
    tokenizer.h \
    interpreter.h
unix {
    target.path = /usr/lib
    INSTALLS += target
}
