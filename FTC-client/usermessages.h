#ifndef USERMESSAGES_H
#define USERMESSAGES_H

#include <QAbstractListModel>
#include "controller.h"
#include <QList>
#include <QString>
#include <QDebug>

class UserMessages : public QAbstractListModel
{
    Q_OBJECT
private:
    Controller *controller;
    QList<QString> *m_data;
    static void* getMessages_thread(void *arg);

public:
    explicit UserMessages(QObject *parent = 0);
    // QAbstractItemModel interface
    virtual int rowCount(const QModelIndex &parent) const;
    virtual QVariant data(const QModelIndex &index, int role) const;
};

#endif // USERMESSAGES_H
