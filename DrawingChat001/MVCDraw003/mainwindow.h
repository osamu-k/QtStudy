#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "drawingcontroller.h"
#include "drawingview.h"

#include <QMainWindow>

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void newDrawing();
    void openFile();
    void saveFile();

    void setShapeFreeHand();
    void setShapeRectangle();
    void setLineColor();
    void setFillColor();
    void setLineWidth();
    void setOutlineEnabled();
    void setFillColorEnabled();

    void newWindow();

private:
    DrawingController *m_controller;
    DrawingView *m_view;

    QMenu *m_menuFile;
    QMenu *m_menuEdit;
    QMenu *m_menuShapeType;
    QMenu *m_menuDisplay;

    QAction *m_actionNew;
    QAction *m_actionOpen;
    QAction *m_actionSave;
    QAction *m_actionShapeFreeHand;
    QAction *m_actionShapeRectangle;
    QAction *m_actionLineColor;
    QAction *m_actionFillColor;
    QAction *m_actionLineWidth;
    QAction *m_actionOutlineEnabled;
    QAction *m_actionFillColorEnabled;
    QAction *m_actionNewWindow;
};

#endif // MAINWINDOW_H
