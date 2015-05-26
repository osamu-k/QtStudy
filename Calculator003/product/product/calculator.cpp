#include "calculator.h"

#include <QDebug>
#include <QGridLayout>
#include <QHBoxLayout>
#include <QLineEdit>
#include <QPushButton>
#include <QVBoxLayout>

#include <algorithm>
using namespace std;

Calculator::Calculator(QWidget *parent)
    : QWidget(parent)
    , m_stateNum1Waiting(this)
    , m_stateNum1Entered(this)
    , m_stateNum2Waiting(this)
    , m_stateNum2Entered(this)
    , m_stateShowResult(this)
    , m_state(STATE_NUM1_WAITING)
{
    lineDisplay = createLineEdit("lineDisplay");
    lineInput = createLineEdit("lineInput");

    button0 = createNumberButton( 0 );
    button1 = createNumberButton( 1 );
    button2 = createNumberButton( 2 );
    button3 = createNumberButton( 3 );
    button4 = createNumberButton( 4 );
    button5 = createNumberButton( 5 );
    button6 = createNumberButton( 6 );
    button7 = createNumberButton( 7 );
    button8 = createNumberButton( 8 );
    button9 = createNumberButton( 9 );

    buttonAdd = createOperatorButton( "+", "buttonAdd", [](long x, long y)->long{ return x + y; });
    buttonSub = createOperatorButton( "-", "buttonSub", [](long x, long y)->long{ return x - y; });
    buttonMul = createOperatorButton( "×", "buttonMul", [](long x, long y)->long{ return x * y; });
    buttonDiv = createOperatorButton( "÷", "buttonDiv", [](long x, long y)->long{ return x / y; });

    buttonSign = createButton("+/-","buttonSign"    ,SLOT(signButtonClicked())     );
    buttonEq   = createButton("="  ,"buttonEqual"   ,SLOT(equalButtonClicked())    );
    buttonAC   = createButton("AC" ,"buttonAllClear",SLOT(allClearButtonClicked()) );
    buttonC    = createButton("C"  ,"buttonClear"   ,SLOT(clearButtonClicked())    );

    QVBoxLayout *vboxLayout = new QVBoxLayout;
    vboxLayout->addWidget(lineDisplay);
    vboxLayout->addWidget(lineInput);

    QHBoxLayout *hboxLayout1 = new QHBoxLayout;
    hboxLayout1->setMargin(0);

    hboxLayout1->addWidget(buttonAC);
    hboxLayout1->addWidget(buttonC );
    hboxLayout1->addWidget(buttonSign);

    QGridLayout *gridLayout = new QGridLayout;
    gridLayout->setMargin(0);

    gridLayout->addWidget(button7   ,0,0);
    gridLayout->addWidget(button8   ,0,1);
    gridLayout->addWidget(button9   ,0,2);

    gridLayout->addWidget(button4   ,1,0);
    gridLayout->addWidget(button5   ,1,1);
    gridLayout->addWidget(button6   ,1,2);

    gridLayout->addWidget(button1   ,2,0);
    gridLayout->addWidget(button2   ,2,1);
    gridLayout->addWidget(button3   ,2,2);

    gridLayout->addWidget(button0   ,3,0,1,3);

    QVBoxLayout *vboxLayout1 = new QVBoxLayout;
    vboxLayout1->addLayout( hboxLayout1 );
    vboxLayout1->addLayout( gridLayout );

    QVBoxLayout *vboxLayout2 = new QVBoxLayout;
    vboxLayout2->setMargin(0);
    vboxLayout2->addWidget(buttonDiv);
    vboxLayout2->addWidget(buttonMul);
    vboxLayout2->addWidget(buttonSub);
    vboxLayout2->addWidget(buttonAdd);
    vboxLayout2->addWidget(buttonEq );

    QHBoxLayout *hboxLayout2 = new QHBoxLayout;
    hboxLayout2->addLayout( vboxLayout1 );
    hboxLayout2->addLayout( vboxLayout2 );
    hboxLayout2->setStretchFactor( vboxLayout1, 3 );
    hboxLayout2->setStretchFactor( vboxLayout2, 1 );

    QVBoxLayout *vboxLayout3 = new QVBoxLayout;
    vboxLayout3->addWidget(lineDisplay);
    vboxLayout3->addWidget(lineInput);
    vboxLayout3->addLayout( hboxLayout2 );

    setLayout( vboxLayout3 );

    m_stateMap[STATE_NUM1_WAITING] = &m_stateNum1Waiting;
    m_stateMap[STATE_NUM1_ENTERED] = &m_stateNum1Entered;
    m_stateMap[STATE_NUM2_WAITING] = &m_stateNum2Waiting;
    m_stateMap[STATE_NUM2_ENTERED] = &m_stateNum2Entered;
    m_stateMap[STATE_SHOW_RESULT ] = &m_stateShowResult;

    m_state = STATE_NUM1_WAITING;
    m_stateMap[ m_state ]->disableIrrelevantButtons();
}

