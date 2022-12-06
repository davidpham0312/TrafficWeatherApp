#ifndef FORECASTCALLBACKS_H
#define FORECASTCALLBACKS_H

#include "forecastdatasample.h"
#include <QList>
using namespace std::placeholders;

#define member_func_to_ptr(ref_to_function, ptr_instance) std::bind(ref_to_function, ptr_instance, _1, _2)
//typedef void (*OnForecastDataReady)(QList<ForecastDataSample> samples, bool success);
typedef std::function<void(QList<ForecastDataSample> samples, bool success)>  OnForecastDataReady;
typedef void (*OnDataStored)(void);

#endif // FORECASTCALLBACKS_H
