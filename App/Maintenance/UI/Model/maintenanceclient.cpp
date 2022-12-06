#include "maintenanceclient.h"

MaintenanceClient::MaintenanceClient(QObject *parent)
    : HttpClient{parent}
{

}

void MaintenanceClient::fetchTasksCount(MaintenanceParams params, OnMaintenanceDataReady callback)
{
    if(pendingRequest) return; // ignore any new request untill previous one is handled
    pendingRequest = true;
    this->readyCallback = callback;
    HttpClient::requestData(params.toHttpRequestUrl());
}


#include "Data/db_paths.h"
void MaintenanceClient::onRequestFinished(QNetworkReply *reply)
{
    //read the response content
    this->currentData = reply->readAll();
    if(reply->error() != QNetworkReply::NoError) {
        qDebug() << reply->error() << " on url " << reply->url();
        return;
    }

    // convert from json to maintenance data
    Json2MaintenanceData converter;
    converter.process(currentData);
    MaintenanceData data = converter.getTaskData();
    QByteArray json = data.toJsonObject();

    //store specific task data to a temp file
    storeReplyContentToFile(TEMP_PATH_MAINTENANCE,TEMP_FILE_MAINTENANCE,json);

    //push changers to the caller
    pendingRequest = false;
    readyCallback(data,true);


    HttpClient::onRequestFinished(reply); //cleanup by parent
}

void MaintenanceClient::onRequestFailed(QNetworkReply::NetworkError errorCode)
{
    pendingRequest = false;
    //send emplty list and indicate failure
    readyCallback(MaintenanceData(),false);
}
