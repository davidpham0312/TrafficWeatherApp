#include "maintenancedatabase.h"

MaintenanceDataBase::MaintenanceDataBase()
{

}

void MaintenanceDataBase::fetchMaintenanceData(QString filename, OnMaintenanceDataReady callback)
{
    // TODO: put this inside a thread
    QByteArray data;
    dbLoad(filename,data);
//    MaintenanceData::fromJson(data);
//    Json2MaintenanceData converter;
//    converter.process(data);
    callback(MaintenanceData::fromJson(data), true);
}

void MaintenanceDataBase::storeMaintenanceData(QString filename, OnMaintenanceDataStored callback)
{
    // TODO: put this inside a thread
    dbStore(filename);
    callback();
}

QString MaintenanceDataBase::getDbPath()
{
    return DB_PATH_MAINTENANCE;
}

QString MaintenanceDataBase::getTempPath()
{
    return TEMP_PATH_MAINTENANCE;
}

QString MaintenanceDataBase::getTempFile()
{
    return TEMP_FILE_MAINTENANCE;
}
