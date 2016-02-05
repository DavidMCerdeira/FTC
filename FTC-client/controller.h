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
#include "ftc.h"

class UserMessagesModel;
class LoginModel;
class searchEmployeeResultModel;
class SearchWorkingModel;

class Controller
{
private:
    Controller();
    ServerCon *con;
    UserMessagesModel *usrmsgs;
    LoginModel *log;
    searchEmployeeResultModel *employeeRlsts;
    SearchWorkingModel *workingRlsts;

    FTC ftc;
    MyMessageQueue msgQ;

    pthread_t ftcListen_handle;

public:
    ~Controller();
    static Controller* getInstance();

    /* Home */
    void setUserMessagesModel(UserMessagesModel*);
    void setLoginModel(LoginModel*);

    void logOut();
    void login();

    /* Search */
    void setSearchEmployeeModel(searchEmployeeResultModel*);
    void setSearchWorking(SearchWorkingModel*);
    QStringList getDepartments();

    /* not UI */
    static void* ftcListen_thread(void *arg);
    void ftcEventHandler(char *event, Controller *self);
};

#endif // CONTROLLER_H
