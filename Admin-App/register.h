#ifndef REGISTER_H
#define REGISTER_H

#include <QDate>
#include <QImage>
#include <QList>
#include <QString>

class Register
{
    QList<QImage> m_faceList;
    QString m_name;
    QString m_contactNumber;
    QDate m_birth;
    QString m_email;
    int m_departIdx;
    int m_jobsIdx;
    int m_permissionsIdx;
public:
    Register();

    void setName(QString name);
    void setContactNumber(QString contactNumber);
    void setBirth(const QDate &birth);
    void setEmail(QString mail);
    void setDepartIdx(int departIdx);
    void setJobsIdx(int jobsIdx);
    void setPermissionsIdx(int permissionsIdx);
    void addFace(QImage face);

    void commitUser();
};

#endif // REGISTER_H
