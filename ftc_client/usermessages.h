#ifndef USERMESSAGES_H
#define USERMESSAGES_H

#include <QAbstractListModel>
#include <QList>
#include <QString>
#include <QDebug>
#include "controller.h"


class UserMessagesModel : public QAbstractListModel
{
    Q_OBJECT
private:
    QStringList m_data;
    pthread_mutex_t mutex;

public:
    explicit UserMessagesModel(QObject *parent = 0);
    ~UserMessagesModel();
    // QAbstractItemModel interface
    virtual int rowCount(const QModelIndex &parent) const;
    virtual QVariant data(const QModelIndex &index, int role) const;

    void lock();
    void unlock();

signals:
    void insertData(QString str);
    void insertData(QStringList strs);
    void clearData();

private slots:
    void insertNewData(QString str);
    void insertNewData(QStringList str);
    void clearAllData();
};

#endif // USERMESSAGES_H