Calculator::~Calculator()
{
}

//QLineEdit *Calculator::createLineDisplay()
//{
//    return createLineEdit("lineDisplay");
//}

//QLineEdit *Calculator::createLineInput()
//{
//    return createLineEdit("lineInput");
//}

QLineEdit *Calculator::createLineEdit( QString objectName )
{
    QLineEdit *lineEdit = new QLineEdit;
    lineEdit->setObjectName(objectName);
    lineEdit->setReadOnly(true);
    lineEdit->setAlignment(Qt::AlignRight);
    return lineEdit;
}

QPushButton *Calculator::createButton( QString label, QString objectName, const char* slot )
{
    QPushButton *button = new QPushButton(label);
    button->setObjectName(objectName);
    connect( button, SIGNAL(clicked()), this, slot );
    return button;
}

QPushButton *Calculator::createNumberButton( int i )
{
    QString label = QString::number(i);
    QString objectName = QString("button%1").arg(i);
    QPushButton *button = createButton( label, objectName, SLOT(numberButtonClicked()) );
    m_numberButtonMap[button] = label;
    return button;
}

QPushButton *Calculator::createOperatorButton( QString operatorString, QString objectName, func_ptr func )
{
    QPushButton *button = createButton( operatorString, objectName, SLOT(operatorButtonClicked()) );
    m_operatorButtonMap[button] = operatorString;
    m_buttonFunctionMap[button] = func;
    return button;
}

void Calculator::disableIrrelevantButtons()
{
    m_stateMap[m_state]->disableIrrelevantButtons();
}

void Calculator::numberButtonClicked()
{
    QPushButton *button = qobject_cast<QPushButton*>( sender() );
    QString digit = m_numberButtonMap[button];
    m_stateMap[m_state]->numberButtonClicked(digit);
}

void Calculator::operatorButtonClicked()
{
    QPushButton *button = qobject_cast<QPushButton*>( sender() );
    QString operatorString = m_operatorButtonMap[button];
    func_ptr func = m_buttonFunctionMap[button];
    m_stateMap[m_state]->operatorButtonClicked(operatorString,func);
}

