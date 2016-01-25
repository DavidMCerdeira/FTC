#ifndef CLIENT_CONNECTION_H
#define CLIENT_CONNECTION_H

#include <pthread.h>
#include <iostream>
#include <list>
#include <string>
#include <sys/socket.h>
#include <netdb.h>
#include <sys/types.h>
#include <signal.h>
#include <unistd.h>
#include "request_handler.h"
#include "ftc_error.h"

#define MAX_LINE_BUFF 1024 //bytes
#define SIG_CON_CLOSED (SIGRTMIN + 1)

using namespace std;

class Client_Connection
{
public:
    Client_Connection(int sock);
    ~Client_Connection();
    int get_clientSock();
     /*debug purposes*/
     void print_sock();
private:
    static void* manage_connection(void *arg);
    pthread_t thread_manage_connection;
    static void connection_ended(void* arg);
    char reqBuffer[MAX_LINE_BUFF];
    Request_Handler clReqHandler;
    bool conState;
    int clSock;
};

#endif // CLIENT_CONNECTION_H
