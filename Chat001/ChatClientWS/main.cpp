#include "chatclientwswidget.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    ChatClientWSWidget w;
    w.show();

    return a.exec();
}
