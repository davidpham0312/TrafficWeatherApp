#ifndef FORECASTDATA_H
#define FORECASTDATA_H

#include <QString>
#include <QList>
#include <QDateTime>

class ForecastConditionReason{
private:
    QString precipitationCondition;
    QString roadCondition;
    QString windCondition;
    bool freezingRainCondition;
    bool winterSlipperiness;
    QString visibilityCondition;
    QString frictionCondition;

public:
    const QString &getPrecipitationCondition() const;
    const QString &getRoadCondition() const;
    const QString &getWindCondition() const;
    bool getFreezingRainCondition() const;
    bool getWinterSlipperiness() const;
    const QString &getVisibilityCondition() const;
    const QString &getFrictionCondition() const;
    void setPrecipitationCondition(const QString &newPrecipitationCondition);
    void setRoadCondition(const QString &newRoadCondition);
    void setWindCondition(const QString &newWindCondition);
    void setFreezingRainCondition(bool newFreezingRainCondition);
    void setWinterSlipperiness(bool newWinterSlipperiness);
    void setVisibilityCondition(const QString &newVisibilityCondition);
    void setFrictionCondition(const QString &newFrictionCondition);
};


class ForecastDataSample
{
private:
    QString id;
    QDateTime time;
    QString type;
    QString forecastName;
    bool daylight;
    double roadTemp;
    double airTemp;
    double windSpeed;
    int windDirection;
    QString overallRoadCondition;
    QString weatherSymbol;
    QString reliability;
    ForecastConditionReason forecastReason;

public:
    ForecastDataSample();
    const QString &getId() const;
    void setId(const QString & newId);
    const QString &getType() const;
    void setType(const QString &newType);
    bool getDaylight() const;
    void setDaylight(bool newDaylight);
    double getRoadTemp() const;
    void setRoadTemp(double newRoadTemp);
    double getAirTemp() const;
    void setAirTemp(double newAirTemp);
    double getWindSpeed() const;
    void setWindSpeed(double newWindSpeed);
    int getWindDirection() const;
    void setWindDirection(int newWindDirection);
    const QString &getOverallRoadCondition() const;
    void setOverallRoadCondition(const QString &newOverallRoadCondition);
    const QString &getWeatherSymbol() const;
    void setWeatherSymbol(const QString &newWeatherSymbol);
    const QString &getReliability() const;
    void setReliability(const QString &newReliability);
    const QDateTime &getTime() const;
    void setTime(const QDateTime &newTime);
    ForecastConditionReason &getForecastReason();
    void setForecastReason(const ForecastConditionReason &newForecastReason);
    const QString &getForecastName() const;
    void setForecastName(const QString &newForecastType);
};

#endif // FORECASTDATA_H
