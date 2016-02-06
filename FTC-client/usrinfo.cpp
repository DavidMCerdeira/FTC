#include "usrinfo.h"

using namespace std;

UserInfo::UserInfo(const UserBasicInfo* const basic, bool clockedIn,
                   const UserPersonalInfo* const personal)
    :m_basicInfo(basic), m_bClockedIn(clockedIn), m_personalInfo(personal)
{

}

std::string UserInfo::getName()
{
    return m_basicInfo->m_strName;
}

Permissions UserInfo::getPermission()
{
    return m_basicInfo->m_permission;
}

std::list<string> UserInfo::getMessages()
{
    return m_personalInfo->messages;
}

bool UserInfo::isClockedIn()
{
    return m_bClockedIn;
}

bool UserInfo::clockUser()
{
    return m_bClockedIn = !m_bClockedIn;
}
