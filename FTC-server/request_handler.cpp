#include "request_handler.h"

Request_Handler::Request_Handler(string data)
{
    db = DB_Accesser::_instance();

}

string Request_Handle::get_specific(){
    return this->specific;
}
