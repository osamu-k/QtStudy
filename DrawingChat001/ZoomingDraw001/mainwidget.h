#ifndef MAINWIDGET_H
#define MAINWIDGET_H

#include "drawingpad.h"
#include <QWidget>

class MainWidget : public QWidget
{
    Q_OBJECT

public:
    MainWidget(QWidget *parent = 0);
    ~MainWidget();

private slots:
    void scaleChanged(int);

private:
    DrawingPad *m_drawingPad;
};

#endif // MAINWIDGET_H
