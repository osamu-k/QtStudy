#include "calculator.h"

#include <QDebug>
#include <QGridLayout>
#include <QLineEdit>
#include <QPushButton>
#include <QVBoxLayout>

#include <algorithm>
using namespace std;

Calculator::Calculator(QWidget *parent)
    : QWidget(parent)
    , m_stateNum1Waiting(this)
    , m_stateNum1IntegerPart(this)
    , m_stateNum1DecimalPart(this)
    , m_stateNum2Waiting(this)
    , m_stateNum2IntegerPart(this)
    , m_stateNum2DecimalPart(this)
    , m_stateShowResult(this)
    , m_state(STATE_NUM1_WAITING)
{
    QVBoxLayout *vboxLayout = new QVBoxLayout;

    QLineEdit *lineDisplay = createLineEdit("lineDisplay");
    vboxLayout->addWidget(lineDisplay);

    QLineEdit *lineInput = createLineEdit("lineInput");
    vboxLayout->addWidget(lineInput);

    QPushButton *button0 = createNumberButton( 0 );
    QPushButton *button1 = createNumberButton( 1 );
    QPushButton *button2 = createNumberButton( 2 );
    QPushButton *button3 = createNumberButton( 3 );
    QPushButton *button4 = createNumberButton( 4 );
    QPushButton *button5 = createNumberButton( 5 );
    QPushButton *button6 = createNumberButton( 6 );
    QPushButton *button7 = createNumberButton( 7 );
    QPushButton *button8 = createNumberButton( 8 );
    QPushButton *button9 = createNumberButton( 9 );

    QPushButton *buttonDot = createDotButton();
    QPushButton *buttonSign = createSignButton();

    QPushButton *buttonAdd = createAddButton();
    QPushButton *buttonSub = createSubButton();
    QPushButton *buttonMul = createMulButton();
    QPushButton *buttonDiv = createDivButton();

    QPushButton *buttonEq = createEqualButton();

    QPushButton *buttonAC = createAllClearButton();
    QPushButton *buttonC = createClearButton();

    QGridLayout *gridLayout = new QGridLayout;

    gridLayout->addWidget(buttonAC  ,0,0);
    gridLayout->addWidget(buttonC   ,0,1);
    gridLayout->addWidget(buttonSign,0,2);
    gridLayout->addWidget(buttonDiv ,0,3);

    gridLayout->addWidget(button7   ,1,0);
    gridLayout->addWidget(button8   ,1,1);
    gridLayout->addWidget(button9   ,1,2);
    gridLayout->addWidget(buttonMul ,1,3);

    gridLayout->addWidget(button4   ,2,0);
    gridLayout->addWidget(button5   ,2,1);
    gridLayout->addWidget(button6   ,2,2);
    gridLayout->addWidget(buttonSub ,2,3);

    gridLayout->addWidget(button1   ,3,0);
    gridLayout->addWidget(button2   ,3,1);
    gridLayout->addWidget(button3   ,3,2);
    gridLayout->addWidget(buttonAdd ,3,3);

    gridLayout->addWidget(button0   ,4,0,1,2);
    gridLayout->addWidget(buttonDot ,4,2);
    gridLayout->addWidget(buttonDot ,4,2);
    gridLayout->addWidget(buttonEq  ,4,3);

    vboxLayout->addLayout(gridLayout);
    setLayout(vboxLayout);

    m_stateMap[STATE_NUM1_WAITING     ] = &m_stateNum1Waiting;
    m_stateMap[STATE_NUM1_INTEGER_PART] = &m_stateNum1IntegerPart;
    m_stateMap[STATE_NUM1_DECIMAL_PART] = &m_stateNum1DecimalPart;
    m_stateMap[STATE_NUM2_WAITING     ] = &m_stateNum2Waiting;
    m_stateMap[STATE_NUM2_INTEGER_PART] = &m_stateNum2IntegerPart;
    m_stateMap[STATE_NUM2_DECIMAL_PART] = &m_stateNum2DecimalPart;
    m_stateMap[STATE_SHOW_RESULT      ] = &m_stateShowResult;

//    m_state = &m_stateNum1Waiting;
    m_state = STATE_NUM1_WAITING;
    m_stateMap[ m_state ]->disableIrrelevantButtons();
}

Calculator::~Calculator()
{
}

QLineEdit *Calculator::createLineDisplay()
{
    return createLineEdit("lineDisplay");
}

QLineEdit *Calculator::createLineInput()
{
    return createLineEdit("lineInput");
}

