#include "chatclientwidget.h"

#include <QLabel>
#include <QTimer>
#include <QVBoxLayout>
#include <QDebug>

ChatClientWidget::ChatClientWidget(QWidget *parent)
    : QWidget(parent)
    , m_chatClient(new ChatClient(this))
{
    m_textLog = new QTextEdit;
    m_textLog->setReadOnly(true);

    m_textInput = new QTextEdit;

    m_buttonClear = new QPushButton(tr("clear"));
    m_buttonSend = new QPushButton(tr("send"));

    m_buttonConnect = new QPushButton(tr("connect"));
    m_buttonDisconnect = new QPushButton(tr("disconnect"));

    QLabel *labelAddress = new QLabel(tr("server"));
    m_lineServerAddress = new QLineEdit;
    QLabel *labelPort = new QLabel("port");
    m_lineServerPort = new QLineEdit;

    m_buttonTest = new QPushButton(tr("send long message"));
    m_lineTestSize = new QLineEdit;
    m_lineTestSize->setText("5000");

    QHBoxLayout *layoutButtons = new QHBoxLayout;
    layoutButtons->addWidget(m_buttonConnect);
    layoutButtons->addWidget(m_buttonDisconnect);
    layoutButtons->addStretch();
    layoutButtons->addWidget(m_buttonClear);
    layoutButtons->addWidget(m_buttonSend);

    QHBoxLayout *layoutNetwork = new QHBoxLayout;
    layoutNetwork->addWidget(labelAddress);
    layoutNetwork->addWidget(m_lineServerAddress);
    layoutNetwork->addWidget(labelPort);
    layoutNetwork->addWidget(m_lineServerPort);

    layoutNetwork->setStretchFactor(m_lineServerAddress,1);
    QLabel *labelTestSize = new QLabel(tr("test data size"));
    layoutNetwork->setStretchFactor(m_lineServerPort,0);
    QLabel *labelTestBytes = new QLabel(tr("bytes"));

    QHBoxLayout *layoutTest = new QHBoxLayout;
    layoutTest->addWidget(m_buttonTest);
    layoutTest->addWidget(labelTestSize);
    layoutTest->addWidget(m_lineTestSize);
    layoutTest->addWidget(labelTestBytes);

    QVBoxLayout *layout = new QVBoxLayout;
    layout->addWidget(m_textLog);
    layout->addWidget(m_textInput);
    layout->addLayout(layoutButtons);
    layout->addLayout(layoutNetwork);
    layout->addLayout(layoutTest);
    setLayout(layout);

    resize(400,400);
    m_textInput->setFixedHeight(100);

    m_messageBox = new QMessageBox(this);
    m_messageBoxConnecting = new QMessageBox(this);
    m_messageBoxConnecting->setText("connecting to host...");
    m_messageBoxConnecting->setStandardButtons(QMessageBox::Cancel);

    connect(m_buttonConnect     ,SIGNAL(clicked(bool)),this,SLOT(buttonConnectClicked()));
    connect(m_buttonDisconnect  ,SIGNAL(clicked(bool)),this,SLOT(buttonDisconnectClicked()));
    connect(m_buttonClear       ,SIGNAL(clicked(bool)),this,SLOT(buttonClearClicked()));
    connect(m_buttonSend        ,SIGNAL(clicked(bool)),this,SLOT(buttonSendClicked()));
    connect(m_buttonTest        ,SIGNAL(clicked(bool)),this,SLOT(buttonTestClicked()));

    connect(m_chatClient, SIGNAL(posted(QString)), this, SLOT(messagePosted(QString)));
    connect(m_chatClient, SIGNAL(stateChanged(ChatClient::State)),
            this, SLOT(stateChanged(ChatClient::State)));
    connect(m_chatClient, SIGNAL(error(QString)), this, SLOT(chatClientError(QString)));

    stateChanged(ChatClient::UnconnectedState);
}

ChatClientWidget::~ChatClientWidget()
{
}

void ChatClientWidget::buttonConnectClicked()
{
    if( m_lineServerAddress->text().isEmpty() )
    {
        m_messageBox->setText("server address is empty.");
        m_messageBox->exec();
        return;
    }
    if( m_lineServerPort->text().isEmpty() )
    {
        m_messageBox->setText("server port is empty.");
        m_messageBox->exec();
        return;
    }
    bool ok;
    qint16 port = m_lineServerPort->text().toInt( &ok );
    if( ! ok ){
        m_messageBox->setText("server port is not integer.");
        m_messageBox->exec();
        return;
    }
    m_chatClient->connectToServer(m_lineServerAddress->text(),port);
}

void ChatClientWidget::buttonDisconnectClicked()
{
    m_chatClient->disconnectFromServer();
}

void ChatClientWidget::buttonClearClicked()
{
    m_textInput->clear();
}

void ChatClientWidget::buttonSendClicked()
{
    m_chatClient->post(m_textInput->toPlainText());
    m_textInput->clear();
}

void ChatClientWidget::messagePosted(QString message)
{
    m_textLog->append(message);
}

void ChatClientWidget::stateChanged(ChatClient::State state)
{
    switch(state)
    {
    case ChatClient::UnconnectedState:
        m_textInput->setEnabled(false);
        m_buttonConnect->setEnabled(true);
        m_buttonDisconnect->setEnabled(false);
        m_buttonClear->setEnabled(false);
        m_buttonSend->setEnabled(false);
//        if( m_messageBoxConnecting->isVisible() ){
            QTimer::singleShot(1000,m_messageBoxConnecting,SLOT(hide()));
//        }
        break;

    case ChatClient::ConnectingState:
        m_textInput->setEnabled(false);
        m_buttonConnect->setEnabled(false);
        m_buttonDisconnect->setEnabled(false);
        m_buttonClear->setEnabled(false);
        m_buttonSend->setEnabled(false);
        m_messageBoxConnecting->show();
        break;

    case ChatClient::ConnectedState:
        m_textInput->setEnabled(true);
        m_buttonConnect->setEnabled(false);
        m_buttonDisconnect->setEnabled(true);
        m_buttonClear->setEnabled(true);
        m_buttonSend->setEnabled(true);
//        if( m_messageBoxConnecting->isVisible() ){
            QTimer::singleShot(1000,m_messageBoxConnecting,SLOT(hide()));
//        }
        break;

    case ChatClient::DisconnectingState:
        m_textInput->setEnabled(false);
        m_buttonConnect->setEnabled(false);
        m_buttonDisconnect->setEnabled(false);
        m_buttonClear->setEnabled(false);
        m_buttonSend->setEnabled(false);
        break;

    default:
        break;
    }
}

void ChatClientWidget::chatClientError(QString message)
{
    m_messageBox->setText(message);
    m_messageBox->exec();
}

void ChatClientWidget::buttonTestClicked()
{
    bool ok;
    int size = m_lineTestSize->text().toInt(&ok);
    if( ! ok ){
        m_messageBox->setText(tr("test message size must be an integer."));
        m_messageBox->exec();
        return;
    }
    QString message;
    for( int i = 0; i < size; i++ ){
        message.append( QChar('0'+(i%10)) );
    }
    m_chatClient->post(message);
}
