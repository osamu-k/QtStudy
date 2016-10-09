#include "chatclientwidget.h"
#include <QApplication>
#include <QDesktopWidget>
#include <QScreen>

#include <QDebug>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    ChatClientWidget w;
    w.show();

    return a.exec();
}
