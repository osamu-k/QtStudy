#-------------------------------------------------
#
# Project created by QtCreator 2015-05-30T21:52:11
#
#-------------------------------------------------

QT       -= core gui

TARGET = ExprLibCpp2
TEMPLATE = lib
CONFIG += staticlib

SOURCES += \
    evaluator.cpp \
    interpreter.cpp \
    parser.cpp \
    tokenizer.cpp \
    syntaxnode.cpp

HEADERS += \
    evaluator.h \
    interpreter.h \
    nodevisitor.h \
    parser.h \
    token.h \
    tokenizer.h \
    syntaxnode.h
unix {
    target.path = /usr/lib
    INSTALLS += target
}
