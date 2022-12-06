#include "messagesclient.h"
#include "json2messagelist.h"


MessagesClient::MessagesClient(QObject *parent): HttpClient(parent)
{

}


void MessagesClient::fetchMessages(MessagesParams params, OnMessagesReady callback)
{
    if(pendingRequest) return; // ignore any new request untill previous one is handled
    pendingRequest = true;
    this->readyCallback = callback;
    HttpClient::requestData(params.toHttpRequestUrl());
}


void MessagesClient::onRequestFailed(QNetworkReply::NetworkError errorCode)
{
    pendingRequest = false;
    //send emplty list and indicate failure
    readyCallback(QList<Message>(),false);
}

#include "Data/db_paths.h"
void MessagesClient::onRequestFinished(QNetworkReply *reply)
{
    //read the response content
    this->currentData = reply->readAll();
    if(reply->error() != QNetworkReply::NoError) {
        qDebug() << reply->error() << " on url " << reply->url();
        return;
    }
    // convert from json to message list
    Json2MessageList converter;
    converter.process(currentData);

    //push changers to the caller
    pendingRequest = false;
    readyCallback(converter.getMessages(),true);

    //store to a temp file
    storeReplyContentToFile(TEMP_PATH_MESSAGES,TEMP_FILE_MESSAGES,currentData);

    HttpClient::onRequestFinished(reply); //cleanup by parent
}
