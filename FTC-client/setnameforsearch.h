#ifndef SETNAMEFORSEARCH_H
#define SETNAMEFORSEARCH_H

#include <QObject>
#include "controller.h"

class setNameForSearch: public QObject
{
     Q_OBJECT
public:
    Q_INVOKABLE void setName(QString name);
    setNameForSearch();
};

#endif // SETNAMEFORSEARCH_H
