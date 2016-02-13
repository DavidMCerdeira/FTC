#include "server_connection.h"
#include <errno.h>

#define TIMEOUTINTERVAL 60.00

Server_Connection::Server_Connection(): BUFFER_SIZE(_BUFFER_SIZE)
{
    pthread_attr_t tAttr;

    if(!this->openConnection())
     {
        syslog(LOG_ERR, "Server_Connection::Server_Connection: Not connecting\n");
        pthread_exit(0);
     }
    /* Connection Main thread creation */
    conState = true;

    /* To make the next Threads Detachable */
    pthread_attr_setdetachstate(&tAttr, PTHREAD_CREATE_DETACHED);
    pthread_attr_init(&tAttr);

    clReqManager =  new Request_Manager();

    if(pthread_create(&this->thread_connection_receive, &tAttr, &connection_receive, static_cast<void*>(this)) != 0)
        syslog(LOG_ERR, "Server_Connection: Error creating thread_connection_receive");

    if(pthread_create(&this->thread_connection_send, &tAttr, &connection_send,static_cast<void*>(this)) != 0)
        syslog(LOG_ERR, "Server_Connection: Error creating thread_connection_send");

    pthread_mutex_init(&this->write_mutex, NULL);

    if(pthread_create(&this->thread_check_connection_state, &tAttr, &check_connection_state,static_cast<void*>(this)) != 0)
        syslog(LOG_ERR, "Server_Connection: Error creating thread_check_connection_state");

    /* var initialization for the timeout evaluation */
    time(&last_communication_time);
}

Server_Connection::~Server_Connection()
{    
    /* Clean up all the threads */
    pthread_cancel(this->thread_connection_receive);
    pthread_cancel(this->thread_connection_receive);
    pthread_cancel(this->thread_connection_send);
    
    close(this->sockfd);
    
    delete clReqManager;
}

bool Server_Connection::openConnection(){
        /* create TCP socket */
        int errn;

        /* get host address */
        server = gethostbyname(_IP_ADDR);

        if(server == NULL)
        {
            syslog(LOG_ERR, "Server_Connectio::open_connection: Host not found");
            return false;
        }

        sockfd = socket(PF_INET, SOCK_STREAM, 0);

        if(sockfd < 0)
        {
            syslog(LOG_ERR, "Server_Connection::openConnection: create socket");
            return false;
        }

        memset(&serv_addr, 0, sizeof(serv_addr));       /* create & zero struct */
        serv_addr.sin_family = AF_INET;                 /* select internet protocol */
        serv_addr.sin_port = port;               /* set the port # */
        serv_addr.sin_addr.s_addr = *((long*)(server->h_addr_list[0]));  /* set the addr */

        if( ::connect(sockfd, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0)
        {
            errn = errno;
            syslog(LOG_ERR, "Server_Connection::open_connection: ERROR Connecting to server");
            return false;
        }
}

Request_Manager* Server_Connection::getRequestManager(){
    return clReqManager;
}

void* Server_Connection::connection_receive(void *arg)
{
    Server_Connection *own = reinterpret_cast<Server_Connection*>(arg);
    int status;

    /*While connection active*/
    while(own->conState == true)
    {
        status = recv(own->sockfd, &own->reqBuffer[0],  MAX_LINE_BUFF, 0);

        if(status > 0)
        {
            /*Call request Manager*/
            own->clReqManager->add_response(own->reqBuffer);
            
            /* Save time of current communication */
            time(&(own->last_communication_time));
        }
    }

    pthread_exit(0);
}

void* Server_Connection::connection_send(void *arg)
{
    Server_Connection *own = reinterpret_cast<Server_Connection*>(arg);
    string send_content;

    while(1)
    {
        /* Waiting for the response to send */
        send_content = own->clReqManager->get_request();

        if(!own->c_send(send_content))
            syslog(LOG_ERR,"Server_Connection::connection_send: error c_send");
    }
    pthread_exit(0);
}

void* Server_Connection::check_connection_state(void *arg)
{
    Server_Connection *own = static_cast<Server_Connection*>(arg);
    double sleepTime = TIMEOUTINTERVAL, curInterval;
    time_t wakeupTime;
    sigval sig_par;

    while(1)
    {
        /* Sleep until is time to check connections state */
        sleep(static_cast<int>(sleepTime));

        /*Get the time since last communication established with the client*/
        time(&wakeupTime);
        curInterval = difftime(wakeupTime, (own->last_communication_time));

        if(curInterval >= TIMEOUTINTERVAL)
        {           
            /* Ask the Write function to write and test the communication */
            if(own->c_send("FTC/TestConnection") > 0)
                sleepTime =TIMEOUTINTERVAL;
            else
            {
                /* Notify server object that it has to remove this object */
                sig_par.sival_int = own->sockfd;
                sigqueue(getpid(), SIG_CON_CLOSED, sig_par);
            }
        }
        else
        {
            /* Set the Interval to guarantee determinism */
            sleepTime = curInterval;
        }
    }

    pthread_exit(0);
}

bool Server_Connection::c_send(string buff)
{
    /* Guarantees that no one is trying to write at the same time */
    pthread_mutex_lock(&write_mutex);                  

    if(send(this->sockfd, buff.c_str(), sizeof(buff), MSG_NOSIGNAL) == -1)
       return false;

    pthread_mutex_unlock(&write_mutex);

    return true;
}

int Server_Connection::get_clientSock()
{
    return this->sockfd;
}

