#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "logindialog.h"
#include <qdebug.h>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    QString name, password;
    LoginDialog *login = new LoginDialog(&name, &password);
    connect(login, SIGNAL(rejected()), this, SLOT(quit()));
    login->exec();

    qDebug() << name << password;
    /* validate */

    ui->setupUi(this);
    connect(ui->tabs, SIGNAL(currentChanged(int)), this, SLOT(slot_tabChanged(int)));

    /* regist tab--> */
    connect(ui->regist_addUserPushButton, SIGNAL(pressed()), this, SLOT(regist_commit()));
    /* <--regist tab */

    /* search tab--> */
    connect(ui->search_searchPushButton, SIGNAL(pressed()), this, SLOT(search_commit()));
    /* <--search tab */

    /* send message tab--> */
    connect(ui->msgs_sendPushButton, SIGNAL(pressed()), this, SLOT(sendMsg_commit()));
    /* <--send message tab */

    flow.setTable(ui->flow_tableWidget);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::slot_tabChanged(int idx)
{
    switch(idx){
    case 0:
        break;
    case 1:
        break;
    case 2:
        break;
    case 3:
        break;
    default:
        qDebug() << "Literally wtf!?!?";
        break;
    }
}

void MainWindow::regist_name()
{
    regist.setName(ui->regist_nameLineEdit->text());
}

void MainWindow::regist_contact()
{
    regist.setContactNumber(ui->regist_contactLineEdit->text());
}

void MainWindow::regist_email()
{
    regist.setEmail(ui->regist_emailLineEdit->text());
}

void MainWindow::regist_commit()
{
    regist.setName(ui->regist_nameLineEdit->text());
    regist.setContactNumber(ui->regist_contactLineEdit->text());
    regist.setEmail(ui->regist_emailLineEdit->text());
    regist.setDepartIdx(ui->regist_departmentsComboBox->currentIndex());
    regist.setJobsIdx(ui->regist_jobComboBox->currentIndex());
    regist.setPermissionsIdx(ui->regist_permissionComboBox->currentIndex());
    regist.setBirth(ui->regist_birthDateEdit->date());
    regist.commitUser();
}

void MainWindow::search_name()
{
    search.setName(ui->search_idLineEdit->text());
}

void MainWindow::search_commit()
{
    search.setName(ui->search_idLineEdit->text());
    search.setDepartIdx(ui->search_departmentsComboBox->currentIndex());
    search.setJobsIdx(ui->search_jobsComboBox->currentIndex());
    search.setPermissions(ui->search_permissionsComboBox->currentIndex());
    search.commit();
}

void MainWindow::sendMsg_commit()
{
    sendMsg.setId(ui->msgs_idLineEdit->text());
    sendMsg.setBroadcast((ui->msgs_broadCastCheckBox->checkState() == Qt::Unchecked) ? false : true);
    sendMsg.setMsg(ui->msgs_messageTextEdit->toPlainText());
    sendMsg.commit();
}

void MainWindow::quit()
{
    exit(0);
}

