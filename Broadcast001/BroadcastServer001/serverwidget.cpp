#include <QPushButton>
#include <QVBoxLayout>
#include "serverwidget.h"

ServerWidget::ServerWidget(QWidget *parent) :
    QWidget(parent)
{
    QPushButton *buttonListen = new QPushButton("listen");
    QVBoxLayout *layout = new QVBoxLayout;
    layout->addWidget(buttonListen);
    setLayout(layout);

    connect(buttonListen,&QPushButton::clicked,this,&ServerWidget::startListen);
}

ServerWidget::~ServerWidget()
{
}

void ServerWidget::startListen()
{
    m_server.startListen(12345);
}
