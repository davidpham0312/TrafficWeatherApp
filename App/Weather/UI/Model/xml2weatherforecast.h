#ifndef XML2WEATHERFORECAST_H
#define XML2WEATHERFORECAST_H


#include <QMap>
#include <QByteArray>
#include <QXmlStreamReader>
#include "weatherforecastdata.h"
#include "xml2weatherdataconverter.h"


class Xml2WeatherForecast : public Xml2WeatherDataConverter
{
private:
    WeatherForecastData forecast;
public:
    Xml2WeatherForecast();
    WeatherForecastData getForecast() const;
protected:
    void populateParameter2ListMapper(QMap<QString, QList<QPair<QDateTime,double>>* > &parameter2ListMapper);
};


#endif // XML2WEATHERFORECAST_H
