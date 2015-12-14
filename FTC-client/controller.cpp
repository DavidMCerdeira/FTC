#include "controller.h"

Controller::Controller()
{
    qDebug() << "Creating controller instance" << endl;
}

Controller::~Controller()
{
    delete instance;
    instance = NULL;
}

Controller* Controller::getInstance()
{
    if(instance == NULL)
        instance = new Controller();

    return instance;
}

QList<QString>* Controller::getUserMessages()
{
    QList<QString> *temp = new QList<QString>();
    temp->append("Um dois três");
    temp->append("Três Dois Um");

    return temp;
}

QString Controller::getUserName()
{
    return QString("John Doe");
}
