#include "request_manager.h"
#define MAXNR_OF_REQ 5

Request_Manager::Request_Manager()
{
    /* Structures to syncronize the pending request access */
    if(sem_init(&(this->sem_pendingReq), 0, 0) != 0)
    {
        syslog(LOG_ERR, "Request::Request_Manager: semaphore init");
        pthread_exit(0);
    }

    pthread_mutex_init(&mux_pendingReq, NULL);

    /* Structures to syncronize the pending responses list access */
    if(sem_init(&sem_pendingResp, 0, 0) != 0)
        syslog(LOG_ERR, "Request::Request_Manager: semaphore init");

    pthread_mutex_init(&mux_pendingResp, NULL);

    if(pthread_create(&(this->thread_req_interpreter), 0, req_interpreter, static_cast<void*>(this)) != 0)
        pthread_exit(0);

    pthread_detach(this->thread_req_interpreter);
}

Request_Manager::~Request_Manager()
{
    pthread_cancel(this->thread_req_interpreter);
    this->pendingReq.erase(this->pendingReq.begin(), this->pendingReq.end());
    this->pendingResp.erase(this->pendingResp.begin(), this->pendingResp.end());
}

/*Tranlates the request into a function Manager*/
void* Request_Manager::req_interpreter(void *arg)
{
    FTC_Frame *cur_request_frame, *cur_response_frame;
    Request_Manager *own = static_cast<Request_Manager*>(arg);

    while(1)
    {
        /*wait for requests*/
        cur_request_frame = new FTC_Frame(own->get_request());

        /* identifie which request was received */
        own->req_handler = own->factory.which_handler(cur_request_frame);

        if(own->req_handler != NULL)
        {
            cout << cur_request_frame->get_fullFrame();

            /* handle the specific request */
            if(own->req_handler->handler())
                cur_response_frame = new FTC_Frame(own->req_handler->get_reqSpecific(), own->req_handler->get_result_data());
            else
                cur_response_frame = new FTC_Frame(own->req_handler->get_reqSpecific(), "{\"nothing\":0}");

            warnx(cur_response_frame->get_fullFrame().c_str());

            /* Store the response to the send thread */
            own->add_response(cur_response_frame->get_fullFrame());
            delete cur_response_frame;

            delete cur_request_frame;
        }
    }
    return NULL;
}

void Request_Manager::add_request(const char* new_rq)
{
    string cmd(new_rq);

    cout << "add Request:" << cmd << endl;

    pthread_mutex_lock(&mux_pendingReq);

    /* Add to request buffer */
    pendingReq.push_back(cmd);
    sem_post(&(sem_pendingReq));

    pthread_mutex_unlock(&mux_pendingReq);
}

string Request_Manager::get_request()
{
   string nextReq;

    cout << "Get Request " << endl;

    sem_wait(&(sem_pendingReq));
    pthread_mutex_lock(&(mux_pendingReq));

    nextReq = *(pendingReq.begin());
    (pendingReq.pop_front());

    pthread_mutex_unlock(&(mux_pendingReq));

    cout << "Get request finish!" << endl;
    return nextReq;
}

void Request_Manager::add_response(const string m_resp)
{
    pthread_mutex_lock(&mux_pendingResp);

    this->pendingResp.push_back(m_resp);
    sem_post(&(this->sem_pendingResp));

    pthread_mutex_unlock(&mux_pendingResp);
}

string Request_Manager::get_response()
{
    string retResp("");

    sem_wait(&sem_pendingResp);
    pthread_mutex_lock(&mux_pendingResp);

    retResp = *(pendingResp.begin());
    (pendingResp.pop_front());

    pthread_mutex_unlock(&mux_pendingResp);

    return retResp;
}
