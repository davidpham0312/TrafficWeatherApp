#ifndef WEATHERDATABASE_H
#define WEATHERDATABASE_H

#include "Data/absdatabase.h"
#include "Data/db_paths.h"
#include "Weather/weathercallbacks.h"
#include "xml2weatherforecast.h"
#include "xml2weatherobservation.h"


class WeatherDataBase : public AbsDataBase
{
public:
    WeatherDataBase();
    void fetchWeatherObservations(QString filename, OnWeatherObservationsDataReady callback);
    void fetchWeatherForecast(QString filename, OnWeatherForecastDataReady callback);
    void storeObservationWeatherData(QString filename, OnWeatherDataStored callback);
    void storeForecastWeatherData(QString filename, OnWeatherDataStored callback);
    //gets a list of all files stored in the database
    QStringList getStoredObservationsFilesList();
    QStringList getStoredForecastFilesList();

    // AbsDataBase interface
protected:
    QString getDbPath();
    QString getTempPath();
    QString getTempFile();
};

#endif // WEATHERDATABASE_H
