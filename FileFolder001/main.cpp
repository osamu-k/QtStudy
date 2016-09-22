#include <QGuiApplication>
#include <QQmlApplicationEngine>

#include "standardpaths.h"

void QtAppDelegateInitialize();

int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QGuiApplication app(argc, argv);

    QtAppDelegateInitialize();

    qmlRegisterType<StandardPaths>("FileFolder", 1, 0, "StandardPaths");

    QQmlApplicationEngine engine;
    engine.load(QUrl(QLatin1String("qrc:/main.qml")));

    return app.exec();
}
