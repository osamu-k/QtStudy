#-------------------------------------------------
#
# Project created by QtCreator 2015-04-29T22:40:51
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = ExprInterpreter01
TEMPLATE = app


SOURCES += main.cpp\
        mainwidget.cpp \
    interpreter/evaluator.cpp \
    interpreter/node.cpp \
    interpreter/nodevisitor.cpp \
    interpreter/parser.cpp \
    interpreter/token.cpp \
    interpreter/tokenizer.cpp

HEADERS  += mainwidget.h \
    interpreter/evaluator.h \
    interpreter/node.h \
    interpreter/nodevisitor.h \
    interpreter/parser.h \
    interpreter/token.h \
    interpreter/tokenizer.h

INCLUDEPATH += interpreter
