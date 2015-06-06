#ifndef DRAWINGVIEW_H
#define DRAWINGVIEW_H

#include <QWidget>

class DrawingView : public QWidget
{
    Q_OBJECT
public:
    explicit DrawingView(QWidget *parent = 0);
    ~DrawingView();

signals:

public slots:
};

#endif // DRAWINGVIEW_H
