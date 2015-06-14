#ifndef CALCULATOR_H
#define CALCULATOR_H

#include <QWidget>

class QLayout;

class Calculator : public QWidget
{
    Q_OBJECT
public:
    explicit Calculator(QWidget *parent = 0);
    ~Calculator();

signals:

public slots:

private:
    QLayout *setupNumberButtons();
    QLayout *setupVariousButtons();
    QLayout *setupOperatorButtons();
};

#endif // CALCULATOR_H
