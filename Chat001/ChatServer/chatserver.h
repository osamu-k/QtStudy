#ifndef CHATSERVER_H
#define CHATSERVER_H

#include "messagebuffer.h"
#include <QMap>
#include <QObject>
#include <QTcpServer>
#include <QTcpSocket>

class ChatServer : public QObject
{
    Q_OBJECT

public:
    explicit ChatServer(QObject *parent = 0);
    ~ChatServer();
    void listen(qint16 port);
    void stop();

signals:

public slots:

private slots:
    void newConnection();
    void readyRead();
    void disconnected();

private:
    void castMessage(QTcpSocket *socket, QString message);

    QTcpServer m_tcpServer;
    QList<QTcpSocket*> m_socketList;
//    MessageBuffer m_buffer;
    QMap<QTcpSocket*,MessageBuffer*> m_bufferMap;
};

#endif // CHATSERVER_H
