#ifndef REQUEST_MANAGER_H
#define REQUEST_MANAGER_H

#include <pthread.h>
#include <list>
#include <semaphore.h>
#include <string>
#include <cstring>
#include <iostream>
#include <json/json.h>
#include <syslog.h>
#include <err.h>

#include "ftc_frame.h"

#define NR_OF_REQUESTS 4

using namespace std;

class Request_Manager
{
public:
    Request_Manager();
    ~Request_Manager();

    void add_request(const string new_req);
    void add_response(const string resp);
    string get_request();

    Json::Value getRespectiveResponseData(string idx);

    Json::Value getUserInfo(int id);
    Json::Value getUserMessages(int id);
    Json::Value getSearchResults(string name, string department, int job);
    Json::Value clockUser(int id);

    Json::Value getDepartments();
    Json::Value getJobs();
    /*string  get_strOfRespList();*/

private:
    /*List of all request Managers*/
    pthread_t thread_resp_redirect;
    static void* resp_redirect(void *arg);

    string get_response();

    sem_t sem_pendingReq;
    pthread_mutex_t mux_pendingReq;
    list<string> pendingReq;

    sem_t sem_pendingResp;
    pthread_mutex_t mux_pendingResp;
    list<string> pendingResp;

    sem_t *sem_redirectResp;
    pthread_mutex_t* mux_redirectResp;
    list<Json::Value> *respectiveData;
    vector<string> requests;

    void addRespectiveResponse(string idx, string data);
    int NUMBER_OF_REQUESTS;
};

#endif // REQUEST_Manager_H

