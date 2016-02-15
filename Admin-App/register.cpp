#include "register.h"
#include <QDebug>

Register::Register()
{

}

void Register::setName(QString name)
{
    m_name = name;
}

void Register::setContactNumber(QString contactNumber)
{
    m_contactNumber = contactNumber;
}

void Register::setBirth(const QDate &birth)
{
    m_birth = birth;
}

void Register::setEmail(QString mail)
{
    m_email = mail;
}

void Register::setDepartIdx(int departIdx)
{
    m_departIdx = departIdx;
}

void Register::setJobsIdx(int jobsIdx)
{
    m_jobsIdx = jobsIdx;
}

void Register::setPermissionsIdx(int permissionsIdx)
{
    m_permissionsIdx = permissionsIdx;
}

void Register::addFace(QImage face)
{
    m_faceList.push_back(face);
}

void Register::commitUser()
{
    /*/*/
    qDebug() << m_name << m_contactNumber << m_birth << m_email << m_departIdx << m_jobsIdx << m_permissionsIdx;
}

