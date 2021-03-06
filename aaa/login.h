#ifndef LOGIN_H
#define LOGIN_H

#include <QAbstractListModel>
#include <QList>
#include <QString>
#include <QDebug>
#include "controller.h"

class LoginModel : public QAbstractListModel
{
    Q_OBJECT
    QString text;
    bool m_bPrivilege;
    bool m_bLogged;

    pthread_mutex_t mutex;

public:
    explicit LoginModel(QObject *parent = 0);
    ~LoginModel();
    virtual int rowCount(const QModelIndex &parent) const;
    /* this is function is redundant as we only have one element */
    virtual QVariant data(const QModelIndex &index, int role) const;

    Q_PROPERTY(bool priviledged READ getPriviledge)
    Q_PROPERTY(bool logged READ getLoggedState)

    Q_INVOKABLE void logout();
    Q_INVOKABLE void clockUser();

    void lock();
    void unlock();

signals:
    void logIn(QString str, bool priv);
    void explicitLogOut();

private slots:
    void xLogout();
    void xLogin(QString str, bool priv);

private:
    bool getPriviledge(){return m_bPrivilege;}
    bool getLoggedState(){return m_bLogged;}
    void setNameAndPriv(QString str, bool priv);
};

#endif // LOGIN_H
