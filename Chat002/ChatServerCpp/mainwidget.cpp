#include "mainwidget.h"

#include <QHBoxLayout>
#include <QLabel>
#include <QPushButton>
#include <QVBoxLayout>

MainWidget::MainWidget(QWidget *parent)
    : QWidget(parent)
    , m_textLog(nullptr)
    , m_chatServer(nullptr)
{
    m_textLog = new QTextEdit;
    m_textLog->setReadOnly(true);

    QPushButton *buttonStart = new QPushButton(tr("Start listen"));
    QPushButton *buttonStop = new QPushButton(tr("Stop listen"));
    QLabel *labelPort = new QLabel(tr(" port:"));
    m_editPort = new QLineEdit;
    m_editPort->setText("12345");

    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->addWidget(m_textLog);

    QHBoxLayout *buttonLayout = new QHBoxLayout;
    buttonLayout->addStretch();
    buttonLayout->addWidget(buttonStart);
    buttonLayout->addWidget(buttonStop);
    buttonLayout->addWidget(labelPort);
    buttonLayout->addWidget(m_editPort);
    buttonLayout->addStretch();

    layout->addLayout(buttonLayout);

    resize(400,400);

    connect(buttonStart, &QPushButton::clicked, this, &MainWidget::startClicked);
    connect(buttonStop, &QPushButton::clicked, this, &MainWidget::stopClicked);

    m_chatServer = ChatServer::instance();

    connect( m_chatServer, &ChatServer::connected, this, &MainWidget::socketConnected );
    connect( m_chatServer, &ChatServer::disconnected, this, &MainWidget::socketDisconnected );
    connect( m_chatServer, &ChatServer::messageReceived, this, &MainWidget::socketMessageReceived );
}

MainWidget::~MainWidget()
{
}

void MainWidget::startClicked()
{
    bool ok = false;
    quint16 port = m_editPort->text().toInt(&ok);
    if(ok){
        m_chatServer->listen(QHostAddress::Any,port);
        m_textLog->append( QString(tr("listening on %1")).arg(port));
    }
    else{
        m_textLog->append( tr("port no. is not an integer.") );
    }
}

void MainWidget::stopClicked()
{
    m_chatServer->close();
    m_textLog->append( tr("closed.") );
}

void MainWidget::socketConnected(QTcpSocket *tcpSocket)
{
    QString address = tcpSocket->peerAddress().toString();
    quint16 port = tcpSocket->peerPort();
    m_textLog->append( QString(tr("connected from %1:%2")).arg(address).arg(port));
}

void MainWidget::socketDisconnected(QTcpSocket *tcpSocket)
{
    QString address = tcpSocket->peerAddress().toString();
    quint16 port = tcpSocket->peerPort();
    m_textLog->append( QString(tr("disconnected from %1:%2")).arg(address).arg(port));
}

void MainWidget::socketMessageReceived(QTcpSocket *tcpSocket, QString message)
{
    QString address = tcpSocket->peerAddress().toString();
    quint16 port = tcpSocket->peerPort();
    m_textLog->append( QString(tr("message sent from %1:%2")).arg(address).arg(port));
    m_textLog->append(message);
}
