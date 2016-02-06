#include "controller.h"

static Controller *instance = NULL;

Controller::Controller()
    : msgQ(FTC_EVENT_MSGQ_NAME), con(), ftc(&con)
{
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
    usrmsgs = ptr;
}

void Controller::setLoginModel(LoginModel *ptr)
{
    log = ptr;
}

void Controller::logOut()
{
    qDebug() << "Logout";
    ftc.explicitLogout();
    log->explicitLogOut();
    if(usrmsgs != NULL){
        usrmsgs->clearData();
    }
}

QStringList Controller::getDepartments()
{
    QList<QString> temp;

    /*ask server*/
    temp.append("lol1");
    temp.append("lol2");
    temp.append("lol3");
    temp.append("lol4");

    return temp;
}

void* Controller::ftcListen_thread(void *arg)
{
    Controller *self = static_cast<Controller*>(arg);

    int buffSize = 50;
    char *buff;
    int nRcvd = -1;

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

void Controller::ftcEventHandler(char *event, Controller *self)
{
    while(self->log == nullptr);
    while(self->usrmsgs == nullptr);

    if(strcmp(event, FTC_Events::usr_present) == 0){
        /* notify user it has been detected */
    }
    else if(strcmp(event, FTC_Events::usr_absent) == 0){
        /* user left so logout */
        qDebug() << "User walked away";
        self->logOut();
    }
    else if(strcmp(event, FTC_Events::usr_valid) == 0){
        /* show that user is valid while waiting for info */
        qDebug() << "User is valid lol";
    }
    else if(strcmp(event, FTC_Events::usr_unkwon) == 0){
        /* display some error message */
    }
    else if(strcmp(event, FTC_Events::usr_infRdy) == 0){
        UserInfo *usr = ftc.getUserInfo();
        if(usr == NULL){
            errx(1, "Error, No user info");
        }
        bool priv = (usr->getPermission() != Permissions::NON_PRIVILEDGED) ? (true) : (false);
        self->log->logIn(QString(usr->getName().c_str()), priv);
        //self->usrmsgs->insertData();
    }
    else{
        /* literally wtf */
        errx(1, "Unknown message from message queue:%s\n"
                "Here is the message:%s\n",
                    self->msgQ.getName(), event);
    }

    free(event);
}

void Controller::searchEmployee(SearchEmployeeResultModel *srch)
{
    if(srch != NULL){
        srch->insertData("O Bóias não trabalha");
    }
    else{
        errx(1, "Error: No employee search result model");
    }
}

void Controller::searchWorking(SearchWorkingModel *srch)
{
    if(srch != NULL){
        srch->insertData("E tem gases");
    }
    else{
        errx(1, "Error: No employee search result model");
    }
}
