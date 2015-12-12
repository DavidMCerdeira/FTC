#include "servercon.h"

ServerCon::ServerCon(QObject *parent)
    : port(_PORT_NUMBER), BUFFER_SIZE(_BUFFER_SIZE), QObject(parent)
{
    openConnection();
}

ServerCon::~ServerCon()
{
    close(sockfd);
}


void ServerCon::openConnection()
{
    /* create TCP socket */
    sockfd = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if(sockfd < 0){
        cout << "ERROR Opening Socket" << endl;
        exit(1);
    }

    /* get host address */
    server = gethostbyname(_IP_ADDR);
    if(server == NULL)
    {
        cout << "ERROR Host not found" << endl;
        exit(1);
    }

    memset(&serv_addr, 0, sizeof(serv_addr));       /* create & zero struct */
    serv_addr.sin_family = AF_INET;        /* select internet protocol */
    serv_addr.sin_port = htons(port);                       /* set the port # */
    serv_addr.sin_addr.s_addr = *((long*)(server->h_addr_list[0]));  /* set the addr */

    if( ::connect(sockfd, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0){
        cout << "ERROR Connecting to server" << endl;
        exit(1);
    }

    cout << "Connected to Server!" << endl;
}

void ServerCon::sayHello()
{
    const int buffSize = 255;
    char buffer[buffSize] = "Hello server!";

    int n = send(sockfd, buffer, strlen(buffer),0 );
    if (n < 0){
        cout << "ERROR writing to socket" << endl;
        return;
    }

    memset(buffer, 0, buffSize);

   recv(sockfd, buffer, buffSize, 0);
   if (n < 0){
        cout << "ERROR reading from socket" << endl;
        return;
   }

   cout << buffer << endl;
}

void ServerCon::write(char* buffer)
{
    if(strlen(buffer) > BUFFER_SIZE)
    {
        throw(-1);
        return;
    }
    else{
        int n = send(sockfd, buffer, strlen(buffer),0 );
        if (n < 0){
            cout << "ERROR writing to socket" << endl;
            return;
        }
    }
}

