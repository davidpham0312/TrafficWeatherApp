#ifndef MESSAGESDATABASE_H
#define MESSAGESDATABASE_H

#include "MessagesCallbacks.h"
#include <QList>


class MessagesDataBase
{
public:
    MessagesDataBase();
    void loadMessagesFromDB(QString fileName, OnMessagesReady);
    void storeMessagesToDB(QString filename, OnMessagesStored);
    QList<QString> getStoredDataList();
};

#endif // MESSAGESDATABASE_H
