#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include "servercon.h"
#include <QtQml>

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;

    qmlRegisterType<ServerCon>("Connection", 1, 0, "Con");


    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));

    return app.exec();
}

