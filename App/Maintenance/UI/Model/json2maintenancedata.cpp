#include "json2maintenancedata.h"

Json2MaintenanceData::Json2MaintenanceData()
{

}

MaintenanceData Json2MaintenanceData::getTaskData() const
{
    return tasksCount;
}

void Json2MaintenanceData::setTasksCount(MaintenanceData newTasksCount)
{
    tasksCount = newTasksCount;
}

#include<QFile>
//process the json document from the request response, and store parsed data to an variable
void Json2MaintenanceData::process(QByteArray &json)
{
    QJsonDocument doc = QJsonDocument::fromJson(json);
    QJsonObject jsonObj = doc.object();
    auto features = jsonObj.value("features").toArray();
    int count  = features.count();
    tasksCount.setTasksCount(count);

    //if there are tasks, get the task type from one of them
    if(count > 0) {
    QString taskID = jsonObj
        .value("features")
        .toArray()
        .at(0)
        .toObject()
        .value("properties")
        .toObject()
        .value("tasks")
        .toArray()
        .at(0)
        .toString();
    tasksCount.setTasksID(taskID);
     }
}
