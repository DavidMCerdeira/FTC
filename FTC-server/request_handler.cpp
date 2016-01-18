#include "request_handler.h"
#define MAXNR_OF_REQ 5

#define _DEBUG_

Request_Handler::Request_Handler()
{   // result = pthread_create(&thread_run, NULL, run, static_cast<void*>(this));
    /*Initializes the sem for request handling counter*/
#ifdef _DEBUG_
    cout << "Request_Handler::Request_Handler" <<endl;
#endif
    if(sem_init(&(this->sem_pendingReq), 0, 1) != 0)
        return;

    if(pthread_create(&(this->th_req_interpreter), 0, req_interpreter, static_cast<void*>(this)) != 0)
        return; //*Try catch would be more appropriate
    pthread_detach(this->th_req_interpreter);
}

/*Tranlates the request into a function handler*/
void* Request_Handler::req_interpreter(void *arg){
    string frame, cmd, cmd_data;
    Request_Handler *own = static_cast<Request_Handler*>(arg);
    int begin_indx, last_indx;

    /*wait for requests*/
    sem_wait(&(own->sem_pendingReq));
    frame = *(own->pendingReq.end());
    own->pendingReq.pop_back();

    /*set cmd string*/
    begin_indx = frame.find_first_of('\\') + 1; //gets the index to the first letter of the command
    last_indx = frame.find_first_of('\\', begin_indx) - 1; //gets the index to the last letter of the command
    cmd = frame.substr(begin_indx, (last_indx - begin_indx + 1));

    /*set cmd_data string*/
    begin_indx = frame.find_first_of('\\', last_indx + 2) + 1; //gets the index to the first letter of data
    last_indx = frame.find_first_of('\\', begin_indx) - 1; //gets the index of the last letter of data
    cmd_data = cmd.substr(begin_indx, (last_indx - begin_indx + 1));

    /*According to the cmd call the respective handler*/
    if(cmd == "valid") {
       own->req_valid(cmd_data);
    }
    else if(cmd == "search"){
       own->req_search(cmd_data);
    }
    else if(cmd == "message"){
       own->req_message(cmd_data);
    }
    else if (cmd == "clock"){
       own->req_clock(cmd_data);
    }
    else{
        cout<<"error :: no command available"<<endl;
    }

    return NULL;
}

void Request_Handler::add_strToReqList(const char* new_rq){
    string cmd(new_rq);

    this->pendingReq.push_back(cmd);
    sem_post(&(this->sem_pendingReq));
}

void Request_Handler::req_valid(const string jsData){
#ifdef _DEBUG_
    cout << "Request_Handler::req_valid\n" << "parsed: " << jsData << endl;
#endif
}

void Request_Handler::req_search(const string jsData){
 #ifdef _DEBUG_
    cout << "Request_Handler::req_search\n" << "parsed: " << jsData << endl;
  #endif
}

void Request_Handler::req_message(const string jsData){
#ifdef _DEBUG_
    cout << "Request_Handler::req_message\n" << "parsed: " << jsData << endl;
#endif
}

void Request_Handler::req_clock(const string jsData){
#ifdef _DEBUG_
    cout << "Request_Handler::req_clock\n" << "parsed: " << jsData << endl;
#endif
}
