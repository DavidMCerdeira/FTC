#include "searchemployee.h"
#include <qdebug.h>

void SearchEmployee::setName(const QString &name)
{
    m_name = name;
}

void SearchEmployee::setDepartIdx(int departIdx)
{
    m_departIdx = departIdx;
}

void SearchEmployee::setJobsIdx(int jobsIdx)
{
    m_jobsIdx = jobsIdx;
}

void SearchEmployee::commit()
{
    qDebug() << m_name << m_departIdx << m_jobsIdx << m_permissions << endl;
}

void SearchEmployee::setPermissions(int permissions)
{
    m_permissions = permissions;
}

SearchEmployee::SearchEmployee()
{

}
