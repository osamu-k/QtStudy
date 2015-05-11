#include "mainwidget.h"
#include "drawingmodel.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    DrawingModel model;

    MainWidget mainWidget1;
    mainWidget1.setDrawingModel(&model);
    mainWidget1.show();

    MainWidget mainWidget2;
    mainWidget2.setDrawingModel(&model);
    mainWidget2.show();

    return a.exec();
}
