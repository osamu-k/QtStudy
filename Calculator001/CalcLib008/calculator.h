#ifndef CALCULATOR_H
#define CALCULATOR_H

#include <QWidget>

class QLayout;
class QLineEdit;

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

    QLineEdit *m_display1;
    QLineEdit *m_display2;
};

#endif // CALCULATOR_H
