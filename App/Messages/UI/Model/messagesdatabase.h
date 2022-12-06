#ifndef MESSAGESDATABASE_H
#define MESSAGESDATABASE_H

#include "Data/absdatabase.h"
#include "Data/db_paths.h"
#include "Messages/MessagesCallbacks.h"
#include "Messages/UI/Model/json2messagelist.h"

class MessagesDataBase : public AbsDataBase
{
public:
    MessagesDataBase();
    void fetchMessages(QString filename, OnMessagesReady callback);
    void storeMessages(QString filename, OnMessagesStored callback);
    // AbsDataBase interface
protected:
    QString getDbPath();
    QString getTempPath();
    QString getTempFile();
};

#endif // MESSAGESDATABASE_H
