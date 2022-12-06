#include "forecastdatasample.h"

const QString &ForecastDataSample::getId() const
{
    return id;
}

void ForecastDataSample::setId(const QString & newId)
{
    id = newId;
}

const QString &ForecastDataSample::getType() const
{
    return type;
}

void ForecastDataSample::setType(const QString &newType)
{
    type = newType;
}

bool ForecastDataSample::getDaylight() const
{
    return daylight;
}

void ForecastDataSample::setDaylight(bool newDaylight)
{
    daylight = newDaylight;
}

double ForecastDataSample::getRoadTemp() const
{
    return roadTemp;
}

void ForecastDataSample::setRoadTemp(double newRoadTemp)
{
    roadTemp = newRoadTemp;
}

double ForecastDataSample::getAirTemp() const
{
    return airTemp;
}

void ForecastDataSample::setAirTemp(double newAirTemp)
{
    airTemp = newAirTemp;
}

double ForecastDataSample::getWindSpeed() const
{
    return windSpeed;
}

void ForecastDataSample::setWindSpeed(double newWindSpeed)
{
    windSpeed = newWindSpeed;
}

int ForecastDataSample::getWindDirection() const
{
    return windDirection;
}

void ForecastDataSample::setWindDirection(int newWindDirection)
{
    windDirection = newWindDirection;
}

const QString &ForecastDataSample::getOverallRoadCondition() const
{
    return overallRoadCondition;
}

void ForecastDataSample::setOverallRoadCondition(const QString &newOverallRoadCondition)
{
    overallRoadCondition = newOverallRoadCondition;
}

const QString &ForecastDataSample::getWeatherSymbol() const
{
    return weatherSymbol;
}

void ForecastDataSample::setWeatherSymbol(const QString &newWeatherSymbol)
{
    weatherSymbol = newWeatherSymbol;
}

const QString &ForecastDataSample::getReliability() const
{
    return reliability;
}

void ForecastDataSample::setReliability(const QString &newReliability)
{
    reliability = newReliability;
}


const QDateTime &ForecastDataSample::getTime() const
{
    return time;
}

void ForecastDataSample::setTime(const QDateTime &newTime)
{
    time = newTime;
}

ForecastConditionReason &ForecastDataSample::getForecastReason()
{
    return forecastReason;
}

void ForecastDataSample::setForecastReason(const ForecastConditionReason &newForecastReason)
{
    forecastReason = newForecastReason;
}

const QString &ForecastDataSample::getForecastName() const
{
    return forecastName;
}

void ForecastDataSample::setForecastName(const QString &newForecastType)
{
    forecastName = newForecastType;
}

ForecastDataSample::ForecastDataSample()
{

}

void ForecastConditionReason::setPrecipitationCondition(const QString &newPrecipitationCondition)
{
    precipitationCondition = newPrecipitationCondition;
}

void ForecastConditionReason::setRoadCondition(const QString &newRoadCondition)
{
    roadCondition = newRoadCondition;
}

void ForecastConditionReason::setWindCondition(const QString &newWindCondition)
{
    windCondition = newWindCondition;
}

void ForecastConditionReason::setFreezingRainCondition(bool newFreezingRainCondition)
{
    freezingRainCondition = newFreezingRainCondition;
}

void ForecastConditionReason::setWinterSlipperiness(bool newWinterSlipperiness)
{
    winterSlipperiness = newWinterSlipperiness;
}

void ForecastConditionReason::setVisibilityCondition(const QString &newVisibilityCondition)
{
    visibilityCondition = newVisibilityCondition;
}

void ForecastConditionReason::setFrictionCondition(const QString &newFrictionCondition)
{
    frictionCondition = newFrictionCondition;
}

const QString &ForecastConditionReason::getPrecipitationCondition() const
{
    return precipitationCondition;
}

const QString &ForecastConditionReason::getRoadCondition() const
{
    return roadCondition;
}

const QString &ForecastConditionReason::getWindCondition() const
{
    return windCondition;
}

bool ForecastConditionReason::getFreezingRainCondition() const
{
    return freezingRainCondition;
}

bool ForecastConditionReason::getWinterSlipperiness() const
{
    return winterSlipperiness;
}

const QString &ForecastConditionReason::getVisibilityCondition() const
{
    return visibilityCondition;
}

const QString &ForecastConditionReason::getFrictionCondition() const
{
    return frictionCondition;
}
