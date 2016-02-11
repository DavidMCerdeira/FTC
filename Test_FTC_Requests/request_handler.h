#ifndef REQUEST_HANDLER_H
#define REQUEST_HANDLER_H

#include <json/json.h>
#include <db_accesser.h>
#include <ctime>
#include <string>
#include <cstdio>
#include <vector>

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
        this->reqSpecific = "search";
    }
    bool handler();
};

class Clock_Request: public Request_Handler
{
public:
    Clock_Request(string data, string reqSpecific): Request_Handler(data)
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
    GetBasicInfo_Request(string data): Request_Handler(data)
    {
        this->reqSpecific = "getBasicInfo";
    }
    bool handler();
};

class GetMessages_Request: public Request_Handler
{
public:
    GetMessages_Request(string data): Request_Handler(data)
    {
        this->reqSpecific = "getMessages";
    }
    bool handler();
};

#endif // REQUEST_HANDLER_H
