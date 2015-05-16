#include <QDataStream>
#include <QPushButton>
#include <QVBoxLayout>
#include "mainwidget.h"
#include "broadcaster.h"

MainWidget::MainWidget(QWidget *parent)
    : QWidget(parent)
{
    m_outputText = new QTextEdit;
    m_outputText->setReadOnly(true);
    m_inputText = new QTextEdit;
    QPushButton *sendButton = new QPushButton("send");
    QPushButton *newButton = new QPushButton("new window");

    QVBoxLayout *layout = new QVBoxLayout;
    layout->addWidget(m_outputText);
    layout->addWidget(m_inputText);
    layout->addWidget(sendButton);
    layout->addWidget(newButton);
    layout->setStretchFactor(m_outputText,8);
    layout->setStretchFactor(m_inputText,2);
    setLayout(layout);

    connect(sendButton,&QPushButton::clicked,this,&MainWidget::sendButtonClicked);
    connect(newButton,&QPushButton::clicked,this,&MainWidget::newButtonClicked);

    m_broadcaster = Broadcaster::instance();
    m_broadcaster->subscribe(this);
}

MainWidget::~MainWidget()
{
    m_broadcaster->unsubscribe(this);
}

void MainWidget::sendButtonClicked()
{
    QString text = m_inputText->toPlainText();
    if( ! text.isEmpty() ){
        QByteArray data;
        QDataStream outStream(&data, QIODevice::WriteOnly);
        outStream << text;
        m_inputText->clear();
        m_broadcaster->post(data);
    }
}

void MainWidget::newButtonClicked()
{
    MainWidget *mainWidget = new MainWidget;
    mainWidget->show();
}

void MainWidget::deliver(QByteArray data)
{
    QDataStream inStream(data);
    QString message;
    inStream >> message;
    m_outputText->append(message);
}
