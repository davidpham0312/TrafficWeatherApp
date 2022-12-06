#include "weathercharthelper.h"
#include <qalgorithms.h>
#include <QDebug>
#include <QFileDialog>
#include <QDir>
#include <QFont>
#include <QColor>

//customChartClass constructor
WeatherChartHelper::WeatherChartHelper(QWidget *parent) : QWidget(parent)
{
    for (int i = 0; i < 3; ++i) currentObsLineSeries[i] = new QLineSeries;
    for (int i = 0; i < 3; ++i) loadedObsLineSeries[i] = new QLineSeries;
    for (int i = 0; i < 2; ++i) currentForecastLineSeries[i] = new QLineSeries;
    for (int i = 0; i < 2; ++i) loadedForecastLineSeries[i] = new QLineSeries;
    dateTimeObservationsAxis = new QDateTimeAxis;
    dateTimeForecastAxis = new QDateTimeAxis;
    observationsYAxis = new QValueAxis;
    forecastYAxis = new  QValueAxis;
    initWeatherCharts();
}

WeatherChartHelper::~WeatherChartHelper()
{

}

QChartView *WeatherChartHelper::getObservationsChartView() const
{
    return observationsChartView;
}

void WeatherChartHelper::saveObservtionToPng()
{
    QString fileName = QFileDialog::getSaveFileName(nullptr, tr("Save File"),
                               QDir::homePath(),
                               "PNG (*.png)");
    if(!fileName.isEmpty())
        observationsChartView->grab().save(fileName.append(".png"),"PNG");
}

void WeatherChartHelper::saveForecastToPng()
{
    QString fileName = QFileDialog::getSaveFileName(nullptr, tr("Save File"),
                               QDir::homePath(),
                               "PNG (*.png)");
    if(!fileName.isEmpty())
        forecastChartView->grab().save(fileName.append(".png"),"PNG");
}

QChartView *WeatherChartHelper::getForecastChartView() const
{
    return forecastChartView;
}

//--------------------------------------------------------------


QChartView *WeatherChartHelper::plotWeatherCurrObservations(WeatherObservationData data)
{
    return plotObservations(data, currentObsLineSeries);
}

QChartView *WeatherChartHelper::plotWeatherLoadedObservations(WeatherObservationData data)
{

    return plotObservations(data, loadedObsLineSeries);
}

QChartView *WeatherChartHelper::plotWeatherCurrForecast(WeatherForecastData data)
{
    return plotForecast(data, currentForecastLineSeries);
}

QChartView *WeatherChartHelper::plotWeatherLoadedForecast(WeatherForecastData data)
{
    return plotForecast(data, loadedForecastLineSeries);
}

void WeatherChartHelper::clearWeatherGraphs()
{
    currentObsLineSeries[0]->clear();
    currentObsLineSeries[1]->clear();
    currentObsLineSeries[2]->clear();
    loadedObsLineSeries[0]->clear();
    loadedObsLineSeries[1]->clear();
    loadedObsLineSeries[2]->clear();
    currentForecastLineSeries[0]->clear();
    currentForecastLineSeries[1]->clear();
    loadedForecastLineSeries[0]->clear();
    loadedForecastLineSeries[1]->clear();
}

QChartView *WeatherChartHelper::plotObservations(WeatherObservationData data, QLineSeries**series)
{
    observationsChartView->show();
    forecastChartView->hide();
    //clear line series
    series[0]->clear();
    series[1]->clear();
    series[2]->clear();
    observationsChart->removeSeries(series[0]);
    observationsChart->removeSeries(series[1]);
    observationsChart->removeSeries(series[2]);
    //append with new data
    double max = -INFINITY;
    double min = INFINITY;
    foreach (auto item, data.getTemperatureObservations()) {
        if(item.second > max) max = item.second;
        if(item.second < min) min = item.second;
        series[0]->append(item.first.toMSecsSinceEpoch(), item.second);
    }

    foreach (auto item, data.getWindObservations()) {
        if(item.second > max) max = item.second;
        if(item.second < min) min = item.second;
        series[1]->append(item.first.toMSecsSinceEpoch(), item.second);
    }

    foreach (auto item, data.getCloudinessObservations()) {
        if(item.second > max) max = item.second;
        if (item.second < min) min = item.second;
        series[2]->append(item.first.toMSecsSinceEpoch(), item.second);
    }

    observationsYAxis->setMax(max + abs(max)*0.2);
    observationsYAxis->setMin(min - abs(min)*0.2);
    dateTimeObservationsAxis->setMin(data.getTemperatureObservations().first().first);
    dateTimeObservationsAxis->setMax(data.getTemperatureObservations().last().first);
    observationsChart->addSeries(series[0]);
    observationsChart->addSeries(series[1]);
    observationsChart->addSeries(series[2]);
    series[0]->attachAxis(observationsYAxis);
    series[1]->attachAxis(observationsYAxis);
    series[2]->attachAxis(observationsYAxis);

    return observationsChartView;
}

