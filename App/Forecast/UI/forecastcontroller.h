#ifndef FORECASTCONTROLLER_H
#define FORECASTCONTROLLER_H

#include <QObject>
#include <Weather/weatherparams.h>
#include <Forecast/forecastdatasample.h>
#include <Forecast/forecastparams.h>
#include <Forecast/UI/Model/forecastrepository.h>
#include <Forecast/UI/forecastview.h>

class ForecastController : public QObject
{
    Q_OBJECT
public:
//    ForecastController(ForecastRepository forecastRepo, ForecastView *forecastView, QObject *parent = nullptr);
    ForecastController(ForecastView *forecastView, QObject *parent = nullptr);

public slots:
    void visualizeButtonClicked(const double minLongitude, const double minLatitude, const double maxLongitude, const double maxLatitude, const int hours);
    void saveButtonClicked(QString filename);
    void compareButtonClicked();
    void requestComparingData(QString filename);
    void checkUserInputs(const double minLongitude, const double maxLongitude, const double minLatitude, const double maxLatitude);
private:
    void onDataFetchedFromServer(QList<ForecastDataSample> forecastData, bool success);
    void onDataLoadedFromDB(QList<ForecastDataSample> forecastData, bool success);
private:
    ForecastView *forecastView_;
    ForecastRepository* forecastRepo_;
    ForecastParams forecastParams;

    QStringList fileList;
signals:
    void weather_tab_show_forecast(WeatherParams params);
};

#endif // FORECASTCONTROLLER_H
