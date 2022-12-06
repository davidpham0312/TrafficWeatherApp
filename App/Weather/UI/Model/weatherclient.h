#ifndef WEATHERCLIENT_H
#define WEATHERCLIENT_H

#include "Weather/weatherparams.h"
#include "Weather/weathercallbacks.h"
#include <QList>
#include <QObject>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include "Data/httpclient.h"

class WeatherClient: public HttpClient
{
     Q_OBJECT
public:
    explicit WeatherClient(QObject *parent = nullptr);
    void fetchWeatherObservations(WeatherParams params, OnWeatherObservationsDataReady callback);
    void fetchWeatherForecast(WeatherParams params, OnWeatherForecastDataReady callback);

protected:
    //internal callback for handling request response success
    void onRequestFinished(QNetworkReply* reply);
    //internal callback for handling request response failure
    void onRequestFailed(QNetworkReply::NetworkError errorCode);

private:
    OnWeatherObservationsDataReady observationReadyCallback;
    OnWeatherForecastDataReady forecastReadyCallback;
    bool pendingRequestObservation = false;
    bool pendingRequestForecast = false;
    QByteArray currentData;
};

#endif // WEATHERCLIENT_H
