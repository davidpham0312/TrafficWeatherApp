#include "forecastdatabase.h"

ForecastDataBase::ForecastDataBase()
{
    
}

void ForecastDataBase::fetchForecastData(QString filename, OnForecastDataReady callback)
{
    // TODO: put this inside a thread
    QByteArray data;
    dbLoad(filename,data);
    Json2ForecastList converter;
    converter.process(data);
    callback(converter.getForecastList(), true);
}

void ForecastDataBase::storeForecastData(QString filename, OnDataStored callback)
{
    // TODO: put this inside a thread
    dbStore(filename);
    callback();
}

QString ForecastDataBase::getDbPath()
{
    return DB_PATH_FORECAST;
}

QString ForecastDataBase::getTempPath()
{
    return TEMP_PATH_FORECAST;
}

QString ForecastDataBase::getTempFile()
{
    return TEMP_FILE_FORECAST;
}
