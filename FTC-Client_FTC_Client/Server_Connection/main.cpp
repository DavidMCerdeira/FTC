#include <iostream>
#include <request_manager.h>
#include "request_manager.h"
#include "server_connection.h"

using namespace std;

int main(int argc, char *argv[])
{
    Server_Connection con;
    Request_Manager* myManager = con.getRequestManager();
    Json::Value user;

    struct hostent* host;
    struct sockaddr_in addr;
    int sd, port = 8888;

    user = myManager->getUserInfo(2);

//    host = gethostbyname("127.0.0.1");
//    sd = socket(PF_INET, SOCK_STREAM, 0);        /* create socket */

//    if ( sd < 0 )
//    cout << "socket" << endl;
//    ;

//    memset(&addr, 0, sizeof(addr));       /* create & zero struct */
//    addr.sin_family = AF_INET;        /* select internet protocol */
//    addr.sin_port = htons(port);                       /* set the port # */
//    addr.sin_addr.s_addr = *(long*)(host->h_addr_list[0]);  /* set the addr */

//    /*---If connection successful, send the message and read results---*/
//    if ( connect(sd, (struct sockaddr*)&addr, sizeof(addr)) == 0)
//    {



//        cout << "Hello World!" << endl;
//        return 0;
//    }
    return 0;
}
