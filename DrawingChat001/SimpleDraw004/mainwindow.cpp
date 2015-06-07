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
    , m_actionLineWidth(0)
{
    m_drawingPad = new DrawingPad;
    setCentralWidget(m_drawingPad);

    m_actionShapeFreeHand = new QAction(tr("FreeHand"),this);
    m_actionShapeRectangle = new QAction(tr("Rectangle"),this);
    m_actionLineColor = new QAction(tr("Line Color"),this);
    m_actionLineWidth = new QAction(tr("Line Width"),this);

    m_menuEdit = menuBar()->addMenu(tr("Edit"));
    m_menuShapeType = m_menuEdit->addMenu(tr("Shape"));

    m_menuShapeType->addAction(m_actionShapeFreeHand);
    m_menuShapeType->addAction(m_actionShapeRectangle);
    m_menuEdit->addAction(m_actionLineColor);
    m_menuEdit->addAction(m_actionLineWidth);

    m_actionShapeFreeHand->setCheckable(true);
    m_actionShapeFreeHand->setChecked(true);
    m_actionShapeRectangle->setCheckable(true);
    m_actionShapeRectangle->setChecked(false);

    connect(m_actionShapeFreeHand,SIGNAL(triggered()),this,SLOT(setShapeFreeHand()));
    connect(m_actionShapeRectangle,SIGNAL(triggered()),this,SLOT(setShapeRectangle()));
    connect(m_actionLineColor,SIGNAL(triggered()),this,SLOT(setLineColor()));
    connect(m_actionLineWidth,SIGNAL(triggered()),this,SLOT(setLineWidth()));
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
        m_drawingPad->setLineColor(dialog.selectedColor());
    }
}

void MainWindow::setLineWidth()
{
    LineWidthDialog dialog(this);
    dialog.setLineWidth(m_drawingPad->lineWidth());
    if( dialog.exec() ){
        m_drawingPad->setLineWidth(dialog.lineWidth());
    }
}
