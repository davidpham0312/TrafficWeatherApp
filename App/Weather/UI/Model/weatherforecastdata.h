#ifndef WEATHERFORECASTDATA_H
#define WEATHERFORECASTDATA_H

#include<QDateTime>
#include<QPair>

class Xml2WeatherForecast;
class WeatherForecastData{
    QList<QPair<QDateTime,double>> temperatureForecast;
    QList<QPair<QDateTime,double>> windForecast;
    friend Xml2WeatherForecast;

public:
    const QList<QPair<QDateTime, double> > &getTemperatureForecast() const;
    const QList<QPair<QDateTime, double> > &getWindForecast() const;


    QPair<QDateTime, double> minTemp;
    QPair<QDateTime, double> minWind;
    QPair<QDateTime, double> maxTemp;
    QPair<QDateTime, double> maxWind;
    double avgTemp;
    double avgWind;
    QPair<QDateTime, double> newMax;
    QPair<QDateTime, double> newMin;
    double newAvr;

    //this function does all the calculations
    void calculateMinMaxAvg(QList<QPair<QDateTime, double>> dataList);

    //these functions just give the requested values
    QPair<QDateTime, double> getMinTemp();
    QPair<QDateTime, double> getMinWind();
    QPair<QDateTime, double> getMaxTemp();
    QPair<QDateTime, double> getMaxWind();
    double getAvgTemp();
    double getAvgWind();
};

#endif // WEATHERFORECASTDATA_H
