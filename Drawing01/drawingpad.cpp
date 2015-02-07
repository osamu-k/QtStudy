/**
drawingpad.cpp

Copyright (c) Osamu Kobayashi

This software is released under the MIT License.
http://opensource.org/licenses/mit-license.php
*/

#include <QDataStream>
#include <QDebug>
#include <QFile>
#include <QFileDialog>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QTcpSocket>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include "canvas.h"
#include "colorselector.h"
#include "drawingpad.h"
#include "widthselector.h"

const int DrawingPad::defaultPort = 12345;
const char * const DrawingPad::defaultServer = "127.0.0.1";

DrawingPad::DrawingPad(QWidget *parent)
    : QWidget(parent)
    , m_canvas( 0 )
    , m_listenButton( 0 )
    , m_listenPortEdit( 0 )
    , m_connectButton( 0 )
    , m_connectAddressEdit( 0 )
    , m_connectPortEdit( 0 )
    , m_connected( false )
{
    m_canvas = new Canvas;

    QList<QColor> colorList;
    colorList << Qt::black << Qt::red << Qt::green << Qt::blue;
    QList<ColorSelector *> colorSelectorList;
    foreach( QColor color, colorList ){
        ColorSelector *selector = new ColorSelector( color );
        selector->setFixedSize( 50, 50 );
        colorSelectorList << selector;
    }

    QList<int> widthList;
    widthList << 40 << 20 << 10 << 5;
    foreach( int width, widthList ){
        WidthSelector *selector = new WidthSelector( width );
        selector->setFixedSize( 50, 50 );
        m_widthSelectorList << selector;
    }

    QVBoxLayout *colorLayout = new QVBoxLayout;
    foreach( ColorSelector *selector, colorSelectorList ){
        colorLayout->addWidget( selector );
    }

    QVBoxLayout *widthLayout = new QVBoxLayout;
    foreach( WidthSelector *selector, m_widthSelectorList ){
        widthLayout->addWidget( selector );
    }

    QVBoxLayout *settingLayout = new QVBoxLayout;
    settingLayout->addLayout( colorLayout );
    settingLayout->addLayout( widthLayout );
    settingLayout->addStretch();

    QHBoxLayout *hlayout = new QHBoxLayout;
    hlayout->addLayout( settingLayout );
    hlayout->addWidget( m_canvas );

#if 0
    QPushButton *newButton = new QPushButton( "New" );
    QPushButton *openButton = new QPushButton( "Open" );
    QPushButton *saveButton = new QPushButton( "Save" );
    QPushButton *saveAsPNGButton = new QPushButton( "Save as PNG" );

    QHBoxLayout *fileLayout = new QHBoxLayout;
    fileLayout->setSpacing( 5 );
    fileLayout->addWidget( newButton );
    fileLayout->addWidget( openButton );
    fileLayout->addWidget( saveButton );
    fileLayout->addWidget( saveAsPNGButton );
    fileLayout->addStretch();
#endif
    QLayout *fileLayout = setupFileButtons();

    m_listenButton = new QPushButton( "start listen" );
    m_listenPortEdit = new QLineEdit();
    m_listenPortEdit->setText( QString::number( defaultPort ) );
    m_connectButton = new QPushButton( "connect to" );
    m_connectAddressEdit = new QLineEdit();
    m_connectAddressEdit->setText( defaultServer );
    m_connectPortEdit = new QLineEdit();
    m_connectPortEdit->setText( QString::number( defaultPort ) );

    QHBoxLayout *networkLayout1 = new QHBoxLayout;
    networkLayout1->setSpacing( 5 );
    networkLayout1->addWidget( m_listenButton );
    networkLayout1->addWidget( new QLabel("on port") );
    networkLayout1->addWidget( m_listenPortEdit );
    networkLayout1->addStretch(1);

    QHBoxLayout *networkLayout2 = new QHBoxLayout;
    networkLayout2->setSpacing( 5 );
    networkLayout2->addWidget( m_connectButton );
    networkLayout2->addWidget( new QLabel("server") );
    networkLayout2->addWidget( m_connectAddressEdit, 1 );
    networkLayout2->addWidget( new QLabel("port") );
    networkLayout2->addWidget( m_connectPortEdit );

    QVBoxLayout *buttonLayout = new QVBoxLayout;
    buttonLayout->setSpacing( 0 );
    buttonLayout->addLayout( fileLayout );
    buttonLayout->addLayout( networkLayout1 );
    buttonLayout->addLayout( networkLayout2 );

    QVBoxLayout *topLayout = new QVBoxLayout;
    topLayout->addLayout( hlayout );
    topLayout->addLayout( buttonLayout );
    setLayout( topLayout );

    resize( 600, 500 );

    foreach( ColorSelector *colorSelector, colorSelectorList ){
        connect( colorSelector, SIGNAL(selected(QColor)), m_canvas, SLOT(setLineColor(QColor)) );
        foreach( WidthSelector *widthSelector, m_widthSelectorList ){
            connect( colorSelector, SIGNAL(selected(QColor)), widthSelector, SLOT(setColor(QColor)) );
        }
    }
    foreach( WidthSelector *selector, m_widthSelectorList ){
        connect( selector, SIGNAL(selected(int)), this, SLOT(widthSelected(int)) );
    }

#if 0
    connect( newButton, SIGNAL(clicked()), this, SLOT(newButtonClicked()) );
    connect( openButton, SIGNAL(clicked()), this, SLOT(openButtonClicked()) );
    connect( saveButton, SIGNAL(clicked()), this, SLOT(saveButtonClicked()) );
    connect( saveAsPNGButton, SIGNAL(clicked()), this, SLOT(saveAsPNGButtonClicked()) );
#endif
    connect( m_listenButton, SIGNAL(clicked()), this, SLOT(listenButtonClicked()) );
    connect( m_connectButton, SIGNAL(clicked()), this, SLOT(connectButtonClicked()) );

    m_canvas->setLineColor( Qt::black );
    widthSelected( 2 );

    connect( &m_listener, SIGNAL(newConnection(ServerSocket *)), this, SLOT(newConnection(ServerSocket *)) );
    //m_listener.setDataConsumer( m_canvas);

    connect( &m_clientSocket, SIGNAL(connected()), this, SLOT(connectedToServer()) );
    connect( &m_clientSocket, SIGNAL(received(QByteArray)), m_canvas, SLOT(addData(QByteArray)) );
    connect( &m_clientSocket, SIGNAL(disconnected()), this, SLOT(disconnectedFromServer()) );

    connect( m_canvas, SIGNAL(dataAdded(QByteArray)), &m_clientSocket, SLOT(send(QByteArray)) );
}

