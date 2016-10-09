#ifndef CHATCLIENTWS_H
#define CHATCLIENTWS_H

#include <QObject>
#include <QWebSocket>

class ChatClientWS : public QObject
{
    Q_OBJECT

public:

    enum State {
        UnconnectedState,
        ConnectingState,
        ConnectedState,
        DisconnectingState,
    };

    explicit ChatClientWS(QObject *parent = 0);

    void connectToServer(QString server, qint16 port);
    void disconnectFromServer();
    void post(QString message);

signals:
    void posted(QString message);
    void stateChanged(ChatClientWS::State);
    void error(QString);

public slots:

private slots:
    void connected();
    void disconnected();
    void error(QAbstractSocket::SocketError);
    void textMessageReceived(const QString &);
    void socketStateChanged(QAbstractSocket::SocketState);

private:
    void setState(State state);
    QWebSocket m_socket;
    State m_state;
};

#endif // CHATCLIENTWS_H
