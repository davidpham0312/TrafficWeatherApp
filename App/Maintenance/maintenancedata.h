#ifndef MAINTENANCEDATA_H
#define MAINTENANCEDATA_H

#include <QString>
#include <QJsonObject>
#include <QJsonDocument>

//tells whether data is coming from database of server
enum MaintenanceDataSrc {
    DIGI_TRAFFIC, LOCAL_DB
};

class MaintenanceData
{

private:
    int tasksCount; // number of tasks for each task type
    QString tasksID; //task type id

public:
    MaintenanceData();
    int getTasksCount() const ;
    void setTasksCount(int newTasksCount);
    const QString &getTasksID() const;
    void setTasksID(const QString &newTasksID);
    //serialization
    const QByteArray toJsonObject();
    static MaintenanceData fromJson(QByteArray &json);

};

#endif // MAINTENANCEDATA_H
