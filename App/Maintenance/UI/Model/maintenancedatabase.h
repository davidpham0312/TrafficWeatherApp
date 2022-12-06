#ifndef MAINTENANCEDATABASE_H

#define MAINTENANCEDATABASE_H
#include "Data/db_paths.h"
#include "Data/absdatabase.h"
#include "Maintenance/maintenancecallbacks.h"
#include "Maintenance/UI/Model/json2maintenancedata.h"

class MaintenanceDataBase : public AbsDataBase
{
public:
    MaintenanceDataBase();
    void fetchMaintenanceData(QString filename, OnMaintenanceDataReady callback);
    void storeMaintenanceData(QString filename, OnMaintenanceDataStored callback);

    // AbsDataBase interface
protected:
    QString getDbPath();
    QString getTempPath();
    QString getTempFile();
};


#endif // MAINTENANCEDATABASE_H
