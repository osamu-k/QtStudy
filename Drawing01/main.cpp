/**
main.cpp

Copyright (c) Osamu Kobayashi

This software is released under the MIT License.
http://opensource.org/licenses/mit-license.php
*/

#include "drawingpad.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    DrawingPad w;
    w.show();

    return a.exec();
}
