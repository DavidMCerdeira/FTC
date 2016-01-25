#include "searchemployeeresultmodel.h"

searchEmployeeResultModel::searchEmployeeResultModel(QObject *parent)
    : QAbstractListModel(parent)
{
    Controller::getInstance()->setSearchEmployeeModel(this);
}

int searchEmployeeResultModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);

    return result.count();
}

QVariant searchEmployeeResultModel::data(const QModelIndex &index, int role) const
{
    // the index returns the requested row and column information.
    // we ignore the column and only use the row information
    int row = index.row();
    // boundary check for the row
    if(row < 0 || row >= result.count()) {
        return QVariant();
    }
    // A model can return data for different roles.
    // The default role is the display role.
    // it can be accesses in QML with "model.display"
    switch(role) {
    case Qt::DisplayRole:
        // Return the color name for the particular row
        // Qt automatically converts it to the QVariant type
        return result[row];
    }
    // The view asked for other data, just return an empty QVariant
    return QVariant();
}

void searchEmployeeResultModel::insertData(QString str)
{
    result.append(str);
}

void searchEmployeeResultModel::clearData()
{
    result.clear();
}
