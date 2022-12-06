#include "combinedview.h"
#include "ui_combinedview.h"

CombinedView::CombinedView(QWidget *parent)
    : QWidget(parent), ui(new Ui::CombinedView) {
  ui->setupUi(this);
  repo = new WeatherRepository(this);
  chart = new WeatherChartHelper(this);

  ui->combined_weather_chart_layout->addWidget(
      chart->getObservationsChartView());
  ui->combined_weather_chart_layout->addWidget(chart->getForecastChartView());
}

CombinedView::~CombinedView() {
  delete ui;
  delete repo;
}

void CombinedView::show_observations(WeatherParams params) {
  repo->fetchWeatherObservations(
      params, [this](WeatherObservationData data, bool) {
        if (data.getTemperatureObservations().isEmpty()) {
          ui->no_data_lable->show();
          chart->getObservationsChartView()->hide();
          chart->getForecastChartView()->hide();
        } else {
          ui->no_data_lable->hide();
          chart->plotWeatherCurrObservations(data);
        }
      });
}

void CombinedView::show_forecast(WeatherParams params) {
  repo->fetchWeatherForecast(params, [this](WeatherForecastData data, bool) {
    if (data.getTemperatureForecast().isEmpty()) {
      ui->no_data_lable->show();
      chart->getObservationsChartView()->hide();
      chart->getForecastChartView()->hide();
    } else {
      ui->no_data_lable->hide();
      chart->plotWeatherCurrForecast(data);
    }
  });
}
