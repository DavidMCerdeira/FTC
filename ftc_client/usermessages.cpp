#include "usermessages.h"

UserMessagesModel::UserMessagesModel(QObject *parent)
    : QAbstractListModel(parent), mutex(PTHREAD_MUTEX_INITIALIZER)
{
    connect(this, SIGNAL(insertData(QString)), this, SLOT(insertNewData(QString)));
    connect(this, SIGNAL(insertData(QStringList)), this, SLOT(insertNewData(QStringList)));
    connect(this, SIGNAL(clearData()), this, SLOT(clearAllData()));

    Controller::getInstance()->setUserMessagesModel(this);
}

UserMessagesModel::~UserMessagesModel()
{
    Controller::getInstance()->resetUserMessagesModel();
}

int UserMessagesModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);

    return  m_data.count();
}

QVariant UserMessagesModel::data(const QModelIndex &index, int role) const
{
    // the index returns the requested row and column information.
    // we ignore the column and only use the row information
    int row = index.row();
    // boundary check for the row
    if(row < 0 || row >= m_data.count()) {
        return QVariant();
    }
    // A model can return data for different roles.
    // The default role is the display role.
    // it can be accesses in QML with "model.display"
    switch(role) {
    case Qt::DisplayRole:
        // Return the color name for the particular row
        // Qt automatically converts it to the QVariant type
        return m_data.value(row);
    }
    // The view asked for other data, just return an empty QVariant
    return QVariant();
}

void UserMessagesModel::lock()
{
    pthread_mutex_lock(&mutex);

}

void UserMessagesModel::unlock()
{
    pthread_mutex_unlock(&mutex);
}

void UserMessagesModel::insertNewData(QString str)
{
    m_data.append(str);
    emit dataChanged(QModelIndex(), QModelIndex());
    beginResetModel();
    endResetModel();
}

void UserMessagesModel::insertNewData(QStringList str)
{
    m_data = str;
    emit dataChanged(QModelIndex(), QModelIndex());
    beginResetModel();
    endResetModel();
}

void UserMessagesModel::clearAllData()
{
    m_data.clear();
    emit dataChanged(QModelIndex(), QModelIndex());
    beginResetModel();
    endResetModel();
}
