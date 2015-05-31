#include <QLineEdit>
#include <QDebug>
#include <QTextEdit>
#include <QVBoxLayout>
#include "mainwidget.h"

MainWidget::MainWidget(QWidget *parent)
    : QWidget(parent)
    , parser(&tokenizer)
{
    lineInput = new QLineEdit;
    lineError = new QLineEdit;
    textDisplay = new QTextEdit;
    textDisplay->setReadOnly(true);
    treeViewer = new TreeViewer;
    treeViewer->setMinimumSize(300,300);
    QVBoxLayout *layout = new QVBoxLayout;
    layout->addWidget( lineInput );
    layout->addWidget( lineError );
    layout->addWidget( textDisplay );
    layout->addWidget( treeViewer );
//    layout->setStretchFactor( textDisplay, 0 );
    layout->setStretchFactor( treeViewer, 100 );
    setLayout( layout );
    connect( lineInput, SIGNAL(textChanged(QString)), this, SLOT(inputTextChanged()) );
    connect( lineInput, SIGNAL(returnPressed()), this, SLOT(returnPressed()) );
}

MainWidget::~MainWidget()
{
}

void MainWidget::inputTextChanged()
{
    QString expression = lineInput->text();
    SyntaxNode *node = parser.parse( expression.toLatin1().constData() );
    lineError->clear();
    if( ! expression.isEmpty() ){
        if( parser.isError() ){
            lineError->setText( QString("Syntax error ! %1").arg(parser.errorMessage().c_str()) );
        }
    }
    treeViewer->setNode( node );
}

void MainWidget::returnPressed()
{
    qDebug() << "returnPressed";
    QString expression = lineInput->text();

    lineError->clear();

    SyntaxNode *node = parser.parse( expression.toLatin1().constData() );
    if( parser.isError() ){
        lineError->setText( QString("Syntax error ! %1").arg(parser.errorMessage().c_str()) );
        return;
    }

    int value = evaluator.evaluate( node );
    if( evaluator.isError() ){
        lineError->setText( QString("Evaluation error ! %1").arg(evaluator.errorMessage().c_str()) );
        return;
    }
    QString result = QString( "%1 <- %2" ).arg(QString::number(value)).arg(expression);
    textDisplay->append( result );
    lineInput->clear();

    treeViewer->setNode( node );
}
