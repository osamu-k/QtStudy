#ifndef CALCULATOR_H
#define CALCULATOR_H

#include <QMap>
#include <QWidget>

class QLayout;
class QLineEdit;
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

    bool calculateAdd(long operand1, long operand2);
    bool calculateSub(long operand1, long operand2);
    bool calculateMul(long operand1, long operand2);
    bool calculateDiv(long operand1, long operand2);
    void showAnswer(long answer);

    QLineEdit *m_display1;
    QLineEdit *m_display2;

    typedef bool (Calculator::*operatorFuncPtr)(long,long);
    QMap<QPushButton *, operatorFuncPtr> m_operatorMap;
    operatorFuncPtr m_operatorFunc;
};

#endif // CALCULATOR_H
