#ifndef CHATSERVERWIDGET_H
#define CHATSERVERWIDGET_H

#include "chatserver.h"

#include <QLineEdit>
#include <QPushButton>
#include <QWidget>

class ChatServerWidget : public QWidget
{
    Q_OBJECT

public:
    explicit ChatServerWidget(QWidget *parent = 0);
    ~ChatServerWidget();

private slots:
    void buttonListenClicked();
    void buttonStopClicked();

private:
    QLineEdit *m_linePort;
    QPushButton *m_buttonListen;
    QPushButton *m_buttonStop;

    ChatServer m_chatServer;
};

#endif // CHATSERVERWIDGET_H
