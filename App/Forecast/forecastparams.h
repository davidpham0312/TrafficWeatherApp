#ifndef FORECASTPARAMS_H
#define FORECASTPARAMS_H

#include <QString>
#include<QJsonObject>
#include<QJsonDocument>

class ForecastParams
{
    double minLongitude = 21;
    double minLatitude = 61;
    double maxLongitude = 22;
    double maxLatitude = 62;
    const QString messagesBaseUrl = "https://tie.digitraffic.fi/api/v3/data/road-conditions";

public:
    ForecastParams();
    double getMinLongitude() const;
    double getMinLatitude() const;
    double getMaxLongitude() const;
    double getMaxLatitude() const;
    void setMinLongitude(double newMinLongitude);
    void setMinLatitude(double newMinLatitude);
    void setMaxLongitude(double newMaxLongitude);
    void setMaxLatitude(double newMaxLatitude);
    QString toHttpRequestUrl();


    //serialization
    const QByteArray toJsonObject();
    static ForecastParams fromJson(QByteArray &json);
};

#endif // FORECASTPARAMS_H
