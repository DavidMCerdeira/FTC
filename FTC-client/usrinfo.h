#ifndef USRINFO_H
#define USRINFO_H

#include <string>
#include <list>
#include "mysemaphore.h"


enum Permissions
{
    NON_PRIVILEDGED,
    PRIVILEDGED
};

struct UserBasicInfo
{
    int m_nId;
    std::string m_strName;
    Permissions m_permission;
};

struct Clock
{
    /* time */

    /* in/out */
};

struct UserPersonalInfo
{
    std::list<std::string> messages;
    std::list<Clock> clockEvents;
};

class UserInfo
{
    const UserBasicInfo* const m_basicInfo;
    bool m_bClockedIn;
    const UserPersonalInfo* const m_personalInfo;

public:
    UserInfo(const UserBasicInfo* const basic, bool clockedIn,
                const UserPersonalInfo* const personal = NULL);

    std::string getName();
    Permissions getPermission();
    std::list<std::string> getMessages();
    bool isClockedIn();
    bool clockUser();

private:
    static void* fillUserInfo_thread(void *arg);
};

#endif // USRINFO_H
