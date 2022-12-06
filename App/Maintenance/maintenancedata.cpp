#include "maintenancedata.h"

int MaintenanceData::getTasksCount() const
{
    return tasksCount;
}

void MaintenanceData::setTasksCount(int newTasksCount)
{
    tasksCount = newTasksCount;
}

const QString &MaintenanceData::getTasksID() const
{
    return tasksID;
}

void MaintenanceData::setTasksID(const QString &newTasksID)
{
    tasksID = newTasksID;
}

const QByteArray MaintenanceData::toJsonObject()
{
    QJsonObject obj;
    obj["tasksID"] = this->tasksID;
    obj["tasksCount"] = this->tasksCount;
    QJsonDocument doc(obj);
    return doc.toJson();
}

MaintenanceData MaintenanceData::fromJson(QByteArray &json)
{
    QJsonDocument doc = QJsonDocument::fromJson(json);
    QJsonObject obj = doc.object();
    MaintenanceData data;
    data.tasksID = obj["tasksID"].toString();
    data.tasksCount = obj["tasksCount"].toInt();
    return data;
}


MaintenanceData::MaintenanceData()
{
}
