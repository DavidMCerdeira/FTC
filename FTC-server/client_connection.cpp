#include "client_connection.h"


Client_Connection::Client_Connection(int _clSock) : clSock(_clSock)
{
    pthread_attr_t tAttr;
    conState = true;
    pthread_attr_setdetachstate(&tAttr, PTHREAD_CREATE_DETACHED);
    pthread_attr_init(&tAttr);
    if(pthread_create(&this->thread_manage_connection, &tAttr, &manage_connection, static_cast<void*>(this)) != 0)
        throw ERROR_THCLIENT_CONNECTION;      
}

Client_Connection::~Client_Connection()
{
    pthread_cancel(this->thread_manage_connection);
}

void* Client_Connection::manage_connection(void *arg)
{
    Client_Connection *own = reinterpret_cast<Client_Connection*>(arg);
    int status;
    sigval sig_par;

    /*Prepare Clean Up handler*/
    pthread_cleanup_push(Client_Connection::connection_ended,static_cast<void*>(own));
    /*While connection active*/
    while(own->conState == true){
        status = recv(own->clSock, &own->reqBuffer[0],  MAX_LINE_BUFF, 0);
        if(status < 0){
           /*Connection unactive*/
           own->conState = false;
           /*Inform server that this connection is ended*/
           sig_par.sival_int = own->clSock;
           //sigqueue(getpid(), SIG_CON_CLOSED, sig_par);
        }
        else if(status > 0){
           /*Call request handler*/
            own->clReqHandler.add_strToReqList(own->reqBuffer);
            cout<<"received: "<< own->reqBuffer <<endl;

         }
    }
    pthread_exit(0);
}

//int Client_Connection::get_clientSock(){
//    return this->clSock;
//}
//void Client_Connection::print_sock(){
//    cout<<"Client_Socket: "<< this->clSock << endl;
//}*/

void Client_Connection::connection_ended(void*arg){
   Client_Connection *own = static_cast<Client_Connection*>(arg);
   close(own->clSock);
   //implement destroy clReqHandler
   return NULL;
}
