#include "setnameforsearch.h"

void setNameForSearch::setName(QString name)
{
    Controller::getInstance()->setEmployee(name);
}

setNameForSearch::setNameForSearch()
{

}
