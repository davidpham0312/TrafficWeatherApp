#ifndef WEATHERCONTROLLER_H
#define WEATHERCONTROLLER_H

#include <QObject>
#include <QDateTime>
#include <QList>
#include <QPair>
#include <QMessageBox>
#include <Weather/weatherparams.h>
#include <Weather/UI/Model/weatherrepository.h>
#include <Weather/UI/weatherview.h>
#include <Dialogs/waitdialog.h>
#include <weathercharthelper.h>
class WeatherController : public QObject
{
    Q_OBJECT
public:
    explicit WeatherController(WeatherRepository &weatherRepo, WeatherView *weatherView ,
                               QObject *parent = nullptr);
    ~WeatherController();
    void visualizeButtonClicked(QString timeStep, WeatherParams params);
    void saveButtonClicked(QString savedDataTitle, WeatherViewState state);
    void requestSavedFilesList(WeatherViewState state);
    void getSavedObservationData(QString savedDataTitle);
    void getSavedForcastData(QString savedDataTitle);
    void compareToSavedDataClicked(QString savedDataTitle, WeatherViewState state);
    void averageButtonClicked(WeatherViewState state);


protected:
    bool checkDateTime(QDateTime startTime, QDateTime endTime);

signals:
private:
    WeatherView *weatherView_;
    WeatherRepository &weatherRepo_;
    QList<QPair<QDateTime, double>> tempMap;
    QList<QPair<QDateTime, double>> windMap;
    QList<QPair<QDateTime, double>> cloudMap;
    QList<QPair<QDateTime, double>> tempPredMap;
    QList<QPair<QDateTime, double>> winPredMap;
    QDateTime startTime_;
    QDateTime endTime_;
    QString currentTimeStep;

};

#endif // WEATHERCONTROLLER_H