QLayout *DrawingPad::setupFileButtons()
{
    QPushButton *newButton = new QPushButton( "New" );
    QPushButton *openButton = new QPushButton( "Open" );
    QPushButton *saveButton = new QPushButton( "Save" );
    QPushButton *saveAsPNGButton = new QPushButton( "Save as PNG" );

    QHBoxLayout *fileLayout = new QHBoxLayout;
    fileLayout->setSpacing( 5 );
    fileLayout->addWidget( newButton );
    fileLayout->addWidget( openButton );
    fileLayout->addWidget( saveButton );
    fileLayout->addWidget( saveAsPNGButton );
    fileLayout->addStretch();

    connect( newButton, SIGNAL(clicked()), this, SLOT(newButtonClicked()) );
    connect( openButton, SIGNAL(clicked()), this, SLOT(openButtonClicked()) );
    connect( saveButton, SIGNAL(clicked()), this, SLOT(saveButtonClicked()) );
    connect( saveAsPNGButton, SIGNAL(clicked()), this, SLOT(saveAsPNGButtonClicked()) );

    return fileLayout;
}

DrawingPad::~DrawingPad()
{
}

void DrawingPad::widthSelected( int width )
{
    m_canvas->setLineWidth( width );
    foreach( WidthSelector *selector, m_widthSelectorList ){
        selector->setSelected( selector->lineWidth() == width );
    }
}

