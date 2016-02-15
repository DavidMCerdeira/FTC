#ifndef TERMINALFLOW_H
#define TERMINALFLOW_H

#include <QObject>
#include <QTableWidget>

class TerminalFlow : public QObject
{
    Q_OBJECT
    QTableWidget *m_table;
    bool m_update;
    QStringList m_header;

public:
    explicit TerminalFlow(QObject *parent = 0);

    void setTable(QTableWidget *table);
    void setAutoUpdate(bool state);

private:
    void createTable();
    static void* pollForData(void *arg);

signals:

public slots:
};

#endif // TERMINALFLOW_H
