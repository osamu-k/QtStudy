#ifndef CALCULATOR_H
#define CALCULATOR_H

#include <QMap>
#include <QWidget>

class QLayout;
class QLineEdit;
class QPushButton;

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

    bool calculateAdd();
    bool calculateSub();
    bool calculateMul();
    bool calculateDiv();
    void resetCurrentValue();
    void showCurrentValue();

    QLineEdit *m_display1;
    QLineEdit *m_display2;

    typedef bool (Calculator::*operatorFuncPtr)();
    QMap<QObject *,int> m_numberMap;
    QMap<QObject *, operatorFuncPtr> m_operatorMap;
    QMap<QObject *, QString> m_operatorSymbol;
    long m_currentValue;
    int m_currentSign;
    bool m_digitCount;
    long m_lastValue;
    bool m_showingAnswer;
    operatorFuncPtr m_operatorFunc;
};

#endif // CALCULATOR_H
