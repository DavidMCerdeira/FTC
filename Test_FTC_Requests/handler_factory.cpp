#include "handler_factory.h"

Handler_Factory::Handler_Factory()
{

}

Request_Handler* Handler_Factory::which_handler(FTC_Frame *frame)
{
    if(frame->get_frameSpecific() == "search")
    {
        return new Search_Request(frame->get_frameData());
    }
    else if(frame->get_frameSpecific() == "getBasicInfo")
    {
        return new GetBasicInfo_Request(frame->get_frameData());
    }
    else if(frame->get_frameSpecific() == "getMessages")
    {

    }
    else if(frame->get_frameSpecific() == "clockIn")
    {
        return new Clock_Request(frame->get_frameData(), "clockIn");
    }
    else if(frame->get_frameSpecific() == "clockOut")
    {
        return new Clock_Request(frame->get_frameData(), "clockOut");
    }
    return NULL;
}
