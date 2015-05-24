#include "mainwidget.h"
#include "drawingpad.h"
#include "shapewriter.h"

#include <QDataStream>
#include <QDebug>
#include <QFileDialog>
#include <QPushButton>
#include <QHBoxLayout>
#include <QVBoxLayout>

#include <functional>

MainWidget::MainWidget(QWidget *parent) : QWidget(parent)
{
    QPushButton *buttonFreeHand = new QPushButton("Free Hand");
    QPushButton *buttonRectangle = new QPushButton("Rectangle");
    QPushButton *buttonSave = new QPushButton("Save");
    QPushButton *buttonOpen = new QPushButton("Open");
    QPushButton *buttonClear = new QPushButton("Clear");
    QPushButton *buttonMove = new QPushButton("Move");
    QPushButton *buttonConnect = new QPushButton("Connect");
    QPushButton *buttonDisconnect = new QPushButton("Disconnect");
    QHBoxLayout *buttonLayout = new QHBoxLayout;
    buttonLayout->addWidget(buttonFreeHand);
    buttonLayout->addWidget(buttonRectangle);
    buttonLayout->addWidget(buttonSave);
    buttonLayout->addWidget(buttonOpen);
    buttonLayout->addWidget(buttonClear);
    buttonLayout->addWidget(buttonMove);
    buttonLayout->addWidget(buttonConnect);
    buttonLayout->addWidget(buttonDisconnect);

    m_pad = new DrawingPad;
//    m_pad->setModel(m_model);

    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->addLayout( buttonLayout );
    mainLayout->addWidget(m_pad);
    setLayout(mainLayout);

    resize(500,500);

    connect( buttonFreeHand,
             &QPushButton::clicked,
             [=](){m_pad->setShapeType(DrawingPad::SHAPE_FREEHAND);} );

    connect( buttonRectangle,
             &QPushButton::clicked,
             [=](){m_pad->setShapeType(DrawingPad::SHAPE_RECTANGLE);} );

    connect( buttonSave,
             &QPushButton::clicked,
             this,
             &MainWidget::save );

    connect( buttonOpen,
             &QPushButton::clicked,
             this,
             &MainWidget::open );

    connect( buttonClear,
             &QPushButton::clicked,
             this,
             &MainWidget::clear );

    connect( buttonMove,
             &QPushButton::clicked,
             m_pad,
             &DrawingPad::moveShape );

    connect( buttonConnect,
             &QPushButton::clicked,
             this,
             &MainWidget::connectToHost );

    connect( buttonDisconnect,
             &QPushButton::clicked,
             this,
             &MainWidget::disconnectFromHost );
}

MainWidget::~MainWidget()
{

}

void MainWidget::setDrawingModel(DrawingModel*model)
{
    m_model = model;
    m_pad->setModel(model);
}

void MainWidget::save()
{
    qDebug() << "save button clicked.";
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
        m_model->writeTo( out );
    }
}

void MainWidget::open()
{
    qDebug() << "open button clicked.";
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
        m_model->readFrom( in );
    }
}

void MainWidget::clear()
{
    qDebug() << "clear button clicked.";
    m_model->clear();
}

void MainWidget::connectToHost()
{
    qDebug() << "connect button clicked";
    m_model->connectToHost();
}

void MainWidget::disconnectFromHost()
{
    qDebug() << "disconnect button clicked";
    m_model->disconnectFromtHost();
}
