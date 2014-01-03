/****************************************************************************
**
** Copyright (C) 2014 Osamu Kobayashi.
** Contact: osamu-k@arion.ocn.ne.jp
**
** This file may be used under the terms of
** the GNU General Public License version 3.0
** as published by the Free Software Foundation
** http://www.gnu.org/copyleft/gpl.html.
**
****************************************************************************/

#include <QtGui/QGuiApplication>
#include <QtQml>
#include "qtquick2applicationviewer.h"
#include "gamemodel.h"

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    qmlRegisterType<GameModel>("LifeGame", 1, 0, "GameModel");

    QtQuick2ApplicationViewer viewer;
    viewer.setMainQmlFile(QStringLiteral("qml/LifeGameQML01/main.qml"));
    viewer.showExpanded();

    return app.exec();
}
