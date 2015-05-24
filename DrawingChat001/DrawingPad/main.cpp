#include "mainwidget.h"
#include "drawingmodel.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    DrawingModel model;

    MainWidget mainWidget;
    mainWidget.setDrawingModel(&model);
    mainWidget.show();

    return a.exec();
}
