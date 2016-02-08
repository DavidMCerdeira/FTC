#ifndef REQUEST_HANDLER_H
#define REQUEST_HANDLER_H

#include <json/json.h>
#include <db_accesser.h>

class Request_Handler
{
public:
    Request_Handler(string data);
    string get_result_data();
    string get_respSpecific();

    virtual bool handle() = 0;

protected:
    string reqSpecific;
    string respProducedSpecific;
    Json::Value inData;
    Json::Value outData;
    DB_Accesser *db;
    bool boolParse;
};

class Search_Request: public Request_Handler
{
public:
    Search_Request(string data): Request_Handler(data){}
    bool handle();
    static string get_identifier();
private:
    static string identifier;
};

#endif // REQUEST_HANDLER_H
