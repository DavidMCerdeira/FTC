#ifndef SEARCHWORKINGMODEL_H
#define SEARCHWORKINGMODEL_H

#include <QObject>
#include <QAbstractListModel>
#include <controller.h>

class SearchWorkingModel : public QAbstractListModel
{
    Q_OBJECT
private:
    QList<QString> working;

public:
    explicit SearchWorkingModel(QObject *parent = 0);
    // QAbstractItemModel interface
    virtual int rowCount(const QModelIndex &parent) const;
    virtual QVariant data(const QModelIndex &index, int role) const;

    void insertData(QString str);
    void clearData();
};

#endif // SEARCHWORKINGMODEL_H
