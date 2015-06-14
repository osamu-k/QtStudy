#include "calculator.h"
#include <QGridLayout>
#include <QHBoxLayout>
#include <QLineEdit>
#include <QPushButton>
#include <QVBoxLayout>

#include <QDebug>

Calculator::Calculator(QWidget *parent)
    : QWidget(parent)
    , m_display1(0)
    , m_display2(0)
    , m_operatorFunc(0)
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

    m_operatorMap[buttonAdd] = &Calculator::calculateAdd;
    m_operatorMap[buttonSub] = &Calculator::calculateSub;
    m_operatorMap[buttonMul] = &Calculator::calculateMul;
    m_operatorMap[buttonDiv] = &Calculator::calculateDiv;

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
    if( button ){
        QString str = m_display2->text();
        if( str == "0" ){
            m_display2->setText(button->text());
        }
        else{
            str.append(button->text());
            m_display2->setText(str);
        }
    }
}

void Calculator::operatorButtonClicked()
{
    QPushButton *button = qobject_cast<QPushButton *>(sender());
    if( button ){
        QString str = m_display2->text();
        str.append(" ");
        str.append(button->text());
        m_display1->setText(str);
        m_display2->clear();

        m_operatorFunc = m_operatorMap[button];
    }
}

void Calculator::equalButtonClicked()
{
    if( m_operatorFunc ){
        QStringList slist = m_display1->text().split(" ");
        if( (slist.size() == 2) && (! m_display2->text().isEmpty()) ){
            long operand1 = slist[0].toLong();
            long operand2 = m_display2->text().toLong();
            if( (this->*m_operatorFunc)(operand1,operand2) ){
                m_operatorFunc = 0;
            }
        }
    }
}

void Calculator::signButtonClicked()
{
}

void Calculator::clearButtonClicked()
{
}

void Calculator::allClearButtonClicked()
{
}

bool Calculator::calculateAdd(long operand1, long operand2)
{
    showAnswer(operand1 + operand2);
    return true;
}

bool Calculator::calculateSub(long operand1, long operand2)
{
    showAnswer(operand1 - operand2);
    return true;
}

bool Calculator::calculateMul(long operand1, long operand2)
{
    showAnswer(operand1 * operand2);
    return true;
}

bool Calculator::calculateDiv(long operand1, long operand2)
{
    if( operand2 != 0 ){
        showAnswer(operand1 / operand2);
        return true;
    }
    else{
        return false;
    }
}

void Calculator::showAnswer(long answer)
{
    m_display1->setText(QString::number(answer));
    m_display2->clear();
}
