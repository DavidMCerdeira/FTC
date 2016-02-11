#include <iostream>
#include <mysql/mysql.h>
#include "request_manager.h"
#include "ftc_frame.h"

using namespace std;

int main()
{
    string response;
    Request_Manager manager;
    FTC_Frame frame("getBasicInfo","{\"worker_id\": 2}");//, \"department\":1,\"job\":1}");

    mysql_library_init(0, NULL, NULL);

    manager.add_request(frame.get_fullFrame().c_str());

    response = manager.get_response();
    cout << response << endl;

    mysql_library_end();
    return 0;
}
