#include "request_handler.h"

Request_Handler::Request_Handler(string data)
{
    Json::Reader inReader;
    db = DB_Accesser::instance();
    boolParse = inReader.parse(data, inData, false); //"returns false if not parsed"
}

string Request_Handler::get_result_data(){
    Json::StyledWriter outWriter;
    string ret = outWriter.write(this->outData);
    return ret;
}

string Request_Handler::get_respSpecific()
{
    return this->respProducedSpecific;
}


bool Search_Request::handle(){}

