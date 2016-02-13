#include "servercon.h"

ServerCon::ServerCon()
    : port(_PORT_NUMBER), BUFFER_SIZE(_BUFFER_SIZE)
{
    //openConnection();
    pthread_attr_t attr;
    pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_DETACHED);
    pthread_attr_init(&attr);

    /* Creating threads to send and receive data from/to server */
    if(pthread_create(&send_thread, &attr, receiveFromServer, static_cast<void*>(this)) != 0)
        syslog(LOG_ERR, "ServerCon: error creating thread receive");

    if(pthread_create(&receive_thread, &attr, sendToServer, static_cast<void*>(this)) != 0)
        syslog(LOG_ERR, "ServerCon: error creating thread send");

   /* Mutex and semphores initialization */
    if(pthread_mutex_init(&reqMux, NULL) != 0 || sem_init(&reqSem, 0, 0) != 0)
       syslog(LOG_ERR,"ServerCon: Error sem or mux Request list error!\n");

    for(int i = 0; i < NR_OF_REQUESTS; i++)
    {
        if(pthread_mutex_init(&req_respectiveMux[i], NULL) || sem_init(&req_respectiveSem[i], 0, 0))
            syslog(LOG_ERR, "ServerCon: Error sem or mux protecting response: %d", i);
    }
}

ServerCon::~ServerCon()
{
    close(sockfd);
}

void ServerCon::openConnection()
{
    /* create TCP socket */
    sockfd = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if(sockfd < 0)
    {
        cout << "ERROR Opening Socket" << endl;
        exit(1);
    }

    /* get host address */
    server = gethostbyname(_IP_ADDR);
    if(server == NULL)
    {
        cout << "ERROR Host not found" << endl;
        exit(1);
    }

    memset(&serv_addr, 0, sizeof(serv_addr));       /* create & zero struct */
    serv_addr.sin_family = AF_INET;                 /* select internet protocol */
    serv_addr.sin_port = htons(port);               /* set the port # */
    serv_addr.sin_addr.s_addr = *((long*)(server->h_addr_list[0]));  /* set the addr */

    if( ::connect(sockfd, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0)
    {
        syslog(LOG_ERR, "ERROR Connecting to server");
        exit(1);
    }
}

void ServerCon::write(char* buffer)
{
    if(strlen(buffer) > BUFFER_SIZE)
    {
        return;
    }
    else
    {
        int n = send(sockfd, buffer, strlen(buffer), 0);
        if (n < 0)
        {
            syslog(LOG_ERR,"ServerCon::Write: ERROR writing to socket");
            return;
        }
    }
}

void* ServerCon::sendToServer(void* arg)
{
    ServerCon* own = static_cast<ServerCon*> arg;
    string request;
    while(1)
    {
        request = own->getFrom_reqList();
        write(request.c_str());
    }
    pthread_exit(0);
}

void* ServerCon::receiveFromServer(void *arg)
{
    int status;
    char *buffer;

    ServerCon* own = static_cast<ServerCon*> arg;
    while(1)
    {
        /* Waiting for responses */
        status = recv(own->sockfd, buffer, _BUFFER_SIZE, 0)\;
        if(status > 0)
        {
            responseForwarding(new string(buffer));
        }
    }
    pthread_exit(0);
}
void addTo_reqList(string req)
{
    if(pthread_mutex_lock(&muxRequest) != 0)
       syslog(LOG_ERR,"ServerCon::addTo_reqList");

}

Json::Value ServerCon::getUserInfo(int id)
{
    UserBasicInfo* basic = new UserBasicInfo;
    basic->m_nId = id;
    basic->m_permission = Permissions::PRIVILEDGED;
    basic->m_strName = std::string("Rita Gay");
    return new UserInfo(basic, false);
}

Json::Value ServerCon::getUserLoginInfo(int id)
{
    UserInfo* usr = getUserInfo(id);

    UserPersonalInfo* personal = new UserPersonalInfo;
    personal->messages.push_back("lol");
    personal->messages.push_back("lol");
    personal->messages.push_back("lol");
    personal->messages.push_back("lol");
    personal->messages.push_back("lol");
    personal->messages.push_back("lol");

    if(!usr->setPersonalData(personal))
    {
        err(1, "Error setting user messages");
    }
    return usr;
}

Json::Value ServerCon::getDepartments()
{
    vector<string> temp;
    /*ask server*/
    temp.push_back("Any");
    temp.push_back("Mecaninca");
    temp.push_back("Electronica");
    temp.push_back("Materiais");
    temp.push_back("Arquitectura");
    return temp;
}

Json::Value ServerCon::getJobs()
{
    vector<string> temp;
    /*ask server*/

    temp.push_back("Any");
    temp.push_back("rececionista");
    temp.push_back("investigador");
    temp.push_back("limpador");
    temp.push_back("arrumador");
    return temp;
}

Json::Value ServerCon::getSearchResult(string name, int department, int job)
{
    Json::Value reqData;
    Json::StyledWriter writer;
    if(name != "\0")
    {
        reqData["name"] = name;
    }

    if(department != "Any")
    {
       reqData["department_id"] = department;
    }
    if(job != 0)
    {
        reqData["job_id"] = job ;
    }

    FTC_Frame request("search", writer.write(&reqData));

    write(request.get_fullFrame().c_str());
}


////void ServerCon::sayHello()
////{
////    const int buffSize = 255;
////    char buffer[buffSize] = "Hello server!";

////    int n = send(sockfd, buffer, strlen(buffer),0 );
////    if (n < 0){
////        cout << "ERROR writing to socket" << endl;
////        return;
////    }

////    memset(buffer, 0, buffSize);

////    recv(sockfd, buffer, buffSize, 0);
////    if (n < 0){
////        cout << "ERROR reading from socket" << endl;
////        return;
////    }

////    cout << buffer << endl;
////}
