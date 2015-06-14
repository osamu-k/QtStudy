#include "calculator.h"
#include <QPushButton>

Calculator::Calculator(QWidget *parent) : QWidget(parent)
{
    QPushButton *button0 = new QPushButton("0",this);
}

Calculator::~Calculator()
{
}
