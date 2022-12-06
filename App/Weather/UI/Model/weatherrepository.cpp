#include "weatherrepository.h"

WeatherRepository::WeatherRepository(QObject *parent)
{
    client = new WeatherClient(parent);
}

WeatherRepository::~WeatherRepository()
{
}

void WeatherRepository::fetchWeatherObservations(WeatherParams params, OnWeatherObservationsDataReady callback)
{
    client->fetchWeatherObservations(params, callback);
}

void WeatherRepository::fetchWeatherObservations(QString filename, OnWeatherObservationsDataReady callback)
{
    db.fetchWeatherObservations(filename, callback);
}

void WeatherRepository::fetchWeatherForecast(WeatherParams params, OnWeatherForecastDataReady callback)
{
    client->fetchWeatherForecast(params, callback);
}

void WeatherRepository::fetchWeatherForecast(QString filename, OnWeatherForecastDataReady callback)
{
    db.fetchWeatherForecast(filename, callback);
}

void WeatherRepository::storeObservationsWeatherData(QString filename, OnWeatherDataStored callback)
{
    db.storeObservationWeatherData(filename, callback);
}

void WeatherRepository::storeForecastWeatherData(QString filename, OnWeatherDataStored callback)
{
    db.storeForecastWeatherData(filename, callback);
}

QStringList WeatherRepository::getStoredObservationsFilesList()
{
    return db.getStoredObservationsFilesList();
}

QStringList WeatherRepository::getStoredForecastFilesList()
{
    return db.getStoredForecastFilesList();
}


