//#include "ftc_error.h"

//FTC_Error::FTC_Error()
//{

//    errorsSet.push_back(error(ERROR_LSOCKET_CREATION,new string("#ERROR: CREATING LISTEN SOCKET")));
//    errorsSet.push_back(error(ERROR_BIND_LSOCKET, new string("#ERROR: BINDING LISTEN SOCKET")));
//    errorsSet.push_back(error(ERROR_LISTEN, new string("#ERROR: LISTENING LISTEN SOCKET")));
//    errorsSet.push_back(error(ERROR_THREAD_CREATE, new string("#ERROR: CREATING LISTEN SOCKET")));
//    errorsSet.push_back(error(ERROR_RUNSERVER_MUTEX, new string("#ERROR: RUN SERVER LOCKING MUTEX")));
//    errorsSet.push_back(error(ERROR_RUNSERVER_UNMUTEX, new string("#ERROR: RUN SERVER UNLOCKING MUTEX")));
//    //errorsSet.push_back();
//}

//void FTC_Error::LogHandler(int eID){
//    for(vector<error>::iterator it = errorsSet.begin(); it != errorsSet.end(); it++)
//    {
//        if(it->e_ID == eID)
//        {
//            syslog(LOG_ERR, "%s\n",it->e_message->c_str());
//            break;
//        }
//    }
//}
