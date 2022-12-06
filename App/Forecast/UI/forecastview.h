#ifndef FORECASTVIEW_H
#define FORECASTVIEW_H

#include <QFrame>
#include <QInputDialog>
#include <QWidget>
#include "forecastcharthelper.h"
#include <Forecast/forecastdatasample.h>
#include <Forecast/UI/forecastcardwidget.h>
#include <Forecast/forecastparams.h>
#include <Data/appdatabase.h>
#include <Dialogs/waitdialog.h>

namespace Ui { class ForecastView; }

class ForecastController;

class ForecastView : public QWidget
{
    Q_OBJECT

public:
    ForecastView(QWidget *parent = nullptr);
    ~ForecastView();
    void displayCurrentForecastCard(QList<ForecastDataSample> allForecastData);
    void displayComparingForecastCard(QList<ForecastDataSample> selectedForecastData);
    void displayCurrentForecastGraphs(QList<ForecastDataSample> allForecastData);
    void displayComparingForecastGraphs(QList<ForecastDataSample> allForecastData);
    void setController(ForecastController *forecastController);
    void saveUserInput();
    void restoreUserInput();
    void showDataChooserDialog(QStringList &items);
    void showAlertDialog(QString message);
    void showWaitingDialog();
    void closeWaitingDialog();
    void showSaveDataDialog();
    void enableButtons();
    void enableSaveButton();
    void showTitle();
    bool checkInputBeforeSave(ForecastParams param);
    void showSaveSuccessNoti();
    void showSaveButton();

    ForecastController *forecastController() const;

public slots:
    void location_added();

private slots:

    void on_forecastVisualizeButton_clicked();

    void on_forecastSaveDataButton_clicked();

    void on_forecastCompareButton_clicked();

    void on_roadTempCheckbox_stateChanged(int arg1);

    void on_airTempCheckBox_stateChanged(int arg1);

    void on_reliabilityCheckbox_stateChanged(int arg1);

    void on_windDirCheckbox_stateChanged(int arg1);

    void on_windSpeedCheckbox_stateChanged(int arg1);

    void on_symbolCheckbox_stateChanged(int arg1);

    void on_daylightCheckbox_stateChanged(int arg1);

    void on_roadCondCheckbox_stateChanged(int arg1);

    void on_reasonCheckbox_stateChanged(int arg1);

    void on_showAllRButton_clicked();

    void on_hideAllRButton_clicked();

    void on_savedDropdown_textActivated(const QString &arg1);

    void on_closeNotiButton_clicked();

    void on_saveTempButton_clicked();

    void on_saveWindButton_clicked();

private:
    Ui::ForecastView *ui;
    ForecastController *forecastController_;
    ForecastCardWidget *currentCard;
    ForecastCardWidget *comparingCard;
    QList<QMap<double, double>> roadAirData;
    QList<QMap<double, double>> windSpeedData;
    QList<QMap<double, double>> windDirData;
    ForecastChartHelper *tempChart;
    ForecastChartHelper *windChart;

    WaitDialog* waitingDialog;
    ForecastParams currentParams;
    QMap<QString, Location> locations;

    void hideAllLayouts();
    void emptyFrame(QFrame *frame);
    ForecastDataSample selectDisplayData(QString hours, QList<ForecastDataSample> forecastDataList);

    void setEnableCheckBoxes(bool isEnabled);
    void setCheckBoxesState(bool isChecked);

    ForecastCardWidget *getCardWidget(ForecastDataSample s);
    void setCurrentRoadAirDataPoint(QList<ForecastDataSample> allForecastData);
    void setCurrentWindDataPoint(QList<ForecastDataSample> allForecastData);
    void setComparingRoadAirDataPoint(QList<ForecastDataSample> allForecastData);
    void setComparingWindDataPoint(QList<ForecastDataSample> allForecastData);
    QString getFilename(QString fileDirectory);
    void initWaitingDialog();

    void displayRoadAirChart();
    void displayWindChart();
};

#endif // FORECASTVIEW_H
