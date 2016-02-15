#ifndef SENDMESSAGE_H
#define SENDMESSAGE_H

#include <QString>

class SendMessage
{
    QString id;
    bool broadcast;
    QString msg;
public:
    explicit SendMessage();

    void setId(const QString &value);
    void setBroadcast(bool value);
    void setMsg(const QString &value);

    void commit();
};

#endif // SENDMESSAGE_H
