#include "weatherclient.h"
#include "xml2weatherobservation.h"
#include "xml2weatherforecast.h"
#include "Data/db_paths.h"

WeatherClient::WeatherClient(QObject *parent)
    : HttpClient{parent}
{

}

void WeatherClient::fetchWeatherObservations(WeatherParams params, OnWeatherObservationsDataReady callback)
{
    if(pendingRequestObservation) return; // ignore any new request untill previous one is handled
    pendingRequestObservation = true;
    this->observationReadyCallback = callback;
    HttpClient::requestData(params.toObservationHttpRequestUrl());
}

void WeatherClient::fetchWeatherForecast(WeatherParams params, OnWeatherForecastDataReady callback)
{
    if(pendingRequestForecast) return; // ignore any new request untill previous one is handled
    pendingRequestForecast = true;
    this->forecastReadyCallback = callback;
    HttpClient::requestData(params.toForecastHttpRequestUrl());
}

void WeatherClient::onRequestFinished(QNetworkReply *reply)
{
    //read the response content
    this->currentData = reply->readAll();
    QString url = reply->url().toString();
    if(reply->error() != QNetworkReply::NoError) {
        qDebug() << reply->error() << " on url " << url;
        if(url.contains("forecast")){
            observationReadyCallback(WeatherObservationData(),false);
        } else if(url.contains("observation")){
            forecastReadyCallback(WeatherForecastData(),false);
        }
        return;
    }

    //check wether the response is for forecast or observation
    if(url.contains("forecast")){
        // convert from json to weather data
        Xml2WeatherForecast converter;
        converter.process(currentData);

        // FIXME: decision needed to handle both obs and forecasr
        // store specific task data to a temp file
        storeReplyContentToFile(TEMP_PATH_WEATHER,TEMP_FILE_WEATHER_FORECAST,currentData);

        //push changes to the caller
        pendingRequestForecast = false;
        forecastReadyCallback(converter.getForecast(),true);

    } else if(url.contains("observation")){
        // convert from json to weather data
         Xml2WeatherObservation converter;
         converter.process(currentData);

        // store specific task data to a temp file
         storeReplyContentToFile(TEMP_PATH_WEATHER,TEMP_FILE_WEATHER_OBSERVATIONS,currentData);

        //push changers to the caller
        pendingRequestObservation = false;
        observationReadyCallback(converter.getObservations(),true);
    }

    HttpClient::onRequestFinished(reply); //cleanup by parent
}

void WeatherClient::onRequestFailed(QNetworkReply::NetworkError errorCode)
{
}
