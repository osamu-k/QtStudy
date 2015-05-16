#ifndef MAINWIDGET_H
#define MAINWIDGET_H

#include <QWidget>
#include "broadcastserver.h"

class MainWidget : public QWidget
{
    Q_OBJECT

public:
    MainWidget(QWidget *parent = 0);
    ~MainWidget();

private:
    void startListen();
    void stopListen();

private:
    BroadcastServer m_broadcastServer;
};

#endif // MAINWIDGET_H
