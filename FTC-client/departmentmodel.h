#ifndef DEPARTMENTMODEL_H
#define DEPARTMENTMODEL_H

#include <QObject>
#include <QStringList>
#include <controller.h>

class departmentModel: public QStringList
{
    Controller *controller;

public:
    Q_INVOKABLE void updateList();
    departmentModel();

};

#endif // DEPARTMENTMODEL_H