QLineEdit *Calculator::createLineEdit( QString objectName )
{
    QLineEdit *lineEdit = new QLineEdit;
    lineEdit->setObjectName(objectName);
    lineEdit->setReadOnly(true);
    lineEdit->setAlignment(Qt::AlignRight);
    return lineEdit;
}

QPushButton *Calculator::createNumberButton( int i )
{
    QString label = QString::number(i);
    QString objectName = QString("button%1").arg(i);
    QPushButton *button = new QPushButton(label);
    button->setObjectName(objectName);
    connect( button, &QPushButton::clicked,
             [=](){ numberButtonClicked(label); } );
    return button;
}

QPushButton *Calculator::createDotButton()
{
    QString label(".");
    QString objectName( "buttonDot" );
    QPushButton *button = new QPushButton(label);
    button->setObjectName(objectName);
    connect( button, &QPushButton::clicked, this, &Calculator::dotButtonClicked );
    return button;
}

QPushButton *Calculator::createSignButton()
{
    QString label("+/-");
    QString objectName( "buttonSign" );
    QPushButton *button = new QPushButton(label);
    button->setObjectName(objectName);
    connect( button, &QPushButton::clicked, this, &Calculator::signButtonClicked );
    return button;
}

QPushButton *Calculator::createAddButton()
{
    return createOperatorButton( "+", "buttonAdd", [](double x, double y)->double{ return x + y; });
}

QPushButton *Calculator::createSubButton()
{
    return createOperatorButton( "-", "buttonSub", [](double x, double y)->double{ return x - y; });
}

QPushButton *Calculator::createMulButton()
{
    return createOperatorButton( "×", "buttonMul", [](double x, double y)->double{ return x * y; });
}

QPushButton *Calculator::createDivButton()
{
    return createOperatorButton( "÷", "buttonDiv", [](double x, double y)->double{ return x / y; });
}

QPushButton *Calculator::createOperatorButton( QString label, QString objectName, double (*func)(double, double) )
{
    QPushButton *button = new QPushButton(label);
    button->setObjectName(objectName);
    connect( button, &QPushButton::clicked, [=](){operatorButtonClicked(label,func);} );
    return button;
}
QPushButton *Calculator::createEqualButton()
{
    QString label("=");
    QString objectName( "buttonEqual" );
    QPushButton *button = new QPushButton(label);
    button->setObjectName(objectName);
    connect( button, &QPushButton::clicked, this, &Calculator::equalButtonClicked );
    return button;
}

QPushButton *Calculator::createAllClearButton()
{
    QString label("AC");
    QString objectName( "buttonAllClear" );
    QPushButton *button = new QPushButton(label);
    button->setObjectName(objectName);
    connect( button, &QPushButton::clicked, this, &Calculator::allClearButtonClicked );
    return button;
}

QPushButton *Calculator::createClearButton()
{
    QString label("C");
    QString objectName( "buttonClear" );
    QPushButton *button = new QPushButton(label);
    button->setObjectName(objectName);
    connect( button, &QPushButton::clicked, this, &Calculator::clearButtonClicked );
    return button;
}

QLineEdit *Calculator::getLineDisplay()
{
    return findChild<QLineEdit *>( "lineDisplay" );
}

QLineEdit *Calculator::getLineInput()
{
    return findChild<QLineEdit *>( "lineInput" );
}

QPushButton *Calculator::getNumberButton( int i )
{
    QString objectName = QString("button%1").arg(i);
    return findChild<QPushButton *>( objectName );
}

QPushButton *Calculator::getDotButton()
{
    return findChild<QPushButton *>( "buttonDot" );
}

QPushButton *Calculator::getSignButton()
{
    return findChild<QPushButton *>( "buttonSign" );
}

QPushButton *Calculator::getAddButton()
{
    return findChild<QPushButton *>( "buttonAdd" );
}

QPushButton *Calculator::getSubButton()
{
    return findChild<QPushButton *>( "buttonSub" );
}

QPushButton *Calculator::getMulButton()
{
    return findChild<QPushButton *>( "buttonMul" );
}

QPushButton *Calculator::getDivButton()
{
    return findChild<QPushButton *>( "buttonDiv" );
}

QPushButton *Calculator::getEqualButton()
{
    return findChild<QPushButton *>( "buttonEqual" );
}

QPushButton *Calculator::getAllClearButton()
{
    return findChild<QPushButton *>( "buttonAllClear" );
}

QPushButton *Calculator::getClearButton()
{
    return findChild<QPushButton *>( "buttonClear" );
}

void Calculator::disableIrrelevantButtons()
{
    m_stateMap[m_state]->disableIrrelevantButtons();
}

