#ifndef TERMINALFLOW_H
#define TERMINALFLOW_H

#include <QObject>
#include <QTableWidget>
#include <QDate>
#include <pthread.h>
#include <unistd.h> //sleep

class TerminalFlow : public QObject
{
    Q_OBJECT
    QTableWidget *m_table;
    bool m_update;
    QStringList m_header;
    pthread_t pollForData_handle;

public:
    explicit TerminalFlow(QObject *parent = 0);

    void setTable(QTableWidget *table);

private:
    void createTable();
    static void* pollForData(void *arg);

signals:

public slots:
    void checkForData();
    void setAutoUpdate(bool state);

};

#endif // TERMINALFLOW_H
