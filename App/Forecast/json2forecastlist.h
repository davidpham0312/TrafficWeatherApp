#ifndef JSON2FORECASTLIST_H
#define JSON2FORECASTLIST_H
#include "forecastdatasample.h"
#include <QList>
#include <QByteArray>
#include <QJsonValue>
#include <QJsonArray>
#include <QJsonObject>
#include <QJsonDocument>
#include <QDateTime>

class Json2ForecastList
{
private:
    QList<ForecastDataSample> forecastList;


public:
    Json2ForecastList();
    void process(QByteArray& json);
    QList<ForecastDataSample> getForecastList();
    void clear();

private:
    bool parseForecastData(QJsonDocument& jsonDoc);

    bool parseRoadCondition(QJsonObject& roadConditionJson, ForecastDataSample& sample);
    bool parseForecastConditionReason(QJsonObject& contactJson, ForecastDataSample& sample);
};

#endif // JSON2FORECASTLIST_H
