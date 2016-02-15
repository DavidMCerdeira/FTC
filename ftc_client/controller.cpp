#include "controller.h"

static Controller *instance = NULL;

Controller::Controller()
    : msgQ(FTC_EVENT_MSGQ_NAME), con(), ftc(&con),
      usrmsgs(nullptr), log(nullptr), cam(nullptr),
      models_mutex(PTHREAD_MUTEX_INITIALIZER),
      modelsCond_mutex(PTHREAD_MUTEX_INITIALIZER),
      modelsRdy_cond(PTHREAD_COND_INITIALIZER),
      srchParams({"", 0, 0})
{
    cout << "Controller constructor" << endl;

    //    jobs = con.getJobs();
    //    departments = con.getDepartments();
    ftc.run();
    pthread_create(&ftcListen_handle, NULL, ftcListen_thread, this);
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

void Controller::setUserMessagesModel(UserMessagesModel *ptr)
{
    cout << "Setting user messages model" << endl;

    pthread_mutex_lock(&models_mutex);
    usrmsgs = ptr;
    pthread_mutex_unlock(&models_mutex);
    checkModelsCondition();
}

void Controller::resetUserMessagesModel()
{
    pthread_mutex_lock(&models_mutex);
    usrmsgs = NULL;
    pthread_mutex_unlock(&models_mutex);
}

void Controller::setLoginModel(LoginModel *ptr)
{
    cout << "Setting login model" << endl;

    pthread_mutex_lock(&models_mutex);
    log = ptr;
    pthread_mutex_unlock(&models_mutex);
    checkModelsCondition();
}

void Controller::resetLoginModel()
{
    log = NULL;
}

void Controller::setCamCap(CamCap *ptr)
{
    cam = ptr;
}

void Controller::resetCamCap()
{
    cam = NULL;
}

void Controller::checkModelsCondition()
{
    pthread_mutex_lock(&modelsCond_mutex);
    if(log != NULL && usrmsgs != NULL){
        pthread_cond_signal(&modelsRdy_cond);
    }
    pthread_mutex_unlock(&modelsCond_mutex);
}

void Controller::logOut()
{
    cout << "Controller logout" << endl;

    ftc.logout();
    log->explicitLogOut();
    if(usrmsgs != NULL){
        usrmsgs->clearData();
    }
}

int Controller::clockUser()
{
    UserInfo *usr = ftc.getUserInfo();
    int clocked = 0;
    int id;
    if(usr->clockUser()){
        clocked = 1;
    }
    else{
        clocked = 0;
    }

    Json::Value ret = con.getRequestManager()->clockUser(id = usr->getId(),
                                            (clocked) ? "in" : "out");
    if(ret.isMember("nothing")){
        errx(1, "Tried to clock in but no info recieved");
    }

    if(id != ret["worker_id"].asInt()){
        errx(1, "Received a different user id");
    }

    if(clocked != ret["clock_state"].asInt()){
        errx(1, "Clock state differs!");
    }

//    log->setClockedState(clocked);
    return clocked;
}

QStringList Controller::getDepartments()
{
    QStringList temp;

    for(vector<string>::iterator it = departments.begin();
        it != departments.end(); it++)
    {
        temp.append(it->c_str());
    }

    return temp;
}


QStringList Controller::getJobs()
{
    QStringList temp;

    for(vector<string>::iterator it = jobs.begin();
        it != jobs.end(); it++)
    {
        temp.append(it->c_str());
    }

    return temp;
}

void* Controller::ftcListen_thread(void *arg)
{
    Controller *self = static_cast<Controller*>(arg);

    int buffSize = 50;
    char *buff;
    int nRcvd = -1;

    cout << "Controller listening ftc" << endl;

    while(1){
        buff = (char*) calloc(buffSize, sizeof(char));
        if(buff == nullptr){
            err(1, "Error allocating buffer to receive message from message queue %s\n",
                self->msgQ.getName());
        }
        nRcvd = self->msgQ.getMsg(buff, buffSize);
        if(nRcvd > buffSize){
            errx(1, "Message too long on message queue:%s\n",
                 self->msgQ.getName());
        }
        self->ftcEventHandler(buff, self);
    }

    pthread_exit(nullptr);
}

QStringList conv(list<string> org)
{
    QStringList list;

    for(std::list<std::string>::iterator it = org.begin();
        it != org.end(); it++)
    {
        list.append(it->c_str());
    }
    return list;
}

void Controller::ftcEventHandler(char *event, Controller *self)
{
    cout << "Controller ftc event handler" << endl;

    if(strcmp(event, FTC_Events::usr_present) == 0){
        /* notify user it has been detected */
    }
    else if(strcmp(event, FTC_Events::usr_absent) == 0){

        pthread_mutex_lock(&modelsCond_mutex);
        if(log == NULL || usrmsgs == NULL){
            pthread_cond_wait(&modelsRdy_cond, &modelsCond_mutex);
        }
        pthread_mutex_unlock(&modelsCond_mutex);
        pthread_mutex_lock(&models_mutex);
        /* user left so logout */
        qDebug() << "User walked away";
        self->logOut();
    }
    else if(strcmp(event, FTC_Events::usr_valid) == 0){
        /* show that user is valid while waiting for info */
        qDebug() << "User is valid, waiting info";
    }
    else if(strcmp(event, FTC_Events::usr_unkwon) == 0){
        /* display some error message */
    }
    else if(strcmp(event, FTC_Events::usr_infRdy) == 0){
        qDebug() << "User info is ready";
        pthread_mutex_lock(&modelsCond_mutex);
        if(log == NULL || usrmsgs == NULL){
            pthread_cond_wait(&modelsRdy_cond, &modelsCond_mutex);
        }
        pthread_mutex_unlock(&modelsCond_mutex);
        pthread_mutex_lock(&models_mutex);
        UserInfo *usr = ftc.getUserInfo();
        if(usr == NULL){
            errx(1, "Error, No user info");
        }

        bool priv = (usr->getPermission() != Permissions::NON_PRIVILEDGED) ? (true) : (false);
        qDebug() << "usr" << usr->getName().c_str();
        self->log->logIn(QString(usr->getName().c_str()), priv);
        self->log->setClockedState(usr->isClockedIn());
        self->usrmsgs->insertData(conv(usr->getMessages()));
    }
    else if(strcmp(event, FTC_Events::need_photo) == 0){
        qDebug() << "Need photo";
        self->ftc.setFace(QImage());
    }
    else{
        /* literally wtf */
        errx(1, "Unknown message from message queue:%s\n"
                "Here is the message:%s\n",
             self->msgQ.getName(), event);
    }
    pthread_mutex_unlock(&models_mutex);
    free(event);
}

void Controller::setEmployee(QString name)
{
    qDebug() << "Name" << name << "controller" << endl;
    srchParams.name = name.toStdString();
}

void Controller::setDepartment(int idx)
{
    qDebug() << "setting department";
    srchParams.department = idx;
}

void Controller::setJob(int idx)
{
    qDebug() << "setting job" << idx;
    srchParams.job = idx;
}

QStringList Controller::search()
{
    list<string> temp;

    QStringList a;

    qDebug() << "Name" << srchParams.name.c_str();
    qDebug() << "Departs" << srchParams.department;
    qDebug() << "Job" << srchParams.job;

    for(list<string>::iterator it = temp.begin();
        it != temp.end(); it++)
    {
        a.append(it->c_str());
    }
    return a;
}
