#include "json2forecastlist.h"

Json2ForecastList::Json2ForecastList()
{
    
}

void Json2ForecastList::process(QByteArray &json)
{
    QJsonDocument doc = QJsonDocument::fromJson(json);
    if(!doc.isEmpty()) parseForecastData(doc);
}


//process the json document from the request response, and store parsed data to an internal list
bool Json2ForecastList::parseForecastData(QJsonDocument &jsonDoc)
{
    QJsonArray arr = jsonDoc.object().value("weatherData").toArray();
    if (arr.isEmpty()) return false;

    foreach (auto entry, arr) { // first pass Array of weather data

        QJsonArray innerArr = entry.toObject().value("roadConditions").toArray();

        foreach (auto predition, innerArr) { // second pass: Array of preditction for a single location
            ForecastDataSample sample;
            QJsonObject obj = predition.toObject();
            if(!obj.isEmpty()){
                parseRoadCondition(obj, sample);
                sample.setId(entry.toObject().value("id").toString());
                forecastList.append(sample);
            }
        }
    }
    return true;
}

bool Json2ForecastList::parseRoadCondition(QJsonObject &json, ForecastDataSample &sample)
{
    QString time = json.value("time").toString();
    if (!time.isEmpty()) sample.setTime(QDateTime::fromString(time, Qt::ISODate));
    sample.setType(json.value("type").toString());
    sample.setForecastName(json.value("forecastName").toString());
    sample.setDaylight(json.value("daylight").toBool());
    sample.setRoadTemp(json.value("roadTemperature").toString("nan").toDouble());
    sample.setAirTemp(json.value("temperature").toString("nan").toDouble());
    sample.setWindSpeed(json.value("windSpeed").toDouble());
    sample.setWindDirection(json.value("windDirection").toInt());
    sample.setOverallRoadCondition(json.value("overallRoadCondition").toString());
    sample.setWeatherSymbol(json.value("weatherSymbol").toString());
    sample.setReliability(json.value("reliability").toString());

    QJsonObject obj = json.value("forecastConditionReason").toObject();
    parseForecastConditionReason(obj,sample);

    return true;
}

bool Json2ForecastList::parseForecastConditionReason(QJsonObject &json, ForecastDataSample &sample)
{
    sample.getForecastReason().setPrecipitationCondition(json.value("precipitationCondition").toString());
    sample.getForecastReason().setRoadCondition(json.value("roadCondition").toString());
    sample.getForecastReason().setWindCondition(json.value("windCondition").toString());
    sample.getForecastReason().setFreezingRainCondition(json.value("freezingRainCondition").toBool());
    sample.getForecastReason().setWinterSlipperiness(json.value("winterSlipperiness").toBool());
    sample.getForecastReason().setVisibilityCondition(json.value("visibilityCondition").toString());
    sample.getForecastReason().setFrictionCondition(json.value("frictionCondition").toString());
    return true;
}

void Json2ForecastList::clear()
{
    this->forecastList.clear();
}

QList<ForecastDataSample> Json2ForecastList::getForecastList()
{
    return this->forecastList;
}
