#ifndef FTC_H
#define FTC_H

#include "mymessagequeue.h"
#include "mysemaphore.h"
#include "rgbled.h"
#include "distancesensor.h"
#include "imgcapturer.h"
#include "servercon.h"

#define FTC_EVENT_MSGQ_NAME      "/ftc_events_msgQ"
#define FTC_USR_PRSNC_SEMPH_NAME "/user_presence_semaph"

struct FTC_Events{
    static char *usr_present;
    static char *usr_absent;
    static char *usr_valid;
    static char *usr_unkwon;
};

class FTC
{
private:
    RGBLed led;
    DistanceSensor ds;
    //ImgCapturer capture;
    //Mat* face;
    ServerCon* serverCon;

    MyMessageQueue messageQ;
    MyBinarySemaphore usrPrsntSemaph;

    pthread_t mainThread_handle;
    pthread_t usrDetectedThread_handle;

public:
    FTC();
    ~FTC();
    void run();
    void explicitLogout();

private:
    void handleUserDetected();
    void handleUserLeft();

    static void* main_thread(void *);
    static void* handleUserDetected_thread(void *);
    static void* handleUserDetected_cleanup(void *);
};

#endif // FTC_H
