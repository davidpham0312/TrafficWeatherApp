#ifndef FORECASTREPOSITORY_H
#define FORECASTREPOSITORY_H


#include<QString>
#include<QObject>
#include<QList>
#include "Forecast/forecastcallbacks.h"
#include "Forecast/forecastparams.h"
#include "Forecast/UI/Model/forecastclient.h"
#include "Forecast/UI/Model/forecastdatabase.h"

class ForecastRepository
{
private:
    ForecastClient* client;
    ForecastDataBase db;

public:
    ForecastRepository(QObject *parent);

    //get data from local database stored in the files named "filename"
    void getForecastData(QString fileName, OnForecastDataReady callback );
    //fetch data from the DigiTraffic servers over http
    void getForecastData(ForecastParams params, OnForecastDataReady callback);
    //store the data locally in the database
    void storeForecastData(QString filename, OnDataStored);
    //gets list of all files in the database
    QStringList getStoredFilesList();
};

#endif // FORECASTREPOSITORY_H
