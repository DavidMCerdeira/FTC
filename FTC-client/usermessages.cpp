#include "usermessages.h"

UserMessages::UserMessages(QObject *parent)
    : QAbstractListModel(parent), controller(Controller::getInstance()), m_data(NULL)
{
    pthread_t getMsgs;
    pthread_attr_t attr;

    pthread_attr_init(&attr);
    pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_DETACHED);


    int ret = pthread_create(&getMsgs, &attr, getMessages_thread, static_cast<void*>(this));
    if(ret){
        /*Handle Error*/
        qDebug() << "Error creating User message thread" << endl;
    }
}

int UserMessages::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    // return our data count
    int i;
    if(m_data != NULL)
        i =  m_data->count();
    else
        i = 0;

    return i;
}

QVariant UserMessages::data(const QModelIndex &index, int role) const
{

    qDebug() << "Data requested" << endl;

    // the index returns the requested row and column information.
    // we ignore the column and only use the row information
    int row = index.row();
    // boundary check for the row
    if(row < 0 || row >= m_data->count()) {
        return QVariant();
    }
    // A model can return data for different roles.
    // The default role is the display role.
    // it can be accesses in QML with "model.display"
    switch(role) {
    case Qt::DisplayRole:
        // Return the color name for the particular row
        // Qt automatically converts it to the QVariant type
        return m_data->value(row);
    }
    // The view asked for other data, just return an empty QVariant
    return QVariant();
}

void* UserMessages::getMessages_thread(void *arg)
{
    UserMessages *self = static_cast<UserMessages*>(arg);

    (self->m_data) = self->controller->getUserMessages();
    return NULL;
}
