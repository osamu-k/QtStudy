#include "mainwindow.h"

#include "linewidthdialog.h"

#include <QColorDialog>
#include <QDebug>
#include <QMenuBar>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , m_drawingPad(0)
    , m_menuEdit(0)
    , m_actionLineColor(0)
    , m_actionFillColor(0)
    , m_actionLineWidth(0)
    , m_actionOutlineEnabled(0)
    , m_actionFillColorEnabled(0)
{
    m_drawingPad = new DrawingPad;
    setCentralWidget(m_drawingPad);

    m_actionShapeFreeHand = new QAction(tr("FreeHand"),this);
    m_actionShapeRectangle = new QAction(tr("Rectangle"),this);
    m_actionLineColor = new QAction(tr("Line Color"),this);
    m_actionFillColor = new QAction(tr("Fill Color"),this);
    m_actionLineWidth = new QAction(tr("Line Width"),this);
    m_actionOutlineEnabled = new QAction(tr("Outline Enabled"),this);
    m_actionFillColorEnabled = new QAction(tr("FillColor Enabled"),this);

    m_actionShapeFreeHand->setCheckable(true);
    m_actionShapeRectangle->setCheckable(true);
    m_actionOutlineEnabled->setCheckable(true);
    m_actionFillColorEnabled->setCheckable(true);

    m_menuEdit = menuBar()->addMenu(tr("Edit"));
    m_menuShapeType = m_menuEdit->addMenu(tr("Shape"));

    m_menuShapeType->addAction(m_actionShapeFreeHand);
    m_menuShapeType->addAction(m_actionShapeRectangle);
    m_menuEdit->addAction(m_actionLineColor);
    m_menuEdit->addAction(m_actionFillColor);
    m_menuEdit->addAction(m_actionLineWidth);
    m_menuEdit->addAction(m_actionOutlineEnabled);
    m_menuEdit->addAction(m_actionFillColorEnabled);

    m_actionShapeFreeHand->setCheckable(true);
    m_actionShapeFreeHand->setChecked(true);
    m_actionShapeRectangle->setCheckable(true);
    m_actionShapeRectangle->setChecked(false);

    connect(m_actionShapeFreeHand,SIGNAL(triggered()),this,SLOT(setShapeFreeHand()));
    connect(m_actionShapeRectangle,SIGNAL(triggered()),this,SLOT(setShapeRectangle()));
    connect(m_actionLineColor,SIGNAL(triggered()),this,SLOT(setLineColor()));
    connect(m_actionFillColor,SIGNAL(triggered()),this,SLOT(setFillColor()));
    connect(m_actionLineWidth,SIGNAL(triggered()),this,SLOT(setLineWidth()));
    connect(m_actionOutlineEnabled,SIGNAL(triggered()),this,SLOT(setOutlineEnabled()));
    connect(m_actionFillColorEnabled,SIGNAL(triggered()),this,SLOT(setFillColorEnabled()));

    m_actionShapeFreeHand->setChecked( m_drawingPad->shapeType() == Shape::TYPE_FREEHAND );
    m_actionShapeRectangle->setChecked( m_drawingPad->shapeType() == Shape::TYPE_RECTANGLE );
    m_actionOutlineEnabled->setChecked( m_drawingPad->drawingSettings().isOutlineEnabled() );
    m_actionFillColorEnabled->setChecked( m_drawingPad->drawingSettings().isFillColorEnabled() );
}

MainWindow::~MainWindow()
{
}

void MainWindow::setShapeFreeHand()
{
    m_actionShapeFreeHand->setChecked(true);
    m_actionShapeRectangle->setChecked(false);
    m_drawingPad->setShapeType(Shape::TYPE_FREEHAND);
}

void MainWindow::setShapeRectangle()
{
    m_actionShapeFreeHand->setChecked(false);
    m_actionShapeRectangle->setChecked(true);
    m_drawingPad->setShapeType(Shape::TYPE_RECTANGLE);
}

void MainWindow::setLineColor()
{
    QColorDialog dialog(this);
    dialog.setWindowTitle(tr("Select line color"));
    if( dialog.exec() ){
        m_drawingPad->drawingSettings().setLineColor(dialog.selectedColor());
    }
}

void MainWindow::setFillColor()
{
    QColorDialog dialog(this);
    dialog.setWindowTitle(tr("Select fill color"));
    if( dialog.exec() ){
        m_drawingPad->drawingSettings().setFillColor(dialog.selectedColor());
    }
}

void MainWindow::setLineWidth()
{
    LineWidthDialog dialog(this);
    dialog.setLineWidth(m_drawingPad->drawingSettings().lineWidth());
    if( dialog.exec() ){
        m_drawingPad->drawingSettings().setLineWidth(dialog.lineWidth());
    }
}

void MainWindow::setOutlineEnabled()
{
    m_drawingPad->drawingSettings().setOutlineEnabled( ! m_drawingPad->drawingSettings().isOutlineEnabled() );
    m_actionOutlineEnabled->setChecked( m_drawingPad->drawingSettings().isOutlineEnabled() );
}

void MainWindow::setFillColorEnabled()
{
    m_drawingPad->drawingSettings().setFillColorEnabled( ! m_drawingPad->drawingSettings().isFillColorEnabled() );
    m_actionFillColorEnabled->setChecked( m_drawingPad->drawingSettings().isFillColorEnabled() );
}
