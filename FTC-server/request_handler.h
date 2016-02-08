#ifndef REQUEST_HANDLER_H
#define REQUEST_HANDLER_H

#include <json/json.h>
#include <db_accesser.h>

class Request_Handler
{
public:
    Request_Handler(string data);
    string get_specific();
    string get_result_data();
    virtual bool handle();

protected:
    string request;
    //const string specific;

    JSON::value inData;
    JSON::value outData;
    JSON::reader inReader;
    JSON::writer outWriter;

    DB_Accesser *db;
};

class Search_Request: public Request_Handler
{
public:
    Search_Request(string data);
    bool handle();
}

#endif // REQUEST_HANDLER_H
