#ifndef WEATHEROBSERVATIONDATA_H
#define WEATHEROBSERVATIONDATA_H

#include <QList>
#include <QPair>
#include <QDateTime>

class Xml2WeatherObservation;
class WeatherObservationData
{
private:
QList<QPair<QDateTime, double>> temperatureObservations;
QList<QPair<QDateTime, double>> windObservations;
QList<QPair<QDateTime, double>> cloudinessObservations;


QPair<QDateTime, double> minTemp;
QPair<QDateTime, double> minWind;
QPair<QDateTime, double> minCloudiness;
QPair<QDateTime, double> maxTemp;
QPair<QDateTime, double> maxWind;
QPair<QDateTime, double> maxCloudiness;
double avgTemp;
double avgWind;
double avgCloudiness;
QPair<QDateTime, double> newMax;
QPair<QDateTime, double> newMin;
double newAvr;

public:
    WeatherObservationData();

    const QList<QPair<QDateTime, double> > &getTemperatureObservations() const;
    const QList<QPair<QDateTime, double> > &getWindObservations() const;
    const QList<QPair<QDateTime, double> > &getCloudinessObservations() const;

    //this function does all the calculations
    void calculateMinMaxAvg(QList<QPair<QDateTime, double>> dataList);

    //these functions just give the requested values
    QPair<QDateTime, double> getMinTemp();
    QPair<QDateTime, double> getMinWind();
    QPair<QDateTime, double> getMinCloudiness();
    QPair<QDateTime, double> getMaxTemp();
    QPair<QDateTime, double> getMaxWind();
    QPair<QDateTime, double> getMaxCloudiness();
    double getAvgTemp();
    double getAvgWind();
    double getAvgCloudiness();



    friend Xml2WeatherObservation;
};

#endif // WEATHEROBSERVATIONDATA_H
