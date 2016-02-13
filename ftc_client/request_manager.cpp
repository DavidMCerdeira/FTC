#include "request_manager.h"
#define MAXNR_OF_REQ 5

Request_Manager::Request_Manager()
{
    /* Structures to syncronize the pending request access */
    if(sem_init(&(this->sem_pendingReq), 0, 0) != 0)
        return;
    pthread_mutex_init(&mux_pendingReq, NULL);

    /* Structures to syncronize the pending responses list access */
    if(sem_init(&sem_pendingResp, 0, 0) != 0){
        syslog(LOG_ERR, "Request_Manager::Request_Manager: Init Semaphores for the respective responses");
        err(1, "couldn't open semaphore");
    }

    pthread_mutex_init(&mux_pendingResp, NULL);

    int i = 0;
    requests.emplace(requests.end(), "search");
    i++;
    requests.emplace(requests.end(), "getBasicInfo");
    i++;
    requests.emplace(requests.end(), "getMessages");
    i++;
    requests.emplace(requests.end(), "clockUser");
    i++;

    //requests.emplace(requests.end(), "getBasInfo");
    //i++;
    NUMBER_OF_REQUESTS = i;

    sem_redirectResp = new sem_t [NUMBER_OF_REQUESTS];
    mux_redirectResp = new pthread_mutex_t [NUMBER_OF_REQUESTS];
    respectiveData =  new list<Json::Value> [NUMBER_OF_REQUESTS];

    for(int i = 0; i < NUMBER_OF_REQUESTS; i++)
    {
        if((sem_init(&sem_redirectResp[i], 0, 0) == -1) || (pthread_mutex_init(&mux_redirectResp[i], NULL) == -1))
        {
            syslog(LOG_ERR, "Request_Manager::Request_Manager: initializing respective responses structures");
            err(1, "Couldn't init semaphore");
            pthread_exit(0);
        }
    }

    if(pthread_create(&(this->thread_resp_redirect), 0, resp_redirect, static_cast<void*>(this)) != 0)
    {
        syslog(LOG_ERR, "Request_Manager::Request_Manager: creating threads to interpret requests");
        err(1, "Couldn't create thread");
        pthread_exit(0);
    }

    pthread_detach(this->thread_resp_redirect);
}

Request_Manager::~Request_Manager()
{
    /* Clean all the resources */
    pthread_cancel(this->thread_resp_redirect);
    this->pendingReq.erase(this->pendingReq.begin(), this->pendingReq.end());
    this->pendingResp.erase(this->pendingResp.begin(), this->pendingResp.end());

    delete [] sem_redirectResp;
    delete [] mux_redirectResp;
}

/*Tranlates the request into a function Manager*/
void* Request_Manager::resp_redirect(void *arg)
{
    FTC_Frame *cur_response_frame;
    Request_Manager *own = static_cast<Request_Manager*>(arg);
    string respHeader, request;

    while(1)
    {
        /* Preparing frame for the specific request */
        cur_response_frame = new FTC_Frame(own->get_response());

        respHeader = cur_response_frame->get_frameSpecific();

        request = respHeader.substr(0, respHeader.find_first_of('_', 0));

        own->addRespectiveResponse(request, cur_response_frame->get_frameData());
        break;

        delete cur_response_frame;
    }

    return NULL;
}

Json::Value Request_Manager::getUserInfo(int id)
{
    Json::Value reqData;
    Json::StyledWriter writerData;
    string requestData_str;

    /* Data structure for this specific request */
    reqData["worker_id"] = id;

    /*convert it to string*/
    requestData_str = writerData.write(reqData);

    /* Preparing frame */
    FTC_Frame requestFrame("getBasicInfo", requestData_str);
    add_request(requestFrame.get_fullFrame());

    return getRespectiveResponseData("getBasicInfo");
}

Json::Value Request_Manager::getUserMessages(int id)
{
    Json::Value reqData;
    Json::StyledWriter writerData;
    string requestData_str;

    /* Data structure for this specific request */
    reqData["worker_id"] = id;

    /*convert it to string*/
    requestData_str = writerData.write(reqData);

    /* Preparing frame */
    FTC_Frame request("getMessages", requestData_str);
    add_request(request.get_fullFrame());

    return this->getRespectiveResponseData("getMessages");
}

