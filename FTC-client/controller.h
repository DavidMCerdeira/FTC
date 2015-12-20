#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <pthread.h>
#include <QList>
#include <QString>
#include <QDebug>

#include "usermessages.h"
#include "login.h"
#include "servercon.h"

class UserMessagesModel;
class LoginModel;

class Controller
{
private:
    Controller();
    //ServerCon con;
    UserMessagesModel *usrmsgs;
    LoginModel *log;

public:
    ~Controller();
    static Controller* getInstance();
    /* Home */
    void setUserMessagesModel(UserMessagesModel*);
    void setLoginModel(LoginModel*);


    /* Search */
};

static Controller *instance = NULL;

#endif // CONTROLLER_H
