#include "server.h"

Server::Server(int l_numConnections) : numConnections(l_numConnections)
{
    pthread_attr_t tAttr;

    countConnections =  0;

        servSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

        if(!(servSocket > 0))
            ERROR_LSOCKET_CREATION();

        address.sin_addr.s_addr = htonl(INADDR_ANY);
        address.sin_port = htons(_LISTENPORT);
        address.sin_family = AF_INET;

        /*Bind the socket to an address*/
       if(bind(servSocket, (struct sockaddr*) &address, sizeof(address)) != 0)
       {
           ERROR_LSOCKET_BIND();
           pthread_exit(0);
       }

       if(listen(servSocket, 5) != 0)
       {
           ERROR_LISTEN();
           pthread_exit(0);
       }

        pthread_attr_init(&tAttr);
        pthread_attr_setdetachstate(&tAttr, PTHREAD_CREATE_DETACHED);

        if(pthread_mutex_init(&lClients_mutex, NULL) != 0)
        {
            ERROR_LCLIENT_MUTEX();
            pthread_exit(0);
        }

        if(pthread_create(&thread_remClient, &tAttr, removeClient, static_cast<void*>(this)) != 0)
        {
            ERROR_RMCLTHREAD_CREATION();
            pthread_exit(0);
        }

        /*Creating server thread*/
        if(pthread_create(&thread_run, &tAttr, run, static_cast<void*>(this)) != 0)
        {
            ERROR_RUNTHREAD_CREATION();
            pthread_exit(0);
        }

    pthread_exit(0);
}

void* Server::run(void* arg){

    Server *own = static_cast<Server*>(arg);
    unsigned int n = sizeof(own->address);
    int newSocket;
    Client_Connection* c;

    pthread_cleanup_push(server_closed, own);

        while(1)
        {
            /*Waits for connection*/
            newSocket = accept(own->servSocket, reinterpret_cast<struct sockaddr*>(&(own->address)), &n);

            if(newSocket != -1)
            {
                /* Detected connection and creation of a connection with the client*/
                c =  new Client_Connection(newSocket);

                if(pthread_mutex_lock(&own->lClients_mutex) != 0)
                {
                    ERROR_RUNTHREAD_CLNT_LKMUTEX();
                    pthread_exit(0);
                }
                else
                {
                    (own->lClients).push_front(*c);

                    if(pthread_mutex_unlock(&own->lClients_mutex))
                    {
                        ERROR_RUNTHREAD_CLNT_ULKMUTEX();
                        pthread_exit(0);
                    }
                }
            }
        }

    pthread_cleanup_pop(1);
    pthread_exit(0);
}

void*  Server::removeClient(void *arg)
{
    list<Client_Connection>::iterator it;
    sigset_t unblocked_sig;
    siginfo_t si;
    Server* own = static_cast<Server*>(arg);
    int sig;

    ///Unblock the Remove signal
    sigemptyset(&unblocked_sig);
    sigaddset(&unblocked_sig, SIG_RM_CLIENT);

    while(1)
    {
        if(sigwaitinfo(&unblocked_sig, &si) == -1)
        {
          ERROR_RMCLTHREAD_SIGWAIT();
        }
        else
        {
            //Find client through socket
            if(pthread_mutex_lock(&own->lClients_mutex) != 0)
                ERROR_RMCLTHREAD_CLNT_LKMUTEX();

            for(it = own->lClients.begin(); it != own->lClients.end(); it++)
                if(it->get_clientSock() == static_cast<int>(si.si_value.sival_int))
                    break;
            own->lClients.erase(it);

            if(pthread_mutex_unlock(&own->lClients_mutex) != 0)
                ERROR_RMCLTHREAD_CLNT_ULKMUTEX();
        }
    }
 }

void Server::server_closed(void*arg)
{
    Server *own = static_cast<Server*>(arg);

    close(own->servSocket);

    pthread_cancel(own->thread_remClient);

    own->lClients.erase(lClients.begin(), lClients.end());
}

void Server::print_clientsSockets()
{
    cout << "Clients: " << endl;
    for(list<Client_Connection>::iterator it=this->lClients.begin(); it != this->lClients.end(); it++)
        cout << "cl: " << it->get_clientSock() << endl;
    cout << endl;
}
