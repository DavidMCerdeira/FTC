#include "servercon.h"
#include <errno.h>

#define TIMEOUTINTERVAL 60.00

ServerCon::ServerCon(): BUFFER_SIZE(_BUFFER_SIZE), port(_PORT_NUMBER)
{
    pthread_attr_t tAttr;

    if(!this->openConnection())
    {
        syslog(LOG_ERR, "Server_Connection::Server_Connection: Not connecting\n");
        err(1, "Couldn't connect");
        pthread_exit(0);
    }
    /* Connection Main thread creation */
    conState = true;

    /* To make the next Threads Detachable */
    pthread_attr_setdetachstate(&tAttr, PTHREAD_CREATE_DETACHED);
    pthread_attr_init(&tAttr);

    clReqManager =  new Request_Manager();

    if(pthread_create(&this->thread_connection_receive, &tAttr, &connection_receive, static_cast<void*>(this)) != 0){
        syslog(LOG_ERR, "Server_Connection: Error creating thread_connection_receive");
        err(1, "Couldn't create pthread");
    }

    if(pthread_create(&this->thread_connection_send, &tAttr, &connection_send,static_cast<void*>(this)) != 0){
        syslog(LOG_ERR, "Server_Connection: Error creating thread_connection_send");
         err(1, "Couldn't create pthread");
    }

    pthread_mutex_init(&this->write_mutex, NULL);

    if(pthread_create(&this->thread_check_connection_state, &tAttr, &check_connection_state,static_cast<void*>(this)) != 0){
        syslog(LOG_ERR, "Server_Connection: Error creating thread_check_connection_state");
         err(1, "Couldn't create pthread");
    }

    /* var initialization for the timeout evaluation */
    time(&last_communication_time);
}

ServerCon::~ServerCon()
{
    /* Clean up all the threads */
    pthread_cancel(this->thread_connection_receive);
    pthread_cancel(this->thread_connection_receive);
    pthread_cancel(this->thread_connection_send);

    close(this->sockfd);

    delete clReqManager;
}

bool ServerCon::openConnection(){
    /* create TCP socket */

    /* get host address */
    server = gethostbyname(_IP_ADDR);

    if(server == NULL)
    {
        syslog(LOG_ERR, "Server_Connectio::open_connection: Host not found");
        return false;
    }

    sockfd = socket(AF_INET, SOCK_STREAM, 0);

    if(sockfd < 0)
    {
        syslog(LOG_ERR, "Server_Connection::openConnection: create socket");
        return false;
    }

    memset(&serv_addr, 0, sizeof(serv_addr));       /* create & zero struct */
    serv_addr.sin_family = AF_INET;                 /* select internet protocol */
    serv_addr.sin_port = htons(port);               /* set the port # */
    serv_addr.sin_addr.s_addr = *((long*)(server->h_addr_list[0]));  /* set the addr */

    if( ::connect(sockfd, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0)
    {
        err(1, "Couldn't connect");
        syslog(LOG_ERR, "Server_Connection::open_connection: ERROR Connecting to server");
        return false;
    }
    return true;
}

Request_Manager* ServerCon::getRequestManager(){
    return clReqManager;
}

void* ServerCon::connection_receive(void *arg)
{
    ServerCon *own = reinterpret_cast<ServerCon*>(arg);
    int status;

    /*While connection active*/
    while(own->conState == true)
    {
        status = recv(own->sockfd, &own->reqBuffer[0],  MAX_LINE_BUFF, 0);
        cout << "Rcvd: " << own->reqBuffer << endl;
        if(status > 0)
        {
            /*Call request Manager*/
            own->clReqManager->add_response(own->reqBuffer);

            /* Save time of current communication */
            time(&(own->last_communication_time));
        }
        memset(own->reqBuffer, 0, MAX_LINE_BUFF);
    }

    pthread_exit(0);
}

void* ServerCon::connection_send(void *arg)
{
    ServerCon *own = reinterpret_cast<ServerCon*>(arg);
    string send_content;

    while(1)
    {
        /* Waiting for the response to send */
        send_content = own->clReqManager->get_request();
        if(!own->c_send(send_content)){
            syslog(LOG_ERR,"Server_Connection::connection_send: error c_send");
            err(1, "Couldn't send content");
        }
    }
    pthread_exit(0);
}

void* ServerCon::check_connection_state(void *arg)
{
    ServerCon *own = static_cast<ServerCon*>(arg);
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

bool ServerCon::c_send(string buff)
{
    bool ret;
    /* Guarantees that no one is trying to write at the same time */
    pthread_mutex_lock(&write_mutex);
    cout << "Sending: " << buff.c_str() << endl;
    if(send(this->sockfd, buff.c_str(), buff.length(), MSG_NOSIGNAL) == -1){
        err(1, "Coulnd't send");
        ret = false;
    }
    else{
        ret = true;
    }

    pthread_mutex_unlock(&write_mutex);

    return ret;
}

int ServerCon::get_clientSock()
{
    return sockfd;
}

