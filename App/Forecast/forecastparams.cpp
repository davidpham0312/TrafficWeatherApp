#include "forecastparams.h"

double ForecastParams::getMinLongitude() const
{
    return minLongitude;
}

double ForecastParams::getMinLatitude() const
{
    return minLatitude;
}

double ForecastParams::getMaxLongitude() const
{
    return maxLongitude;
}

double ForecastParams::getMaxLatitude() const
{
    return maxLatitude;
}

void ForecastParams::setMinLongitude(double newMinLongitude)
{
    minLongitude = newMinLongitude;
}

void ForecastParams::setMinLatitude(double newMinLatitude)
{
    minLatitude = newMinLatitude;
}

void ForecastParams::setMaxLongitude(double newMaxLongitude)
{
    maxLongitude = newMaxLongitude;
}

void ForecastParams::setMaxLatitude(double newMaxLatitude)
{
    maxLatitude = newMaxLatitude;
}

// generates a HTTP get request header from the stored forecast parameters
QString ForecastParams::toHttpRequestUrl()
{
    QString urlStr  = messagesBaseUrl;
    urlStr.append(QString("/%1").arg(this->minLongitude));
    urlStr.append(QString("/%1").arg(this->minLatitude));
    urlStr.append(QString("/%1").arg(this->maxLongitude));
    urlStr.append(QString("/%1").arg(this->maxLatitude));
    return urlStr;
}

const QByteArray ForecastParams::toJsonObject()
{
    QJsonObject obj;
    obj["minLat"] = this->minLatitude;
    obj["minLong"] = this->minLongitude;
    obj["maxLat"] = this->maxLatitude;
    obj["maxLong"] = this->maxLongitude;
    QJsonDocument doc(obj);
    return doc.toJson();
}

ForecastParams ForecastParams::fromJson(QByteArray &json)
{
    QJsonDocument doc = QJsonDocument::fromJson(json);
    QJsonObject obj = doc.object();
    ForecastParams data;
    data.minLatitude = obj["minLat"].toDouble();
    data.minLongitude = obj["minLong"].toDouble();
    data.maxLatitude = obj["maxLat"].toDouble();
    data.maxLongitude = obj["maxLong"].toDouble();
    return data;
}


ForecastParams::ForecastParams()
{

}
