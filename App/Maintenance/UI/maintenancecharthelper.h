#ifndef MAINTENANCECHARTHELPER_H
#define MAINTENANCECHARTHELPER_H

#include <QMap>
#include <QObject>
#include <QChart>
#include <QBarSet>
#include <QBarSeries>
#include <QStackedBarSeries>
#include <QValueAxis>
#include <QBarCategoryAxis>
#include <QChartView>
#include <QToolTip>

class MaintenanceChartHelper : public QObject
{
    Q_OBJECT
public:
    explicit MaintenanceChartHelper(QObject *parent = nullptr);
    ~MaintenanceChartHelper();
    void appendCurrentData(QString type, int val);
    void appendSavedData(QString type, int val);
    void clear();
    QChartView* getChartView();
    void saveToPng();

private:
    QChartView* chartView;
    QChart* chart;
    QBarSet* currentDataSet;
    QBarSet* savedDataSet;
    QValueAxis *axisY;
    QBarCategoryAxis *categoriesAxis;
    QMap<QString, int> dataIndexMapper;
    QBarSeries * barSeries;

private slots:
    void onHover(bool status, int idx);

};

#endif // MAINTENANCECHARTHELPER_H
