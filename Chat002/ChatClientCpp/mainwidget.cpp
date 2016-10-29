#include "mainwidget.h"

#include <QHBoxLayout>
#include <QPushButton>
#include <QSplitter>
#include <QVBoxLayout>

#include <QDebug>

MainWidget::MainWidget(QWidget *parent)
    : QWidget(parent)
    , m_textLog(nullptr)
    , m_textInput(nullptr)
    , m_chatClient(nullptr)
{
    m_textLog = new QTextEdit;
    m_textLog->setReadOnly(true);

    m_textInput = new QTextEdit;

    QSplitter *splitter = new QSplitter;
    splitter->setOrientation(Qt::Vertical);
    splitter->addWidget(m_textLog);
    splitter->addWidget(m_textInput);

    QPushButton *buttonSend = new QPushButton(tr("Send"));
    QPushButton *buttonClear = new QPushButton(tr("Clear"));

    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->addWidget(splitter);

    QHBoxLayout *buttonLayout = new QHBoxLayout;
    buttonLayout->addStretch();
    buttonLayout->addWidget(buttonClear);
    buttonLayout->addWidget(buttonSend);
    buttonLayout->addStretch();

    layout->addLayout(buttonLayout);

    resize(400,400);

    connect( buttonClear, &QPushButton::clicked, this, &MainWidget::clearClicked );
    connect( buttonSend, &QPushButton::clicked, this, &MainWidget::sendClicked );

    m_chatClient = ChatClient::instance();
    connect( m_chatClient, &ChatClient::received, this, &MainWidget::messageReceived );
}

MainWidget::~MainWidget()
{

}

void MainWidget::clearClicked()
{
    qDebug() << "clearClicked";
    m_textInput->clear();
}

void MainWidget::sendClicked()
{
    qDebug() << "sendClicked";
    if( ! m_textInput->toPlainText().isEmpty() ){
        m_chatClient->send(m_textInput->toPlainText());
        m_textInput->clear();
    }
    else{
        qDebug() << "editInput is empty.";
    }
}

void MainWidget::messageReceived(QString message)
{
    m_textLog->append(message);
}
