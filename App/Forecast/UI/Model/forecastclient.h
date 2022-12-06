#ifndef FORECASTCLIENT_H
#define FORECASTCLIENT_H

#include "Data/httpclient.h"
#include "Forecast/forecastparams.h"
#include "Forecast/forecastcallbacks.h"
#include "Forecast/json2forecastlist.h"
#include <QFile>
#include <QList>
#include <QObject>
#include <QNetworkAccessManager>
#include <QNetworkReply>

class ForecastClient : public HttpClient
{
     Q_OBJECT
public:
    explicit ForecastClient(QObject *parent = nullptr);
    //fetch data asynchronously and callback the caller when ready
    void fetchForecastData(ForecastParams, OnForecastDataReady callback);
protected:
    //internal callback for handling request response success
    void onRequestFinished(QNetworkReply* reply);
    //internal callback for handling request response failure
    void onRequestFailed(QNetworkReply::NetworkError errorCode);


private:
    OnForecastDataReady readyCallback;
    QByteArray currentData;
    bool pendingRequest = false;
};

#endif // FORECASTCLIENT_H
