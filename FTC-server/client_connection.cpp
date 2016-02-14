#include "client_connection.h"
#include <stdio.h>

#define TIMEOUTINTERVAL 60.00

Client_Connection::Client_Connection(int _clSock) : clSock(_clSock)
{
    pthread_attr_t tAttr;

    /* Connection Main thread creation */
    conState = true;

    /* To make the next Threads Detachable */
    pthread_attr_setdetachstate(&tAttr, PTHREAD_CREATE_DETACHED);
    pthread_attr_init(&tAttr);

    clReqManager =  new Request_Manager();

    if(pthread_create(&this->thread_connection_receive, &tAttr, &connection_receive, static_cast<void*>(this)) != 0)
        syslog(LOG_ERR, "Client_Connection: Error creating thread_connection_receive");

    if(pthread_create(&this->thread_connection_send, &tAttr, &connection_send,static_cast<void*>(this)) != 0)
        syslog(LOG_ERR, "Client_Connection: Error creating thread_connection_send");

    pthread_mutex_init(&this->write_mutex, NULL);

    if(pthread_create(&this->thread_check_connection_state, &tAttr, &check_connection_state,static_cast<void*>(this)) != 0)
        syslog(LOG_ERR, "Client_Connection: Error creating thread_check_connection_state");

    /* var initialization for the timeout evaluation */
    time(&last_communication_time);
}

Client_Connection::~Client_Connection()
{    
    /* Clean up all the threads */
    pthread_cancel(thread_connection_receive);
    pthread_cancel(thread_check_connection_state);
    pthread_cancel(thread_connection_send);
    
    close(this->clSock);
    
    delete clReqManager;
}

void* Client_Connection::connection_receive(void *arg)
{
    Client_Connection *own = reinterpret_cast<Client_Connection*>(arg);
    int status;

    /*While connection active*/
    while(own->conState == true)
    {
        status = recv(own->clSock, &own->reqBuffer[0],  MAX_LINE_BUFF, 0);

        if(status > 0)
        {
            string req(own->reqBuffer);
            /*Call request Manager*/
            own->clReqManager->add_request(own->reqBuffer);
            /* Save time of current communication */
            time(&(own->last_communication_time));
        }
    }

    pthread_exit(0);
}

void* Client_Connection::connection_send(void *arg)
{
    Client_Connection *own = reinterpret_cast<Client_Connection*>(arg);
    string send_content;

    while(1)
    {
        /* Waiting for the response to send */
        send_content = own->clReqManager->get_response();

        if(!own->c_send(send_content))
            syslog(LOG_ERR, "Client_Connection::connection_send: error c_send");
    }
    pthread_exit(0);
}

void* Client_Connection::check_connection_state(void *arg)
{
    Client_Connection *own = static_cast<Client_Connection*>(arg);
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
                sig_par.sival_int = own->clSock;
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

bool Client_Connection::c_send(string buff)
{
    bool ret;
    /* Guarantees that no one is trying to write at the same time */
    pthread_mutex_lock(&write_mutex);                  
    cout << "Send Content" << buff << endl;

    if(send(this->clSock, buff.c_str(), buff.length(), MSG_NOSIGNAL) == -1)
    {
       cout << "send went wrong!!\n" << endl;
       ret = false;
    }
    else
    {
        ret = true;
    }


    pthread_mutex_unlock(&write_mutex);
    cout <<"send went ok!" << endl;

    return ret;
}

int Client_Connection::get_clientSock()
{
    return this->clSock;
}

