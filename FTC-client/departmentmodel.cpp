#include "departmentmodel.h"
QList<QString> DepartmentModel::m_departments;

DepartmentModel::DepartmentModel(QObject *parent)
    : QStringListModel(parent)
{
    for(QList<QString>::iterator it = m_departments.begin();
        it != m_departments.end(); it++){
        this->stringList().append(*it);
    }
}

int DepartmentModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    return m_departments.count();
}

//QVariant DepartmentModel::data(const QModelIndex &index, int role) const
//{
//    // the index returns the requested row and column information.
//    // we ignore the column and only use the row information
//    int row = index.row();
//    // boundary check for the row
//    if(row < 0 || row >= m_departments.count()) {
//        return QVariant();
//    }
//    // A model can return data for different roles.
//    // The default role is the display role.
//    // it can be accesses in QML with "model.display"
//    switch(role) {
//    case Qt::DisplayRole:
//        // Return the color name for the particular row
//        // Qt automatically converts it to the QVariant type
//        return m_departments.value(row);
//    }
//    // The view asked for other data, just return an empty QVariant
//    return QVariant();
//}


void DepartmentModel::setDepartments(QStringList list)
{
    m_departments.clear();
    m_departments.append(list);
}
