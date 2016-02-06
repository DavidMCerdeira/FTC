#include "ftc.h"

char* FTC_Events::usr_present = const_cast<char*>("USR_PRESENT");
char* FTC_Events::usr_absent  = const_cast<char*>("USR_ABSENT");
char* FTC_Events::usr_valid   = const_cast<char*>("USR_VALID");
char* FTC_Events::usr_unkwon  = const_cast<char*>("USR_UNKWN");
char* FTC_Events::usr_infRdy  = const_cast<char*>("USR_INFRDY");


FTC::FTC(ServerCon* serverCon)
    :messageQ(FTC_EVENT_MSGQ_NAME), usrPrsntSemaph(FTC_USR_PRSNC_SEMPH_NAME),
      m_serverCon(serverCon)
{

}

void FTC::run()
{
    int ret = pthread_create(&mainThread_handle,
                             NULL, FTC::main_thread, this);
    if(ret < 0){
        err(1, "Failed to create ftc's main thread...");
    }
}

FTC::~FTC()
{
    pthread_cancel(mainThread_handle);
}

void FTC::explicitLogout()
{

}

void FTC::handleUserDetected()
{
    int ret = pthread_create(&usrDetectedThread_handle,
                             NULL, FTC::handleUserDetected_thread, this);
    if(ret < 0){
        err(1, "Failed to create ftc's main thread...");
    }

    pthread_join(usrDetectedThread_handle, NULL);
}

void* FTC::handleUserDetected_thread(void *arg)
{
    FTC* self = static_cast<FTC*>(arg);
    bool validUsr = false;
    int userId = 0;

    self->usrPrsntSemaph.set();
    self->messageQ.sendMsg(FTC_Events::usr_present);
    /* set led to detected color */
    self->led.setColor(RGBLed::USR_DETCD);

    /* turn on screen? */

    /* capture face */
    //int face = capture.captureStableFace();

    /* send face to server for recognition */
    validUsr = true;
    userId = 1;

    /* evaluate result */
    /* send acceptance to controller */
    /* change led to apropriate color */
    if(validUsr) {
        self->led.setColor(RGBLed::USR_VALID);
        self->messageQ.sendMsg(FTC_Events::usr_valid);

        /* fill info now that we know its a valid user */
        self->m_userInfo.fillUserInfo(userId);
        self->m_userInfo.waitForInfo();
        self->messageQ.sendMsg(FTC_Events::usr_infRdy);

    }
    else {
        self->messageQ.sendMsg(FTC_Events::usr_unkwon);
        self->led.setColor(RGBLed::USR_UNKWN);
    }

    pthread_exit(nullptr);
}

void FTC::handleUserLeft()
{
    usrPrsntSemaph.reset();
    messageQ.sendMsg(FTC_Events::usr_absent);

    /* cancel handle_user_detected thread */
}

void* FTC::main_thread(void *arg)
{
    FTC* self = static_cast<FTC*>(arg);

    while(1) {
        /* wait presence */
        self->ds.waitDistanceLessThan(50, 200);

        /* deal with user presence */
        self->handleUserDetected();

        /* wait absence or explicit logout */
        sleep(4);
        self->ds.waitDistanceMoreThan(60, 200);

        /* deal with absence */
        self->handleUserLeft();
        while(1){
            sleep(60);
        }
    }
}

std::string FTC::getUserName()
{
    return m_userInfo.getName();
}
