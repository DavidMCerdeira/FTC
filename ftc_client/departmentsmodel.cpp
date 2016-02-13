#include "departmentsmodel.h"

DepartmentsModel::DepartmentsModel()
{
    m_data = Controller::getInstance()->getDepartments();
}

void DepartmentsModel::currentItemChanged(int i)
{
    if(i > m_data.size()){
        qErrnoWarning("Index exceeds dimensions");
        exit(1);
    }

    Controller::getInstance()->setDepartment(i);
}

int DepartmentsModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);

    return  m_data.count();
}

QVariant DepartmentsModel::data(const QModelIndex &index, int role) const
{
    int row = index.row();
    if(row < 0 || row >= m_data.count()) {
        return QVariant();
    }

    switch(role)
    {
    case Qt::DisplayRole:
        return m_data.value(row);
    }

    /*other role*/
    return QVariant();
}
