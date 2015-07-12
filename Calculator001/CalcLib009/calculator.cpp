#include "calculator.h"
#include <QGridLayout>
#include <QHBoxLayout>
#include <QLineEdit>
#include <QPushButton>
#include <QVBoxLayout>

#include <QDebug>

const char *Calculator::operatorSymbolAdd = "+";
const char *Calculator::operatorSymbolSub = "−";
const char *Calculator::operatorSymbolMul = "×";
const char *Calculator::operatorSymbolDiv = "÷";

Calculator::Calculator(QWidget *parent)
    : QWidget(parent)
    , m_display1(0)
    , m_display2(0)
    , m_currentValue(0)
    , m_currentSign(1)
    , m_digitCount(0)
    , m_showingAnswer(false)
    , m_lastValue(0)
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
        m_numberMap[button] = i;
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
    QPushButton *buttonDiv   = new QPushButton(operatorSymbolDiv);
    QPushButton *buttonMul   = new QPushButton(operatorSymbolMul);
    QPushButton *buttonSub   = new QPushButton(operatorSymbolSub);
    QPushButton *buttonAdd   = new QPushButton(operatorSymbolAdd);
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

    m_operatorMap[buttonDiv] = &Calculator::calculateDiv;
    m_operatorMap[buttonMul] = &Calculator::calculateMul;
    m_operatorMap[buttonSub] = &Calculator::calculateSub;
    m_operatorMap[buttonAdd] = &Calculator::calculateAdd;

    m_operatorSymbol[buttonDiv] = operatorSymbolDiv;
    m_operatorSymbol[buttonMul] = operatorSymbolMul;
    m_operatorSymbol[buttonSub] = operatorSymbolSub;
    m_operatorSymbol[buttonAdd] = operatorSymbolAdd;

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
    m_currentValue *= 10;
    m_currentValue += m_numberMap[sender()];
    m_digitCount ++;
    showCurrentValue();
}

void Calculator::operatorButtonClicked()
{
    if( m_operatorFunc == 0){
        if( m_digitCount > 0 ){
            m_lastValue = m_currentValue*m_currentSign;
        }
        else if( m_showingAnswer ){
            // Nothing to do.
        }
        else{
            return;
        }
    }
    else{
        if( ! (this->*m_operatorFunc)() ){
            return;
        }
    }
    QString str = QString::number(m_lastValue);
    str.append(" ");
    str.append(m_operatorSymbol[sender()]);
    m_display1->setText(str);
    m_operatorFunc = m_operatorMap[sender()];
    m_showingAnswer = false;
    resetCurrentValue();
}

void Calculator::equalButtonClicked()
{
    if( m_operatorFunc ){
        if( (this->*m_operatorFunc)() ){
            m_display1->setText(QString::number(m_lastValue));
            m_operatorFunc = 0;
            m_showingAnswer = true;
            resetCurrentValue();
        }
    }
}

void Calculator::signButtonClicked()
{
    m_currentSign *= -1;
    if( m_currentSign > 0 ){
        m_display2->setText(m_display2->text().mid(1));
    }
    else{
        m_display2->setText(QString("-").append(m_display2->text()));
    }
}

void Calculator::clearButtonClicked()
{
    resetCurrentValue();
}

void Calculator::allClearButtonClicked()
{
    m_lastValue = 0;
    m_operatorFunc = 0;
    m_showingAnswer =false;
    m_display1->clear();
    resetCurrentValue();
}

bool Calculator::calculateAdd()
{
    m_lastValue = m_lastValue + (m_currentValue * m_currentSign);
    return true;
}

bool Calculator::calculateSub()
{
    m_lastValue = m_lastValue - (m_currentValue * m_currentSign);
    return true;
}

bool Calculator::calculateMul()
{
    m_lastValue = m_lastValue * (m_currentValue * m_currentSign);
    return true;
}

bool Calculator::calculateDiv()
{
    if( m_currentValue != 0 ){
        m_lastValue = m_lastValue / (m_currentValue * m_currentSign);
        return true;
    }
    else{
        return false;
    }
}

void Calculator::resetCurrentValue()
{
    m_currentValue = 0;
    m_currentSign = 1;
    m_digitCount = 0;
    m_display2->clear();
}

void Calculator::showCurrentValue()
{
    QString text;
    if( m_currentSign < 0 )
        text.append('-');
    text.append(QString::number(m_currentValue));
    m_display2->setText(text);
}
