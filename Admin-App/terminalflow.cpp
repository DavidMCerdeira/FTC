#include "terminalflow.h"
#include <QDebug>

TerminalFlow::TerminalFlow(QObject *parent) : QObject(parent), m_table(NULL), m_update(true)
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
    m_update = state;
}

void TerminalFlow::createTable()
{
    m_table->setColumnCount(m_header.length());
    m_table->setHorizontalHeaderLabels(m_header);
}

void *TerminalFlow::pollForData(void *arg)
{
    TerminalFlow* self = static_cast<TerminalFlow*>(arg);

    int row;
    while(self->m_update){
        /* wait for server */

        if(false){
            row = self->m_table->rowCount() - 1;
            //table
        }
    }

    return arg;
}
