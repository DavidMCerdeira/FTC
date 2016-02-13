#ifndef JOBSMODEL_H
#define JOBSMODEL_H

#include <QAbstractListModel>
#include <QList>
#include <QString>
#include <QDebug>
#include "controller.h"

class JobsModel: public QAbstractListModel
{
    Q_OBJECT
private:
    QStringList m_data;
public:
    Q_INVOKABLE void currentItemChanged(int i);
    Q_INVOKABLE void departmentChanged(int i);
    explicit JobsModel(QObject *parent = 0);

    virtual int rowCount(const QModelIndex &parent) const;
    virtual QVariant data(const QModelIndex &index, int role) const;
};

#endif // JOBSMODEL_H
