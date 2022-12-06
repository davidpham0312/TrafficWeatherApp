#include "weatherdatabase.h"

WeatherDataBase::WeatherDataBase()
{

}

void WeatherDataBase::fetchWeatherObservations(QString filename, OnWeatherObservationsDataReady callback)
{
    // TODO: put this inside a thread
    QByteArray data;
    dbLoad(filename.append(WEATHER_OBSERVATION_EXTENSION),data);
    Xml2WeatherObservation converter;
    converter.process(data);
    callback(converter.getObservations(), true);
}

void WeatherDataBase::fetchWeatherForecast(QString filename, OnWeatherForecastDataReady callback)
{
    // TODO: put this inside a thread
    QByteArray data;
    dbLoad(filename.append(WEATHER_FORECAST_EXTENSION),data);
    Xml2WeatherForecast converter;
    converter.process(data);
    callback(converter.getForecast(), true);
}

void WeatherDataBase::storeObservationWeatherData(QString filename, OnWeatherDataStored callback)
{
    bool b;
    b = dbStore(filename, QString(WEATHER_OBSERVATION_EXTENSION));
    callback(b);
}

void WeatherDataBase::storeForecastWeatherData(QString filename, OnWeatherDataStored callback)
{
    bool b;
    b = dbStore(filename, QString(WEATHER_FORECAST_EXTENSION));
    callback(b);
}

QStringList WeatherDataBase::getStoredObservationsFilesList()
{
    QStringList files;
    foreach(QString file,AbsDataBase::getStoredFilesList()){
        QStringList splitted = file.split(".");
        if(splitted.at(1).compare("forecast") == 0) continue;
        files.append(splitted.at(0));

    }
    return files;
}

QStringList WeatherDataBase::getStoredForecastFilesList()
{
    QStringList files;
    foreach(QString file,AbsDataBase::getStoredFilesList()){
        QStringList splitted = file.split(".");
        if(splitted.at(1).compare("observation") == 0) continue;
        files.append(splitted.at(0));

    }
    return files;
}


QString WeatherDataBase::getDbPath()
{
    return DB_PATH_WEATHER;
}

QString WeatherDataBase::getTempPath()
{
    return TEMP_PATH_WEATHER;
}

QString WeatherDataBase::getTempFile()
{
    return TEMP_FILE_WEATHER;
}