void DrawingPad::newButtonClicked()
{
    m_canvas->clear();
}

void DrawingPad::openButtonClicked()
{
    QFileDialog dialog( this );
    dialog.setAcceptMode( QFileDialog::AcceptOpen );
    dialog.setDefaultSuffix( "drw" );
    dialog.setFileMode( QFileDialog::AnyFile );
    dialog.setViewMode( QFileDialog::Detail );
    dialog.setNameFilter( tr("Drawings (*.drw)") );
    if (dialog.exec()){
        QStringList fileNames = dialog.selectedFiles();
        qDebug() << "file name =" << fileNames[0];

        QFile file( fileNames[0] );
        if( !file.open(QIODevice::ReadOnly ) ){
            return;
        }
        QDataStream in(&file);
        m_canvas->readFrom( in );
    }
}

void DrawingPad::saveButtonClicked()
{
    QFileDialog dialog( this );
    dialog.setAcceptMode( QFileDialog::AcceptSave );
    dialog.setDefaultSuffix( "drw" );
    dialog.setFileMode( QFileDialog::AnyFile );
    dialog.setViewMode( QFileDialog::Detail );
    dialog.setNameFilter( tr("Drawings (*.drw)") );
    if (dialog.exec()){
        QStringList fileNames = dialog.selectedFiles();
        qDebug() << "file name =" << fileNames[0];

        QFile file( fileNames[0] );
        if( !file.open(QIODevice::WriteOnly | QIODevice::Truncate ) ){
            return;
        }
        QDataStream out(&file);
        m_canvas->writeTo( out );
    }
}

void DrawingPad::saveAsPNGButtonClicked()
{
    QFileDialog dialog( this );
    dialog.setAcceptMode( QFileDialog::AcceptSave );
    dialog.setDefaultSuffix( "png" );
    dialog.setFileMode( QFileDialog::AnyFile );
    dialog.setViewMode( QFileDialog::Detail );
    dialog.setNameFilter( tr("PNG Images (*.png)") );
    if (dialog.exec()){
        QStringList fileNames = dialog.selectedFiles();
        qDebug() << "file name =" << fileNames[0];

        QPixmap pixmap = m_canvas->grab();
        pixmap.save( fileNames[0] );
    }
}

void DrawingPad::listenButtonClicked()
{
    if( ! m_listener.isListening() ) {
        int port = m_listenPortEdit->text().toInt();
        m_listener.startListen( port );
    }
    else{
        m_listener.stopListen();
    }

    if( ! m_listener.isListening() ){
        m_listenButton->setText( "start listen" );
        m_connectButton->setEnabled( true );
    }
    else{
        m_listenButton->setText( "stop listen " );
        m_connectButton->setEnabled( false );
    }
}

void DrawingPad::connectButtonClicked()
{
    if( ! m_connected ){
        int port = m_connectPortEdit->text().toInt();
        qDebug() << "connecting to " << m_connectAddressEdit->text() << "on port " << port;
        m_clientSocket.connectToHost( m_connectAddressEdit->text(), port );

        m_connected = true;
    }
    else{
        m_clientSocket.disconnectFromHost();

        m_connected = false;
    }

    if( ! m_connected ){
        m_connectButton->setText( "connect to" );
        m_listenButton->setEnabled( true );
    }
    else{
        m_connectButton->setText( "disconnect" );
        m_listenButton->setEnabled( false );
    }
}

void DrawingPad::newConnection( ServerSocket *serverSocket )
{
    qDebug() << "New connection ! isOpen() = " << serverSocket->isOpen();
    connect( serverSocket, SIGNAL(received(QByteArray)), m_canvas, SLOT(addData(QByteArray)) );
    connect( m_canvas, SIGNAL(dataAdded(QByteArray)), serverSocket, SLOT(broadcastData(QByteArray)) );
}

void DrawingPad::connectedToServer()
{
    qDebug() << "connected !";
}

void DrawingPad::disconnectedFromServer()
{
    qDebug() << "Disconnected !";
    m_connectButton->setText( "connect to" );
    m_listenButton->setEnabled( true );
}
