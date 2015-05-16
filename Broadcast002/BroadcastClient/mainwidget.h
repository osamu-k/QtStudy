#ifndef MAINWIDGET_H
#define MAINWIDGET_H

#include <QTextEdit>
#include <QWidget>
#include "broadcaster.h"
#include "subscriber.h"

class MainWidget : public QWidget, public Subscriber
{
    Q_OBJECT

public:
    MainWidget(QWidget *parent = 0);
    ~MainWidget();
    void deliver(QByteArray data);
private slots:
    void sendButtonClicked();
    void newButtonClicked();
private:
    QTextEdit *m_inputText;
    QTextEdit *m_outputText;
    Broadcaster *m_broadcaster;
};

#endif // MAINWIDGET_H
