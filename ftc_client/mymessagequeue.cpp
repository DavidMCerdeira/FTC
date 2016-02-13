#include "mymessagequeue.h"

MyMessageQueue::MyMessageQueue(const char* name)
    : m_strName(name)
{
    mq_attr at;
    at.mq_maxmsg = 10;
    at.mq_msgsize = 50;
    at.mq_flags = 0;

    /* note: numbers beginnign with 0 are interpretd in octal */
    if((messageQ = mq_open(m_strName, O_CREAT | O_RDWR, 0600, &at)) < 0){
        kill();
        err(1, "Error(%d) Creating message qeue: %s\n",
                    messageQ, m_strName);
    }

    if(mq_getattr(messageQ, &at) < 0){
        kill();
        err(1, "Error reading attributes from message queue: %s",
                m_strName);
    }

    return;
}

MyMessageQueue::~MyMessageQueue()
{
    kill();
}

void MyMessageQueue::sendMsg(const char *msg)
{
    int len = strlen(msg);

    /* send presence to msgQ */
    int ret = mq_send(messageQ, msg, len, 0);
    if(ret < 0){
        kill();
        err(1, "Failure sending message to message queue: %s\n"
               "Here is the message: %s\n",
                        m_strName, msg);
    }
}

int MyMessageQueue::getMsg(char* buff, int len)
{
    unsigned int priority = 0;
    int rcvN = mq_receive(messageQ, buff, len, &priority);
    if(rcvN < 0){
        kill();
        err(1, "Error receiving message on message queue:%s\n",
                    m_strName);
    }

    return rcvN;
}

void MyMessageQueue::kill()
{
    if(messageQ < 0){
        return;
    }
    if(mq_close(messageQ) < 0){
        err(1, "Error closing message queue %s\n",
                    m_strName);
    }

    if(mq_unlink(m_strName)){
        err(1, "Error unlinking message queue %s\n",
                    m_strName);
    }
}
