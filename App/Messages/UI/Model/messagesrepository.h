#ifndef MESSAGESREPOSITORY_H
#define MESSAGESREPOSITORY_H

#include<QString>
#include<QObject>
#include<QList>
#include "Messages/MessagesCallbacks.h"
#include "Messages/messagesparams.h"
#include "Messages/UI/Model/messagesclient.h"
#include "Messages/UI/Model/messagesdatabase.h"



class MessagesRepository
{
private:
    MessagesClient* client;
    MessagesDataBase db;


public:
    MessagesRepository(QObject* parent);
    ~MessagesRepository();
    //get messages from local database stored in the files named "filename"
    void getMessages(QString fileName, OnMessagesReady);
    //fetch messages from the DigiTraffic servers over http
    void getMessages(MessagesParams params, OnMessagesReady);
    //store the messages locally in the database
    void storeMessages(QString filename, OnMessagesStored);
    //get the list of message types
    static QList<QString> getMessageSituationTypes();
    //gets a list of all files stored in the database
    QStringList getStoredFilesList();
};

#endif // MESSAGESREPOSITORY_H
