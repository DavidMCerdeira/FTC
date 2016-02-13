#include "mysemaphore.h"

MyBinarySemaphore::MyBinarySemaphore(const char* name)
    : m_strName(name)
{
    semaph = sem_open(m_strName, O_CREAT, 0600, 0);
    if(semaph == nullptr){
        unlink();
        err(1, "Error opening semaphore:%s ",
                    m_strName);
    }

    if(sem_init(semaph, 0, 0) < 0){
        unlink();
        err(1, "Error initializing semaphore:%s ",
                    m_strName);
    }
}

MyBinarySemaphore::~MyBinarySemaphore()
{
    int ret;

    ret = sem_close(semaph);
    if(ret < 0){
        unlink();
        errx(1, "Error closing semaphore:%s\n", m_strName);
    }

    ret = sem_unlink(m_strName);
    if(ret < 0){
        unlink();
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
            unlink();
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
            unlink();
            err(1, "Error setting semaphore:%s\n",
                        m_strName);
        }
        return;
    }
    else if(val == 0){
        return;
    }
}

void MyBinarySemaphore::wait()
{
    if(sem_wait(semaph) < 0){
        unlink();
        err(1, "Error setting semaphore:%s\n",
                    m_strName);
    }
    return;
}

int MyBinarySemaphore::getValue()
{
    int value;
    sem_getvalue(semaph, &value);
    if(value > 1){
        unlink();
        errx(1, "Semaphore synchronization lost on:%s\n"
                "Unexpected value(%d)...\n",
              m_strName, value);
    }
    return value;
}

void MyBinarySemaphore::unlink()
{
    if(sem_unlink(m_strName) < 0){
        err(1, "Coulnd't unlink semaphore: %s after error",
                    m_strName);
    }
}
