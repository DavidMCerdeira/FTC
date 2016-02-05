#include "mysemaphore.h"

MyBinarySemaphore::MyBinarySemaphore(const char* name)
    : m_strName(name)
{
    semaph = sem_open(m_strName, O_CREAT);
    if(sem_init(semaph, 0, 0) < 0){
        err(1, "Error initializing semaphore:%s\n",
                    m_strName);
    }
}

MyBinarySemaphore::~MyBinarySemaphore()
{
    int ret;

    ret = sem_close(semaph);
    if(ret < 0){
        errx(1, "Error closing semaphore:%s\n", m_strName);
    }

    ret = sem_unlink(m_strName);
    if(ret < 0){
        errx(1, "Error unlinking semaphore:%s\n", m_strName);
    }
}

void MyBinarySemaphore::set()
{
    int val = getValue();

    if(val == 1){
        return;
    }
    else if(val == 0){
        if(sem_post(semaph) < 0){
            errx(1, "Error setting semaphore:%s\n",
                        m_strName);
        }
        return;
    }
}

void MyBinarySemaphore::reset()
{
    int val = getValue();
    if(val == 1){
        if(sem_wait(semaph) < 0){
            err(1, "Error setting semaphore:%s\n",
                        m_strName);
        }
        return;
    }
    else if(val == 0){
        return;
    }
}

int MyBinarySemaphore::getValue()
{
    int value;
    sem_getvalue(semaph, &value);
    if(value > 1){
        errx(1, "Semaphore synchronization lost on:%s\n"
                "Unexpected value(%d)...\n",
              m_strName, value);
    }
    return value;
}
