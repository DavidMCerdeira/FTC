#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QtQml>
#include "servercon.h"
#include "usermessages.h"
//#include "login.h"

#include "controller.h"

int main(int argc, char *argv[])
{
    Controller *control = Controller::getInstance();

    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;

    qmlRegisterType<UserMessagesModel>("UserMessages", 1, 0, "UserMessages");
    qmlRegisterType<LoginModel>("Login", 1, 0, "Login");

    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));

    return app.exec();
}

