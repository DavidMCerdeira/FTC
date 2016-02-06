#include "usrinfo.h"

using namespace std;

UserInfo::UserInfo()
{
    m_bReady = false;
}

void UserInfo::fillUserInfo(int id)
{
    m_bReady = false;
    m_nId = id;
    if(pthread_create(&fillInfoHanle, NULL, fillUserInfo_thread, this) < 0){
        err(1, "Error creating thread...");
    }
}

void* UserInfo::fillUserInfo_thread(void *arg)
{
    UserInfo* self = static_cast<UserInfo*>(arg);

    self->m_strName = "Fucking lol";
    self->m_permission = Permissions::NON_PRIVELDGED;
    self->m_bClockedIn = false;
    sleep(1);
    self->m_bReady = true;
    pthread_exit(NULL);
}

void UserInfo::waitForInfo()
{
    pthread_join(fillInfoHanle, NULL);
}
