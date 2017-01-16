#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>

#include "common.h"
#include "glview.h"

int main(int argc, char *argv[])
{
    LOG_METHOD_CALLED;

    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QGuiApplication app(argc, argv);

    GLView view;
    view.setResizeMode(QQuickView::SizeRootObjectToView);
    view.rootContext()->setContextProperty("mainView", &view);

    view.setSource(QUrl("qrc:/main.qml"));


    view.show();

    return app.exec();
}
