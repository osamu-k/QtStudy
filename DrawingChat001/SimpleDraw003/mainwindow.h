#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "drawingpad.h"

#include <QMainWindow>

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void setShapeFreeHand();
    void setShapeRectangle();
    void setLineColor();
    void setLineWidth();

private:
    DrawingPad *m_drawingPad;
    QMenu *m_menuEdit;
    QMenu *m_menuShapeType;
    QAction *m_actionShapeFreeHand;
    QAction *m_actionShapeRectangle;
    QAction *m_actionLineColor;
    QAction *m_actionLineWidth;
};

#endif // MAINWINDOW_H
