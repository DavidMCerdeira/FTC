#include "db_accesser.h"

DB_Accesser* DB_Accesser::_instance = NULL;

DB_Accesser* DB_Accesser::instance(){
    if(DB_Accesser::_instance == NULL){
        DB_Accesser::_instance = new DB_Accesser();
    }
    return DB_Accesser::_instance;
}

DB_Accesser::DB_Accesser(string i_db_name,
                         string i_db_host,
                         string i_user_name,
                         string i_password,
                         int i_db_port
                         ):
db_name(i_db_name), db_host(i_db_host), db_user_name(i_user_name), db_user_password(i_password) ,db_port(i_db_port)
{
    my_bool bool_ = 1;
    mysql_init(&(this->cur_DB));
  //  mysql_autocommit(&(this->cur_DB), bool_);

    pthread_mutex_init(&this->access_mutex,  NULL);

    mysql_real_connect(&this->cur_DB,
                       (this->db_host=="" ? NULL: this->db_host.c_str()),
                       this->db_user_name.c_str(),
                       this->db_user_password.c_str(),
                       this->db_name.c_str(),
                       this->db_port,
                       NULL,
                       0);
}

DB_Accesser::~DB_Accesser(){
    //mysql_drop_db(&this->cur_DB, this->db_name); //mysql_query("Drop db Query instead");
}

MYSQL_RES* DB_Accesser::db_query(string query){
    MYSQL_RES *retResult;

    pthread_mutex_lock(&(this->access_mutex));

    mysql_real_query(&(this->cur_DB), query.c_str(), query.length()); //Don't forget to anallyze the error
    retResult = mysql_use_result(&(this->cur_DB));

    pthread_mutex_unlock(&(this->access_mutex));

    return retResult;
}
