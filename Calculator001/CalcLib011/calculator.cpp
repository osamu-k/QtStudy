#include "calculator.h"
#include "calcstate.h"

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
    , m_buttonAdd(0)
    , m_buttonSub(0)
    , m_buttonMul(0)
    , m_buttonDiv(0)
    , m_buttonEqual(0)
    , m_currentValue(0)
    , m_currentSign(1)
    , m_lastValue(0)
    , m_operatorFunc(0)
    , m_stateID(CALC_STATE_WAITING_VALUE1)
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

    setupState();
    setState(CALC_STATE_WAITING_VALUE1);
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
    m_buttonDiv   = new QPushButton(operatorSymbolDiv);
    m_buttonMul   = new QPushButton(operatorSymbolMul);
    m_buttonSub   = new QPushButton(operatorSymbolSub);
    m_buttonAdd   = new QPushButton(operatorSymbolAdd);
    m_buttonEqual = new QPushButton("=");

    m_buttonDiv->setObjectName("buttonDiv");
    m_buttonMul->setObjectName("buttonMul");
    m_buttonSub->setObjectName("buttonSub");
    m_buttonAdd->setObjectName("buttonAdd");
    m_buttonEqual->setObjectName("buttonEqual");

    QVBoxLayout *layout = new QVBoxLayout;
    layout->addWidget(m_buttonDiv);
    layout->addWidget(m_buttonMul);
    layout->addWidget(m_buttonSub);
    layout->addWidget(m_buttonAdd);
    layout->addWidget(m_buttonEqual);

    connect(m_buttonDiv,SIGNAL(clicked()),this,SLOT(operatorButtonClicked()));
    connect(m_buttonMul,SIGNAL(clicked()),this,SLOT(operatorButtonClicked()));
    connect(m_buttonSub,SIGNAL(clicked()),this,SLOT(operatorButtonClicked()));
    connect(m_buttonAdd,SIGNAL(clicked()),this,SLOT(operatorButtonClicked()));
    connect(m_buttonEqual,SIGNAL(clicked()),this,SLOT(equalButtonClicked()));

    m_operatorMap[m_buttonDiv] = &Calculator::calculateDiv;
    m_operatorMap[m_buttonMul] = &Calculator::calculateMul;
    m_operatorMap[m_buttonSub] = &Calculator::calculateSub;
    m_operatorMap[m_buttonAdd] = &Calculator::calculateAdd;

    m_operatorSymbol[m_buttonDiv] = operatorSymbolDiv;
    m_operatorSymbol[m_buttonMul] = operatorSymbolMul;
    m_operatorSymbol[m_buttonSub] = operatorSymbolSub;
    m_operatorSymbol[m_buttonAdd] = operatorSymbolAdd;

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

void Calculator::setupState()
{
    m_stateMap[CALC_STATE_WAITING_VALUE1] = new CalcStateWaitingNumber1(this);
    m_stateMap[CALC_STATE_READING_VALUE1] = new CalcStateReadingNumber1(this);
    m_stateMap[CALC_STATE_WAITING_VALUE2] = new CalcStateWaitingNumber2(this);
    m_stateMap[CALC_STATE_READING_VALUE2] = new CalcStateReadingNumber2(this);
    m_stateMap[CALC_STATE_SHOWING_ANSWER] = new CalcStateShowingAnswer(this);
    m_stateMap[CALC_STATE_READING_VALUE1_SHOWING_ANSWER] = new CalcStateReadingNumber1ShowingAnswer(this);
}

void Calculator::setState(CalcStateID state)
{
    m_stateID = state;
    disableButtons();
}

void Calculator::disableButtons()
{
    m_buttonAdd->setDisabled(true);
    m_buttonSub->setDisabled(true);
    m_buttonMul->setDisabled(true);
    m_buttonDiv->setDisabled(true);
    m_buttonEqual->setDisabled(true);

    m_stateMap[m_stateID]->disableButtons();
}

void Calculator::numberButtonClicked()
{
    m_stateMap[m_stateID]->numberButtonClicked();
}

void Calculator::operatorButtonClicked()
{
    m_stateMap[m_stateID]->operatorButtonClicked();
}

void Calculator::equalButtonClicked()
{
    m_stateMap[m_stateID]->equalButtonClicked();
}

void Calculator::signButtonClicked()
{
    m_stateMap[m_stateID]->signButtonClicked();
}

void Calculator::clearButtonClicked()
{
    m_stateMap[m_stateID]->clearButtonClicked();
}

void Calculator::allClearButtonClicked()
{
    m_stateMap[m_stateID]->allClearButtonClicked();
}

void Calculator::appendNumber()
{
    m_currentValue *= 10;
    m_currentValue += m_numberMap[sender()];
    showCurrentValue();
}

bool Calculator::calculateOperator()
{
    if( (this->*m_operatorFunc)() ){
        showLastValue();
        clearCurrentValue();
        return true;
    }
    return false;
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

void Calculator::storeCurrentValue()
{
    m_lastValue = m_currentValue*m_currentSign;
    showLastValue();
    clearCurrentValue();
}

void Calculator::storeOperator()
{
    QString str = m_display1->text();
    str.append(" ");
    str.append(m_operatorSymbol[sender()]);
    m_display1->setText(str);
    m_operatorFunc = m_operatorMap[sender()];
    clearCurrentValue();
}

void Calculator::clearCurrentValue()
{
    m_currentValue = 0;
    m_currentSign = 1;
    m_display2->clear();
}

void Calculator::changeSign()
{
    m_currentSign *= -1;
    if( m_currentSign > 0 ){
        m_display2->setText(m_display2->text().mid(1));
    }
    else{
        m_display2->setText(QString("-").append(m_display2->text()));
    }
}

void Calculator::showCurrentValue()
{
    QString text;
    if( m_currentSign < 0 )
        text.append('-');
    text.append(QString::number(m_currentValue));
    m_display2->setText(text);
}

void Calculator::showLastValue()
{
    m_display1->setText(QString::number(m_lastValue));
}

void Calculator::clearAll()
{
    m_lastValue = 0;
    m_operatorFunc = 0;
    m_display1->clear();
    clearCurrentValue();
}
