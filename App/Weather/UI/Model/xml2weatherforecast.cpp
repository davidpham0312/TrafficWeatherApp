#include "xml2weatherforecast.h"

Xml2WeatherForecast::Xml2WeatherForecast(): Xml2WeatherDataConverter()
{
}

WeatherForecastData Xml2WeatherForecast::getForecast() const
{
    return forecast;
}


void Xml2WeatherForecast::populateParameter2ListMapper(QMap<QString, QList<QPair<QDateTime, double> > *> &mapper)
{
    mapper.insert("Temperature", &forecast.temperatureForecast);
    mapper.insert("WindSpeedMS", &forecast.windForecast);
    //new parameters and lists can be added here
}

