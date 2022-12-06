#ifndef WEATHERVIEW_H
#define WEATHERVIEW_H

#include <QWidget>
#include <QMessageBox>
#include <QDateTime>
#include <Data/appdatabase.h>
#include <Weather/weatherparams.h>
#include <Dialogs/waitdialog.h>
#include <weathercharthelper.h>
#include <Dialogs/savefiledialog.h>
#include <Dialogs/filepickerdialog.h>
#include <sstream>
#include <iomanip>

enum WeatherViewState{FORECAST,OBSERVATIONS};

namespace Ui {
class WeatherView;
}

class WeatherController;

class WeatherView : public QWidget
{
    Q_OBJECT

public:
    explicit WeatherView(QWidget *parent = nullptr);
    ~WeatherView();
    void setController(WeatherController *weatherController);
    void displayMaxTemperature(QPair<QDateTime, double> maximumTemperature);
    void displayMinTemperature(QPair<QDateTime, double> minimumTemperature);
    void displayMaxWind(QPair<QDateTime, double> maxWind);
    void displayMinWind(QPair<QDateTime, double> minWind);
    void displayMaxCloud(QPair<QDateTime, double> maxCloud);
    void displayMinCloud(QPair<QDateTime, double> minCloud);
    void displayTempAverage(double average);
    void displayWindAverage(double average);
    void displayCloudAverage(double average);
    void plotFetchedObservationsData(WeatherObservationData data);
    void plotSavedObservationsData(WeatherObservationData data);
    void plotFetchedForecastData(WeatherForecastData data);
    void plotSavedForecastData(WeatherForecastData data);
    void displayObservedTempEmpty();
    void displayObservedWindEmpty();
    void displayObservedCloudEmpty();
    void displayPredicetedTempEmpty();
    void displayPredictedWindEmpty();

    void displayWaitingDialog();
    void closeWaitingDialog();
    void saveUserInput();
    void restoreUserInput();
    void showDataChooserDialog(QStringList list);
    void showAlertDialog(QString message);
    void showWeatherSavedNoti();
    void showSavePngButton();
    void hideLabels();
    void showLabels();



public slots:
     void location_added();
protected:

    void resetSidebarLabels();

private slots:
    void onWeatherVisualizeButtonClicked();
    void onSaveButtonClicked();
    void onShowAverageButtonClicked();
    void onCompareToSavedDataClicked();
    void on_clearPushButton_clicked();
    void on_timeStepComboBox1_activated(int index);
    void on_savedLocationComboBox_textActivated(const QString &arg1);
    void on_saveAsPngButton_clicked();
    void on_dataCloseNotiButton_clicked();

private:
    Ui::WeatherView *ui;
    WeatherController *newController;
    QDateTime newStartTime;
    QDateTime newEndTime;
    QString displayText;
    int currentIndex = 0;
    QMap<QString, Location> locations;
//    FilePickerDialog *pickerDialog;
    WeatherParams currentParams;
    WaitDialog* waitingDialog;
    WeatherViewState viewState = OBSERVATIONS;
    WeatherChartHelper* linechart;

};

#endif // WEATHERVIEW_H
