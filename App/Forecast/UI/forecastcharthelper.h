#ifndef FORECASTCHARTHELPER_H
#define FORECASTCHARTHELPER_H

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
#include <QFileDialog>
#include <QFont>
class ForecastChartHelper : public QWidget
{
    Q_OBJECT
public:
    explicit ForecastChartHelper(QWidget *parent = nullptr);
    void displayData(QList<QMap<double, double>> dataPoints,QList<QString> &legendText, QString chartTitle,
                     QString xAxisName, QString yAxisName); //function to display data on 1 Y axis
    //function to display data on Y axes
    void displayDataWithTwoYAxes(QList<QMap<double, double>> dataPoints1, QVector<QString> &legend1Text,
                                 QList<QMap<double, double>> dataPoints2,
                                 QVector<QString> &legend2Text,QString chartTitle,
                                 QString xAxisName, QString y1AxisName, QString y2AxisName );
    void saveToPng();
signals:
protected:
    //function that initializes the chart
    void initializeChart();
    //functions define axes
    void addY1Axis(QString y1AxisName);
    void addY2Axis(QString xy2AxisName);
    void addX1Axis(QString xAxisName);

    //add points to lineseries
    QLineSeries* addPoints(QMap<double, double> dataPoints, bool secondLine);
private:
    QLineSeries *lineSeries1;
    QLineSeries *lineSeries2;
    QChartView * chartView_;
    QSize newSize;
    QChart *chart_;
    QLabel *chartPlaceHolder_;
    QValueAxis *x1Axis;
    QValueAxis *y1Axis;
    QValueAxis *y2Axis;
    double maxValue = 0;
    double weatherMax = 0;
    QVector<double> yAxisMaxVal = {};
    QVector<double> max1YValue = {};
    QVector<double> maxXValue = {};
    QVector<double> min1YValue = {};
    QVector<double> minXValue = {};
    QVector<double> max2YValue = {};
    QVector<double> min2YValue = {};
    QVBoxLayout *layout;
};

#endif // FORECASTCHARTHELPER_H
