#ifndef CLIENTWIDGET_H
#define CLIENTWIDGET_H

#include <QByteArray>
#include <QTcpSocket>
#include <QWidget>
#include "broadcastclient.h"

class ClientWidget : public QWidget
{
    Q_OBJECT

public:
    ClientWidget(QWidget *parent = 0);
    ~ClientWidget();

private slots:
    void connectToHost();
    void disconnectFromHost();
    void sendData();
    void dataReceived(QByteArray data);
private:
//    QTcpSocket m_socket;
    BroadcastClient m_broadcastClient;
};

#endif // CLIENTWIDGET_H
