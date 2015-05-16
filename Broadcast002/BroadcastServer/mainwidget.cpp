#include <QApplication>
#include <QDebug>
#include <QPushButton>
#include <QVBoxLayout>
#include "mainwidget.h"

MainWidget::MainWidget(QWidget *parent)
    : QWidget(parent)
{
    QPushButton *buttonStartListen = new QPushButton("Start Listen");
    QPushButton *buttonStopListen = new QPushButton("Stop Listen");
    QPushButton *buttonQuit = new QPushButton("quit");
    QVBoxLayout *layout = new QVBoxLayout;
    layout->addWidget(buttonStartListen);
    layout->addWidget(buttonStopListen);
    layout->addWidget(buttonQuit);
    setLayout(layout);

    connect(buttonStartListen,&QPushButton::clicked,this,&MainWidget::startListen);
    connect(buttonStopListen,&QPushButton::clicked,this,&MainWidget::stopListen);
    connect(buttonQuit,&QPushButton::clicked,qApp,&QApplication::quit);
}

MainWidget::~MainWidget()
{

}

void MainWidget::startListen()
{
    qDebug() << "Start Listen.";
    m_broadcastServer.listen();
}

void MainWidget::stopListen()
{
    qDebug() << "Stop Listen";
}