Json::Value Request_Manager::getSearchResults(string name, string department, int job)
{
    Json::Value reqData;
    Json::StyledWriter writer;
    string str;

    if(name != "\0")
    {
        reqData["name"] = name;
    }

    if(department != "Any")
    {
        reqData["department_id"] = department;
    }

    if(job != 0)
    {
        reqData["job_id"] = job;
    }

    cout << "reqData: " << reqData << endl;

    str = writer.write(reqData);

    FTC_Frame request("search", str);

    cout << "Full frame: " << request.get_fullFrame() << endl;

    add_request(request.get_fullFrame());

    return this->getRespectiveResponseData("search");
}

Json::Value Request_Manager::clockUser(int id)
{
    Json::Value reqData;
    Json::StyledWriter writerData;
    string requestData_str;

    /* Data structure for this specific request */
    reqData["worker_id"] = id;

    /*convert it to string*/
    requestData_str = writerData.write(reqData);

    /* Preparing frame */
    FTC_Frame request("clock", requestData_str);

    add_request(request.get_fullFrame());

    return this->getRespectiveResponseData("clock");

}

void Request_Manager::add_request(const string new_rq)
{
    pthread_mutex_lock(&mux_pendingReq);

    /* Add to request buffer */
    pendingReq.push_back(new_rq);
    if(sem_post(&(sem_pendingReq)) < 0){
        err(1, "Couldn't post semaphore");
    }

    pthread_mutex_unlock(&mux_pendingReq);
}

string Request_Manager::get_request()
{
    string nextReq;

    sem_wait(&(sem_pendingReq));
    pthread_mutex_lock(&(mux_pendingReq));

    nextReq = *(pendingReq.begin());
    (pendingReq.pop_front());

    pthread_mutex_unlock(&(mux_pendingReq));
    return nextReq;
}

void Request_Manager::add_response(const string m_resp)
{
    pthread_mutex_lock(&mux_pendingResp);

    pendingResp.push_back(m_resp);
    sem_post(&(sem_pendingResp));

    pthread_mutex_unlock(&mux_pendingResp);
}

string Request_Manager::get_response()
{
    string retResp;

    sem_wait(&sem_pendingResp);
    pthread_mutex_lock(&mux_pendingResp);

    retResp = *(this->pendingResp.begin());
    (this->pendingResp.pop_front());

    pthread_mutex_unlock(&mux_pendingResp);

    return retResp;
}

Json::Value Request_Manager::getRespectiveResponseData(string idx)
{
    Json::Value ret;
    int i;

    for(i = 0; i < NR_OF_REQUESTS; i++)
    {
        if(requests[i] == idx)
            break;
    }

    if(i == NR_OF_REQUESTS)
    {
        syslog(LOG_ERR, "Request_Manager::getRespectiveResponseData: not a request");
        warnx("Request_Manager::getRespectiveResponseData: not a request");
        ret["nothing"] = 0;
        return ret;
    }

    sem_wait(&sem_redirectResp[i]);
    pthread_mutex_lock(&mux_redirectResp[i]);

    ret = *(this->respectiveData[i].begin());
    (this->respectiveData[i].pop_front());

    pthread_mutex_unlock(&mux_redirectResp[i]);
    return ret;
}

void Request_Manager::addRespectiveResponse(string idx, string data)
{
    Json::Value converted;
    Json::Reader rString;
    int i;

    for(i = 0; i < NR_OF_REQUESTS; i++)
    {
        if(requests[i] == idx)
            break;
    }

    if (i == NR_OF_REQUESTS)
    {
        syslog(LOG_ERR, "Request_Manager::addRespectiveResponse: not a request");
        warnx("Request_Manager::addRespectiveResponse: not a request");
        return;
    }

    if(!rString.parse(data, converted, false))
        return;

    pthread_mutex_lock(&mux_redirectResp[i]);

    respectiveData[i].push_back(converted);
    sem_post(&sem_redirectResp[i]);

    pthread_mutex_unlock(&mux_redirectResp[i]);
}
