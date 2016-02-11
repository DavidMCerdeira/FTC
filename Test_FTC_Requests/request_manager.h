#ifndef REQUEST_MANAGER_H
#define REQUEST_MANAGER_H

#include <pthread.h>
#include <list>
#include <semaphore.h>
#include <string>
#include <iostream>

#include "ftc_frame.h"
#include "request_handler.h"
#include "handler_factory.h"

using namespace std;

class Request_Manager
{
public:
    Request_Manager();
    ~Request_Manager();
    void add_request(const char *new_req);
    string get_response();
    /*string  get_strOfRespList();*/
private:
    /*List of all request Managers*/
    pthread_t thread_req_interpreter;
    static void* req_interpreter(void *arg);

    void add_response(const string resp);
    string get_request();

    Request_Handler* req_handler;
    Handler_Factory factory;

    sem_t sem_pendingReq;
    pthread_mutex_t mux_pendingReq;
    list<string> pendingReq;

    sem_t sem_pendingResp;
    pthread_mutex_t mux_pendingResp;
    list<string> pendingResp;
};

#endif // REQUEST_Manager_H

