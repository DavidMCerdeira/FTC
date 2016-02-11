#include "servercon.h"

ServerCon::ServerCon()
    : port(_PORT_NUMBER), BUFFER_SIZE(_BUFFER_SIZE)
{
    //openConnection();
}

ServerCon::~ServerCon()
{
    close(sockfd);
}

void ServerCon::openConnection()
{
    /* create TCP socket */
    sockfd = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if(sockfd < 0){
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
    serv_addr.sin_family = AF_INET;        /* select internet protocol */
    serv_addr.sin_port = htons(port);                       /* set the port # */
    serv_addr.sin_addr.s_addr = *((long*)(server->h_addr_list[0]));  /* set the addr */

    if( ::connect(sockfd, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0){
        cout << "ERROR Connecting to server" << endl;
        exit(1);
    }

    cout << "Connected to Server!" << endl;
}

void ServerCon::sayHello()
{
    const int buffSize = 255;
    char buffer[buffSize] = "Hello server!";

    int n = send(sockfd, buffer, strlen(buffer),0 );
    if (n < 0){
        cout << "ERROR writing to socket" << endl;
        return;
    }

    memset(buffer, 0, buffSize);

    recv(sockfd, buffer, buffSize, 0);
    if (n < 0){
        cout << "ERROR reading from socket" << endl;
        return;
    }

    cout << buffer << endl;
}

void ServerCon::write(char* buffer)
{
    if(strlen(buffer) > BUFFER_SIZE)
    {

        return;
    }
    else{
        int n = send(sockfd, buffer, strlen(buffer),0 );
        if (n < 0){
            cout << "ERROR writing to socket" << endl;
            return;
        }
    }
}

UserInfo* ServerCon::getUserInfo(int id)
{
    UserBasicInfo* basic = new UserBasicInfo;
    basic->m_nId = id;
    basic->m_permission = Permissions::PRIVILEDGED;
    basic->m_strName = std::string("Rita Gay");

    return new UserInfo(basic, false);
}

UserInfo* ServerCon::getUserLoginInfo(int id)
{
    UserInfo* usr = getUserInfo(id);

    UserPersonalInfo* personal = new UserPersonalInfo;
    personal->messages.push_back("lol");
    personal->messages.push_back("lol");
    personal->messages.push_back("lol");
    personal->messages.push_back("lol");
    personal->messages.push_back("lol");
    personal->messages.push_back("lol");

    if(!usr->setPersonalData(personal)){
        err(1, "Error setting user messages");
    }

    return usr;
}


vector<string> ServerCon::getDepartments()
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

vector<string> ServerCon::getJobs()
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

list<string> ServerCon::getSearchResult(string name, string department, string job)
{
    if(!name.compare("\0")){
        name = "*";
    }
    if(!department.compare("Any")){
        department = "*";
    }
    if(!job.compare("Any")){
        job = "*";
    }
    /* ask server */

    list<string> temp;
    for(int i = 0; i < 10; i++){
        temp.push_back(name + " " + department + " " + job);
    }
    return temp;
}

std::list<Clock> getClockHistory(int id)
{
    std::list<Clock> clocks;
    for(int i = 0; i < 10; i++){
        clocks.push_front(Clock());
    }

    return clocks;
}
