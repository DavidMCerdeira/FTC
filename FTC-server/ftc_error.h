//#ifndef FTC_ERROR_H
//#define FTC_ERROR_H

//#include <string>
//#include <syslog.h>
//#include <vector>

//using namespace std;
//***ERROR SOURCES***/

//enum ErrorSet {
//                ERROR_LSOCKET_CREATION = 0,
//                ERROR_BIND_LSOCKET,
//                ERROR_LCLIENT_MUTEX,
//                ERROR_LISTEN,
//                ERROR_THREAD_CREATE,
//                ERROR_RUNSERVER_MUTEX,
//                ERROR_RUNSERVER_UNMUTEX,
//                ERROR_THCLIENT_CONNECTION
//               };

//struct error{
//   int e_ID;
//   string* e_message;
//   error(int ID, string* mess) : e_ID(ID), e_message(mess)
//   {}
//};

//class FTC_Error
//{
//public:
//    FTC_Error();
//    void LogHandler(int eID);
//private:
//   string directory;
//   vector<error> errorsSet;
//};

//#endif // FTC_ERROR_H
#ifndef FTC_ERROR
#define FTC_ERROR

#include <syslog.h>

#define FTC_ERROR_HANDLER(message) syslog(LOG_ERR, "%s\n", message)

/* Server Errors */
#define ERROR_LSOCKET_CREATION()          FTC_ERROR_HANDLER("FTC-Server::Server-Error creating listen socket!")
#define ERROR_LSOCKET_BIND()              FTC_ERROR_HANDLER("FTC-Server::Server-Error binding listen socket!")
#define ERROR_LISTEN()                    FTC_ERROR_HANDLER("FTC-Server::Server-Error listening!")
#define ERROR_LCLIENT_MUTEX()             FTC_ERROR_HANDLER("FTC-Server::Server-Error creating the list of clients mutex!")
#define ERROR_RUNTHREAD_CREATION()        FTC_ERROR_HANDLER("FTC-Server::Server-Error creating run!")
#define ERROR_RUNTHREAD_CLNT_LKMUTEX()    FTC_ERROR_HANDLER("FTC-Server::run-Error locking the list of clients mutex!")
#define ERROR_RUNTHREAD_CLNT_ULKMUTEX()   FTC_ERROR_HANDLER("FTC-Server::run-Error unlocking the list of clients mutex!")
#define ERROR_RMCLTHREAD_CREATION()       FTC_ERROR_HANDLER("FTC-Server::Server-Error creating thread!")
#define ERROR_RMCLTHREAD_CLNT_LKMUTEX()   FTC_ERROR_HANDLER("FTC-Server::remove_client-Error locking the list of clients mutex!")
#define ERROR_RMCLTHREAD_CLNT_ULKMUTEX()  FTC_ERROR_HANDLER("FTC-Server::remove_client-Error unlocking the list of clients mutex!")
#define ERROR_RMCLTHREAD_SIGWAIT()        FTC_ERROR_HANDLER("FTC-Server::remove_client-Error waiting signal!")
#endif
