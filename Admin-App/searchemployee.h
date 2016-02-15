#ifndef SEARCHEMPLOYEE_H
#define SEARCHEMPLOYEE_H

#include <QString>

class SearchEmployee
{
    QString m_name;
    int m_departIdx;
    int m_jobsIdx;
    int m_permissions;

public:
    explicit SearchEmployee();

    void setName(const QString &name);
    void setDepartIdx(int departIdx);
    void setJobsIdx(int jobsIdx);
    void setPermissions(int permissions);
    void commit();
};

#endif // SEARCHEMPLOYEE_H
