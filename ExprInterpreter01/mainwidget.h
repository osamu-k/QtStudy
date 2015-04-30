#ifndef MAINWIDGET_H
#define MAINWIDGET_H

#include <QWidget>
#include "tokenizer.h"
#include "parser.h"
#include "evaluator.h"

class QLineEdit;
class QTextEdit;

class MainWidget : public QWidget
{
    Q_OBJECT

public:
    MainWidget(QWidget *parent = 0);
    ~MainWidget();

public slots:
    void returnPressed();

private:
    QLineEdit *lineInput;
    QTextEdit *textDisplay;

    Tokenizer tokenizer;
    Parser parser;
    Evaluator evaluator;
};

#endif // MAINWIDGET_H
