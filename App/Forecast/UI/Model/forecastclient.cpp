#include "forecastclient.h"

ForecastClient::ForecastClient(QObject *parent)
    : HttpClient{parent}
{
    
}

void ForecastClient::fetchForecastData(ForecastParams params, OnForecastDataReady callback)
{
    if(pendingRequest) return; // ignore any new request untill previous one is handled
    pendingRequest = true;
    this->readyCallback = callback;
    HttpClient::requestData(params.toHttpRequestUrl());
}

#include "Data/db_paths.h"
void ForecastClient::onRequestFinished(QNetworkReply *reply)
{
    //read the response content
    this->currentData = reply->readAll();
    if(reply->error() != QNetworkReply::NoError) {
        qDebug() << reply->error() << " on url " << reply->url();
        return;
    }
    // convert from json to forecast list
    Json2ForecastList converter;
    converter.process(currentData);

    //push changers to the caller
    pendingRequest = false;
    readyCallback(converter.getForecastList(),true);

    //store to a temp file
    storeReplyContentToFile(TEMP_PATH_FORECAST,TEMP_FILE_FORECAST,currentData);

    HttpClient::onRequestFinished(reply); //cleanup by parent
}

void ForecastClient::onRequestFailed(QNetworkReply::NetworkError errorCode)
{
    pendingRequest = false;
    //send emplty list and indicate failure
    readyCallback(QList<ForecastDataSample>(),false);
}
