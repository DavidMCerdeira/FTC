#ifndef DISTANCESENSOR_H
#define DISTANCESENSOR_H

#include <QObject>
#include <qdebug.h>
#include <mysemaphore.h>

#define DIST_SEM "distance_sensor"

class DistanceSensor : public QObject
{
    Q_OBJECT
    MyBinarySemaphore sem;
public:
    explicit DistanceSensor(QObject *parent = 0);
    Q_INVOKABLE void userDetected();
    Q_INVOKABLE void userLeft();
signals:

public slots:
};

#endif // DISTANCESENSOR_H
