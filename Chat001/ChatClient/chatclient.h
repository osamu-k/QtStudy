#ifndef CHATSERVER_H
#define CHATSERVER_H

#include "messagebuffer.h"

#include <QObject>
#include <QTcpSocket>

class ChatClient : public QObject
{
    Q_OBJECT

public:

    enum State {
        UnconnectedState,
        ConnectingState,
        ConnectedState,
        DisconnectingState,
    };

    explicit ChatClient(QObject *parent = 0);

    void connectToServer(QString server, qint16 port);
    void disconnectFromServer();
    void post(QString message);

signals:
    void posted(QString message);
    void stateChanged(ChatClient::State);
    void error(QString);

public slots:

private slots:
    void connected();
    void disconnected();
    void error(QAbstractSocket::SocketError);
    void readyRead();
    void socketStateChanged(QAbstractSocket::SocketState socketState);

private:
    void setState(State state);
    QTcpSocket m_tcpSocket;
    State m_state;

    MessageBuffer m_buffer;
};

#endif // CHATSERVER_H
