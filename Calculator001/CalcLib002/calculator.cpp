#include "calculator.h"
#include <QPushButton>

Calculator::Calculator(QWidget *parent) : QWidget(parent)
{
    for( int i = 0; i <= 9; i++ ){
        QPushButton *button = new QPushButton(QString::number(i),this);
    }
}

Calculator::~Calculator()
{
}
