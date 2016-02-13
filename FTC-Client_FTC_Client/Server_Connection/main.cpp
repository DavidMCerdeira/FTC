#include <iostream>
#include <request_manager.h>
#include "request_manager.h"
#include "server_connection.h"
#include <err.h>

using namespace std;

int main(int argc, char *argv[])
{
    //*
    ServerCon con;
    Json::Value ret;
    Request_Manager* myManager = con.getRequestManager();

    //ret = myManager->getSearchResults("david", "esrg", 1);
    ret = myManager->getUserInfo(2);

    cout << ret << endl;
    cout << "All done!" << endl;
/*/
    struct hostent* host;
    struct sockaddr_in addr;
    int sd, port = 8888;
    host = gethostbyname("192.168.2.110");
    sd = socket(AF_INET, SOCK_STREAM, 0);

    if ( sd < 0 ){
        cout << "socket" << endl;
    }

    memset(&addr, 0, sizeof(addr));
    addr.sin_family = AF_INET;
    addr.sin_port = htons(port);
    addr.sin_addr.s_addr = *(long*)(host->h_addr_list[0]);

    if ( connect(sd, (struct sockaddr*)&addr, sizeof(addr)) == 0)
    {
        cout << "Hello World!" << endl;
        return 0;
    }
    err(1, "Coulddn't connect");

    //*/
    return 0;
}
