#ifndef WEATHERCALLBACKS_H
#define WEATHERCALLBACKS_H


#include "Weather/UI/Model/weatherobservationdata.h"
#include "Weather/UI/Model/weatherforecastdata.h"

typedef std::function<void(WeatherObservationData data, bool success)> OnWeatherObservationsDataReady;
typedef std::function<void(WeatherForecastData data, bool success)> OnWeatherForecastDataReady;
typedef std::function<void(bool success)> OnWeatherDataStored;

#endif // WEATHERCALLBACKS_H
