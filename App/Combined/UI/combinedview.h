#ifndef COMBINEDVIEW_H
#define COMBINEDVIEW_H

#include <QWidget>
#include <Weather/weatherparams.h>
#include <Weather/UI/Model/weatherrepository.h>
#include <weathercharthelper.h>

namespace Ui {
class CombinedView;
}

class CombinedView : public QWidget
{
    Q_OBJECT

public:
    explicit CombinedView(QWidget *parent = nullptr);
    ~CombinedView();

private:
    Ui::CombinedView *ui;
    WeatherRepository* repo;
    WeatherChartHelper* chart;


public slots:
    void show_observations(WeatherParams params);
    void show_forecast(WeatherParams params);

};

#endif // COMBINEDVIEW_H
