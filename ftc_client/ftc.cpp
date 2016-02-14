#include "ftc.h"

char* FTC_Events::usr_present = const_cast<char*>("USR_PRESENT");
char* FTC_Events::usr_absent  = const_cast<char*>("USR_ABSENT");
char* FTC_Events::usr_valid   = const_cast<char*>("USR_VALID");
char* FTC_Events::usr_unkwon  = const_cast<char*>("USR_UNKWN");
char* FTC_Events::usr_infRdy  = const_cast<char*>("USR_INFRDY");
char* FTC_Events::need_photo  = const_cast<char*>("NEED_PHOTO");


FTC::FTC(ServerCon* serverCon)
    :messageQ(FTC_EVENT_MSGQ_NAME), usrPrsntSemaph(FTC_USR_PRSNC_SEMPH_NAME),
      ds(DIST_SEM), m_serverCon(serverCon), m_userInfo(NULL), imgSem("Image")
{

}

void FTC::run()
{
    int ret = pthread_create(&mainThread_handle,
                             NULL, FTC::main_thread, this);
    if(ret < 0) {
        err(1, "Failed to create ftc's main thread...");
    }
}

FTC::~FTC()
{
    pthread_cancel(mainThread_handle);
}

void FTC::logout()
{
    ds.reset();
    delete m_userInfo;
}

void FTC::handleUserDetected()
{
    /* TODO: Set detached */
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
    int userId;

    self->usrPrsntSemaph.set();
    self->messageQ.sendMsg(FTC_Events::usr_present);
    /* set led to detected color */
    self->led.setColor(RGBLed::USR_DETCD);

    /* turn on screen? */

    //    /* capture face */
    //    self->messageQ.sendMsg(FTC_Events::need_photo);
    //    self->imgSem.wait();
    //     int len = self->face.byteCount();

    /* send face to server for recognition */
    validUsr = true;
    userId = 2;

    /* evaluate result */
    /* send acceptance to controller */
    /* change led to apropriate color */
    if(validUsr) {
        self->led.setColor(RGBLed::USR_VALID);
        self->messageQ.sendMsg(FTC_Events::usr_valid);

        /* fill info now that we know its a valid user */
        if(self->m_userInfo != NULL){
            err(1, "A user logged on, before another could log out");
        }
        Json::Value ret = self->m_serverCon->getRequestManager()->getUserInfo(userId);

        if(ret.isMember("nothing")){
            errx(1, "No data received from user info");
        }

        UserBasicInfo *basic = new UserBasicInfo;
        basic->m_strName = ret["name"].asString();
        basic->m_nId = ret["id"].asInt();
        int priv = ret["priviledge"].asInt();
        basic->m_permission = (priv == 1) ? Permissions::NON_PRIVILEDGED : Permissions::PRIVILEDGED;
        bool clocked = ret["clocked"].asBool();

        UserPersonalInfo *info = new UserPersonalInfo;
        list<string> msgs;
        string msg;

        ret = self->m_serverCon->getRequestManager()->getUserMessages(userId);
//        time_t uTime;
//        struct tm *msgTime;
//        char strtime[30];

        for(Json::Value& msg_it : ret["msgs_array"])
        {
            msg = "By " + msg_it["msg_sender"].asString() + ": ";
            msg += msg_it["msg_content"].asString() + " ";
//            uTime = msg_it["msg_send_time"].asInt();
//            msgTime = gmtime(&uTime);
//            strftime(strtime, 30, "%a %D %R", msgTime);
//            msg += strtime;
            msgs.push_back(msg);
        }
        info->messages = msgs;

        self->m_userInfo = new UserInfo(basic, clocked, info);

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
    led.setColor(RGBLed::USR_LEFT);
    messageQ.sendMsg(FTC_Events::usr_absent);

    /* cancel handle_user_detected thread */
}

void* FTC::main_thread(void *arg)
{
    FTC* self = static_cast<FTC*>(arg);

    while(1) {
        /* wait presence */
        self->ds.wait();
        qDebug() << "User detected";

        /* deal with user presence */
        self->handleUserDetected();

        /* wait absence or explicit logout */

        //self->ds.waitDistanceMoreThan(60, 200);
        sleep(60);
        /* deal with absence */
        self->handleUserLeft();
        while(1){
            sleep(60);
        }
    }
}

UserInfo* FTC::getUserInfo()
{
    return m_userInfo;
}

int FTC::setFace(QImage image)
{
    face = image;
    imgSem.set();
    return 1;
}

