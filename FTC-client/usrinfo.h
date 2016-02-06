#ifndef USRINFO_H
#define USRINFO_H

#include <string>
#include "mysemaphore.h"
#include "servercon.h"

enum Permissions
{
    NON_PRIVELDGED,
    PRIVILEDGED
};

class UserInfo
{
    std::string m_strName;
    Permissions m_permission;
    bool m_bClockedIn;
    int m_nId;
    bool m_bReady;

    pthread_t fillInfoHanle;

public:
    UserInfo();

    std::string getName(){return m_strName;}
    Permissions getPermission(){return m_permission;}
    void fillUserInfo(int id);
    void waitForInfo();

private:
    static void* fillUserInfo_thread(void *arg);
};

#endif // USRINFO_H
