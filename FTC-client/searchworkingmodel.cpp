#include "searchworkingmodel.h"

SearchWorkingModel::SearchWorkingModel(QObject *parent)
    : QAbstractListModel(parent), m_date(QDate())
{

}

int SearchWorkingModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);

    return working.count();
}

QVariant SearchWorkingModel::data(const QModelIndex &index, int role) const
{
    // the index returns the requested row and column information.
    // we ignore the column and only use the row information
    int row = index.row();
    // boundary check for the row
    if(row < 0 || row >= working.count()) {
        return QVariant();
    }
    // A model can return data for different roles.
    // The default role is the display role.
    // it can be accesses in QML with "model.display"
    switch(role) {
    case Qt::DisplayRole:
        // Return the color name for the particular row
        // Qt automatically converts it to the QVariant type
        return working.value(row);
    }
    // The view asked for other data, just return an empty QVariant
    return QVariant();
}

void SearchWorkingModel::insertData(QString str)
{
    working.append(str);
    beginResetModel();
    endResetModel();
}

void SearchWorkingModel::clearData()
{
    working.clear();
    beginResetModel();
    endResetModel();
}

void SearchWorkingModel::search()
{
    Controller::getInstance()->searchWorking(this);
}
