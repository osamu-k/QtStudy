#ifndef MAINWIDGET_H
#define MAINWIDGET_H

#include <QWidget>
#include "drawingmodel.h"
#include "drawingpad.h"

class MainWidget : public QWidget
{
    Q_OBJECT
public:
    explicit MainWidget(QWidget *parent = 0);
    ~MainWidget();
    void setDrawingModel(DrawingModel*model);

signals:

public slots:
    void save();
    void open();
    void clear();
    void connectToHost();
    void disconnectFromHost();

private:
    DrawingPad *m_pad;
    DrawingModel *m_model;
};

#endif // MAINWIDGET_H
