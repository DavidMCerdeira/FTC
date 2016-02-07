#include "login.h"

LoginModel::LoginModel(QObject *parent)
    : QAbstractListModel(parent)
{
    connect(this, SIGNAL(setText(QString)), this, SLOT(setNewText(QString)));
    Controller::getInstance()->setLoginModel(this);

    //emit setText("lol");
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

void LoginModel::setNewText(QString str)
{
    text = str;

    qDebug() << "Text changed to: " << str;
    //emit dataChanged(QModelIndex(), QModelIndex());
    beginResetModel();
    endResetModel();
}

void LoginModel::logout()
{
    Controller::getInstance()->logOut();
}

void LoginModel::clockUser()
{
    qDebug() << "User asked to clock";
}
