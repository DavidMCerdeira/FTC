#include "request_handler.h"

#define CLOCKED_IN true
#define CLOCKED_OUT false

#include <iostream>

using namespace std;

Request_Handler::Request_Handler(string data)
{
    Json::Reader inReader;
    db = DB_Accesser::instance();
    boolParse = inReader.parse(data, inData, false); //"returns false if not parsed"
}

string Request_Handler::get_result_data()
{
    Json::StyledWriter outWriter;
    string ret = outWriter.write(outData);
    return ret;
}

string Request_Handler::get_reqSpecific()
{
    return this->reqSpecific;
}


bool Search_Request::handler()
{
    /* Initilization of the base query, conditions and the table
     * from which the information will be retrieved */
    string query("SELECT w.name, w.idWorker "), conditions(" WHERE "), tables("FROM Worker w");

    /* Prepare search paramenters, conditions and tables that can be used in the query */
    vector<string> conditionsPoss({"w.name=", " ldw.idWorker=w.idWorker And ldw.idDepartment=", " w.idJob= "}),
                   tablesPoss({"",", List_Department_Worker ldw", ""}),
                   searchParameters({"name", "department", "job"});

    MYSQL_RES* qResult;
    MYSQL_ROW row;
    bool conditionsAdded = false;
    Json::Value workerInfo;

    if(!boolParse) return false;

    for(unsigned int i = 0; i < searchParameters.size(); i++)
    {
        /* Check which parameters were used to make the research */
        if(inData.isMember(searchParameters[i]))
        {
            /* Add "from" table to query */
            tables += tablesPoss[i];

            if(conditionsAdded)
                conditions += " AND";

            if(inData[searchParameters[i]].isString())
                /* Add condition to conditions */
                conditions += conditionsPoss[i] + "\'" + inData[searchParameters[i]].asString()  + "\'";
            else
                conditions += conditionsPoss[i] + inData[searchParameters[i]].asString();

            conditionsAdded = true;
        }
    }

    query += tables + conditions;

    if(db->db_query(query, &qResult))
        return false;

    while((row = mysql_fetch_row(qResult)) != NULL)
    {
        workerInfo["name"] = row[0];
        workerInfo["worker_id"] = atoi(row[1]);

        workerInfo["clock_in"] =
                atoi(Clock_Request::get_lastClock("Clock_In", workerInfo["worker_id"].asInt(), db).c_str());

        workerInfo["clock_out"] =
                atoi(Clock_Request::get_lastClock("Clock_Out", workerInfo["worker_id"].asInt(), db).c_str());

        /* Still working case */
        if(workerInfo["clock_in"] > workerInfo["clock_out"])
            workerInfo["clock_out"] = 0;

        outData["worker_array"].append(workerInfo);
    }

    return true;
}

bool Clock_Request::handler()
{
    string query, table;
    MYSQL_RES* qResult;
    bool clockState;
    int retVal;

    /* Check if Data string parsed with success */
    if(!boolParse)
        return false;

    /* Save the worker's clock state */
    if(!Clock_Request::get_workerClockState(inData["worker_id"].asInt(), db, &clockState))
        return false;

    /* If the request is to clock in the worker */
    if(reqSpecific == "clockIn" && !clockState)
    {
      table = "Clock_In";
    }

    /* If the request is to clock out the worker */
    else if(reqSpecific == "clockOut" && clockState)
    {
      table = "Clock_Out";
    }

    /* If something is not ok */
    else
        return false;

    query = "INSERT INTO " + table +" (idWorker,  dateTime) " +
             "VALUE (" + inData["worker_id"].asString() + ", NOW())";

    retVal = db->db_query(query, &qResult);

    /* Check if query went well and if the commit doesn't have any error */
    if(!retVal || mysql_commit(db->get_MYSQL_db()) != 0)
        return false;

    /* Prepares out data, which is respect */
    outData["worker_id"] = inData["worker_id"];
    outData["clock_state"] = clockState;

    return true;
}

