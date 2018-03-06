#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>

#include "logic.h"
#include "grd.h"

int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;
    grd ngrd;

    QQmlContext *context = engine.rootContext();
    context->setContextProperty("grido", &ngrd);

    engine.load(QUrl(QLatin1String("qrc:/main.qml")));
    if (engine.rootObjects().isEmpty())
        return -1;
    return app.exec();
}
