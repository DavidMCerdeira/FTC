#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <pthread.h>
#include <QList>
#include <QString>
#include <QDebug>

#include "usermessages.h"
#include "login.h"
#include "servercon.h"
#include "searchemployeeresultmodel.h"

class UserMessagesModel;
class LoginModel;
class searchEmployeeResultModel;

class Controller
{
private:
    Controller();
    //ServerCon con;
    UserMessagesModel *usrmsgs;
    LoginModel *log;
    searchEmployeeResultModel *employeeRlsts;

public:
    ~Controller();
    static Controller* getInstance();
    /* Home */
    void setUserMessagesModel(UserMessagesModel*);
    void setLoginModel(LoginModel*);

    void logOut();

    /* Search */
    void setSearchEmployeeModel(searchEmployeeResultModel*);

};

static Controller *instance = NULL;

#endif // CONTROLLER_H