void Calculator::numberButtonClicked( QString digit )
{
    m_stateMap[m_state]->numberButtonClicked(digit);
}

void Calculator::dotButtonClicked()
{
    m_stateMap[m_state]->dotButtonClicked();
}

void Calculator::signButtonClicked()
{
    m_stateMap[m_state]->signButtonClicked();
}

void Calculator::operatorButtonClicked(QString label, func_ptr func)
{
    m_stateMap[m_state]->operatorButtonClicked(label,func);
}

void Calculator::equalButtonClicked()
{
    m_stateMap[m_state]->equalButtonClicked();
}

void Calculator::allClearButtonClicked()
{
    m_stateMap[m_state]->allClearButtonClicked();
}

void Calculator::clearButtonClicked()
{
    m_stateMap[m_state]->clearButtonClicked();
}

Calculator::State::State(Calculator *calculator, QString name)
    : m_calculator(calculator),m_name(name)
{
}

Calculator::State::~State()
{
}

void Calculator::State::disableIrrelevantButtons()
{
    m_calculator->getDotButton()  ->setDisabled(false);
    m_calculator->getAddButton()  ->setDisabled(false);
    m_calculator->getSubButton()  ->setDisabled(false);
    m_calculator->getMulButton()  ->setDisabled(false);
    m_calculator->getDivButton()  ->setDisabled(false);
    m_calculator->getEqualButton()->setDisabled(false);
}

void Calculator::State::numberButtonClicked(QString digit)
{
    getLineInput()->setText( getLineInput()->text() + digit );
}

void Calculator::State::dotButtonClicked()
{
}

void Calculator::State::signButtonClicked()
{
    QString instr = getLineInput()->text();
    if( (instr.size()) > 0 && (instr[0] == '-') ){
        instr = instr.right( instr.size() - 1 );
    }
    else{
        instr = "-" + instr;
    }
    getLineInput()->setText( instr );
}

void Calculator::State::operatorButtonClicked(QString label, func_ptr func)
{
    getLineDisplay()->setText( m_calculator->m_currentData + " " + label );
    getLineInput()->clear();
    m_calculator->m_operation = func;
    setState( STATE_NUM2_WAITING);
}

void Calculator::State::equalButtonClicked()
{
}

void Calculator::State::allClearButtonClicked()
{
    getLineDisplay()->clear();
    getLineInput()->clear();
    m_calculator->m_currentData.clear();
    m_calculator->m_operation = 0;
    setState( STATE_NUM1_WAITING );
}

void Calculator::State::clearButtonClicked()
{
}

void Calculator::State::setState( enum state state )
{
    m_calculator->m_state = state;
    m_calculator->disableIrrelevantButtons();
}

Calculator::StateNum1Waiting::StateNum1Waiting(Calculator *calculator)
    : State(calculator,"NUM1_INTEGER_WAITING")
{
}

Calculator::StateNum1Waiting::~StateNum1Waiting()
{
}

void Calculator::StateNum1Waiting::disableIrrelevantButtons()
{
    State::disableIrrelevantButtons();
    m_calculator->getAddButton()  ->setDisabled(true);
    m_calculator->getSubButton()  ->setDisabled(true);
    m_calculator->getMulButton()  ->setDisabled(true);
    m_calculator->getDivButton()  ->setDisabled(true);
    m_calculator->getEqualButton()->setDisabled(true);
}

void Calculator::StateNum1Waiting::numberButtonClicked(QString digit)
{
    State::numberButtonClicked(digit);
    setState( STATE_NUM1_INTEGER_PART );
}

void Calculator::StateNum1Waiting::dotButtonClicked()
{
    QString instr = getLineInput()->text();
    instr += "0.";
    getLineInput()->setText( instr );
    setState( STATE_NUM1_DECIMAL_PART );
}

void Calculator::StateNum1Waiting::signButtonClicked()
{
    State::signButtonClicked();
}

void Calculator::StateNum1Waiting::operatorButtonClicked(QString label, func_ptr func)
{
    // Nothing to do.
}

void Calculator::StateNum1Waiting::equalButtonClicked()
{
    // Nothing to do.
}

void Calculator::StateNum1Waiting::allClearButtonClicked()
{
    State::allClearButtonClicked();
}

void Calculator::StateNum1Waiting::clearButtonClicked()
{
    // Nothing to do.
}

Calculator::StateNum1IntegerPart::StateNum1IntegerPart(Calculator *calculator)
    : State(calculator,"NUM1_INTEGER_PART")
{
}

Calculator::StateNum1IntegerPart::~StateNum1IntegerPart()
{
}

