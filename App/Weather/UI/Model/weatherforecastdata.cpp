#include "weatherforecastdata.h"

const QList<QPair<QDateTime, double> > &WeatherForecastData::getTemperatureForecast() const
{
    return temperatureForecast;
}

const QList<QPair<QDateTime, double> > &WeatherForecastData::getWindForecast() const
{
    return windForecast;
}

void WeatherForecastData::calculateMinMaxAvg(QList<QPair<QDateTime, double>> dataList)
{
    QList<QPair<QDateTime, double>>::Iterator i = std::find_if(dataList.begin(), dataList.end(), [](const QPair<QDateTime, double> &iter )
    {
        return !std::isnan(iter.second);
    });
    QList<QPair<QDateTime, double>>::Iterator j = std::find_if(dataList.begin(), dataList.end(), [](const QPair<QDateTime, double> &iter )
    {
        return !std::isnan(iter.second);
    });
    newMax.second = i->second;
    newMin.second = i->second;
    newMin.first = i->first;
    newMax.first = i->first;
    double sum = 0;
    newAvr = 0;
    std::advance(j, 1);
    for(; j != dataList.end(); ++j)
    {
        if(newMax.second < j->second)
        {
            newMax.second = j->second;
            newMax.first = j->first;
        }
        else if(newMin.second > j->second)
        {
            newMin.second = j->second;
            newMin.first = j->first;
        }

        if(!std::isnan(j->second))
        {
            sum = sum + j->second;
        }
    }
     auto k = dataList.begin();
     newAvr = (sum+k->second)/(dataList.size());
}

QPair<QDateTime, double> WeatherForecastData::getMinTemp()
{
    minTemp = newMin;
    return minTemp;
}

QPair<QDateTime, double> WeatherForecastData::getMinWind()
{
    minWind = newMin;
    return minWind;
}

QPair<QDateTime, double> WeatherForecastData::getMaxTemp()
{
    maxTemp = newMax;
    return maxTemp;
}

QPair<QDateTime, double> WeatherForecastData::getMaxWind()
{
    maxWind = newMax;
    return maxWind;

}

double WeatherForecastData::getAvgTemp()
{
    avgTemp = newAvr;
    return avgTemp;
}

double WeatherForecastData::getAvgWind()
{
    avgWind = newAvr;
    return avgWind;
}
