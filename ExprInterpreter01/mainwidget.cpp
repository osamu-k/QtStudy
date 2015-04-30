#include <QLineEdit>
#include <QDebug>
#include <QTextEdit>
#include <QVBoxLayout>
#include "mainwidget.h"

MainWidget::MainWidget(QWidget *parent)
    : QWidget(parent)
    , parser(&tokenizer)
    , evaluator(&parser)
{
    lineInput = new QLineEdit;
    textDisplay = new QTextEdit;
    textDisplay->setReadOnly(true);
    QVBoxLayout *layout = new QVBoxLayout;
    layout->addWidget( lineInput );
    layout->addWidget( textDisplay );
    setLayout( layout );
    connect( lineInput, SIGNAL(returnPressed()), this, SLOT(returnPressed()) );
}

MainWidget::~MainWidget()
{
}

void MainWidget::returnPressed()
{
    qDebug() << "returnPressed";
    QString expression = lineInput->text();
    int value = evaluator.evaluate( expression.toLatin1().constData() );
    QString result = QString( "%1 <- %2" ).arg(QString::number(value)).arg(expression);
    textDisplay->append( result );
    lineInput->clear();
}
