#include "setnameforsearch.h"

void setNameForSearch::setName(QString name)
{
    qDebug() << "Set name:" << name;
    Controller::getInstance()->setEmployee(name);
}

setNameForSearch::setNameForSearch()
{

}
