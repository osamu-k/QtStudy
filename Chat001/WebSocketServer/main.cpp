#include "webserverwidget.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    WebServerWidget w;
    w.show();

    return a.exec();
}
