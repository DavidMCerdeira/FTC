#include "jobsmodel.h"

JobsModel::JobsModel(QObject *parent)
{
    Q_UNUSED(parent);
    m_data = Controller::getInstance()->getJobs();
}

void JobsModel::currentItemChanged(int i)
{
    if(i > m_data.size()) {
        qErrnoWarning("Index exceeds dimensions");
        exit(1);
    }

    Controller::getInstance()->setJob(i);
}

void JobsModel::departmentChanged(int i)
{
    Q_UNUSED(i);
    qDebug() << "departmente Changed";
    m_data = Controller::getInstance()->getJobs();
    beginResetModel();
    endResetModel();
}

int JobsModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);

    return  m_data.count();
}

QVariant JobsModel::data(const QModelIndex &index, int role) const
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
