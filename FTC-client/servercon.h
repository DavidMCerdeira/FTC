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
#include <QObject>
#include <QDateTime>

using namespace std;


#define _PORT_NUMBER 8888
#define _IP_ADDR "192.168.43.219"
#define _BUFFER_SIZE 0xFF

class ServerCon : public QObject
{
    Q_OBJECT

public:
    Q_INVOKABLE void test() const {
        //1 + 2;
    }

private:
    int sockfd;
    const int port;
    struct sockaddr_in serv_addr;
    struct hostent *server;
    const unsigned int BUFFER_SIZE;

    void write(char*);

public:
    ServerCon(QObject *parent = 0);
    ~ServerCon();

    void sayHello();
    void openConnection();
    void clockUser(long unsigned int id);
};

#endif // SERVERCON_H
