#ifndef CALCULATORSTATE
#define CALCULATORSTATE

#include "calculator.h"
#include <QPushButton>

class CalcState
{
public:
    CalcState(Calculator *calc) : m_calc(calc){}
    virtual ~CalcState(){}

    virtual void disableButtons() = 0;
    virtual void numberButtonClicked() = 0;
    virtual void operatorButtonClicked() = 0;
    virtual void equalButtonClicked() = 0;
    virtual void signButtonClicked() = 0;
    virtual void clearButtonClicked() = 0;
    virtual void allClearButtonClicked() = 0;
protected:
    Calculator *m_calc;
};

class CalcStateWaitingNumber1 : public CalcState
{
public:
    CalcStateWaitingNumber1(Calculator *calc) : CalcState(calc){}

    void disableButtons()
    {
    }
    void numberButtonClicked()
    {
        m_calc->appendNumber();
        m_calc->setState(CALC_STATE_READING_VALUE1);
    }
    void operatorButtonClicked()
    {
    }
    void equalButtonClicked()
    {
    }
    void signButtonClicked()
    {
        m_calc->changeSign();
//        m_calc->showSign();
    }
    void clearButtonClicked()
    {
        m_calc->clearCurrentValue();
    }
    void allClearButtonClicked()
    {
        m_calc->clearAll();
    }
};

class CalcStateReadingNumber1 : public CalcState
{
public:
    CalcStateReadingNumber1(Calculator *calc) : CalcState(calc){}

    void disableButtons()
    {
        m_calc->m_buttonAdd->setDisabled(false);
        m_calc->m_buttonSub->setDisabled(false);
        m_calc->m_buttonMul->setDisabled(false);
        m_calc->m_buttonDiv->setDisabled(false);
    }
    void numberButtonClicked()
    {
        m_calc->appendNumber();
    }
    void operatorButtonClicked()
    {
        m_calc->storeCurrentValue();
        m_calc->storeOperator();
        m_calc->setState(CALC_STATE_WAITING_VALUE2);
    }
    void equalButtonClicked()
    {
    }
    void signButtonClicked()
    {
        m_calc->changeSign();
//        m_calc->showCurrentValue();
    }
    void clearButtonClicked()
    {
        m_calc->clearCurrentValue();
        m_calc->setState(CALC_STATE_WAITING_VALUE1);
    }
    void allClearButtonClicked()
    {
        m_calc->clearAll();
        m_calc->setState(CALC_STATE_WAITING_VALUE1);
    }
};

class CalcStateWaitingNumber2 : public CalcState
{
public:
    CalcStateWaitingNumber2(Calculator *calc) : CalcState(calc){}

    void disableButtons()
    {
    }
    void numberButtonClicked()
    {
        m_calc->appendNumber();
        m_calc->setState(CALC_STATE_READING_VALUE2);
    }
    void operatorButtonClicked()
    {
    }
    void equalButtonClicked()
    {
    }
    void signButtonClicked()
    {
        m_calc->changeSign();
//        m_calc->showSign();
    }
    void clearButtonClicked()
    {
        m_calc->clearCurrentValue();
    }
    void allClearButtonClicked()
    {
        m_calc->clearAll();
        m_calc->setState(CALC_STATE_WAITING_VALUE1);
    }
};

class CalcStateReadingNumber2 : public CalcState
{
public:
    CalcStateReadingNumber2(Calculator *calc) : CalcState(calc){}

    void disableButtons()
    {
        m_calc->m_buttonAdd->setDisabled(false);
        m_calc->m_buttonSub->setDisabled(false);
        m_calc->m_buttonMul->setDisabled(false);
        m_calc->m_buttonDiv->setDisabled(false);
        m_calc->m_buttonEqual->setDisabled(false);
    }
    void numberButtonClicked()
    {
        m_calc->appendNumber();
    }
    void operatorButtonClicked()
    {
        if( m_calc->calculateOperator() ){
            m_calc->storeOperator();
            m_calc->setState(CALC_STATE_WAITING_VALUE2);
        }
    }
    void equalButtonClicked()
    {
        if( m_calc->calculateOperator() ){
            m_calc->setState(CALC_STATE_SHOWING_ANSWER);
        }
    }
    void signButtonClicked()
    {
        m_calc->changeSign();
//        m_calc->showCurrentValue();
    }
    void clearButtonClicked()
    {
        m_calc->clearCurrentValue();
        m_calc->setState(CALC_STATE_WAITING_VALUE2);
    }
    void allClearButtonClicked()
    {
        m_calc->clearAll();
        m_calc->setState(CALC_STATE_WAITING_VALUE1);
    }
};

class CalcStateShowingAnswer : public CalcState
{
public:
    CalcStateShowingAnswer(Calculator *calc) : CalcState(calc){}

    void disableButtons()
    {
        m_calc->m_buttonAdd->setDisabled(false);
        m_calc->m_buttonSub->setDisabled(false);
        m_calc->m_buttonMul->setDisabled(false);
        m_calc->m_buttonDiv->setDisabled(false);
    }
    void numberButtonClicked()
    {
        m_calc->appendNumber();
        m_calc->setState(CALC_STATE_READING_VALUE1_SHOWING_ANSWER);
    }
    void operatorButtonClicked()
    {
        m_calc->storeOperator();
        m_calc->setState(CALC_STATE_WAITING_VALUE2);
    }
    void equalButtonClicked()
    {
    }
    void signButtonClicked()
    {
        m_calc->changeSign();
//        m_calc->showSign();
    }
    void clearButtonClicked()
    {
        m_calc->clearCurrentValue();
    }
    void allClearButtonClicked()
    {
        m_calc->clearAll();
        m_calc->setState(CALC_STATE_WAITING_VALUE1);
    }
};

class CalcStateReadingNumber1ShowingAnswer : public CalcState
{
public:
    CalcStateReadingNumber1ShowingAnswer(Calculator *calc) : CalcState(calc){}

    void disableButtons()
    {
        m_calc->m_buttonAdd->setDisabled(false);
        m_calc->m_buttonSub->setDisabled(false);
        m_calc->m_buttonMul->setDisabled(false);
        m_calc->m_buttonDiv->setDisabled(false);
    }
    void numberButtonClicked()
    {
        m_calc->appendNumber();
    }
    void operatorButtonClicked()
    {
        m_calc->storeCurrentValue();
        m_calc->storeOperator();
        m_calc->setState(CALC_STATE_WAITING_VALUE2);
    }
    void equalButtonClicked()
    {
    }
    void signButtonClicked()
    {
        m_calc->changeSign();
//        m_calc->showCurrentValue();
    }
    void clearButtonClicked()
    {
        m_calc->clearCurrentValue();
        m_calc->setState(CALC_STATE_SHOWING_ANSWER);
    }
    void allClearButtonClicked()
    {
        m_calc->clearAll();
        m_calc->setState(CALC_STATE_WAITING_VALUE1);
    }
};

#endif // CALCULATORSTATE