bool Clock_Request::get_workerClockState(int worker_id, DB_Accesser *db, bool *clockedState)
{
    string query, clock[2];
    int queryRet;
    MYSQL_ROW row[2];
    MYSQL_RES **qResult;
    time_t time_clock[2];
    long unsigned int *row_size[2];

    /*
     * index 0 stores the clock in information
     * index 1 stores the clock out information
    */

    clock[0] = "Clock_In";
    clock[1] = "Clock_Out";

    qResult = new MYSQL_RES* [2];

    for(int i = 0; i < 2; i++)
    {
        /* Prepares the query */
        query = "SELECT MAX(UNIX_TIMESTAMP(clk.dateTime)) "
                "FROM " + clock[i] + " clk " +
                "WHERE clk.idWorker=" + to_string(worker_id);

        queryRet = db->db_query(query, &qResult[i]);

        /* Everything went well */
        if(!queryRet)
        {
            row[i] = mysql_fetch_row(qResult[i]);
            row_size[i] = mysql_fetch_lengths(qResult[i]);
        }
        else
        {
            if(i >= 0)
                mysql_free_result(qResult[0]);
            else if(i == 1)
                mysql_free_result(qResult[1]);

            delete qResult;
            return false;
        }
    }

    /* Guarenteeing the state for the first clocks */
    if(*row_size[0] == 0)
        *clockedState = CLOCKED_OUT;
    else
    {
        time_clock[0] = atoi(row[0][0]);
    }

    if((*row_size[0] != 0) && (*row_size[1] == 0))
        *clockedState = CLOCKED_IN;
    else
    {
        time_clock[1] = atoi(row[1][0]);
    }

    /* Other then the first clocks */
    if(time_clock[1] > time_clock[2])
        *clockedState = CLOCKED_IN;
    else if (time_clock[1] < time_clock[2])
        *clockedState = CLOCKED_OUT;

    /* free memory occupied by the results structures */
    mysql_free_result(qResult[0]);
    mysql_free_result(qResult[1]);

    delete qResult;

    return true;
}

string Clock_Request::get_lastClock(string table, int worker_id, DB_Accesser* db)
{
    string query = "SELECT MAX(UNIX_TIMESTAMP(clk.dateTime)) "
                    "FROM " + table + " clk "
                    "WHERE clk.idWorker=" + to_string(worker_id);
    MYSQL_ROW row;
    MYSQL_RES* qResult;
    string retValue;
    unsigned long *size;

    if(!db->db_query(query, &qResult))
    {
        row = mysql_fetch_row(qResult);

        size = mysql_fetch_lengths(qResult);

        /* It case it never have clocked in that table */
        if (*size == 0)
            retValue = "\0";
        else
            retValue = row[0];
    }
    else
    {
        retValue = "\0";
    }

    mysql_free_result(qResult);

    return retValue;
}

bool GetBasicInfo_Request::handler()
{
    MYSQL_RES *qResult;
    MYSQL_ROW row;
    unsigned long *size;
    bool ret;
    string query = "SELECT w.idWorker, w.name, w.idPrivelege "
                   "FROM Worker w WHERE w.idWorker=";

    if(!boolParse)
        return false;

    query += inData["worker_id"].asString();

    if(db->db_query(query, &qResult))
        return false;

    row = mysql_fetch_row(qResult);
    size = mysql_fetch_lengths(qResult);

    /* Result data according with the expected? */
    if(*size != 0 && *(size + 1) != 0 && *(size + 2) != 0)
    {
        outData["worker_id"] = atoi(row[0]);
        outData["name"] = row[1];
        outData["privelege"] = row[2];
        ret = true;
    }
    else
        ret = false;

    mysql_free_result(qResult);

    return ret;
}

bool GetMessages_Request::handler()
{
    MYSQL_RES *qResult = NULL;
    MYSQL_ROW row = NULL;
    Json::Value msgInfo;
    string query = "SELECT lrm.idMessages, m.content, lsm.dateTime, w.name "
                   "FROM Messages m, List_Sent_Messages lsm, List_Rcvd_Messages lrm, Worker w "
                   "WHERE lsm.idMessages=lrm.idMessages "
                   "AND w.idWorker=lsm.idFromWorker "
                   "AND lrm.isRead=0 "
                   "AND lrm.idToWorker=";

    if(!boolParse)
       return false;

   query += inData["worker_id"].asString();

   if(db->db_query(query, &qResult))
    return false;

    outData["msgs_array"] = Json::Value(Json::arrayValue);

    while ((row = mysql_fetch_row(qResult)) != NULL)
    {
       msgInfo["msg_id"] = atoi(row[0]);
       msgInfo["msg_content"] = row[1];
       msgInfo["msg_sent_time"] = atoi(row[2]);
       msgInfo["msg_sender"] = row[3];

       outData["msgs_array"].append(msgInfo);
    }

   mysql_free_result(qResult);

   return true;
}
