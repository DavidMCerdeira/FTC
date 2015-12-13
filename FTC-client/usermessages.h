#ifndef USERMESSAGES_H
#define USERMESSAGES_H

#include <QObject>

class UserMessages : public QObject
{
    Q_OBJECT
public:
    explicit UserMessages(QObject *parent = 0);

signals:

public slots:
};

#endif // USERMESSAGES_H
