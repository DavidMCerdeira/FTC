#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <pthread.h>
#include <QList>
#include <QString>
#include <QDebug>

class Controller;

#include "usermessages.h"
#include "login.h"
#include "servercon.h"
#include "searchworkingmodel.h"
#include "searchemployeeresultmodel.h"
#include "ftc.h"

class UserMessagesModel;
class LoginModel;
class SearchEmployeeResultModel;
class SearchWorkingModel;

class Controller
{
private:
    Controller();
    ServerCon *con;
    UserMessagesModel *usrmsgs;
    LoginModel *log;

    FTC ftc;
    MyMessageQueue msgQ;

    pthread_t ftcListen_handle;

public:
    ~Controller();
    static Controller* getInstance();

    /* set Home models */
    void setUserMessagesModel(UserMessagesModel*);
    void setLoginModel(LoginModel*);
    QStringList getDepartments();

    /* home related functions */
    void logOut();
    void login();

    /*search related functions */
    void searchEmployee(SearchEmployeeResultModel* srch);
    void searchWorking(SearchWorkingModel* srch);

    /* not UI */
    static void* ftcListen_thread(void *arg);
    void ftcEventHandler(char *event, Controller *self);
};

#endif // CONTROLLER_H
