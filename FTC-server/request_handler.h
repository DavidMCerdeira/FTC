#ifndef REQUEST_HANDLER_H
#define REQUEST_HANDLER_H

#include <json/json.h>
#include <db_accesser.h>
#include <ctime>
#include <string>
#include <cstdio>
#include <vector>

#include "ftc_requests.h"

class Request_Handler
{
public:
    Request_Handler(string data);
    string get_result_data();
    string get_reqSpecific();
    virtual bool handler() = 0;
protected:
    string reqSpecific;
    Json::Value inData;
    Json::Value outData;
    DB_Accesser *db;
    bool boolParse;
};

class Search_Request: public Request_Handler
{
public:
    Search_Request(string data)
    : Request_Handler(data)
    {
        this->reqSpecific = SEARCH_REQUEST;
    }
    bool handler();
};

class Clock_Request: public Request_Handler
{
public:
    Clock_Request(string data, string reqSpecific)
    : Request_Handler(data)
    {
        this->reqSpecific = reqSpecific;
    }
    bool handler();
    static bool get_workerClockState(int worker_id, DB_Accesser *db, bool *clockedState);
    static string get_lastClock(string table, int worker_id, DB_Accesser* db);
};

class GetBasicInfo_Request: public Request_Handler
{
public:
    GetBasicInfo_Request(string data)
    : Request_Handler(data)
    {
        this->reqSpecific = GETUSRINFO_REQUEST;
    }
    bool handler();
};

class GetMessages_Request: public Request_Handler
{
public:
    GetMessages_Request(string data)
    : Request_Handler(data)
    {
        this->reqSpecific = GETMSG_REQUEST;
    }
    bool handler();
};

class GetDepartments_Request: public Request_Handler
{
public:
    GetDepartments_Request(string data)
    : Request_Handler(data)
    {
        this->reqSpecific = GETDEP_REQUEST;
    }
    bool handler();
};

class GetJobs_Request: public Request_Handler
{
public:
    GetJobs_Request(string data)
    : Request_Handler(data)
    {
        this->reqSpecific = GETDEP_REQUEST;
    }

    bool handler();
};

class GetHour_Request: public Request_Handler
{
public:
    GetHour_Request(string data)
    : Request_Handler(data)
    {
        this->reqSpecific = GETHOUR_REQUEST;
    }

    bool handler();
};

#endif // REQUEST_HANDLER_H
