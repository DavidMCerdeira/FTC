#ifndef MYSEMAPHORE_H
#define MYSEMAPHORE_H

#include <fcntl.h>      /* Defines O_* constants */
#include <sys/stat.h>   /* Defines mode constants */
#include <semaphore.h>
#include "err.h"


class MyBinarySemaphore
{
    sem_t *semaph;
    const char* m_strName;

    MyBinarySemaphore();

public:
    MyBinarySemaphore(const char *name);
    ~MyBinarySemaphore();

    void set();
    void reset();
    int getValue();
};

#endif // MYSEMAPHORE_H
