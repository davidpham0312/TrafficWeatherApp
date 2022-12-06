#ifndef WEATHERPARAMS_H
#define WEATHERPARAMS_H

#include<QDateTime>
#include<QString>

#define QUERY_ID_WEATHER_DAILY  "fmi::observations::weather::daily::timevaluepair"
#define QUERY_ID_WEATHER_HOURLY "fmi::observations::weather::hourly::timevaluepair"
#define QUERY_ID_WEATHER        "fmi::observations::weather::timevaluepair"
#define QUERY_ID_FORECAST       "fmi::forecast::harmonie::surface::point::timevaluepair"
#define QUERY_ID_WEATHER_MONTHLY "fmi::observations::weather::monthly::timevaluepair"

//#define QUERY_ID_WEATHER_DAILY

class WeatherParams
{
private:
    // duration
    QDateTime fromTime;
    QDateTime toTime;
    // bbox
    int xMin = 21;
    int yMin = 61;
    int xMax = 22;
    int yMax = 62;
    // time step must be in minutes
    int timeStepInMinutes;
    // query id should be chosen based on timestep and whether observation or forecast
    QString queryID;

    // query parameters:
    /* observations */
    bool t2m = false; //observed temperature
    bool ws_10min = false; //observed wind
    bool n_man = false; //cloudiness
//    bool wd_10min = false; // wind direction (optional)

    /* forecast */
    bool Temperature = false; //predicted temperature
    bool WindSpeedMS = false; //predicted wind speed
//    bool WindDirection = false; //predicted wind direction (optional)

    const QString baseUrl = "https://opendata.fmi.fi/wfs?request=getFeature&version=2.0.0";
public:
    WeatherParams();

    // enable or disable certain observation parameters based on user input
    void setObservationParameters(bool show_temperature,
                                  bool show_windspeed,
                                  bool show_cloudiness);

    // enable or disable certain forecast parameters based on user input
    void setForecastParameters(bool show_temperature,
                               bool show_windspeed);

    QString toObservationHttpRequestUrl(); //only for observations
    QString toForecastHttpRequestUrl(); //only for forecasts
    const QDateTime &getFromTime() const;
    const QDateTime &getToTime() const;
    int getXMin() const;
    int getYMin() const;
    int getXMax() const;
    int getYMax() const;
    int getTimeStepInMinutes() const;
    const QString &getQueryID() const;
    void setFromTime(const QDateTime &newFromTime);
    void setToTime(const QDateTime &newToTime);
    void setXMin(int newXMin);
    void setYMin(int newYMin);
    void setXMax(int newXMax);
    void setYMax(int newYMax);
    // time steps are accepted only in minutes, any conversion must be done from the function user side
    void setTimeStepInMinutes(int newTimeStepInMinutes);
    // please supply one of the predefined QueryIDs QUERY_ID_WEATHER_XXX or QUERY_ID_FORECAST_XXX
    void setQueryID(const QString &newQueryID);


    //serialization
    const QByteArray toJsonObject();
    static WeatherParams fromJson(QByteArray &json);
};

#endif // WEATHERPARAMS_H
