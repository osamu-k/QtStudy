#include "chatserverwidget.h"

#include <QHBoxLayout>
#include <QLabel>
#include <QMessageBox>

ChatServerWidget::ChatServerWidget(QWidget *parent) :
    QWidget(parent)
{
    QLabel *label = new QLabel(tr("port"));
    m_linePort = new QLineEdit;
    m_buttonListen = new QPushButton(tr("listen"));
    m_buttonStop = new QPushButton(tr("stop"));

    QHBoxLayout *layout = new QHBoxLayout;
    layout->addWidget(label);
    layout->addWidget(m_linePort);
    layout->addWidget(m_buttonListen);
    layout->addWidget(m_buttonStop);
    setLayout(layout);

    connect(m_buttonListen, SIGNAL(clicked(bool)), this, SLOT(buttonListenClicked()));
    connect(m_buttonStop, SIGNAL(clicked(bool)), this, SLOT(buttonStopClicked()));
}

ChatServerWidget::~ChatServerWidget()
{

}

void ChatServerWidget::buttonListenClicked()
{
    QString text = m_linePort->text();
    bool ok;
    qint16 port = text.toInt(&ok);
    if(ok){
        m_chatServer.listen(port);
    }
    else{
        QMessageBox messageBox(this);
        messageBox.setText("Port number must be an integer.");
        messageBox.exec();
    }
}

void ChatServerWidget::buttonStopClicked()
{
    m_chatServer.stop();
}
