#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <pthread.h>
#include <QList>
#include <QString>
#include "servercon.h"
#include <QDebug>

class Controller
{
private:
    Controller();
    //ServerCon con;

public:
    ~Controller();
    static Controller* getInstance();
    /* Home */
    QList<QString>* getUserMessages();
    QString getUserName();

    /* Search */
};

static Controller *instance = nullptr;

#endif // CONTROLLER_H
