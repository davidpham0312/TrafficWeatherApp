#include "weatherobservationdata.h"

const QList<QPair<QDateTime, double> > &WeatherObservationData::getTemperatureObservations() const
{
    return temperatureObservations;
}

const QList<QPair<QDateTime, double> > &WeatherObservationData::getWindObservations() const
{
    return windObservations;
}

const QList<QPair<QDateTime, double> > &WeatherObservationData::getCloudinessObservations() const
{
    return cloudinessObservations;
}

void WeatherObservationData::calculateMinMaxAvg(QList<QPair<QDateTime, double>> dataList)
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

QPair<QDateTime, double> WeatherObservationData::getMinTemp()
{
    minTemp = newMin;
    return minTemp;
}

QPair<QDateTime, double> WeatherObservationData::getMinWind()
{
    minWind = newMin;
    return minWind;
}

QPair<QDateTime, double> WeatherObservationData::getMinCloudiness()
{
    minCloudiness = newMin;
    return minCloudiness;
}

QPair<QDateTime, double> WeatherObservationData::getMaxTemp()
{
    maxTemp = newMax;
    return maxTemp;
}

QPair<QDateTime, double> WeatherObservationData::getMaxWind()
{
    maxWind = newMax;
    return maxWind;
}

QPair<QDateTime, double> WeatherObservationData::getMaxCloudiness()
{
    maxCloudiness = newMax;
    return maxCloudiness;
}

double WeatherObservationData::getAvgTemp()
{
    avgTemp = newAvr;
    return avgTemp;
}

double WeatherObservationData::getAvgWind()
{
    avgWind = newAvr;
    return avgWind;
}

double WeatherObservationData::getAvgCloudiness()
{
    avgCloudiness = newAvr;
    return avgCloudiness;
}

WeatherObservationData::WeatherObservationData()
{

}
