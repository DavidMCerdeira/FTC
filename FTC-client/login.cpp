#include "login.h"

#define LogOutMessage "Not Logged In"

LoginModel::LoginModel(QObject *parent)
    : QAbstractListModel(parent)
{
    connect(this, SIGNAL(logIn(QString, bool)), this, SLOT(xLogin(QString, bool)));
    connect(this, SIGNAL(explicitLogOut()), this, SLOT(xLogout()));
    Controller::getInstance()->setLoginModel(this);
    xLogout();

    //setNameAndPriv(LogOutMessage, false);
}

int LoginModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);

    /* return 1 element as that's the only one we have */
    return 1;
}

QVariant LoginModel::data(const QModelIndex &index, int role) const
{
    // the index returns the requested row and column information.
    // we ignore the column and only use the row information
    int row = index.row();
    // boundary check for the row
    if(row < 0 || row > 1) {
        return QVariant();
    }
    // A model can return data for different roles.
    // The default role is the display role.
    // it can be accesses in QML with "model.display"
    switch(role) {
    case Qt::DisplayRole:
        // Return the color name for the particular row
        // Qt automatically converts it to the QVariant type
        return text;
    }
    // The view asked for other data, just return an empty QVariant
    return QVariant();
}

void LoginModel::setNameAndPriv(QString str, bool priv)
{
    text = str;
    m_bPrivilege = priv;

    emit dataChanged(QModelIndex(), QModelIndex());
    beginResetModel();
    endResetModel();
}

void LoginModel::logout()
{
    if(m_bLogged){
        Controller::getInstance()->logOut();
    }
    //xLogout();
}

void LoginModel::xLogout()
{
    m_bLogged = false;
    setNameAndPriv(LogOutMessage, false);
}

void LoginModel::xLogin(QString str, bool priv)
{
    m_bLogged = true;
    setNameAndPriv(str, priv);
}

void LoginModel::clockUser()
{
    if(m_bLogged){
        qDebug() << "User asked to clock";
    }
    else{
        qDebug() << "User tried to clock but it's logged in";
        qDebug() << "Maybe you should tell him...";
    }
}
