#include "mainwidget.h"

#include <QHBoxLayout>
#include <QLabel>
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

    QPushButton *buttonConnect = new QPushButton(tr("connect"));
    QPushButton *buttonDisconnect = new QPushButton(tr("disconnect"));
    QLabel *labelHost = new QLabel(tr(" host:"));
    m_editHost = new QLineEdit;
    QLabel *labelPort = new QLabel(tr(" port:"));
    m_editPort = new QLineEdit;
    m_editHost->setText("localhost");
    m_editPort->setText("12345");

    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->addWidget(splitter);

    QHBoxLayout *buttonLayout = new QHBoxLayout;
    buttonLayout->addStretch();
    buttonLayout->addWidget(buttonClear);
    buttonLayout->addWidget(buttonSend);
    buttonLayout->addStretch();

    layout->addLayout(buttonLayout);

    QHBoxLayout *netLayout = new QHBoxLayout;
    netLayout->addStretch();
    netLayout->addWidget(buttonConnect);
    netLayout->addWidget(buttonDisconnect);
    netLayout->addWidget(labelHost);
    netLayout->addWidget(m_editHost);
    netLayout->addWidget(labelPort);
    netLayout->addWidget(m_editPort);
    netLayout->addStretch();

    layout->addLayout(netLayout);

    resize(400,400);

    connect( buttonClear, &QPushButton::clicked, this, &MainWidget::clearClicked );
    connect( buttonSend, &QPushButton::clicked, this, &MainWidget::sendClicked );

    connect( buttonConnect, &QPushButton::clicked, this, &MainWidget::connectClicked );
    connect( buttonDisconnect, &QPushButton::clicked, this, &MainWidget::disconnectClicked );

    m_chatClient = ChatClient::instance();
    connect( m_chatClient, &ChatClient::received, this, &MainWidget::messageReceived );
}

MainWidget::~MainWidget()
{

}

void MainWidget::connectClicked()
{
    qDebug() << "connect clikced";
    QString host = m_editHost->text();
    if( host.isEmpty() ){
        qDebug() << "Host address is not specified.";
        return;
    }
    bool ok = false;
    quint16 port = m_editPort->text().toInt(&ok);
    if( ! ok ){
        qDebug() << "Port number is not an integer.";
    }
    m_chatClient->connectToHost(host,port);
}

void MainWidget::disconnectClicked()
{
    qDebug() << "disconnect clicked";
    m_chatClient->disconnectFromHost();
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
