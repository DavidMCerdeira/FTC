#include "logindialog.h"
#include "ui_logindialog.h"

LoginDialog::LoginDialog(QString *name, QString *passwd, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::LoginDialog),
    m_name(name), m_passwd(passwd)
{
    ui->setupUi(this);
    connect(this, SIGNAL(accepted()), this, SLOT(login()));
}

LoginDialog::~LoginDialog()
{
    delete ui;
}

void LoginDialog::login()
{
    *m_name = ui->adminid_lineEdit->text();
    *m_passwd = ui->password_lineEdit->text();
}
