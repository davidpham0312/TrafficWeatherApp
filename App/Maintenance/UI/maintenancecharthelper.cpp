#include "maintenancecharthelper.h"

MaintenanceChartHelper::MaintenanceChartHelper(QObject *parent)
    : QObject{parent}
{
    currentDataSet = new QBarSet("from DigiTraffic");
    savedDataSet = new QBarSet("from Saved Data");
    connect(currentDataSet,&QBarSet::hovered,this,&MaintenanceChartHelper::onHover);
    connect(savedDataSet,&QBarSet::hovered,this,&MaintenanceChartHelper::onHover);

    barSeries = new QBarSeries();

    barSeries->append(currentDataSet);
    barSeries->append(savedDataSet);

    chart = new QChart();
    chart->addSeries(barSeries);
    chart->setTitle("Hover over a bar to show task type");
    chart->setAnimationOptions(QChart::SeriesAnimations);

    categoriesAxis = new QBarCategoryAxis();
    chart->addAxis(categoriesAxis, Qt::AlignBottom);
    barSeries->attachAxis(categoriesAxis);

    axisY = new QValueAxis();
    chart->addAxis(axisY, Qt::AlignLeft);
    barSeries->attachAxis(axisY);
    axisY->setMin(0);
    axisY->setMax(0);
    axisY->setTickCount(10);

    chart->legend()->setVisible(true);
    chart->legend()->setAlignment(Qt::AlignBottom);
    chart->setAcceptHoverEvents(true);

    chartView = new QChartView();
    chartView->setChart(chart);
    chartView->setRenderHint(QPainter::Antialiasing);
    chartView->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

}

MaintenanceChartHelper::~MaintenanceChartHelper()
{
    delete chartView;
}

void MaintenanceChartHelper::appendCurrentData(QString type, int val)
{
    int index = dataIndexMapper.value(type,-1);
    if(index == -1){ //data not there yet
        index = dataIndexMapper.size();
        //append mapper
        dataIndexMapper.insert(type,index);
        //create new category for the data
        categoriesAxis->insert(index, type);

        savedDataSet->append(0);
        currentDataSet->append(val);
    }else{
        currentDataSet->replace(index,val);
    }

    //correct max value based on data
    if (val > axisY->max()) {
        axisY->setMax(val);
    }

}

void MaintenanceChartHelper::appendSavedData(QString type, int val)
{
    int index = dataIndexMapper.value(type,-1);
    if(index == -1){ //data not there yet
        index = dataIndexMapper.size();
        //append mapper
        dataIndexMapper.insert(type,index);
        //create new category for the data
        categoriesAxis->insert(index, type);

        currentDataSet->append(0);
        savedDataSet->append(val);
    }else{
        savedDataSet->replace(index,val);
    }

    //correct max value based on data
    if (val > axisY->max()) {
        axisY->setMax(val);
    }

}

void MaintenanceChartHelper::clear()
{
    this->dataIndexMapper.clear();
    barSeries->clear();
    categoriesAxis->clear();
    currentDataSet = new QBarSet("from DigiTraffic");
    savedDataSet = new QBarSet("from Saved Data");
    barSeries->append(currentDataSet);
    barSeries->append(savedDataSet);
    axisY->setMax(0);
}

QChartView *MaintenanceChartHelper::getChartView()
{
    return chartView;
}

#include <QFileDialog>
void MaintenanceChartHelper::saveToPng()
{
    QString fileName = QFileDialog::getSaveFileName(nullptr, tr("Save File"),
                               QDir::homePath(),
                               "PNG (*.png)");
    if(!fileName.isEmpty())
    chartView->grab().save(fileName.append(".png"),"PNG");
}


void MaintenanceChartHelper::onHover(bool status, int idx)
{
    QString type = dataIndexMapper.key(idx,"");
    if(status && !type.isEmpty()){
        QToolTip::showText(QCursor::pos(),type);
    }else{
        QToolTip::hideText();
    }
}
