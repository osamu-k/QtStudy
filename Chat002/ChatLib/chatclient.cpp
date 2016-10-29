#include "chatclient.h"

ChatClient *ChatClient::m_instance = nullptr;

ChatClient *ChatClient::instance(){
    if(m_instance == nullptr){
        m_instance = new ChatClient;
    }
    return m_instance;
}

ChatClient::ChatClient(QObject *parent) : QObject(parent)
{
}

void ChatClient::send(QString message)
{
    emit received(message);
}
