#ifndef SEARCHEMPLOYEERESULTMODEL_H
#define SEARCHEMPLOYEERESULTMODEL_H

#include <QObject>
#include <QStringList>
#include <QAbstractListModel>
#include <controller.h>

class searchEmployeeResultModel: public QAbstractListModel
{
    Q_OBJECT
private:
    QStringList result;
public:
    explicit searchEmployeeResultModel(QObject *parent = 0);
    // QAbstractItemModel interface
    virtual int rowCount(const QModelIndex &parent) const;
    virtual QVariant data(const QModelIndex &index, int role) const;

    void insertData(QString str);
    void clearData();
};

#endif // SEARCHEMPLOYEERESULTMODEL_H
