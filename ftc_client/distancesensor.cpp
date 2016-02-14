#include "distancesensor.h"

DistanceSensor::DistanceSensor(QObject *parent)
       : QObject(parent), sem(DIST_SEM)
{
    sem.reset();
}

void DistanceSensor::userDetected()
{
    sem.set();
}

void DistanceSensor::userLeft()
{
    qDebug() << "User lll";
    sem.reset();
}
