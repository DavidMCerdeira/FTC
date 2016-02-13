#ifndef SERVERCON_H
#define SERVERCON_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <list>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <iostream>
#include <pthread.h>
#include <vector>
#include <json/json.h>
#include <semaphore.h>
#include "ftc_frame.h"
#include <syslog.h>

#include "usrinfo.h"

using namespace std;

#define _PORT_NUMBER 8888
#define _IP_ADDR "192.168.43.219"
#define _BUFFER_SIZE 0xFF

#define NR_OF_REQUESTS 5

#define SEARCH_IDX 0
#define GETUSERS_IDX 1
#define CLOCK_IDX 2
#define GETMSG_IDX 3
#define GETUSERINFO 4

class ServerCon
{
public:
    ServerCon();
    ~ServerCon();

    //void sayHello();
    void openConnection();

    Json::Value getUserInfo(int id);
    Json::Value clockUser(int id);
    Json::Value getSearchResult(string name, string department, string job);
    Json::Value getUserMessages(int userId);
    Json::Value getDepartments();
    Json::Value getJobs();

private:
    int sockfd;
    const int port;
    struct sockaddr_in serv_addr;
    struct hostent *server;
    
    const unsigned int BUFFER_SIZE;
    void write(char*);
    pthread_t receive_thread;
    pthread_t send_thread;
    
    static void* sendToServer(void* arg);
    static void* receiveFromServer(void*arg);

    void responseForwarding(string* rcvd);
    Json::Value getRespectiveResponse(int index);
    void addTo_reqList(string req);
    string getFrom_reqList;

    list<string> reqList;
    sem_t semRequest;
    pthread_mutex_t muxRequest;

    sem_t req_respectiveSem[NR_OF_REQUESTS];
    pthread_mutex_t req_respectiveMux[NR_OF_REQUESTS];
    Json::Value req_respectiveList[NR_OF_REQUESTS];
};

#endif // SERVERCON_H
