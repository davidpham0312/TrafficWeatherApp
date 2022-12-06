#ifndef MAINTENANCEPARAMS_H
#define MAINTENANCEPARAMS_H

#include<QString>
#include<QDateTime>
#include<QJsonObject>
#include<QJsonDocument>

class MaintenanceParams
{
private:
    QDateTime fromTime;
    QDateTime toTime;
    float xMin = 21;
    float yMin = 61;
    float xMax = 22;
    float yMax = 62;
    QString taskID = "BRUSHING";
    const QString baseUrl = "https://tie.digitraffic.fi/api/maintenance/v1/tracking/routes?";


public:
    MaintenanceParams();

    float getXMin() const;
    void setXMin(float newXMin);
    float getYMin() const;
    void setYMin(float newYMin);
    float getXMax() const;
    void setXMax(float newXMax);
    float getYMax() const;
    void setYMax(float newYMax);
    const QString &getTaskID() const;
    void setTaskID(const QString &newTaskID);
    QString toHttpRequestUrl();
    const QDateTime &getFromTime() const;
    void setFromTime(const QDateTime &newFromTime);
    const QDateTime &getToTime() const;
    void setToTime(const QDateTime &newToTime);

    //serialization
    const QByteArray toJsonObject();
    static MaintenanceParams fromJson(QByteArray &json);
};

#endif // MAINTENANCEPARAMS_H
