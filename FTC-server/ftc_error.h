#ifndef FTC_ERROR_H
#define FTC_ERROR_H

#include <string>
#include <syslog.h>
#include <vector>

using namespace std;
/***ERROR SOURCES***/

enum ErrorSet {
                ERROR_LSOCKET_CREATION = 0,
                ERROR_BIND_LSOCKET,
                ERROR_LCLIENT_MUTEX,
                ERROR_LISTEN,
                ERROR_THREAD_CREATE,
                ERROR_RUNSERVER_MUTEX,
                ERROR_RUNSERVER_UNMUTEX,
                ERROR_THCLIENT_CONNECTION
               };

struct error{
   int e_ID;
   string* e_message;
   error(int ID, string* mess) : e_ID(ID), e_message(mess)
   {}
};

class FTC_Error
{
public:
    FTC_Error();
    void LogHandler(int eID);
private:
   string directory;
   vector<error> errorsSet;
};

#endif // FTC_ERROR_H
