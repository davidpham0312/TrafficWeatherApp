#ifndef FORECASTCARDWIDGET_H
#define FORECASTCARDWIDGET_H

#include "Forecast/forecastdatasample.h"
#include <QWidget>

namespace Ui {
class ForecastCardWidget;
}

class ForecastCardWidget : public QWidget
{
    Q_OBJECT

public:
    explicit ForecastCardWidget(QString type, double airTemp, double roadTemp,
                                QString forecastName, QString condition, bool daylight,
                                double windSpeed, double windDir, QString reliability,
                                QString symbol, ForecastConditionReason allReasons, QWidget *parent = nullptr);
    ~ForecastCardWidget();
    void addDataToCard();
    void addComparingDataToCard();
    void addCurrentDataToCard();

    QWidget *getRoadTempCard();
    QWidget *getAirTempCard();
    QWidget *getRoadCondCard();
    QWidget *getDaylightCard();
    QWidget *getWindSpeedCard();
    QWidget *getWindDirCard();
    QWidget *getReliabilityCard();
    QWidget *getSymbolCard();
    QWidget *getReasonCard();

private:
    Ui::ForecastCardWidget *ui;
    QString type_;
    double airTemp_;
    double roadTemp_;
    QString forecastName_;
    QString condition_;
    bool daylight_;
    double windSpeed_;
    double windDir_;
    QString reliability_;
    QString symbol_;
    ForecastConditionReason allReasons_;

    void showOrHideReasons();
    void hideDefaultCards();
    void setCardAlignment();
};

#endif // FORECASTCARDWIDGET_H
