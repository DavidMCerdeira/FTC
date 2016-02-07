#ifndef SEARCHWORKINGMODEL_H
#define SEARCHWORKINGMODEL_H

#include <QObject>
#include <QAbstractListModel>
#include <QDate>
#include <controller.h>
#include <QDebug>

class SearchWorkingModel : public QAbstractListModel
{
    Q_OBJECT
public:
    Q_PROPERTY(QDate date READ getSearchDate WRITE setSearchDate)
    Q_INVOKABLE void search();

private:
    QList<QString> working;
    QDate m_date;

public:
    explicit SearchWorkingModel(QObject *parent = 0);
    virtual int rowCount(const QModelIndex &parent) const;
    virtual QVariant data(const QModelIndex &index, int role) const;

    void setSearchDate(const QDate &newDate){m_date = newDate;}
    QDate getSearchDate(){return m_date;}
    void insertData(QString str);
    void clearData();
};

#endif // SEARCHWORKINGMODEL_H
