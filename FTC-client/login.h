#ifndef LOGIN_H
#define LOGIN_H

#include <QAbstractListModel>
#include <QList>
#include <QString>
#include <QDebug>
#include "controller.h"

class LoginModel : public QAbstractListModel
{
    Q_OBJECT

public:
    explicit LoginModel(QObject *parent = 0);
    virtual int rowCount(const QModelIndex &parent) const;
    /* this is function is redundant as we only have one element */
    virtual QVariant data(const QModelIndex &index, int role) const;

    Q_INVOKABLE void logout();
    Q_INVOKABLE void clockUser();

signals:
    void setText(QString str);

private slots:
    void setNewText(QString str);

private:
    QString text;
    void setStrState(QString state);
};

#endif // LOGIN_H