QChartView *WeatherChartHelper::plotForecast(WeatherForecastData data, QLineSeries **series)
{
    forecastChartView->show();
    observationsChartView->hide();
    //clear line series
    series[0]->clear();
    series[1]->clear();
    forecastChart->removeSeries(series[0]);
    forecastChart->removeSeries(series[1]);
    //append with new data
    double max = -INFINITY;
    double min = INFINITY;

    foreach (auto item, data.getTemperatureForecast()) {
        if(item.second > max) max = item.second;
        if(item.second < min) min = item.second;
        series[0]->append(item.first.toMSecsSinceEpoch(), item.second);
    }

    foreach (auto item, data.getWindForecast()) {
        if(item.second > max) max = item.second;
        if(item.second < min) min = item.second;
        series[1]->append(item.first.toMSecsSinceEpoch(), item.second);
    }

    forecastYAxis->setMax(max + abs(max)*0.2);
    forecastYAxis->setMin(min - abs(min)*0.2);
    dateTimeForecastAxis->setMin(data.getTemperatureForecast().first().first);
    dateTimeForecastAxis->setMax(data.getTemperatureForecast().last().first);
    forecastChart->addSeries(series[0]);
    forecastChart->addSeries(series[1]);
    series[0]->attachAxis(forecastYAxis);
    series[1]->attachAxis(forecastYAxis);
    return forecastChartView;
}

void WeatherChartHelper::initWeatherCharts()
{
    //init series
    QColor color;
    currentObsLineSeries[0]->setName("temperature(°C)");
    currentObsLineSeries[1]->setName("wind(m/s)");
    currentObsLineSeries[2]->setName("cloudiness");

    loadedObsLineSeries[0]->setColor(color.fromRgb(255, 69, 0));
    loadedObsLineSeries[0]->setName("saved temperature(°C)");
    loadedObsLineSeries[1]->setColor(color.fromRgb(139,0,0));
    loadedObsLineSeries[1]->setName("saved wind(m/s)");
    loadedObsLineSeries[2]->setColor(color.fromRgb(0,100,0));
    loadedObsLineSeries[2]->setName("saved cloudiness");

    currentForecastLineSeries[0]->setName("temperature(°C)");
    currentForecastLineSeries[1]->setName("wind(m/s)");
    loadedForecastLineSeries[0]->setName("saved temperature(°C)");
    loadedForecastLineSeries[1]->setName("saved wind(m/s)");

    //creat charts
    observationsChart = new QChart();
    forecastChart = new QChart();

    //add series to charts
    observationsChart->addSeries(currentObsLineSeries[0]);
    observationsChart->addSeries(currentObsLineSeries[1]);
    observationsChart->addSeries(currentObsLineSeries[2]);
    observationsChart->addSeries(loadedObsLineSeries[0] );
    observationsChart->addSeries(loadedObsLineSeries[1] );
    observationsChart->addSeries(loadedObsLineSeries[2] );
    observationsChart->legend()->show();
    QFont font;
    font.setBold(true);
    font.setPixelSize(22);
    observationsChart->setTitleFont(font);
    observationsChart->setTitle("Weather Observations");

    forecastChart->addSeries(currentForecastLineSeries[0]);
    forecastChart->addSeries(currentForecastLineSeries[1]);
    forecastChart->addSeries(loadedForecastLineSeries[0]);
    forecastChart->addSeries(loadedForecastLineSeries[1]);
    forecastChart->legend()->show();
    forecastChart->setTitleFont(font);
    forecastChart->setTitle("Weather Forecast");

    //configure the axis
    dateTimeObservationsAxis->setFormat("hh:mm/dd/MM");
    dateTimeObservationsAxis->setTitleText("Time");
    observationsChart->addAxis(dateTimeObservationsAxis, Qt::AlignBottom);

    dateTimeForecastAxis->setFormat("hh:mm/dd/MM");
    dateTimeForecastAxis->setTitleText("Time");
    forecastChart->addAxis(dateTimeForecastAxis, Qt::AlignBottom);

    observationsYAxis->setTitleText("Values");
    observationsChart->addAxis(observationsYAxis, Qt::AlignLeft);

    forecastYAxis->setTitleText("Values");
    forecastChart->addAxis(forecastYAxis, Qt::AlignLeft);

    currentObsLineSeries[0]->attachAxis(dateTimeObservationsAxis);
    currentObsLineSeries[1]->attachAxis(dateTimeObservationsAxis);
    currentObsLineSeries[2]->attachAxis(dateTimeObservationsAxis);
    loadedObsLineSeries[0]->attachAxis(dateTimeObservationsAxis);
    loadedObsLineSeries[1]->attachAxis(dateTimeObservationsAxis);
    loadedObsLineSeries[2]->attachAxis(dateTimeObservationsAxis);

    currentForecastLineSeries[0]->attachAxis(dateTimeForecastAxis);
    currentForecastLineSeries[1]->attachAxis(dateTimeForecastAxis);
    loadedForecastLineSeries[0]->attachAxis(dateTimeForecastAxis);
    loadedForecastLineSeries[1]->attachAxis(dateTimeForecastAxis);

    observationsChartView = new QChartView(this);
    observationsChartView->setChart(observationsChart);
    observationsChartView->setRenderHint(QPainter::Antialiasing);
    observationsChartView->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    forecastChartView = new QChartView(this);
    forecastChartView->setChart(forecastChart);
    forecastChartView->setRenderHint(QPainter::Antialiasing);
    forecastChartView->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    observationsChartView->hide();
    forecastChartView->hide();
}

