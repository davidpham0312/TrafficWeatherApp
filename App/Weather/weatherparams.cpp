#include "weatherparams.h"

const QDateTime &WeatherParams::getFromTime() const
{
    return fromTime;
}

const QDateTime &WeatherParams::getToTime() const
{
    return toTime;
}

int WeatherParams::getXMin() const
{
    return xMin;
}

int WeatherParams::getYMin() const
{
    return yMin;
}

int WeatherParams::getXMax() const
{
    return xMax;
}

int WeatherParams::getYMax() const
{
    return yMax;
}

int WeatherParams::getTimeStepInMinutes() const
{
    return timeStepInMinutes;
}

const QString &WeatherParams::getQueryID() const
{
    return queryID;
}

void WeatherParams::setFromTime(const QDateTime &newFromTime)
{
    fromTime = newFromTime;
}

void WeatherParams::setToTime(const QDateTime &newToTime)
{
    toTime = newToTime;
}

void WeatherParams::setXMin(int newXMin)
{
    xMin = newXMin;
}

void WeatherParams::setYMin(int newYMin)
{
    yMin = newYMin;
}

void WeatherParams::setXMax(int newXMax)
{
    xMax = newXMax;
}

void WeatherParams::setYMax(int newYMax)
{
    yMax = newYMax;
}

void WeatherParams::setTimeStepInMinutes(int newTimeStepInMinutes)
{
    timeStepInMinutes = newTimeStepInMinutes;
}

void WeatherParams::setQueryID(const QString &newQueryID)
{
    queryID = newQueryID;
}

#include<QJsonObject>
#include<QJsonDocument>

const QByteArray WeatherParams::toJsonObject()
{
    QJsonObject obj;
    obj["xMin"] = this->xMin;
    obj["xMax"] = this->xMax;
    obj["yMin"] = this->yMin;
    obj["yMax"] = this->yMax;
    obj["queryID"] = this->queryID;
    obj["timeStepInMinutes"] = this->timeStepInMinutes;
    obj["fromTime"] = this->fromTime.toString(Qt::ISODate);
    obj["toTime"] = this->toTime.toString(Qt::ISODate);
    QJsonDocument doc(obj);
    return doc.toJson();
}

WeatherParams WeatherParams::fromJson(QByteArray &json)
{
    QJsonDocument doc = QJsonDocument::fromJson(json);
    QJsonObject obj = doc.object();
    WeatherParams data;
    data.xMin = obj["xMin"].toDouble();
    data.xMax = obj["xMax"].toDouble();
    data.yMin = obj["yMin"].toDouble();
    data.yMax = obj["yMax"].toDouble();
    data.queryID = obj["queryID"].toString();
    data.timeStepInMinutes = obj["timeStepInMinutes"].toInt();
    data.fromTime = QDateTime::fromString(obj["fromTime"].toString() ,Qt::ISODate);
    data.toTime = QDateTime::fromString(obj["toTime"].toString() ,Qt::ISODate);
    return data;
}

WeatherParams::WeatherParams()
{

}

void WeatherParams::setObservationParameters(bool show_temperature, bool show_windspeed, bool show_cloudiness)
{
    this->t2m = show_temperature;
    this->ws_10min = show_windspeed;
    this->n_man = show_cloudiness;
}

void WeatherParams::setForecastParameters(bool show_temperature, bool show_windspeed)
{
    this->Temperature = show_temperature;
    this->WindSpeedMS = show_windspeed;
}

QString WeatherParams::toObservationHttpRequestUrl()
{
    QString urlStr  = baseUrl;
    urlStr.append(QString("&storedquery_id=%1").arg(this->queryID));

    if(this->fromTime.isValid())
    urlStr.append(QString("&starttime=%1").arg(this->fromTime.toString("yyyy-MM-ddThh:mm:ssZ")));
    if(this->toTime.isValid())
    urlStr.append(QString("&endtime=%1").arg(this->toTime.toString("yyyy-MM-ddThh:mm:ssZ")));
    urlStr.append(QString("&timestep=%1").arg(this->timeStepInMinutes));

    /*Build the observation parameters*/
    urlStr.append(QString("&parameters="));
    if(this->t2m) urlStr.append(QString("t2m"));
    if(this->ws_10min){
        if(this->t2m) urlStr.append(QString(","));
        urlStr.append(QString("ws_10min"));
    }
    if (this->n_man) {
        if(this->n_man) urlStr.append(QString(","));
        urlStr.append(QString("n_man"));
    }

    urlStr.append(QString("&bbox=%1,%2,%3,%4")
                  .arg(this->xMin)
                  .arg(this->yMin)
                  .arg(this->xMax)
                  .arg(this->yMax)
                  );

    urlStr.append(QString("&maxlocations=1"));

    return urlStr;
}

QString WeatherParams::toForecastHttpRequestUrl()
{
    QString urlStr  = baseUrl;
    urlStr.append(QString("&storedquery_id=%1").arg(this->queryID));

    if(this->fromTime.isValid())
    urlStr.append(QString("&starttime=%1").arg(this->fromTime.toString("yyyy-MM-ddThh:mm:ssZ")));
    if(this->toTime.isValid())
    urlStr.append(QString("&endtime=%1").arg(this->toTime.toString("yyyy-MM-ddThh:mm:ssZ")));
    urlStr.append(QString("&timestep=%1").arg(this->timeStepInMinutes));

    /*Build the observation parameters*/
    urlStr.append(QString("&parameters="));
    if(this->Temperature) urlStr.append(QString("Temperature"));
    if (this->WindSpeedMS) {
        if(this->Temperature) urlStr.append(QString(","));
        urlStr.append(QString("WindSpeedMS"));
    }

    urlStr.append(QString("&latlon=%1,%2")
                  .arg((this->yMin+this->yMax)/2)
                  .arg((this->xMin+this->xMax)/2)
                  );

    urlStr.append(QString("&maxlocations=1"));
    return urlStr;
}

