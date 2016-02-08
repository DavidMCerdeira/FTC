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
    return NULL;
}