void Calculator::signButtonClicked()
{
    m_stateMap[m_state]->signButtonClicked();
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

Calculator::State::State(Calculator *calculator)
    : m_calculator(calculator)
{
}

Calculator::State::~State()
{
}

void Calculator::State::disableIrrelevantButtons()
{
    m_calculator->buttonAdd  ->setDisabled(false);
    m_calculator->buttonSub  ->setDisabled(false);
    m_calculator->buttonMul  ->setDisabled(false);
    m_calculator->buttonDiv  ->setDisabled(false);
    m_calculator->buttonEq   ->setDisabled(false);
}

void Calculator::State::numberButtonClicked(QString digit)
{
    getLineInput()->setText( getLineInput()->text() + digit );
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
    double answer = m_calculator->m_operation(
                        m_calculator->m_currentData.toDouble(),
                        getLineInput()->text().toDouble() );
    getLineDisplay()->setText( QString::number(answer) );
    getLineInput()->clear();
    m_calculator->m_operation = 0;
    setState( STATE_SHOW_RESULT );
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

// State: NUM1_WAITING

Calculator::StateNum1Waiting::StateNum1Waiting(Calculator *calculator)
    : State(calculator)
{
}

void Calculator::StateNum1Waiting::disableIrrelevantButtons()
{
    State::disableIrrelevantButtons();
    m_calculator->buttonAdd  ->setDisabled(true);
    m_calculator->buttonSub  ->setDisabled(true);
    m_calculator->buttonMul  ->setDisabled(true);
    m_calculator->buttonDiv  ->setDisabled(true);
    m_calculator->buttonEq   ->setDisabled(true);
}

void Calculator::StateNum1Waiting::numberButtonClicked(QString digit)
{
    State::numberButtonClicked(digit);
    setState( STATE_NUM1_ENTERED );
}

// State: NUM1_ENTERED

Calculator::StateNum1Entered::StateNum1Entered(Calculator *calculator)
    : State(calculator)
{
}

void Calculator::StateNum1Entered::disableIrrelevantButtons()
{
    State::disableIrrelevantButtons();
    m_calculator->buttonEq->setDisabled(true);
}

void Calculator::StateNum1Entered::numberButtonClicked(QString digit)
{
    State::numberButtonClicked(digit);
}

void Calculator::StateNum1Entered::operatorButtonClicked(QString label, func_ptr func)
{
    m_calculator->m_currentData = getLineInput()->text();
    State::operatorButtonClicked(label,func);
}

void Calculator::StateNum1Entered::clearButtonClicked()
{
    getLineInput()->clear();
    setState( STATE_NUM1_WAITING );
}

// State: NUM2_WAITING

Calculator::StateNum2Waiting::StateNum2Waiting(Calculator *calculator)
    : State(calculator)
{
}

void Calculator::StateNum2Waiting::disableIrrelevantButtons()
{
    State::disableIrrelevantButtons();
    m_calculator->buttonAdd  ->setDisabled(true);
    m_calculator->buttonSub  ->setDisabled(true);
    m_calculator->buttonMul  ->setDisabled(true);
    m_calculator->buttonDiv  ->setDisabled(true);
    m_calculator->buttonEq   ->setDisabled(true);
}

void Calculator::StateNum2Waiting::numberButtonClicked(QString digit)
{
    State::numberButtonClicked(digit);
    setState( STATE_NUM2_ENTERED );
}

// State: NUM2_ENTERED

Calculator::StateNum2Entered::StateNum2Entered(Calculator *calculator)
    : State(calculator)
{
}

void Calculator::StateNum2Entered::disableIrrelevantButtons()
{
    State::disableIrrelevantButtons();
}

void Calculator::StateNum2Entered::numberButtonClicked(QString digit)
{
    State::numberButtonClicked(digit);
}

void Calculator::StateNum2Entered::operatorButtonClicked(QString label, func_ptr func)
{
    long answer = m_calculator->m_operation(
                        m_calculator->m_currentData.toLong(),
                        getLineInput()->text().toLong() );
    m_calculator->m_currentData = QString::number(answer);
    State::operatorButtonClicked(label,func);
}

void Calculator::StateNum2Entered::clearButtonClicked()
{
    getLineInput()->clear();
    setState( STATE_NUM2_WAITING );
}

// State: SHOW_RESULT

Calculator::StateShowResult::StateShowResult(Calculator *calculator)
    : State(calculator)
{
}

void Calculator::StateShowResult::disableIrrelevantButtons()
{
    State::disableIrrelevantButtons();
    m_calculator->buttonEq->setDisabled(true);
}

void Calculator::StateShowResult::numberButtonClicked(QString digit)
{
    State::numberButtonClicked(digit);
    setState( STATE_NUM1_ENTERED );
}

void Calculator::StateShowResult::operatorButtonClicked(QString label, func_ptr func)
{
    m_calculator->m_currentData = getLineDisplay()->text();
    State::operatorButtonClicked(label,func);
}
