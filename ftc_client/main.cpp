#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QtQml>
#include <QPixmap>
#include <QCursor>
#include <QQmlContext>
#include "servercon.h"
#include "controller.h"
#include "departmentsmodel.h"
#include "jobsmodel.h"
#include "searchresultmodel.h"
#include "setnameforsearch.h"
#include "camcap.h"
#include "distancesensor.h"

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;

    qmlRegisterType<UserMessagesModel>("UserMessages", 1, 0, "UserMessages");
    qmlRegisterType<LoginModel>("Login", 1, 0, "Login");
    qmlRegisterType<JobsModel>("JobsModel", 1, 0, "JobsModel");
    qmlRegisterType<DepartmentsModel>("DepartmentsModel", 1, 0, "DepartmentsModel");
    qmlRegisterType<SearchResultModel>("SearchResultModel", 1, 0, "SearchResulModel");
    qmlRegisterType<setNameForSearch>("SetNameForSearch", 1, 0, "SetNameForSearch");
    qmlRegisterType<DistanceSensor>("DistanceSensor", 1, 0, "DistanceSensor");

    /*make cursor inivisible*/
//    QPixmap nullCursor(16, 16);
//    nullCursor.fill(Qt::transparent);
//    app.setOverrideCursor(QCursor(nullCursor));

    engine.addImageProvider(QLatin1String("WebCam"), new CamCap);
    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));

    return app.exec();
}

