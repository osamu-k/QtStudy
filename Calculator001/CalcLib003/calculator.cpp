#include "calculator.h"
#include <QGridLayout>
#include <QPushButton>

#include <QDebug>

Calculator::Calculator(QWidget *parent) : QWidget(parent)
{
    QGridLayout *gridNumber = new QGridLayout;
    for( int i = 0; i <= 9; i++ ){
        QPushButton *button = new QPushButton(QString::number(i),this);
        int row = 0, col = 0, rowspan = 1, colspan = 1;
        if( i == 0 ){
            row = 3;
            col = 0;
            colspan = 3;
        }
        else{
            row = 2 - (i - 1) / 3;
            col = (i - 1) % 3;
        }
        gridNumber->addWidget(button,row,col,rowspan,colspan);
    }
    setLayout(gridNumber);
}

Calculator::~Calculator()
{
}
