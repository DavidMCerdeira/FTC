#ifndef SEARCHRESULTMODEL_H
#define SEARCHRESULTMODEL_H

#include <QAbstractListModel>
#include <QList>
#include <QString>
#include <QDebug>
#include "controller.h"

class SearchResultModel: public QAbstractListModel
{
    Q_OBJECT
private:
    QStringList m_data;
public:
    explicit SearchResultModel(QObject *parent = 0);
    Q_INVOKABLE void search();
    virtual int rowCount(const QModelIndex &parent) const;
    virtual QVariant data(const QModelIndex &index, int role) const;

signals:
    void insertData(QString str);
    void insertData(QStringList strs);
    void clearData();

private slots:
    void insertNewData(QString str);
    void insertNewData(QStringList str);
    void clearAllData();
};

#endif // SEARCHRESULTMODEL_H
