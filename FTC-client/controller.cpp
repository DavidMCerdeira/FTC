#include "controller.h"

static Controller *instance = NULL;

Controller::Controller()
    : msgQ(FTC_EVENT_MSGQ_NAME)
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

    usrmsgs->insertData("Ola! Eu sou uma mensagem!");
}

void Controller::setLoginModel(LoginModel *ptr)
{
    log = ptr;

    log->setText("Maria Albertina");
}

void Controller::logOut()
{
    qDebug() << "Logout";
    ftc.explicitLogout();
    log->setText("Not Logged in");
}

void Controller::setSearchEmployeeModel(searchEmployeeResultModel *model)
{
    employeeRlsts = model;

    model->insertData("O Bóias não trabalha");
}

void Controller::setSearchWorking(SearchWorkingModel *model)
{
    workingRlsts = model;

    model->insertData("Loleiras");
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
        buff = (char*) malloc(buffSize);
        if(buff == nullptr){
            err(1, "Error allocating buffer to receive message from message queue %s\n",
                        self->msgQ.getName());
        }
        nRcvd = self->msgQ.getMsg(buff, buffSize);
        qDebug() << "Received Message: " << buff;
        self->ftcEventHandler(buff, self);
    }
}

void Controller::ftcEventHandler(char *event, Controller *self)
{
    if(strcmp(event, FTC_Events::usr_present) != 0){
        /* notify user it has been detected */
    }
    else if(strcmp(event, FTC_Events::usr_absent) != 0){
        /* user left so logout */
        self->logOut();
    }
    else if(strcmp(event, FTC_Events::usr_valid) != 0){
        /* ask for usr id and info */
    }
    else if(strcmp(event, FTC_Events::usr_unkwon) != 0){
        /* display some error message */
    }
    else{
        /* literally wtf */
        err(1, "Unknown message from message queue:%s\n"
               "Here is the message:%s\n",
                    self->msgQ.getName(), event);
    }

    free(event);
}
