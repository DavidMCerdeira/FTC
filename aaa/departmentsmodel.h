#ifndef DEPARTMENTSMODEL_H
#define DEPARTMENTSMODEL_H

#include <QAbstractListModel>
#include <QList>
#include <QString>
#include <QDebug>
#include "controller.h"

class DepartmentsModel: public QAbstractListModel
{
    Q_OBJECT
private:
    QStringList m_data;
public:
    Q_INVOKABLE void currentItemChanged(int i);
    DepartmentsModel();

    virtual int rowCount(const QModelIndex &parent) const;
    virtual QVariant data(const QModelIndex &index, int role) const;
};

#endif // DEPARTMENTSMODEL_H
