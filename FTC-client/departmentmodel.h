#ifndef DEPARTMENTMODEL_H
#define DEPARTMENTMODEL_H

#include <QObject>
#include <QStringListModel>


class DepartmentModel: public QStringListModel
{
    Q_OBJECT
private:
    static QList<QString> m_departments;
    virtual int rowCount(const QModelIndex &parent) const;
public:
    explicit DepartmentModel(QObject *parent = 0);
//    virtual int rowCount(const QModelIndex &parent) const;
//    virtual QVariant data(const QModelIndex &index, int role) const;
    virtual QHash<int, QByteArray> roleNames(){
      QHash<int, QByteArray> temp;
      temp.insert(Qt::UserRole + 1, QByteArray("text"));
      return temp;
    }

    static void setDepartments(QStringList list);
};

#endif // DEPARTMENTMODEL_H
