#include <QByteArray>
#include <QDataStream>
#include <QDebug>
#include <QPushButton>
#include <QVBoxLayout>
#include "clientwidget.h"

ClientWidget::ClientWidget(QWidget *parent)
    : QWidget(parent)
{
    QPushButton *buttonConnect = new QPushButton("connect");
    QPushButton *buttonDisconnect = new QPushButton("disconnect");
    QPushButton *buttonSend = new QPushButton("send");
    QVBoxLayout *layout = new QVBoxLayout;
    layout->addWidget(buttonConnect);
    layout->addWidget(buttonDisconnect);
    layout->addWidget(buttonSend);
    setLayout(layout);

    connect(buttonConnect,&QPushButton::clicked,this,&ClientWidget::connectToHost);
    connect(buttonDisconnect,&QPushButton::clicked,this,&ClientWidget::disconnectFromHost);
    connect(buttonSend,&QPushButton::clicked,this,&ClientWidget::sendData);
    connect(&m_broadcastClient,&BroadcastClient::dataReceived,
            this,&ClientWidget::dataReceived );
//    connect(&m_socket,&QTcpSocket::connected,this,&ClientWidget::connected);
//    connect(&m_socket,&QTcpSocket::readyRead,this,&ClientWidget::dataReceived);
}

ClientWidget::~ClientWidget()
{

}

void ClientWidget::connectToHost()
{
//    m_socket.connectToHost("127.0.0.1", 12345);
    m_broadcastClient.connectToHost();
}

//void ClientWidget::connected()
//{
//    qDebug() << "connected !";
//}

void ClientWidget::disconnectFromHost()
{
    qDebug() << "disconnect ...";
//    m_socket.disconnectFromHost();
    m_broadcastClient.disconnectFromHost();
}

void ClientWidget::sendData()
{
    qDebug() << "send data.";

    QByteArray byteArray;
    QDataStream byteArrayStream(&byteArray,QIODevice::WriteOnly);
    byteArrayStream << QString("Hello !");

//    QDataStream outStream(&m_socket);
//    outStream << byteArray;
//    m_socket.flush();
    m_broadcastClient.sendData(byteArray);
}

void ClientWidget::dataReceived(QByteArray data)
{
    qDebug() << "ClientWidget::dataReceived received data size =" << data.size();
    QDataStream inStream(data);
    QString string;
    inStream >> string;
    qDebug() << "data = " << string;

//    qDebug() << "data recieved !";
//    QTcpSocket *socket = qobject_cast<QTcpSocket *>(sender());
//    if(socket){
//        QDataStream inStream(socket);
//        QByteArray byteArray;
//        inStream >> byteArray;
//        QDataStream byteArrayStream(byteArray);
//        QString data;
//        byteArrayStream >> data;
//        qDebug() << "data = " << data;
//    }
}
