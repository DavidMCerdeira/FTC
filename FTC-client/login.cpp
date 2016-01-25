#include "login.h"

LoginModel::LoginModel(QObject *parent)
    : QAbstractListModel(parent)
{
    text = "";
    Controller::getInstance()->setLoginModel(this);
}

int LoginModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);

    /* return 1 element as that's the only one we have */
    return 1;
}

QVariant LoginModel::data(const QModelIndex &index, int role) const
{
    qDebug() << "Login data requested" << endl;

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
        qDebug() << "Returned: " << text << endl;
        return text;
    }
    // The view asked for other data, just return an empty QVariant
    return QVariant();
}

 void LoginModel::setText(QString str)
 {
     text = str;
 }
 
 void LoginModel::logout()
 {
     Controller::getInstance()->logOut();
     //QModelIndex idx = new QModelIndex();
 }
