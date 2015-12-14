#ifndef SERVER_H
#define SERVER_H

#include <iostream>
#include <pthread.h>
#include <sys/socket.h>
#include <netdb.h>
#include <sys/types.h>

#include "client_connection.h"

#define _LISTENPORT 8888
//#define _MAXLENGTHBUFF

using namespace std;

class Server
{
public:
    Server(int numConnections = 2);

private:
    void  removeClient(int sig, siginfo_t *si, void *ucontext);
    static void* run(void*);

    pthread_t thread_run;

    int servSocket;
    struct sockaddr_in address;
    
    list<Client_Connection> lClients;
    pthread_mutex_t lClients_mutex;
    
    const short numConnections;
    unsigned short countConnections;   

};

#endif // SERVER_H
