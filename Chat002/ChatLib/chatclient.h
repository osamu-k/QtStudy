#ifndef CHATCLIENT_H
#define CHATCLIENT_H

#include <QObject>

class ChatClient : public QObject
{
    Q_OBJECT

public:
    static ChatClient *instance();
    void send(QString message);

signals:
    void received(QString message);

public slots:

private:
    ChatClient(QObject *parent = 0);

    static ChatClient *m_instance;
};

#endif // CHATCLIENT_H
