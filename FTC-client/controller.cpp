#include "controller.h"

Controller::Controller()
{
    qDebug() << "Creating controller instance" << endl;
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

    usrmsgs->insertData("Ola! Eu sou uma mensagem :3");
}

void Controller::setLoginModel(LoginModel *ptr)
{
    log = ptr;

    log->setText("Maria Albertina");
}
