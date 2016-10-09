#ifndef WEBSERVERWIDGET_H
#define WEBSERVERWIDGET_H

#include "chatserverws.h"

#include <QLineEdit>
#include <QPushButton>
#include <QWidget>

class ChatServerWSWidget : public QWidget
{
    Q_OBJECT

public:
    explicit ChatServerWSWidget(QWidget *parent = 0);
    ~ChatServerWSWidget();

    void listen(qint16 port);
    void stop();

private slots:
    void buttonListenClicked();
    void buttonStopClicked();

private:
    QLineEdit *m_linePort;
    QPushButton *m_buttonListen;
    QPushButton *m_buttonStop;

    ChatServerWS m_chatServer;
};

#endif // WEBSERVERWIDGET_H
