#ifndef HANDLER_FACTORY_H
#define HANDLER_FACTORY_H

#include "request_handler.h"
#include "ftc_frame.h"
#include <err.h>


class Handler_Factory
{
public:
    Handler_Factory();
    Request_Handler* which_handler(FTC_Frame* frame);
};

#endif // HANDLER_FACTORY_H