void Calculator::StateNum1IntegerPart::disableIrrelevantButtons()
{
    State::disableIrrelevantButtons();
    m_calculator->getEqualButton()->setDisabled(true);
}

void Calculator::StateNum1IntegerPart::numberButtonClicked(QString digit)
{
    State::numberButtonClicked(digit);
}

void Calculator::StateNum1IntegerPart::dotButtonClicked()
{
    QString instr = getLineInput()->text();
    instr += ".";
    getLineInput()->setText( instr );
    setState( STATE_NUM1_DECIMAL_PART );
}

void Calculator::StateNum1IntegerPart::signButtonClicked()
{
    State::signButtonClicked();
}

void Calculator::StateNum1IntegerPart::operatorButtonClicked(QString label, func_ptr func)
{
    m_calculator->m_currentData = getLineInput()->text();
    State::operatorButtonClicked(label,func);
}

void Calculator::StateNum1IntegerPart::equalButtonClicked()
{
    // Nothing to do.
}

void Calculator::StateNum1IntegerPart::allClearButtonClicked()
{
    State::allClearButtonClicked();
}

void Calculator::StateNum1IntegerPart::clearButtonClicked()
{
    getLineInput()->clear();
    setState( STATE_NUM1_WAITING );
}

Calculator::StateNum1DecimalPart::StateNum1DecimalPart(Calculator *calculator)
    : State(calculator,"NUM1_DECIMAL_PART")
{
}

Calculator::StateNum1DecimalPart::~StateNum1DecimalPart()
{
}

void Calculator::StateNum1DecimalPart::disableIrrelevantButtons()
{
    State::disableIrrelevantButtons();
    m_calculator->getDotButton()  ->setDisabled(true);
    m_calculator->getEqualButton()->setDisabled(true);
}

void Calculator::StateNum1DecimalPart::numberButtonClicked(QString digit)
{
    State::numberButtonClicked(digit);
}
void Calculator::StateNum1DecimalPart::dotButtonClicked()
{
    // Nothing to do
}

void Calculator::StateNum1DecimalPart::signButtonClicked()
{
    State::signButtonClicked();
}

void Calculator::StateNum1DecimalPart::operatorButtonClicked(QString label, func_ptr func)
{
    m_calculator->m_currentData = getLineInput()->text();
    State::operatorButtonClicked(label,func);
}

void Calculator::StateNum1DecimalPart::equalButtonClicked()
{
    // Nothing to do.
}

void Calculator::StateNum1DecimalPart::allClearButtonClicked()
{
    State::allClearButtonClicked();
}

void Calculator::StateNum1DecimalPart::clearButtonClicked()
{
    getLineInput()->clear();
    setState( STATE_NUM1_WAITING );
}

Calculator::StateNum2Waiting::StateNum2Waiting(Calculator *calculator)
    : State(calculator,"NUM2_WAITING")
{
}

Calculator::StateNum2Waiting::~StateNum2Waiting()
{
}

void Calculator::StateNum2Waiting::disableIrrelevantButtons()
{
    State::disableIrrelevantButtons();
    m_calculator->getAddButton()  ->setDisabled(true);
    m_calculator->getSubButton()  ->setDisabled(true);
    m_calculator->getMulButton()  ->setDisabled(true);
    m_calculator->getDivButton()  ->setDisabled(true);
    m_calculator->getEqualButton()->setDisabled(true);
}

void Calculator::StateNum2Waiting::numberButtonClicked(QString digit)
{
    State::numberButtonClicked(digit);
    setState( STATE_NUM2_INTEGER_PART );
}

void Calculator::StateNum2Waiting::dotButtonClicked()
{
    QString instr = getLineInput()->text();
    instr += "0.";
    getLineInput()->setText( instr );
    setState( STATE_NUM2_DECIMAL_PART );
}

void Calculator::StateNum2Waiting::signButtonClicked()
{
    State::signButtonClicked();
}

void Calculator::StateNum2Waiting::operatorButtonClicked(QString label, func_ptr func)
{
    // Nothing to do.
}

void Calculator::StateNum2Waiting::equalButtonClicked()
{
    // Nothing to do.
}

void Calculator::StateNum2Waiting::allClearButtonClicked()
{
    State::allClearButtonClicked();
}

void Calculator::StateNum2Waiting::clearButtonClicked()
{
    // Nothing to do.
}

Calculator::StateNum2IntegerPart::StateNum2IntegerPart(Calculator *calculator)
    : State(calculator,"NUM2_INTEGER_PART")
{
}

Calculator::StateNum2IntegerPart::~StateNum2IntegerPart()
{
}

