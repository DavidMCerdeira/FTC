#ifndef SEARCHEMPLOYEERESULTMODEL_H
#define SEARCHEMPLOYEERESULTMODEL_H

#include <QObject>
#include <QStringList>
#include <QAbstractListModel>
#include <controller.h>

class SearchEmployeeResultModel: public QAbstractListModel
{
    Q_OBJECT
public:
    Q_PROPERTY(QString employeeName READ employeeName WRITE setEmployeeName)
    Q_INVOKABLE void search(QString department, QString job);
    Q_INVOKABLE void clearResult(){result = QStringList();};

private:
    QStringList result;
    QString employee;
public:
    explicit SearchEmployeeResultModel(QObject *parent = 0);
    // QAbstractItemModel interface
    virtual int rowCount(const QModelIndex &parent) const;
    virtual QVariant data(const QModelIndex &index, int role) const;

    QString employeeName(){return employee;}
    void setEmployeeName(QString name){employee = name;}

signals:
    void insertData(QString str);
    void clearData();

private slots:
    void insertNewData(QString str);
    void clearAllData();

};

#endif // SEARCHEMPLOYEERESULTMODEL_H
