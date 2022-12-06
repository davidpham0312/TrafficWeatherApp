#include "messagesrepository.h"


MessagesRepository::MessagesRepository(QObject *parent)
{
    client = new MessagesClient(parent);
}

MessagesRepository::~MessagesRepository()
{
}

void MessagesRepository::getMessages(QString fileName, OnMessagesReady callback)
{
    db.fetchMessages(fileName,callback);
}

void MessagesRepository::getMessages(MessagesParams params, OnMessagesReady callback)
{
    client->fetchMessages(params, callback);
}

void MessagesRepository::storeMessages(QString filename, OnMessagesStored callback)
{
    db.storeMessages(filename, callback);
}

QList<QString> MessagesRepository::getMessageSituationTypes()
{
    static QList<QString> situationTypes;
    if(situationTypes.isEmpty()){
        situationTypes.append("TRAFFIC_ANNOUNCEMENT");
        situationTypes.append("EXEMPTED_TRANSPORT");
        situationTypes.append("WEIGHT_RESTRICTION");
        situationTypes.append("ROAD_WORK");
    }
    return situationTypes;
}

QStringList MessagesRepository::getStoredFilesList()
{
    return db.getStoredFilesList();
}
