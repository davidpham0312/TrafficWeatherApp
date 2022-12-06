#include "forecastrepository.h"

ForecastRepository::ForecastRepository(QObject *parent)
{
    client = new ForecastClient(parent);
}

void ForecastRepository::getForecastData(QString fileName, OnForecastDataReady callback)
{
    db.fetchForecastData(fileName,callback);
}

void ForecastRepository::getForecastData(ForecastParams params, OnForecastDataReady callback)
{
    client->fetchForecastData(params, callback);
}

void ForecastRepository::storeForecastData(QString filename, OnDataStored callback)
{
    db.storeForecastData(filename, callback);
}

QStringList ForecastRepository::getStoredFilesList()
{
    return db.getStoredFilesList();
}
