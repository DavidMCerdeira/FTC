#ifndef DISTANCESENSOR_H
#define DISTANCESENSOR_H

#include <pthread.h>

struct DistanceSensorParameters{
    int cm;
    int timeSteps;
};

class DistanceSensor
{
private:
    int fd;

public:
    DistanceSensor();
    ~DistanceSensor();

    /*waits for treshold measure*/
    void waitDistanceLessThan(int cm, int timeSteps);
    void waitDistanceMoreThan(int cm, int timeSteps);
    void stopWaiting();

private:
    void* waitDistanceLessThan_thread(void *arg);
    void* waitDistanceMoreThan_thread(void *arg);
};

#endif // DISTANCESENSOR_H
