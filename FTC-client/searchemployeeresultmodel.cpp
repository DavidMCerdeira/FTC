#include "searchemployeeresultmodel.h"

SearchEmployeeResultModel::SearchEmployeeResultModel(QObject *parent)
    : QAbstractListModel(parent), result(), employee("")
{
    connect(this, SIGNAL(insertData(QString)), this, SLOT(insertNewData(QString)));
    connect(this, SIGNAL(clearData()), this, SLOT(clearAllData()));

    //Controller::getInstance()->setSearchEmployeeModel(this);
}

int SearchEmployeeResultModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);

    return result.count();
}

QVariant SearchEmployeeResultModel::data(const QModelIndex &index, int role) const
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

void SearchEmployeeResultModel::insertNewData(QString str)
{
    result.append(str);
    beginResetModel();
    endResetModel();
}

void SearchEmployeeResultModel::clearAllData()
{
    result.clear();
    beginResetModel();
    endResetModel();
}

void SearchEmployeeResultModel::search(QString department, QString job)
{
    qDebug() << "Employee:" << employee << "on" << department << "which is:" << job << "search asked.";
    Controller::getInstance()->searchEmployee(this);
}
