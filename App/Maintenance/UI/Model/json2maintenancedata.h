#ifndef JSON2MAINTENANCEDATA_H
#define JSON2MAINTENANCEDATA_H
#include <QByteArray>
#include <QJsonValue>
#include <QJsonArray>
#include <QJsonObject>
#include <QJsonDocument>
#include <QDateTime>

#include "Maintenance/maintenancedata.h"

class Json2MaintenanceData
{
private:
    MaintenanceData tasksCount;
public:
    Json2MaintenanceData();
    void process(QByteArray& json);
    MaintenanceData getTaskData() const;
    void setTasksCount(MaintenanceData newTasksCount);
};

#endif // JSON2MAINTENANCEDATA_H
