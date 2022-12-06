#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPushButton>
#include <Weather/UI/weathercontroller.h>
#include <QComboBox>
#include <ui_combinedview.h>
#include <ui_weatherview.h>
#include <ui_maintenanceview.h>
#include <ui_forecastview.h>
#include <ui_messagesview.h>
#include <ui_mainwindow.h>


QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE


class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void changeButtonStyle(QPushButton* currentButton, int state, int buttonNumber);
    MessagesView *getMsgWindow();
    ForecastView *getForecastWindow();
    WeatherView *getWeatherWindow();
private slots:
    void on_trafficButton_clicked();

    void on_weatherButton_clicked();


    void save_maintenance_clicked(bool);
    void save_forecast_clicked(bool);
    void save_weather_clicked(bool);
    void save_messages_clicked(bool);
    void restore_maintenance_clicked(bool);
    void restore_forecast_clicked(bool);
    void restore_weather_clicked(bool);
    void restore_messages_clicked(bool);


    void add_location_clicked(bool);


signals:
    void newLocationAdded();

private:
    Ui::MainWindow *ui;


};
#endif // MAINWINDOW_H
