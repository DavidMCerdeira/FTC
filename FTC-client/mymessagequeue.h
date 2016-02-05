#ifndef MYMESSAGEQUEUE_H
#define MYMESSAGEQUEUE_H

#include <fcntl.h>      /* Defines O_* constants */
#include <sys/stat.h>   /* Defines mode constants */
#include <mqueue.h>
#include <err.h> /*err()*/
#include <cstring>

class MyMessageQueue
{
    mqd_t messageQ;
    const char* m_strName;
private:
    MyMessageQueue();

public:
    MyMessageQueue(const char *name);
    ~MyMessageQueue();

    void kill();

    void sendMsg(const char* msg);
    int  getMsg(char* buff, int len);

    const char* getName(){return m_strName;}
};

#endif // MYMESSAGEQUEUE_H
