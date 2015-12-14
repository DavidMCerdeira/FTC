#ifndef REQUEST_HANDLER_H
#define REQUEST_HANDLER_H

#include <pthread.h>
#include <list>
#include <semaphore.h>
#include <string>
#include <iostream>

using namespace std;

class Request_Handler
{
public:
    Request_Handler();
    void add_strToReqList(char *new_req);
private:
    /*List of all request handlers*/
    pthread_t th_req_interpreter;
    static void* req_interpreter(void *arg);

    sem_t *sem_pendingReq;
    list<string> pendingReq;

};

#endif // REQUEST_HANDLER_H
