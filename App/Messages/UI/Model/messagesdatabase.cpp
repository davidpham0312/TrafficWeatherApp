#include "messagesdatabase.h"

MessagesDataBase::MessagesDataBase()
{

}

void MessagesDataBase::fetchMessages(QString filename, OnMessagesReady callback)
{
    // TODO: put this inside a thread
    QByteArray data;
    dbLoad(filename,data);
    Json2MessageList converter;
    converter.process(data);
    callback(converter.getMessages(), true);
}

void MessagesDataBase::storeMessages(QString filename, OnMessagesStored callback)
{
    // TODO: put this inside a thread
    dbStore(filename);
    callback();
}

QString MessagesDataBase::getDbPath()
{
    return DB_PATH_MESSAGES;
}

QString MessagesDataBase::getTempPath()
{
    return TEMP_PATH_MESSAGES;
}

QString MessagesDataBase::getTempFile()
{
    return TEMP_FILE_MESSAGES;
}
