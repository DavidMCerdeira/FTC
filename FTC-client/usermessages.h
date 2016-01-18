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
    QList<QString> m_data;

public:
    explicit UserMessagesModel(QObject *parent = 0);
    // QAbstractItemModel interface
    virtual int rowCount(const QModelIndex &parent) const;
    virtual QVariant data(const QModelIndex &index, int role) const;

    void insertData(QString str);
    void clearData();
};

#endif // USERMESSAGES_H
