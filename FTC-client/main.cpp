#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QtQml>
#include <QPixmap>
#include <QCursor>
#include <QQmlContext>
#include "servercon.h"
#include "controller.h"
#include "departmentmodel.h"

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    DepartmentModel::setDepartments(Controller::getInstance()->getDepartments());

    QQmlApplicationEngine engine;

    qmlRegisterType<UserMessagesModel>("UserMessages", 1, 0, "UserMessages");
    qmlRegisterType<LoginModel>("Login", 1, 0, "Login");
    qmlRegisterType<SearchEmployeeResultModel>("SearchEmployeeModel", 1, 0, "SearchEmployeeModel");
    qmlRegisterType<SearchWorkingModel>("SearchWorkingResult", 1, 0, "SearchWorkingResult");
    qmlRegisterType<DepartmentModel>("DepartmentModel", 1, 0, "DepartmentModel");

    /*make cursor inivisible*/
//    QPixmap nullCursor(16, 16);
//    nullCursor.fill(Qt::transparent);
//    app.setOverrideCursor(QCursor(nullCursor));

    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));

    return app.exec();
}

