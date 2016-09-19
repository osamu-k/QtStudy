#include <QDir>
#include <QGuiApplication>
#include <QQmlApplicationEngine>

#include "renderer.h"

int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QGuiApplication app(argc, argv);

    qmlRegisterType<Renderer>("QML3D001", 1, 0, "Renderer3D");

    QQmlApplicationEngine engine;
    engine.load(QUrl(QLatin1String("qrc:/main.qml")));

    return app.exec();
}
