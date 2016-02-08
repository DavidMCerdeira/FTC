#ifndef DB_ACCESSER_H
#define DB_ACCESSER_H

#include <mysql/mysql.h>
#include <pthread.h>
#include <string>

using namespace std;

#define DEF_DB_USER "root"       //
#define DEF_DB_PASSWORD "123123" //
#define DEF_DB_HOST ""         //local connection
#define DEF_DB_PORT 3307         //stablished port
#define DEF_DB_NAME "FTCdb"      //

class DB_Accesser
{
public:
    static DB_Accesser* instance();
    ~DB_Accesser();

    MYSQL_RES* db_query(string query);

protected:
    DB_Accesser(string i_db_name = DEF_DB_NAME,
                string i_db_host = DEF_DB_HOST,
                string i_user_name = DEF_DB_USER,
                string i_password = DEF_DB_PASSWORD,
                int i_db_port = DEF_DB_PORT);

private:
    static DB_Accesser* _instance;

    MYSQL cur_DB;

    pthread_mutex_t access_mutex;

    string db_name;
    string db_host;
    string db_user_name;
    string db_user_password;
    int db_port;
};

#endif // DB_ACCESSER_H
