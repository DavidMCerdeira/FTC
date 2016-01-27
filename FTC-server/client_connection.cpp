#include "client_connection.h"

#define TIMEOUTINTERVAL 2.00

Client_Connection::Client_Connection(int _clSock) : clSock(_clSock)
{
    pthread_attr_t tAttr;

    /* Connection Main thread creation */
    conState = true;

    /* To make the next Threads Detachable */
    pthread_attr_setdetachstate(&tAttr, PTHREAD_CREATE_DETACHED);
    pthread_attr_init(&tAttr);

    clReqHandler =  new Request_Handler();

    if(pthread_create(&this->thread_connection_receive, &tAttr, &connection_receive, static_cast<void*>(this)) != 0)
        //throw ERROR_THCLIENT_CONNECTION
        ;

    if(pthread_create(&this->thread_connection_send, &tAttr, &connection_send,static_cast<void*>(this)) != 0)
    ;

    pthread_mutex_init(&this->write_mutex, NULL);

    if(pthread_create(&this->thread_check_connection_state, &tAttr, &check_connection_state,static_cast<void*>(this)) != 0)
        //throw //Don't Forget to set the error
        ;

    /* timeout evaluation var initialization */
    time(&last_communication_time);
}

Client_Connection::~Client_Connection()
{
    cout << "Cleaning client socket: " << this->clSock << endl;
    pthread_cancel(this->thread_connection_receive);
    pthread_cancel(this->thread_connection_receive);
    pthread_cancel(this->thread_connection_send);
    close(this->clSock);
    delete clReqHandler;
}

void* Client_Connection::connection_receive(void *arg)
{
    Client_Connection *own = reinterpret_cast<Client_Connection*>(arg);
    int status;

    /*Prepare Clean Up handler*/
    //pthread_cleanup_push(connection_ended,static_cast<void*>(own));

    /*While connection active*/
    while(own->conState == true)
    {
        status = recv(own->clSock, &own->reqBuffer[0],  MAX_LINE_BUFF, 0);

        if(status > 0)
        {
            /*Call request handler*/
            own->clReqHandler->add_request(own->reqBuffer);
            time(&(own->last_communication_time));
        }
    }

    pthread_exit(0);
    //pthread_cleanup_pop(1);
}

void* Client_Connection::connection_send(void *arg)
{
    Client_Connection *own = reinterpret_cast<Client_Connection*>(arg);
    string send_content;

    while(1)
    {
        send_content = own->clReqHandler->get_response();

        if(!own->w_send(send_content))
        //Connection Problems
        ;
    }
    pthread_exit(0);
}

void* Client_Connection::check_connection_state(void *arg){
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
            if(own->w_send("FTC/TestConnection") > 0)
                sleepTime =TIMEOUTINTERVAL;
            else
            {
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

bool Client_Connection::w_send(string buff)
{
    pthread_mutex_lock(&write_mutex);                  

    if(send(this->clSock, buff.c_str(), sizeof(buff), MSG_NOSIGNAL) == -1)
       return false;

    pthread_mutex_unlock(&write_mutex);

    return true;
}

//void Client_Connection::connection_ended(void*arg)
//{
//   Client_Connection *own = static_cast<Client_Connection*>(arg);

//   close(own->clSock);
//   //implement destroy clReqHandler
//}

int Client_Connection::get_clientSock()
{
    return this->clSock;
}

//void Client_Connection::print_sock(){
//    cout<<"Client_Socket: "<< this->clSock << endl;
//}*/
