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

void Controller::logOut()
{
    qDebug() << "Logout";
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
