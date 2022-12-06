#ifndef MAINTENANCEREPOSITORY_H
#define MAINTENANCEREPOSITORY_H

#include<QString>
#include<QObject>
#include<QList>
#include "Maintenance/maintenancecallbacks.h"
#include "Maintenance/maintenanceparams.h"
#include "maintenanceclient.h"
#include "maintenancedatabase.h"



class MaintenanceRepository
{

private:
    MaintenanceClient* client;
    MaintenanceDataBase db;
    static QList<QString> situationTypes;


public:
    MaintenanceRepository(QObject* parent);

    //get data from local database stored in the files named "filename"
    void getSpecificTaskData(QString fileName, OnMaintenanceDataReady);
    //fetch specific task count from the DigiTraffic servers over http
    void getSpecificTaskData(MaintenanceParams params, OnMaintenanceDataReady);

    //store the data locally in the database
    void storeSpecificTaskData(QString filename, OnMaintenanceDataStored);

    //this function returns a list of all files in the database
    QStringList getStoredFilesList();

    // this function will return a list of all maintenance task types
    static QList<QString> getMaintenanceTaskTypes();


};

#endif // MAINTENANCEREPOSITORY_H
