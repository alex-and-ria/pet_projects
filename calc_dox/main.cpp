#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QtWidgets/QApplication>
#include <QQmlContext>
#include <QQmlComponent>
#include "calc_dox.h"

int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QApplication app(argc, argv);

    QQmlApplicationEngine engine;
    calc_dox calc(&engine);

    if (engine.rootObjects().isEmpty())
        return -1;

    return app.exec();
}
