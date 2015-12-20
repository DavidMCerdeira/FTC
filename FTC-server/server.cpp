#include "server.h"


#define _DEBUG_

Server::Server(int l_numConnections) : numConnections(l_numConnections)
{
    int result;
    pthread_attr_t tAttr;

    countConnections =  0;

#ifdef _DEBUG_
    cout<<"Server::Server\n"<<endl;
#endif

    /*Create a socket*/
    servSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

    if(!(servSocket > 0)) {
        //perror("FTC Server");
        return;
    }

    address.sin_addr.s_addr = htonl(INADDR_ANY);
    address.sin_port = htons(_LISTENPORT);
    address.sin_family = AF_INET;

    /*Bind the socket to an address*/
    result = bind(servSocket, (struct sockaddr*) &address, sizeof(address));

    if(result != 0){
        //perror("FTC Server");
        return;
    }

    result = listen(servSocket, 5);

    if(result != 0){
        //perror("FTC Server");
        return;
    }

    pthread_mutex_init(&lClients_mutex, NULL);

    /*Creating server thread*/
    pthread_attr_setdetachstate(&tAttr, PTHREAD_CREATE_DETACHED);
    pthread_attr_init(&tAttr);
    result = pthread_create(&thread_run, NULL, run, static_cast<void*>(this));
    if(result != 0){
        /*Couldn't create thread*/
        return;
    }

    pthread_exit(0);
}

void* Server::run(void* arg){

    Server *own = static_cast<Server*>(arg);
    unsigned int n = sizeof(own->address);
    int newSocket;
    Client_Connection* c;

#ifdef _DEBUG_
    cout<<"\nServer::run\n"<<endl;
#endif

    while(1){
        /*Waits for connection*/
        newSocket = accept(own->servSocket, (struct sockaddr*)(&(own->address)), &n);

#ifdef _DEBUG_
        cout<<"newsocket: " << newSocket << endl; //debug
#endif

        if(newSocket != -1){
            /*Detected connection and creation of a connection with the client*/
            c =  new Client_Connection(newSocket);

            pthread_mutex_lock(&own->lClients_mutex);
            (own->lClients).push_front(*c);
            pthread_mutex_unlock(&own->lClients_mutex);

            delete c;
        }
    }

#ifdef _DEBUG_
    cout << "Out of Run function!\n"<< endl;
#endif
    return NULL;
}

 void  Server::removeClient(int sig, siginfo_t *si, void *ucontext){
     list<Client_Connection>::iterator it;

     if(sig == SIG_RM_CLIENT){
#ifdef _DEBUG_
         cout << "Server:removeClient" <<endl;
#endif
        /*Find client through socket*/
        for(it = lClients.begin(); it != lClients.end(); it++)
          if(it->get_clientSock() == si->si_value.sival_int)
              break;
        lClients.erase(it);
     }
 }
