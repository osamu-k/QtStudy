#ifndef CHATSERVER_H
#define CHATSERVER_H

#include <QList>
#include <QObject>
#include <QTcpServer>
#include <QTcpSocket>

class ChatServer : public QObject
{
    Q_OBJECT
public:
    static ChatServer *ChatServer::instance();

    void listen(const QHostAddress &address = QHostAddress::Any, quint16 port = 0);
    void close();

signals:
    void connected(QTcpSocket *tcpSocket);
    void disconnected(QTcpSocket *tcpSocket);
    void messageReceived(QTcpSocket *tcpSocket, QString message);

public slots:
    void serverAcceptError(QAbstractSocket::SocketError socketError);
    void serverNewConnection();
    void socketReadyRead();
    void socketDisconnected();

private:
    explicit ChatServer(QObject *parent = 0);

    static ChatServer *m_instance;

    QTcpServer *m_tcpServer;
    QList<QTcpSocket*> m_tcpSocketList;
};

#endif // CHATSERVER_H
