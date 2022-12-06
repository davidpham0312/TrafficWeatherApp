#include "maintenanceparams.h"

float MaintenanceParams::getXMin() const
{
    return xMin;
}

void MaintenanceParams::setXMin(float newXMin)
{
    xMin = newXMin;
}

float MaintenanceParams::getYMin() const
{
    return yMin;
}

void MaintenanceParams::setYMin(float newYMin)
{
    yMin = newYMin;
}

float MaintenanceParams::getXMax() const
{
    return xMax;
}

void MaintenanceParams::setXMax(float newXMax)
{
    xMax = newXMax;
}

float MaintenanceParams::getYMax() const
{
    return yMax;
}

void MaintenanceParams::setYMax(float newYMax)
{
    yMax = newYMax;
}

const QString &MaintenanceParams::getTaskID() const
{
    return taskID;
}

void MaintenanceParams::setTaskID(const QString &newTaskID)
{
    taskID = newTaskID;
}

QString MaintenanceParams::toHttpRequestUrl()
{
    QString urlStr  = baseUrl;
    urlStr.append(QString("createdAfter=%1").arg(this->fromTime.toString(Qt::ISODate).append("Z")));
    urlStr.append(QString("&createdBefore=%1").arg(this->toTime.toString(Qt::ISODate).append("Z")));
    urlStr.append(QString("&xMin=%1").arg(this->xMin));
    urlStr.append(QString("&yMin=%1").arg(this->yMin));
    urlStr.append(QString("&xMax=%1").arg(this->xMax));
    urlStr.append(QString("&yMax=%1").arg(this->yMax));
    urlStr.append(QString("&taskId=%1&domain=state-roads").arg(this->taskID));
    qDebug() << urlStr;
    return urlStr;
}

const QDateTime &MaintenanceParams::getFromTime() const
{
    return fromTime;
}

void MaintenanceParams::setFromTime(const QDateTime &newFromTime)
{
    fromTime = newFromTime;
}

const QDateTime &MaintenanceParams::getToTime() const
{
    return toTime;
}

void MaintenanceParams::setToTime(const QDateTime &newToTime)
{
    toTime = newToTime;
}

const QByteArray MaintenanceParams::toJsonObject()
{
    QJsonObject obj;
    obj["fromTime"] = this->fromTime.toString(Qt::ISODate);
    obj["toTime"] = this->toTime.toString(Qt::ISODate);
    obj["taskID"] = this->taskID;
    obj["xMin"] = this->xMin;
    obj["yMin"] = this->yMin;
    obj["xMax"] = this->xMax;
    obj["yMax"] = this->yMax;
    QJsonDocument doc(obj);
    return doc.toJson();
}

MaintenanceParams MaintenanceParams::fromJson(QByteArray &json)
{
    QJsonDocument doc = QJsonDocument::fromJson(json);
    QJsonObject obj = doc.object();
    MaintenanceParams data;
    data.fromTime = QDateTime::fromString(obj["fromTime"].toString(), Qt::ISODate);
    data.toTime = QDateTime::fromString(obj["toTime"].toString(), Qt::ISODate);
    data.taskID = obj["taskID"].toString();
    data.xMin = obj["xMin"].toDouble();
    data.yMin = obj["yMin"].toDouble();
    data.xMax = obj["xMax"].toDouble();
    data.yMax = obj["yMax"].toDouble();
    return data;
}

MaintenanceParams::MaintenanceParams()
{

}
