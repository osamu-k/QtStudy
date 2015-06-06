#ifndef MAINWIDGET_H
#define MAINWIDGET_H

#include <QWidget>
#include "tokenizer.h"
#include "parser.h"
#include "evaluator.h"
#include "treeviewer.h"

class QLineEdit;
class QTextEdit;

class MainWidget : public QWidget
{
    Q_OBJECT

public:
    MainWidget(QWidget *parent = 0);
    ~MainWidget();

public slots:
    void inputTextChanged();
    void returnPressed();

private:
    QLineEdit *lineInput;
    QLineEdit *lineError;
    QTextEdit *textDisplay;
    TreeViewer *treeViewer;

    Tokenizer tokenizer;
    Parser parser;
    Evaluator evaluator;
};

#endif // MAINWIDGET_H
