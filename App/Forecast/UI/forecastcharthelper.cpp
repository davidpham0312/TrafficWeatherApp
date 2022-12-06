#include "forecastcharthelper.h"
ForecastChartHelper::ForecastChartHelper(QWidget *parent) : QWidget(parent)
{
    y1Axis = nullptr;
    y2Axis = nullptr;

    initializeChart();
}

//function that displays data on the x and one y axes
void ForecastChartHelper::displayData(QList<QMap<double, double>> dataPoints, QList<QString> &legendText, QString chartTitle,
                            QString xAxisName, QString yAxisName)
{
    max1YValue.clear();
    maxXValue.clear();
    //create X and Y axes
    addX1Axis(xAxisName);
    addY1Axis(yAxisName);
    //extract from list and add to series
    for(int i = 0; i < dataPoints.size(); ++i)
    {
        //add points to lineseries
            lineSeries1 = addPoints(dataPoints[i], false);
            lineSeries1->setName(legendText[i]);
        //add lineseries to chart
        chart_->addSeries(lineSeries1);

        //attach the points to axes
        //this is for better distribution on the x and y axis
        //although may not stay in the end
        lineSeries1->attachAxis(x1Axis);
        lineSeries1->attachAxis(y1Axis);

    }

    //set Axes min and max to be the max element in all series, so that all data is visible
    y1Axis->setMax(*std::max_element(max1YValue.begin(), max1YValue.end()));
    x1Axis->setMax(*std::max_element(maxXValue.begin(), maxXValue.end()));
    y1Axis->setMin(*std::min_element(min1YValue.begin(), min1YValue.end()));
    x1Axis->setMin(0);

    QFont font;
    font.setBold(true);
    font.setPixelSize(22);
    chart_->setTitleFont(font);
    chart_->setTitle(chartTitle);
    chart_->legend()->show();
}

void ForecastChartHelper::displayDataWithTwoYAxes(QList<QMap<double, double>> dataPoints1,
                                        QVector<QString> &legend1Text,
                                        QList<QMap<double, double>> dataPoints2,
                                        QVector<QString> &legend2Text,
                                        QString chartTitle,
                                        QString xAxisName,
                                        QString y1AxisName,
                                        QString y2AxisName )
{
    max1YValue.clear();
    max2YValue.clear();
    maxXValue.clear();
    //add axis
    addY2Axis(y2AxisName);
    addY1Axis(y1AxisName);
    addX1Axis(xAxisName);
    //add data from the first list for Y1 axis
    for(int i = 0; i < dataPoints1.size(); ++i)
    {
        lineSeries1 = addPoints(dataPoints1[i], false);
        chart_->addSeries(lineSeries1);
        lineSeries1[0].setName(legend1Text[i]);
        lineSeries1->attachAxis(x1Axis);
        lineSeries1->attachAxis(y1Axis);
    }
    //add data from the second list for Y2 axis
    for(int i = 0; i < dataPoints2.size(); ++i)
    {
        lineSeries2 = addPoints(dataPoints2[i], true);
        chart_->addSeries(lineSeries2);
        lineSeries2[0].setName(legend2Text[i]);
        lineSeries2->attachAxis(x1Axis);
        lineSeries2->attachAxis(y2Axis);
    }
    //set maximums on axis
    y1Axis->setMax(*std::max_element(max1YValue.begin(), max1YValue.end()));
    y1Axis->setMin(*std::min_element(min1YValue.begin(), min1YValue.end()));
    y2Axis->setMax(*std::max_element(max2YValue.begin(), max2YValue.end()));
    y2Axis->setMin(*std::min_element(min2YValue.begin(), min2YValue.end()));
    x1Axis->setMax(*std::max_element(maxXValue.begin(), maxXValue.end()));
    x1Axis->setMin(0);
    QFont font;
    font.setBold(true);
    font.setPixelSize(22);
    chart_->setTitleFont(font);
    chart_->setTitle(chartTitle);
    chart_->legend()->show();
}

void ForecastChartHelper::saveToPng()
{
    QString fileName = QFileDialog::getSaveFileName(nullptr, tr("Save File"),
                               QDir::homePath(),
                               "PNG (*.png)");
    if(!fileName.isEmpty())
        chartView_->grab().save(fileName.append(".png"),"PNG");
}
//function creates a chart view
//size adjustable depending on need
void ForecastChartHelper::initializeChart()
{
        chart_ = new QChart();
        chart_->legend()->hide();
        chartView_ = new QChartView(chart_, this);
        chartView_->resize(this->size());
        chartView_->setRenderHint(QPainter::Antialiasing);
        layout = new QVBoxLayout(this);
        layout->addWidget(chartView_, 5);
        this->show();


}

void ForecastChartHelper::addY1Axis(QString y1AxisName)
{
    y1Axis = new QValueAxis;
    y1Axis->setTitleText(y1AxisName);
    chart_->addAxis(y1Axis, Qt::AlignLeft);
}

void ForecastChartHelper::addY2Axis(QString y2AxisName)
{
    y2Axis = new QValueAxis;
    y2Axis->setTitleText(y2AxisName);
    chart_->addAxis(y2Axis, Qt::AlignRight);
}

void ForecastChartHelper::addX1Axis(QString xAxisName)
{
    x1Axis = new QValueAxis;
    x1Axis->setTitleText(xAxisName);
    chart_->addAxis(x1Axis, Qt::AlignBottom);
}
QLineSeries* ForecastChartHelper::addPoints(QMap<double, double> dataPoints, bool secondLine)
{
    QLineSeries *lineSeries = new QLineSeries;
    //Add data to lineseries
    for(auto i = dataPoints.begin(); i != dataPoints.end(); i++)
    {
        lineSeries->append(i.key(), i.value());
    }
    //extract maximum Y axis
    if(secondLine == true)
    {
        max2YValue.push_back(*std::max_element(dataPoints.begin(), dataPoints.end()));
        min2YValue.push_back(*std::min_element(dataPoints.begin(), dataPoints.end()));
    }
    else
    {
    max1YValue.push_back(*std::max_element(dataPoints.begin(), dataPoints.end()));
    min1YValue.push_back(*std::min_element(dataPoints.begin(), dataPoints.end()));
    }

    //extract maximum of X axis
    QMap<double, double>::Iterator i = dataPoints.begin();
    QMap<double, double>::Iterator j = dataPoints.begin();
    maxValue = i.key();
    std::advance(j, 1);
    for(; j != dataPoints.end(); ++j)
    {
        if(maxValue < j.key())
        {
            maxValue = j.key();
        }
    }
    maxXValue.push_back(maxValue);
    return lineSeries;
}
