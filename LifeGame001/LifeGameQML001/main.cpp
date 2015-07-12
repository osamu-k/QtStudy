#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QtQml>
#include "gamemodel.h"

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    qmlRegisterType<GameModel>("LifeGame", 1, 0, "GameModel");

    QQmlApplicationEngine engine;
    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));

    return app.exec();
}
