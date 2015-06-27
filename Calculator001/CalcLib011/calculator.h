#ifndef CALCULATOR_H
#define CALCULATOR_H

#include <QMap>
#include <QWidget>

class QLayout;
class QLineEdit;
class QPushButton;

class CalcState;
class CalcStateWaitingNumber1;
class CalcStateReadingNumber1;
class CalcStateWaitingNumber2;
class CalcStateReadingNumber2;
class CalcStateShowingAnswer;
class CalcStateReadingNumber1ShowingAnswer;

enum CalcStateID {
    CALC_STATE_WAITING_VALUE1,
    CALC_STATE_READING_VALUE1,
    CALC_STATE_WAITING_VALUE2,
    CALC_STATE_READING_VALUE2,
    CALC_STATE_SHOWING_ANSWER,
    CALC_STATE_READING_VALUE1_SHOWING_ANSWER
};

class Calculator : public QWidget
{
    Q_OBJECT
public:
    explicit Calculator(QWidget *parent = 0);
    ~Calculator();

    static const char *operatorSymbolAdd;
    static const char *operatorSymbolSub;
    static const char *operatorSymbolMul;
    static const char *operatorSymbolDiv;

signals:

public slots:

private slots:
    void numberButtonClicked();
    void operatorButtonClicked();
    void equalButtonClicked();
    void signButtonClicked();
    void clearButtonClicked();
    void allClearButtonClicked();

private:
    QLayout *setupNumberButtons();
    QLayout *setupVariousButtons();
    QLayout *setupOperatorButtons();
    QLayout *setupDisplays();

    void setupState();

    void setState(CalcStateID state);
    void disableButtons();

    void appendNumber();

    bool calculateOperator();

    bool calculateAdd();
    bool calculateSub();
    bool calculateMul();
    bool calculateDiv();

    void storeCurrentValue();
    void storeOperator();

    void changeSign();

    void clearCurrentValue();
    void clearAll();

    void showCurrentValue();
    void showLastValue();

    QLineEdit *m_display1;
    QLineEdit *m_display2;

    QPushButton *m_buttonAdd;
    QPushButton *m_buttonSub;
    QPushButton *m_buttonMul;
    QPushButton *m_buttonDiv;
    QPushButton *m_buttonEqual;

    typedef bool (Calculator::*operatorFuncPtr)();
    QMap<QObject *,int> m_numberMap;
    QMap<QObject *, operatorFuncPtr> m_operatorMap;
    QMap<QObject *, QString> m_operatorSymbol;
    long m_currentValue;
    int m_currentSign;
    long m_lastValue;
    operatorFuncPtr m_operatorFunc;

    CalcStateID m_stateID;
    QMap<CalcStateID,CalcState *> m_stateMap;

    friend class CalcState;
    friend class CalcStateWaitingNumber1;
    friend class CalcStateReadingNumber1;
    friend class CalcStateWaitingNumber2;
    friend class CalcStateReadingNumber2;
    friend class CalcStateShowingAnswer;
    friend class CalcStateReadingNumber1ShowingAnswer;
};

#endif // CALCULATOR_H
