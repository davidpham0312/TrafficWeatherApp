/*
 * Custom chart widget class, used for creating visualization charts for
 * the data pulled from different APIs
 *
 */
#ifndef WEATHERCHARTHELPER_H
#define WEATHERCHARTHELPER_H

#include "Weather/UI/Model/weatherforecastdata.h"
#include "Weather/UI/Model/weatherobservationdata.h"
#include <QWidget>
#include <QChart>
#include <QChartView>
#include <QLineSeries>
#include <QVBoxLayout>
#include <QValueAxis>
#include <QMap>
#include <QVector>
#include <QList>
#include <QLabel>
#include <QString>
#include <QDateTimeAxis>
#include <QDateTime>
#include <QSize>

class WeatherChartHelper : public QWidget
{
    Q_OBJECT
public:
    explicit WeatherChartHelper(QWidget *parent = nullptr);
    ~WeatherChartHelper();


private:/*new graph*/
    // line series for observations and forecast
    /*line series hold the actual data*/
    QLineSeries* currentObsLineSeries[3];
    QLineSeries* loadedObsLineSeries[3];
    QLineSeries* currentForecastLineSeries[2];
    QLineSeries* loadedForecastLineSeries[2];

    /* this is the axis that shows the dates for the
    different values */
    QDateTimeAxis*  dateTimeObservationsAxis;
    QValueAxis*     observationsYAxis;

    QDateTimeAxis*  dateTimeForecastAxis;
    QValueAxis*     forecastYAxis;

    //charts
    QChartView* observationsChartView;
    QChart* observationsChart;
    QChartView* forecastChartView;
    QChart* forecastChart;
public:
    //clears the series and shows the newly fetched data
    QChartView *plotWeatherCurrObservations(WeatherObservationData data);
    //clears the series and shows newly selected saved data
    QChartView *plotWeatherLoadedObservations(WeatherObservationData data);

    //clears the series and shows the newly fetched data
    QChartView *plotWeatherCurrForecast(WeatherForecastData data);
    //clears the series and shows newly selected saved data
    QChartView *plotWeatherLoadedForecast(WeatherForecastData data);

    //utility function to clear the graphs
    void clearWeatherGraphs();

    QChartView *getForecastChartView() const;

    QChartView *getObservationsChartView() const;
    void saveObservtionToPng();
    void saveForecastToPng();

private:
    void initWeatherCharts();
    QChartView *plotObservations(WeatherObservationData data, QLineSeries** series);
    QChartView *plotForecast(WeatherForecastData data, QLineSeries** series);

};

#endif // WEATHERCHARTHELPER_H
