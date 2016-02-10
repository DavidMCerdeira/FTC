#ifndef SERVERCON_H
#define SERVERCON_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <iostream>
#include <pthread.h>

#include "usrinfo.h"

using namespace std;

#define _PORT_NUMBER 8888
#define _IP_ADDR "192.168.43.219"
#define _BUFFER_SIZE 0xFF

class ServerCon
{
private:
    int sockfd;
    const int port;
    struct sockaddr_in serv_addr;
    struct hostent *server;
    const unsigned int BUFFER_SIZE;

    void write(char*);

public:
    ServerCon();
    ~ServerCon();

    void sayHello();
    void openConnection();

    UserInfo* getUserInfo(int id);
    UserInfo* getUserLoginInfo(int id);
    std::list<Clock> getClockHistory(int id);

    void clockUser(long unsigned int id);
    void getUserMessages();
};

#endif // SERVERCON_H
