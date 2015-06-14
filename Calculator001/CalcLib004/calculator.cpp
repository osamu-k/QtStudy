#include "calculator.h"
#include <QGridLayout>
#include <QHBoxLayout>
#include <QPushButton>
#include <QVBoxLayout>

#include <QDebug>

Calculator::Calculator(QWidget *parent) : QWidget(parent)
{
    QLayout *layoutNumber = setupNumberButtons();
    QLayout *layoutVarious = setupVariousButtons();

    QVBoxLayout *layout = new QVBoxLayout;
    layout->addLayout(layoutVarious);
    layout->addLayout(layoutNumber);
    setLayout(layout);
}

Calculator::~Calculator()
{
}

QLayout *Calculator::setupNumberButtons()
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
    return gridNumber;
}

QLayout *Calculator::setupVariousButtons()
{
    QPushButton *buttonAC =   new QPushButton("AC");
    QPushButton *buttonC  =   new QPushButton("C");
    QPushButton *buttonSign = new QPushButton("+/-");

    QHBoxLayout *layout = new QHBoxLayout;
    layout->addWidget(buttonAC);
    layout->addWidget(buttonC);
    layout->addWidget(buttonSign);
    return layout;
}
