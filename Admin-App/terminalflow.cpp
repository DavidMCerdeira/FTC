#include "terminalflow.h"
#include <QDebug>

TerminalFlow::TerminalFlow(QObject *parent) : QObject(parent), m_table(NULL), m_update(false)
{
    m_header.push_back("Name");
    m_header.push_back("Id");
    m_header.push_back("Clock");
    m_header.push_back("Hours");
}

void TerminalFlow::setTable(QTableWidget *table)
{
    if(m_table == NULL){
        m_table = table;
        createTable();
    }
    else{
        qDebug() << "Table already atributed";
    }
}

void TerminalFlow::setAutoUpdate(bool state)
{
    if(m_update != state){
        m_update = state;
        if(m_update){
            pthread_attr_t attr;
            pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_DETACHED);
            pthread_create(&pollForData_handle, NULL, TerminalFlow::pollForData, this);
        }
    }
}

void TerminalFlow::createTable()
{
    m_table->setColumnCount(m_header.length());
    m_table->setHorizontalHeaderLabels(m_header);
}

void *TerminalFlow::pollForData(void *arg)
{
    TerminalFlow* self = static_cast<TerminalFlow*>(arg);

    while(self->m_update){
        /* wait for server */
        if(true){
            self->checkForData();
            sleep(2);
        }
    }
    return arg;
}

void TerminalFlow::checkForData()
{
    int row = 0;
    int col = 0;
    row = m_table->rowCount();
    m_table->insertRow(row);
    m_table->setItem(row, col++, new QTableWidgetItem("Lol"));
    m_table->setItem(row, col++, new QTableWidgetItem("123"));
    m_table->setItem(row, col++, new QTableWidgetItem("In"));
    m_table->setItem(row, col++, new QTableWidgetItem(QDateTime().currentDateTime().toString()));
}
