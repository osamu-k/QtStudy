#ifndef CHATSERVERWS_H
#define CHATSERVERWS_H

#include "messagebuffer.h"

#include <QWebSocket>
#include <QWebSocketServer>
#include <QObject>

class ChatServerWS : public QObject
{
    Q_OBJECT
public:
    explicit ChatServerWS(QObject *parent = 0);
    void listen(qint16 port);
    void stop();

signals:

public slots:

private slots:
    void newConnection();
    void textMessageReceived(const QString &);
    void disconnected();

private:
    QWebSocketServer m_server;
    QList<QWebSocket*> m_socketList;
    QMap<QWebSocket*,MessageBuffer*> m_bufferMap;
};

#endif // CHATSERVERWS_H
