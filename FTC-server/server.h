#ifndef SERVER_H
#define SERVER_H

#include <ftc_error.h>
#include <iostream>
#include <pthread.h>
#include <sys/socket.h>
#include <netdb.h>
#include <sys/types.h>
#include "ftc_error.h"

#include "client_connection.h"

#define _LISTENPORT 8888
#define  DEFAULT_NR_OF_CONS 2
#define SIG_RM_CLIENT (SIGRTMIN + 1)

using namespace std;

class Server
{
public:
    Server(int numConnections = DEFAULT_NR_OF_CONS);
    ~Server();

private:
    pthread_t thread_remClient;
    static void* removeClient(void *arg);
    static void* run(void* arg);
    static void server_closed(void*arg);
    void print_clientsSockets();
    pthread_t thread_run;

    int servSocket;
    struct sockaddr_in address;
    
    list<Client_Connection> lClients;
    pthread_mutex_t lClients_mutex;
    const int max_numConnections;
    int countConnections;
    //FTC_Error serv_handler;
};



#endif // SERVER_H

