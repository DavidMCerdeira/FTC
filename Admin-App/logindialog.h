#ifndef LOGINDIALOG_H
#define LOGINDIALOG_H

#include <QDialog>

namespace Ui {
class LoginDialog;
}

class LoginDialog : public QDialog
{
    Q_OBJECT
    QString *m_name;
    QString *m_passwd;

public:
    explicit LoginDialog(QString *name, QString *passwd, QWidget *parent = 0);
    ~LoginDialog();

private:
    Ui::LoginDialog *ui;

private slots:
    void login();
};

#endif // LOGINDIALOG_H
