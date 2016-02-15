#ifndef FTC_H
#define FTC_H

#include "mymessagequeue.h"
#include "mysemaphore.h"
#include "rgbled.h"
#include "distancesensor.h"
#include "imgcapturer.h"
#include "servercon.h"
#include <string.h>
#include <QImage>

#include "usrinfo.h"
#include "mysemaphore.h"
#include <json/json.h>
#include <time.h>

#define FTC_EVENT_MSGQ_NAME      "/ftc_events_msgQ"
#define FTC_USR_PRSNC_SEMPH_NAME "/user_presence_semaph"

struct FTC_Events{
    static char *usr_present;
    static char *usr_absent;
    static char *usr_valid;
    static char *usr_infRdy;
    static char *usr_unkwon;
    static char *need_photo;
};

class FTC
{
private:
    RGBLed led;
    MyMessageQueue messageQ;
    MyBinarySemaphore usrPrsntSemaph;
    MyBinarySemaphore ds;
    ServerCon *m_serverCon;
    UserInfo *m_userInfo;

    pthread_t mainThread_handle;
    pthread_t usrDetectedThread_handle;

    MyBinarySemaphore imgSem;
    QImage face;

public:
    FTC(ServerCon* serverCon);
    ~FTC();
    void run();
    void logout();
    UserInfo* getUserInfo();
    int setFace(QImage image);

private:
    void handleUserDetected();
    void handleUserLeft();
    int faceValidate();

    static void* main_thread(void *);
    static void* handleUserDetected_thread(void *);
    static void* handleUserDetected_cleanup(void *);
};

#endif // FTC_H
