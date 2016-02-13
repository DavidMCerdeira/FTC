#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <pthread.h>
#include <QList>
#include <QString>
#include <QDebug>

#include <searchresultmodel.h>
#include <usermessages.h>
#include <login.h>
#include "servercon.h"
#include "ftc.h"
#include "camcap.h"

class UserMessagesModel;
class LoginModel;
class SearchEmployeeResultModel;
class SearchWorkingModel;
class SearchResultModel;
class CamCap;

struct SearchParams
{
    string name;
    int department;
    int job;
};

class Controller
{
private:
    Controller();
    MyMessageQueue msgQ;
    ServerCon con;
    FTC ftc;

    UserMessagesModel *usrmsgs;
    LoginModel *log;
    CamCap* cam;

    pthread_mutex_t models_mutex;
    pthread_mutex_t modelsCond_mutex;
    pthread_cond_t modelsRdy_cond;

    pthread_t ftcListen_handle;
    SearchParams srchParams;

    vector<string> departments;
    vector<string> jobs;

public:
    ~Controller();
    static Controller* getInstance();

    /* set Home models */
    void setUserMessagesModel(UserMessagesModel*);
    void resetUserMessagesModel();
    void setLoginModel(LoginModel*);
    void resetLoginModel();
    void setCamCap(CamCap*);
    void resetCamCap();

    QStringList getDepartments();
    QStringList getJobs();
    QStringList search();
    /* home related functions */
    void logOut();
    void login();

    /*search related functions */
    void setEmployee(QString name);
    void setDepartment(int idx);
    void setJob(int i);

private:
    /* not UI */
    static void* ftcListen_thread(void *arg);
    void ftcEventHandler(char *event, Controller *self);

    void checkModelsCondition();
};

#endif // CONTROLLER_H
