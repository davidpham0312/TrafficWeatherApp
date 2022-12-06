#ifndef FORECASTDATABASE_H
#define FORECASTDATABASE_H

#include "Data/db_paths.h"
#include "Data/absdatabase.h"
#include "Forecast/forecastcallbacks.h"
#include "Forecast/json2forecastlist.h"

class ForecastDataBase : public AbsDataBase
{
public:
    ForecastDataBase();
    void fetchForecastData(QString filename, OnForecastDataReady callback);
    void storeForecastData(QString filename, OnDataStored callback);

    // AbsDataBase interface
protected:
    QString getDbPath();
    QString getTempPath();
    QString getTempFile();
};

#endif // FORECASTDATABASE_H
