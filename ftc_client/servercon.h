#ifndef SERVER_CONNECTION_H
#define SERVER_CONNECTION_H

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
#include <syslog.h>
#include <cstdlib>
#include "request_manager.h"
#include <err.h>

#define MAX_LINE_BUFF 1024 //bytes
#define SIG_CON_CLOSED (SIGRTMIN + 1)

#define _PORT_NUMBER 8888
#define _IP_ADDR "192.168.2.110"
#define _BUFFER_SIZE 1024

using namespace std;

class ServerCon
{
    int cur_numConnections;

public:
    ServerCon();
    ~ServerCon();

    int get_clientSock();
    bool openConnection();
    /*debug purposes*/
     void print_sock();

    Request_Manager* getRequestManager();

private:
    /* Guarantees the reception of data */
    pthread_t thread_connection_receive;
    static void* connection_receive(void *arg);

    /* Guarantees the connections verification  */
    pthread_t thread_check_connection_state;
    static void* check_connection_state(void*arg);

    /* Guarantees that the data is sent */
    pthread_t thread_connection_send;
    static void* connection_send(void* arg);
    pthread_mutex_t write_mutex; // Protects  Write Function
    bool c_send(string buff);

    /* Clean up Manager */
    static void connection_ended(void* arg);

    /* Receive buffer */
    char reqBuffer[MAX_LINE_BUFF];
    char respBuffer[MAX_LINE_BUFF];

    Request_Manager *clReqManager;

    bool conState; // Connection state. If true is alive
    int sockfd;    // Socket ID

    struct sockaddr_in serv_addr;
    struct hostent *server;
    const unsigned int BUFFER_SIZE;
    int port;

    time_t last_communication_time; // Saves the time of last communication
};

#endif // Server_CONNECTION_H
