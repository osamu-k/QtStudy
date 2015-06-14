#include "calculator.h"
#include <QGridLayout>
#include <QHBoxLayout>
#include <QLineEdit>
#include <QPushButton>
#include <QVBoxLayout>

#include <QDebug>

Calculator::Calculator(QWidget *parent) : QWidget(parent)
{
    QLayout *layoutNumber = setupNumberButtons();
    QLayout *layoutVarious = setupVariousButtons();
    QLayout *layoutOperator = setupOperatorButtons();
    QLayout *layoutDisplay = setupDisplays();

    QVBoxLayout *vboxLayout = new QVBoxLayout;
    vboxLayout->addLayout(layoutVarious);
    vboxLayout->addLayout(layoutNumber);

    QHBoxLayout *hboxLayout = new QHBoxLayout;
    hboxLayout->addLayout(vboxLayout);
    hboxLayout->addLayout(layoutOperator);

    QVBoxLayout *topLayout = new QVBoxLayout;
    topLayout->addLayout(layoutDisplay);
    topLayout->addLayout(hboxLayout);

    setLayout(topLayout);
}

Calculator::~Calculator()
{
}

QLayout *Calculator::setupNumberButtons()
{
    QGridLayout *gridNumber = new QGridLayout;
    for( int i = 0; i <= 9; i++ ){
        QPushButton *button = new QPushButton(QString::number(i),this);
        button->setObjectName(QString("button%1").arg(i));
        int row = 0, col = 0, rowspan = 1, colspan = 1;
        if( i == 0 ){
            row = 3;
            col = 0;
            colspan = 3;
        }
        else{
            row = 2 - (i - 1) / 3;
            col = (i - 1) % 3;
        }
        gridNumber->addWidget(button,row,col,rowspan,colspan);
        connect(button,SIGNAL(clicked()),this,SLOT(numberButtonClicked()));
    }
    return gridNumber;
}

QLayout *Calculator::setupVariousButtons()
{
    QPushButton *buttonAC =   new QPushButton("AC");
    QPushButton *buttonC  =   new QPushButton("C");
    QPushButton *buttonSign = new QPushButton("+/-");

    buttonAC->setObjectName(("buttonAC"));
    buttonC->setObjectName("buttonC");
    buttonSign->setObjectName("buttonSign");

    QHBoxLayout *layout = new QHBoxLayout;
    layout->addWidget(buttonAC);
    layout->addWidget(buttonC);
    layout->addWidget(buttonSign);

    connect(buttonAC,SIGNAL(clicked()),this,SLOT(allClearButtonClicked()));
    connect(buttonC,SIGNAL(clicked()),this,SLOT(clearButtonClicked()));
    connect(buttonSign,SIGNAL(clicked()),this,SLOT(signButtonClicked()));

    return layout;
}

QLayout *Calculator::setupOperatorButtons()
{
    QPushButton *buttonDiv   = new QPushButton("÷");
    QPushButton *buttonMul   = new QPushButton("×");
    QPushButton *buttonSub   = new QPushButton("−");
    QPushButton *buttonAdd   = new QPushButton("+");
    QPushButton *buttonEqual = new QPushButton("=");

    buttonDiv->setObjectName("buttonDiv");
    buttonMul->setObjectName("buttonMul");
    buttonSub->setObjectName("buttonSub");
    buttonAdd->setObjectName("buttonAdd");
    buttonEqual->setObjectName("buttonEqual");

    QVBoxLayout *layout = new QVBoxLayout;
    layout->addWidget(buttonDiv);
    layout->addWidget(buttonMul);
    layout->addWidget(buttonSub);
    layout->addWidget(buttonAdd);
    layout->addWidget(buttonEqual);

    connect(buttonDiv,SIGNAL(clicked()),this,SLOT(operatorButtonClicked()));
    connect(buttonMul,SIGNAL(clicked()),this,SLOT(operatorButtonClicked()));
    connect(buttonSub,SIGNAL(clicked()),this,SLOT(operatorButtonClicked()));
    connect(buttonAdd,SIGNAL(clicked()),this,SLOT(operatorButtonClicked()));
    connect(buttonEqual,SIGNAL(clicked()),this,SLOT(equalButtonClicked()));

    return layout;
}

QLayout *Calculator::setupDisplays()
{
    m_display1 = new QLineEdit;
    m_display1->setReadOnly(true);
    m_display1->setAlignment(Qt::AlignRight);
    m_display1->setObjectName("display1");

    m_display2 = new QLineEdit;
    m_display2->setReadOnly(true);
    m_display2->setAlignment(Qt::AlignRight);
    m_display2->setObjectName("display2");

    QVBoxLayout *layout = new QVBoxLayout;
    layout->addWidget(m_display1);
    layout->addWidget(m_display2);
    return layout;
}

void Calculator::numberButtonClicked()
{
    QPushButton *button = qobject_cast<QPushButton *>(sender());
    if(button){
        qDebug() << "number button " << button->text() << " clicked !";
        qDebug() << "objectName is " << button->objectName();
    }
}

void Calculator::operatorButtonClicked()
{
    QPushButton *button = qobject_cast<QPushButton *>(sender());
    if(button){
        qDebug() << "operator button " << button->text() << " clicked !";
        qDebug() << "objectName is " << button->objectName();
    }
}

void Calculator::equalButtonClicked()
{
    QPushButton *button = qobject_cast<QPushButton *>(sender());
    if(button){
        qDebug() << "equal button " << button->text() << " clicked !";
        qDebug() << "objectName is " << button->objectName();
    }
}

void Calculator::signButtonClicked()
{
    QPushButton *button = qobject_cast<QPushButton *>(sender());
    if(button){
        qDebug() << "sign button " << button->text() << " clicked !";
        qDebug() << "objectName is " << button->objectName();
    }
}

void Calculator::clearButtonClicked()
{
    QPushButton *button = qobject_cast<QPushButton *>(sender());
    if(button){
        qDebug() << "clear button " << button->text() << " clicked !";
        qDebug() << "objectName is " << button->objectName();
    }
}

void Calculator::allClearButtonClicked()
{
    QPushButton *button = qobject_cast<QPushButton *>(sender());
    if(button){
        qDebug() << "all clear button " << button->text() << " clicked !";
        qDebug() << "objectName is " << button->objectName();
    }
}
