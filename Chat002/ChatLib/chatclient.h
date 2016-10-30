#ifndef CHATCLIENT_H
#define CHATCLIENT_H

#include <QObject>
#include <QTcpSocket>

class ChatClient : public QObject
{
    Q_OBJECT

public:
    static ChatClient *instance();

    void connectToHost(const QString &hostName, quint16 port);
    void disconnectFromHost();
    void send(QString message);

signals:
    void received(QString message);

public slots:

private slots:
    void socketConnected();
    void socketDisconnected();
    void socketError(QAbstractSocket::SocketError socketError);
    void socketReadyRead();

private:
    ChatClient(QObject *parent = 0);

    static ChatClient *m_instance;

    QTcpSocket *m_tcpSocket;
};

#endif // CHATCLIENT_H
