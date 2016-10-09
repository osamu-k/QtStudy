#ifndef CHATCLIENTWSWIDGET_H
#define CHATCLIENTWSWIDGET_H

#include "chatclientws.h"

#include <QWidget>
#include <QLineEdit>
#include <QMessageBox>
#include <QPushButton>
#include <QTextEdit>

class ChatClientWSWidget : public QWidget
{
    Q_OBJECT

public:
    ChatClientWSWidget(QWidget *parent = 0);
    ~ChatClientWSWidget();
    void post(QString message);

private slots:
    void buttonConnectClicked();
    void buttonDisconnectClicked();
    void buttonClearClicked();
    void buttonSendClicked();
    void messagePosted(QString);
    void stateChanged(ChatClientWS::State);
    void chatClientError(QString);
    void buttonTestClicked();

private:
    QTextEdit *m_textLog;
    QTextEdit *m_textInput;
    QPushButton *m_buttonConnect;
    QPushButton *m_buttonDisconnect;
    QPushButton *m_buttonClear;
    QPushButton *m_buttonSend;
    QLineEdit *m_lineServerAddress;
    QLineEdit *m_lineServerPort;
    QPushButton *m_buttonTest;
    QLineEdit *m_lineTestSize;

    ChatClientWS *m_chatClient;

    QMessageBox *m_messageBox;
    QMessageBox *m_messageBoxConnecting;
};

#endif // CHATCLIENTWSWIDGET_H
