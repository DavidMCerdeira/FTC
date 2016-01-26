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
#include "searchworkingmodel.h"

class UserMessagesModel;
class LoginModel;
class searchEmployeeResultModel;
class SearchWorkingModel;

class Controller
{
private:
    Controller();
    //ServerCon con;
    UserMessagesModel *usrmsgs;
    LoginModel *log;
    searchEmployeeResultModel *employeeRlsts;
    SearchWorkingModel *workingRlsts;

public:
    ~Controller();
    static Controller* getInstance();
    /* Home */
    void setUserMessagesModel(UserMessagesModel*);
    void setLoginModel(LoginModel*);

    void logOut();

    /* Search */
    void setSearchEmployeeModel(searchEmployeeResultModel*);
    void setSearchWorking(SearchWorkingModel*);
};

static Controller *instance = NULL;

#endif // CONTROLLER_H
