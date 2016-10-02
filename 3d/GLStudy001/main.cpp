#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include "modelrenderer.h"

int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QGuiApplication app(argc, argv);

    qmlRegisterType< ModelRenderer >("GLStudy", 1, 0, "ModelRenderer");

    QQmlApplicationEngine engine;
    engine.load(QUrl(QLatin1String("qrc:/main.qml")));

    return app.exec();
}
