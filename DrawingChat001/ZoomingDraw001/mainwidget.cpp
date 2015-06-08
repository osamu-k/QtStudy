#include "mainwidget.h"

#include <QScrollArea>
#include <QSlider>
#include <QVBoxLayout>

MainWidget::MainWidget(QWidget *parent)
    : QWidget(parent)
    , m_drawingPad(0)
{
    QScrollArea *scrollArea = new QScrollArea;
    m_drawingPad = new DrawingPad;
    m_drawingPad->setOriginalSize(QSize(500,500));
    QSlider *slider = new QSlider(Qt::Horizontal);
    slider->setRange(10,1000);
    slider->setValue(100);

    scrollArea->setWidget(m_drawingPad);

    QVBoxLayout *layout = new QVBoxLayout;
    layout->addWidget(scrollArea);
    layout->addWidget(slider);
    setLayout(layout);

    connect( slider, SIGNAL(valueChanged(int)), this, SLOT(scaleChanged(int)) );
}

MainWidget::~MainWidget()
{

}

void MainWidget::scaleChanged(int scale)
{
    m_drawingPad->setScale( static_cast<qreal>(scale) / 100.0 );
}