void Calculator::StateNum2IntegerPart::disableIrrelevantButtons()
{
    State::disableIrrelevantButtons();
}

void Calculator::StateNum2IntegerPart::numberButtonClicked(QString digit)
{
    State::numberButtonClicked(digit);
}

void Calculator::StateNum2IntegerPart::dotButtonClicked()
{
    QString instr = getLineInput()->text();
    instr += ".";
    getLineInput()->setText( instr );
    setState( STATE_NUM2_DECIMAL_PART );
}

void Calculator::StateNum2IntegerPart::signButtonClicked()
{
    State::signButtonClicked();
}

void Calculator::StateNum2IntegerPart::operatorButtonClicked(QString label, func_ptr func)
{
    double answer = m_calculator->m_operation(
                        m_calculator->m_currentData.toDouble(),
                        getLineInput()->text().toDouble() );
    m_calculator->m_currentData = QString::number(answer);
    State::operatorButtonClicked(label,func);
}

void Calculator::StateNum2IntegerPart::equalButtonClicked()
{
    double answer = m_calculator->m_operation(
                        m_calculator->m_currentData.toDouble(),
                        getLineInput()->text().toDouble() );
    getLineDisplay()->setText( QString::number(answer) );
    getLineInput()->clear();
    m_calculator->m_operation = 0;
    setState( STATE_SHOW_RESULT );
}

void Calculator::StateNum2IntegerPart::allClearButtonClicked()
{
    State::allClearButtonClicked();
}

void Calculator::StateNum2IntegerPart::clearButtonClicked()
{
    getLineInput()->clear();
    setState( STATE_NUM2_WAITING );
}

Calculator::StateNum2DecimalPart::StateNum2DecimalPart(Calculator *calculator)
    : State(calculator,"NUM2_DECIMAL_PART")
{
}

Calculator::StateNum2DecimalPart::~StateNum2DecimalPart()
{
}

void Calculator::StateNum2DecimalPart::disableIrrelevantButtons()
{
    State::disableIrrelevantButtons();
    m_calculator->getDotButton()->setDisabled(true);
}

void Calculator::StateNum2DecimalPart::numberButtonClicked(QString digit)
{
    State::numberButtonClicked(digit);
}

void Calculator::StateNum2DecimalPart::dotButtonClicked()
{
    // Nothing to do
}

void Calculator::StateNum2DecimalPart::signButtonClicked()
{
    State::signButtonClicked();
}

void Calculator::StateNum2DecimalPart::operatorButtonClicked(QString label, func_ptr func)
{
    State::operatorButtonClicked(label,func);
}

void Calculator::StateNum2DecimalPart::equalButtonClicked()
{
    double answer = m_calculator->m_operation(
                        m_calculator->m_currentData.toDouble(),
                        getLineInput()->text().toDouble() );
    getLineDisplay()->setText( QString::number(answer) );
    getLineInput()->clear();
    m_calculator->m_operation = 0;
    setState( STATE_SHOW_RESULT );
}

void Calculator::StateNum2DecimalPart::allClearButtonClicked()
{
    State::allClearButtonClicked();
}

void Calculator::StateNum2DecimalPart::clearButtonClicked()
{
    getLineInput()->clear();
    setState( STATE_NUM2_WAITING );
}

Calculator::StateShowResult::StateShowResult(Calculator *calculator)
    : State(calculator,"SHOW_RESULT")
{
}

Calculator::StateShowResult::~StateShowResult()
{
}

void Calculator::StateShowResult::disableIrrelevantButtons()
{
    State::disableIrrelevantButtons();
    m_calculator->getEqualButton()->setDisabled(true);
}

void Calculator::StateShowResult::numberButtonClicked(QString digit)
{
    State::numberButtonClicked(digit);
    setState( STATE_NUM1_INTEGER_PART );
}

void Calculator::StateShowResult::dotButtonClicked()
{
    QString instr = getLineInput()->text();
    instr += "0.";
    getLineInput()->setText( instr );
    setState( STATE_NUM1_DECIMAL_PART );
}

void Calculator::StateShowResult::signButtonClicked()
{
    State::signButtonClicked();
}

void Calculator::StateShowResult::operatorButtonClicked(QString label, func_ptr func)
{
    m_calculator->m_currentData = getLineDisplay()->text();
    State::operatorButtonClicked(label,func);
}

void Calculator::StateShowResult::equalButtonClicked()
{
    // Nothing to do.
}

void Calculator::StateShowResult::allClearButtonClicked()
{
    State::allClearButtonClicked();
}

void Calculator::StateShowResult::clearButtonClicked()
{
}
