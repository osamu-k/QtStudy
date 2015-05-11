#ifndef SERVERWIDGET_H
#define SERVERWIDGET_H

#include <QWidget>
#include "broadcastserver.h"

class ServerWidget : public QWidget
{
    Q_OBJECT

public:
    ServerWidget(QWidget *parent = 0);
    ~ServerWidget();
private slots:
    void startListen();
private:
    BroadcastServer m_server;
};

#endif // SERVERWIDGET_H
