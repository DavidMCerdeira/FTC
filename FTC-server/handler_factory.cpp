#include "handler_factory.h"
#include <iostream>
#include "ftc_requests.h"

Handler_Factory::Handler_Factory()
{

}

Request_Handler* Handler_Factory::which_handler(FTC_Frame *frame)
{
    if(frame->get_frameSpecific() == SEARCH_REQUEST)
    {
        return new Search_Request(frame->get_frameData());
    }
    else if(frame->get_frameSpecific() == GETUSRINFO_REQUEST)
    {
       return new GetBasicInfo_Request(frame->get_frameData());
    }
    else if(frame->get_frameSpecific() == GETMSG_REQUEST)
    {
        return new GetMessages_Request(frame->get_frameData());
    }
    else if(frame->get_frameSpecific() == CLOCKIN_REQUEST)
    {
        return new Clock_Request(frame->get_frameData(), CLOCKIN_REQUEST);
    }
    else if(frame->get_frameSpecific() == CLOCKOUT_REQUEST)
    {
        return new Clock_Request(frame->get_frameData(), CLOCKOUT_REQUEST);
    }
    else if(frame->get_frameSpecific() == GETJOBS_REQUEST)
    {
        return new GetJobs_Request(frame->get_frameData());
    }
    else if(frame->get_frameSpecific() == GETDEP_REQUEST)
    {
        return new GetDepartments_Request(frame->get_frameData());
    }
    else if(frame->get_frameSpecific() == GETHOUR_REQUEST)
    {
        return new GetHour_Request(frame->get_frameData());
    }

    return NULL;
}
