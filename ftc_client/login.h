#ifndef LOGIN_H
#define LOGIN_H

#include <QAbstractListModel>
#include <QList>
#include <QString>
#include <QDebug>
#include "controller.h"
#include "ftc_requests.h"

class LoginModel : public QAbstractListModel
{
    Q_OBJECT
    QString text;
    bool m_bPrivilege;
    bool m_bLogged;
    bool m_clocked;

    pthread_mutex_t mutex;

public:
    explicit LoginModel(QObject *parent = 0);
    ~LoginModel();
    virtual int rowCount(const QModelIndex &parent) const;
    /* this is function is redundant as we only have one element */
    virtual QVariant data(const QModelIndex &index, int role) const;

    Q_PROPERTY(bool priviledged READ getPriviledge)
    Q_PROPERTY(bool logged READ getLoggedState)
    Q_PROPERTY(int clocked READ getClockedInState)

    Q_INVOKABLE void logout();
    Q_INVOKABLE void clockUser();

    bool getClockedInState();
    void setClockedState(bool clockedIn);
    void lock();
    void unlock();

signals:
    void logIn(QString str, bool priv);
    void explicitLogOut();
    void clockChanged(bool clockedIn);

private slots:
    void xLogout();
    void xLogin(QString str, bool priv);

private:
    bool getPriviledge(){return m_bPrivilege;}
    bool getLoggedState(){return m_bLogged;}
    void setNameAndPriv(QString str, bool priv);
};

#endif // LOGIN_H
