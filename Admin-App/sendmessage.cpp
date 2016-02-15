#include "sendmessage.h"
#include <qdebug.h>

void SendMessage::setId(const QString &value)
{
    id = value;
}

void SendMessage::setBroadcast(bool value)
{
    broadcast = value;
}

void SendMessage::setMsg(const QString &value)
{
    msg = value;
}

void SendMessage::commit()
{
    qDebug() << id << broadcast << msg;
}

SendMessage::SendMessage()
{

}
