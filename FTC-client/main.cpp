#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QtQml>
#include "servercon.h"
#include "usermessages.h"

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;

    qmlRegisterType<UserMessages>("UserMessages", 1, 0, "UserMessages");

    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));

    return app.exec();
}

