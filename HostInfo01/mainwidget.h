#ifndef MAINWIDGET_H
#define MAINWIDGET_H

#include <QWidget>
#include <QHostAddress>
#include <QHostInfo>
#include <QNetworkAccessManager>
#include <QNetworkReply>

class MainWidget : public QWidget
{
    Q_OBJECT

public:
    MainWidget(QWidget *parent = 0);
    ~MainWidget();

private slots:
    void testButtonClicked();
    void hostLookuped(QHostInfo);
    void replyFinishedV6(QNetworkReply*);
    void replyFinishedV4(QNetworkReply*);

private:
    QNetworkAccessManager *m_naman = nullptr;
    QHostAddress m_v6Addr;
    QHostAddress m_v4Addr;
};

#endif // MAINWIDGET_H
