#ifndef CALCULATOR_H
#define CALCULATOR_H

#include <QMap>
#include <QPushButton>
#include <QWidget>

#include <functional>

class QGridLayout;
class QLineEdit;
class QPushButton;

class Calculator : public QWidget
{
    Q_OBJECT

public:
    explicit Calculator(QWidget *parent = 0);
    ~Calculator();

signals:

public slots:

private:
    typedef long(*func_ptr)(long, long);

private slots:
    void numberButtonClicked(QString digit);
    void signButtonClicked();
    void operatorButtonClicked(QString label, func_ptr func);
    void equalButtonClicked();
    void allClearButtonClicked();
    void clearButtonClicked();

private:
    QLineEdit *createLineDisplay();
    QLineEdit *createLineInput();
    QLineEdit *createLineEdit(QString objectName);

    QPushButton *createNumberButton( int i );
    QPushButton *createSignButton();
    QPushButton *createAddButton();
    QPushButton *createSubButton();
    QPushButton *createMulButton();
    QPushButton *createDivButton();
    QPushButton *createOperatorButton( QString label, QString objectName, func_ptr func );
    QPushButton *createEqualButton();
    QPushButton *createAllClearButton();
    QPushButton *createClearButton();

    QLineEdit *lineDisplay;
    QLineEdit *lineInput;

    QPushButton *button0;
    QPushButton *button1;
    QPushButton *button2;
    QPushButton *button3;
    QPushButton *button4;
    QPushButton *button5;
    QPushButton *button6;
    QPushButton *button7;
    QPushButton *button8;
    QPushButton *button9;

    QPushButton *buttonSign;

    QPushButton *buttonAdd;
    QPushButton *buttonSub;
    QPushButton *buttonMul;
    QPushButton *buttonDiv;

    QPushButton *buttonEq;

    QPushButton *buttonAC;
    QPushButton *buttonC;

    void disableIrrelevantButtons();

    enum state{
        STATE_NUM1_WAITING,
        STATE_NUM1_ENTERED,
        STATE_NUM2_WAITING,
        STATE_NUM2_ENTERED,
        STATE_SHOW_RESULT
    };

    QString m_currentData;
    func_ptr m_operation;

    class State
    {
    public:
        State(Calculator *calculator);
        virtual ~State();
        virtual void disableIrrelevantButtons();
        virtual void numberButtonClicked(QString digit);
        virtual void signButtonClicked();
        virtual void operatorButtonClicked(QString label, func_ptr func);
        virtual void equalButtonClicked();
        virtual void allClearButtonClicked();
        virtual void clearButtonClicked();
        QLineEdit *getLineDisplay() { return m_calculator->lineDisplay; }
        QLineEdit *getLineInput() { return m_calculator->lineInput; }
    protected:
        void setState( enum state state );
        Calculator *m_calculator;
    };
    class StateNum1Waiting : public State
    {
    public:
        StateNum1Waiting(Calculator *calculator);
        virtual void disableIrrelevantButtons();
        virtual void numberButtonClicked(QString digit);
    };
    class StateNum1Entered : public State
    {
    public:
        StateNum1Entered(Calculator *calculator);
        virtual void disableIrrelevantButtons();
        virtual void numberButtonClicked(QString digit);
        virtual void operatorButtonClicked(QString label, func_ptr func);
        virtual void clearButtonClicked();
    };
    class StateNum2Waiting : public State
    {
    public:
        StateNum2Waiting(Calculator *calculator);
        virtual void disableIrrelevantButtons();
        virtual void numberButtonClicked(QString digit);
    };
    class StateNum2Entered : public State
    {
    public:
        StateNum2Entered(Calculator *calculator);
        virtual void disableIrrelevantButtons();
        virtual void numberButtonClicked(QString digit);
        virtual void operatorButtonClicked(QString label, func_ptr func);
        virtual void clearButtonClicked();
    };
    class StateShowResult : public State
    {
    public:
        StateShowResult(Calculator *calculator);
        virtual void disableIrrelevantButtons();
        virtual void numberButtonClicked(QString digit);
        virtual void operatorButtonClicked(QString label, func_ptr func);
    };

    StateNum1Waiting m_stateNum1Waiting;
    StateNum1Entered m_stateNum1Entered;
    StateNum2Waiting m_stateNum2Waiting;
    StateNum2Entered m_stateNum2Entered;
    StateShowResult  m_stateShowResult;

    QMap<enum state, State *> m_stateMap;

    enum state m_state;
};

#endif // CALCULATOR_H
