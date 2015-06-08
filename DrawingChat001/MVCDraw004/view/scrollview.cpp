#include "scrollview.h"

#include "drawingview.h"

#include <QScrollArea>
#include <QSlider>
#include <QVBoxLayout>

ScrollView::ScrollView()
{
    QScrollArea *scrollArea = new QScrollArea;
    m_drawingView = new DrawingView;
    m_drawingView->setOriginalSize(QSize(500,500));
    QSlider *slider = new QSlider(Qt::Horizontal);
    slider->setRange(10,1000);
    slider->setValue(100);

    scrollArea->setWidget(m_drawingView);

    QVBoxLayout *layout = new QVBoxLayout;
    layout->addWidget(scrollArea);
    layout->addWidget(slider);
    setLayout(layout);

    connect( slider, SIGNAL(valueChanged(int)), this, SLOT(scaleChanged(int)) );
}

ScrollView::~ScrollView()
{

}

void ScrollView::scaleChanged(int scale)
{
    m_drawingView->setScale( static_cast<qreal>(scale) / 100.0 );
}
