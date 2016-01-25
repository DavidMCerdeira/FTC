#include "server.h"

Server::Server(int l_numConnections) : numConnections(l_numConnections)
{
    pthread_attr_t tAttr;

    countConnections =  0;

    try{
        servSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
        if(!(servSocket > 0)) {
           throw ERROR_LSOCKET_CREATION;
        }

        address.sin_addr.s_addr = htonl(INADDR_ANY);
        address.sin_port = htons(_LISTENPORT);
        address.sin_family = AF_INET;

        /*Bind the socket to an address*/
       if(bind(servSocket, (struct sockaddr*) &address, sizeof(address)) != 0)
           throw ERROR_BIND_LSOCKET;

        if(listen(servSocket, 5) != 0)
           throw ERROR_LISTEN;

        pthread_attr_init(&tAttr);
        pthread_attr_setdetachstate(&tAttr, PTHREAD_CREATE_DETACHED);

        if(pthread_mutex_init(&lClients_mutex, NULL) != 0)
           throw ERROR_LCLIENT_MUTEX;

        //if(pthread_create(&thread_remClient, &tAttr, removeClient, static_cast<void*>(this)) != 0)
            //throw
        //;

        /*Creating server thread*/
        if(pthread_create(&thread_run, &tAttr, run, static_cast<void*>(this)) != 0)
            throw ERROR_THREAD_CREATE;
    }
    catch(ErrorSet e_ID){
        serv_handler.LogHandler(e_ID);
    }

    pthread_exit(0);
}

void* Server::run(void* arg){

    Server *own = static_cast<Server*>(arg);
    unsigned int n = sizeof(own->address);
    int newSocket;
    Client_Connection* c;
    pthread_cleanup_push(server_closed, own);
    try{
    while(1){
        /*Waits for connection*/
        newSocket = accept(own->servSocket, reinterpret_cast<struct sockaddr*>(&(own->address)), &n);
        if(newSocket != -1){
            /* Detected connection and creation of a connection with the client*/

                c =  new Client_Connection(newSocket);

                if(pthread_mutex_lock(&own->lClients_mutex) != 0)
                    throw ERROR_RUNSERVER_MUTEX;

                (own->lClients).push_front(*c);

                if(pthread_mutex_unlock(&own->lClients_mutex))
                    throw ERROR_RUNSERVER_UNMUTEX;
            }
        }
    }
    catch(int e_ID){
        own->serv_handler.LogHandler(e_ID);
    }
    pthread_cleanup_pop(1);
    pthread_exit(0);
}

/*
void*  Server::removeClient(void *arg){
    list<Client_Connection>::iterator it;
    sigset_t unblocked_sig;
    siginfo_t si;
    Server* own = static_cast<Server*>(arg);
    int sig;

    ///Unblock the Remove signal
    sigemptyset(&unblocked_sig);
    sigaddset(&unblocked_sig, SIG_RM_CLIENT);
    pthread_sigmask(SIG_UNBLOCK, &unblocked_sig, NULL);

    if(sigwaitinfo(&unblocked_sig, &sig,&si) != 0)
        //throw
        ;

    if(pthread_mutex_lock(&own->lClients_mutex) != 0)
        //throw
        ;

    if(sig == SIG_RM_CLIENT){
    //Find client through socket
    for(it = own->lClients.begin(); it != own->lClients.end(); it++)
      if(it->get_clientSock() == si.si_val)
          break;
    lClients.erase(it);

    if(pthread_mutex_unlock(&own->lClients_mutex) != 0)
        //throw
        ;
    }
 }//*/

void Server::server_closed(void*arg){
    Server *own = static_cast<Server*>(arg);
    close(own->servSocket);
}
