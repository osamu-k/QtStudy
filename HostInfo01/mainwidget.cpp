#include "mainwidget.h"

#include <QPushButton>
#include <QUrl>
#include <QVBoxLayout>
#include <QDebug>

MainWidget::MainWidget(QWidget *parent)
    : QWidget(parent)
{
    QPushButton *buttonTest = new QPushButton("test !");
    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->addWidget(buttonTest);

    connect(buttonTest,SIGNAL(clicked(bool)),this,SLOT(testButtonClicked()));

    m_naman = new QNetworkAccessManager(this);
}

MainWidget::~MainWidget()
{
}

void MainWidget::testButtonClicked()
{
    qDebug() << "test button clicked !";

    QHostInfo::lookupHost("www.iij.ad.jp",this,SLOT(hostLookuped(QHostInfo)));
}

void MainWidget::hostLookuped(QHostInfo hostInfo)
{
    m_v4Addr.clear();
    m_v6Addr.clear();

    qDebug() << "ipV6 addresses:";
    for( auto address: hostInfo.addresses()){
        if( address.protocol() == QAbstractSocket::IPv6Protocol ){
            qDebug() << "  " << address;
            m_v6Addr = address;
            break;
        }
    }
    qDebug() << "ipV4 addresses:";
    for( auto address: hostInfo.addresses()){
        if( address.protocol() == QAbstractSocket::IPv4Protocol ){
            qDebug() << "  " << address;
            m_v4Addr = address;
            break;
        }
    }

    if(! m_v6Addr.isNull()){
        QUrl url;
        url.setScheme("http");
        url.setHost(m_v6Addr.toString());
        qDebug() << "request to " << url;

        connect(m_naman,SIGNAL(finished(QNetworkReply*)),
                this,SLOT(replyFinishedV6(QNetworkReply*)));
        m_naman->get(QNetworkRequest(url));
    }
    else if(! m_v4Addr.isNull()){
        QUrl url;
        url.setScheme("http");
        url.setHost(m_v4Addr.toString());
        qDebug() << "request to " << url;

        connect(m_naman,SIGNAL(finished(QNetworkReply*)),
                this,SLOT(replyFinishedV4(QNetworkReply*)));
        m_naman->get(QNetworkRequest(url));
    }
}

void MainWidget::replyFinishedV6(QNetworkReply *reply)
{
    qDebug() << "reply finished V6";
    qDebug() << "error = " << reply->error();

    disconnect(m_naman,SIGNAL(finished(QNetworkReply*)),
               this,SLOT(replyFinishedV6(QNetworkReply*)));

    if(reply->error() == QNetworkReply::NoError){
        QString repString(reply->readAll());
        qDebug() << repString;
    }
    else if(! m_v4Addr.isNull()){
        QUrl url;
        url.setScheme("http");
        url.setHost(m_v4Addr.toString());
        qDebug() << "request to " << url;

        connect(m_naman,SIGNAL(finished(QNetworkReply*)),
                this,SLOT(replyFinishedV4(QNetworkReply*)));
        m_naman->get(QNetworkRequest(url));
    }
}

void MainWidget::replyFinishedV4(QNetworkReply *reply)
{
    qDebug() << "reply finished V4";
    qDebug() << "error = " << reply->error();

    disconnect(m_naman,SIGNAL(finished(QNetworkReply*)),
               this,SLOT(replyFinishedV4(QNetworkReply*)));

    if(reply->error() == QNetworkReply::NoError){
        QString repString(reply->readAll());
        qDebug() << repString;
    }
}
