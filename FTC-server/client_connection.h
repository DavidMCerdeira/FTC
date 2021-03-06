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
#include <ctime>
#include "request_manager.h"
#include "ftc_error.h"

#define MAX_LINE_BUFF 1024 //bytes
#define SIG_CON_CLOSED (SIGRTMIN + 1)

using namespace std;

class Client_Connection
{    int cur_numConnections;

public:
    Client_Connection(int sock);
    ~Client_Connection();

    int get_clientSock();

    /*debug purposes*/
     void print_sock();

private:
    /* Guarantees the rec1eption of data */
    pthread_t thread_connection_receive;
    static void* connection_receive(void *arg);

    /* Guarantees the connections verification  */
    pthread_t thread_check_connection_state;
    static void* check_connection_state(void*arg);

    /* Guarantees that the data is sent */
    pthread_t thread_connection_send;
    static void* connection_send(void* arg);
    pthread_mutex_t write_mutex;                  // Protects  Write Function
    bool c_send(string buff);

    /* Clean up Manager */
    static void connection_ended(void* arg);

    /* Receive buffer */
    char reqBuffer[MAX_LINE_BUFF];
    char respBuffer[MAX_LINE_BUFF];

    Request_Manager *clReqManager;

    bool conState; // Connection state. If true is alive
    int clSock;    // Socket ID
    time_t last_communication_time; // Saves the time of last communication
};

#endif // CLIENT_CONNECTION_H
