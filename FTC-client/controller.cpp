#include "controller.h"

static Controller *instance = NULL;

Controller::Controller()
    : msgQ(FTC_EVENT_MSGQ_NAME), con(), ftc(&con)
{
    cout << "Controller constructor" << endl;
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

    usrmsgs = ptr;
}

void Controller::setLoginModel(LoginModel *ptr)
{
    cout << "Setting login model" << endl;

    log = ptr;
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

    cout << "Controller listening ftc" << endl;

    while(self->log == NULL){ /*TODO: condition variable*/
        //cout << "Log:" << self->log << endl;
        sleep(1);
    }
    while(self->usrmsgs == NULL){ /*TODO: condition variable*/
        //cout << "UsrMsg:" << self->usrmsgs << endl;
        sleep(1);
    }
    cout << "Controller broke cycles" << endl;

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
        UserInfo *usr = ftc.getUserInfo();
        if(usr == NULL){
            errx(1, "Error, No user info");
        }
        bool priv = (usr->getPermission() != Permissions::NON_PRIVILEDGED) ? (true) : (false);
        self->log->logIn(QString(usr->getName().c_str()), priv);
        self->usrmsgs->insertData(conv(usr->getMessages()));
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
