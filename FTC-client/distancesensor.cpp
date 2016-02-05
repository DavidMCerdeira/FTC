#include "distancesensor.h"

DistanceSensor::DistanceSensor()
{

}

DistanceSensor::~DistanceSensor()
{

}

void DistanceSensor::waitDistanceLessThan(int cm, int timeSteps)
{
    cm = cm+timeSteps;
}

void* DistanceSensor::waitDistanceLessThan_thread(void *arg)
{

}

void DistanceSensor::waitDistanceMoreThan(int cm, int timeSteps)
{
    cm = cm+timeSteps;
}

void* DistanceSensor::waitDistanceMoreThan_thread(void *arg)
{

}

void stopWaiting()
{

}
