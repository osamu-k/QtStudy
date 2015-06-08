#ifndef SCROLLVIEW_H
#define SCROLLVIEW_H

#include "drawingview.h"
#include <QWidget>

class ScrollView : public QWidget
{
    Q_OBJECT

public:
    ScrollView();
    ~ScrollView();
    QSize sizeHint() const { return QSize(500,500); }

    DrawingView *drawingView() { return m_drawingView; }

private slots:
    void scaleChanged(int);

private:
    DrawingView *m_drawingView;
};

#endif // SCROLLVIEW_H
