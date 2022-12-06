#ifndef WEATHERREPOSITORY_H
#define WEATHERREPOSITORY_H

#include<QString>
#include<QObject>
#include<QList>
#include "Weather/weathercallbacks.h"
#include "Weather/weatherparams.h"
#include "Weather/UI/Model/weatherclient.h"
#include "Weather/UI/Model/weatherdatabase.h"

class WeatherRepository
{
    WeatherClient* client;
    WeatherDataBase db;
public:
    WeatherRepository(QObject* parent);
    ~WeatherRepository();
    void fetchWeatherObservations(WeatherParams params, OnWeatherObservationsDataReady callback);
    void fetchWeatherObservations(QString filename, OnWeatherObservationsDataReady callback);
    void fetchWeatherForecast(WeatherParams params, OnWeatherForecastDataReady callback);
    void fetchWeatherForecast(QString filename, OnWeatherForecastDataReady callback);
    void storeObservationsWeatherData(QString filename, OnWeatherDataStored callback);
    void storeForecastWeatherData(QString filename, OnWeatherDataStored callback);
    //gets a list of all files stored in the database
    QStringList getStoredObservationsFilesList();
    QStringList getStoredForecastFilesList();

};

#endif // WEATHERREPOSITORY_H
