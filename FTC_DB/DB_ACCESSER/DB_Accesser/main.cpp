#include <iostream>
#include <db_accesser.h>
#include <stdio.h>

using namespace std;

int main(int argc, char *argv[])
{
    DB_Accesser *myDB;
    MYSQL_RES *qResult;
    int nrFields;
    MYSQL_ROW row;

    myDB = DB_Accesser::instance();

    qResult = myDB->db_query("SELECT * FROM Jobs");
    //qResult = mysql_use_result(&FTC_con);

    nrFields = mysql_num_fields(qResult);

    while((row = mysql_fetch_row(qResult)) != NULL)
    {
        for(int i = 0; i < nrFields; i++)
        {
            printf("%s\n", row[i]);
        }
    }

    return 0;
}
