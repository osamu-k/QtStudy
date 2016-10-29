#include "mainwidget.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWidget w;
    MainWidget w2;
    w.show();
    w2.show();

    return a.exec();
}
