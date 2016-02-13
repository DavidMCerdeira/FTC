#include "usrinfo.h"

using namespace std;

UserInfo::UserInfo(UserBasicInfo* const basic, bool clockedIn,
                   UserPersonalInfo* const personal)
    :m_basicInfo(basic), m_bClockedIn(clockedIn), m_personalInfo(personal)
{

}

UserInfo::~UserInfo()
{
    delete m_basicInfo;
    delete m_personalInfo;
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
    if(m_personalInfo != NULL){
        return m_personalInfo->messages;
    }
    else{
        return list<string>();
    }
}

bool UserInfo::isClockedIn()
{
    return m_bClockedIn;
}

bool UserInfo::clockUser()
{
    return m_bClockedIn = !m_bClockedIn;
}

bool UserInfo::setPersonalData(UserPersonalInfo *personal)
{
    if(m_personalInfo != NULL){
        return false;
    }
    else {
         m_personalInfo = personal;
         return true;
    }
}

