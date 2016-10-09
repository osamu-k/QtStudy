#ifndef CHATCLIENTWIDGET_H
#define CHATCLIENTWIDGET_H

#include "chatclient.h"

#include <QWidget>
#include <QLineEdit>
#include <QMessageBox>
#include <QPushButton>
#include <QTextEdit>

class ChatClientWidget : public QWidget
{
    Q_OBJECT

public:
    ChatClientWidget(QWidget *parent = 0);
    ~ChatClientWidget();
    void post(QString message);

private slots:
    void buttonConnectClicked();
    void buttonDisconnectClicked();
    void buttonClearClicked();
    void buttonSendClicked();
    void messagePosted(QString);
    void stateChanged(ChatClient::State);
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

    ChatClient *m_chatClient;

    QMessageBox *m_messageBox;
    QMessageBox *m_messageBoxConnecting;
};

#endif // CHATCLIENTWIDGET_H
