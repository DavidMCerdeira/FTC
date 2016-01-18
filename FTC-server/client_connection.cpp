#include "client_connection.h"

#define _DEBUG_

Client_Connection::Client_Connection(int _clSock) : clSock(_clSock)
{
    int result;
    pthread_attr_t tAttr;
#ifdef _DEBUG_
    cout<<"\nClient_Connection::Client_Connection\n"<<endl;
#endif

    conState = true;
    pthread_attr_setdetachstate(&tAttr, PTHREAD_CREATE_DETACHED);
    pthread_attr_init(&tAttr);
    result = pthread_create(&this->thread_manage_connection, &tAttr, &manage_connection, static_cast<void*>(this));
    if(result != 0){
        /*Couldn't create thread*/
        return;
    }
}

void* Client_Connection::manage_connection(void *arg){
    Client_Connection *own = reinterpret_cast<Client_Connection*>(arg);
    int status;
    sigval sig_par;

#ifdef _DEBUG_
    cout<<"Client_Connection::manage_connection"<<endl;
#endif
    /*While connection active*/
    while(own->conState == true){
        status = recv(own->clSock, &own->reqBuffer[0],  MAX_LINE_BUFF, 0);
        if(status < 0){
           /*Connection unactive*/
           own->conState = false;
           /*Inform server that this connection has ended*/
           sig_par.sival_int = own->clSock;
           sigqueue(getpid(), SIG_RM_CLIENT, sig_par);
        }
        else if(status > 0){
           /*Call request handler*/
            //own->clReqHandler.add_strToReqList(own->reqBuffer);
            cout<<"received: "<< own->reqBuffer <<endl;
         }
    }

return NULL;
}

int Client_Connection::get_clientSock(){
    return this->clSock;
}

void Client_Connection::print_sock(){
    cout<<"Client_Socket: "<< this->clSock << endl;
}
