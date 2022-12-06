#include "mainwindow.h"
#include "./ui_mainwindow.h"
//messages includes
#include<functional>
#include<Messages/message.h>
#include<Messages/messagesparams.h>
#include<Messages/UI/Model/messagesrepository.h>
#include <Dialogs/locationdialog.h>

#include<QStandardItemModel>
#include<Forecast/UI/forecastcontroller.h>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    //setup user settings signal slot connections
    connect(ui->actionMaintenance_inputs, &QAction::triggered, this, &MainWindow::save_maintenance_clicked);
    connect(ui->actionMessages_inputs, &QAction::triggered, this, &MainWindow::save_messages_clicked);
    connect(ui->actionForecast_inputs, &QAction::triggered, this, &MainWindow::save_forecast_clicked);
    connect(ui->actionWeather_inputs, &QAction::triggered, this, &MainWindow::save_weather_clicked);
    connect(ui->actionMaintenance_inputs_2, &QAction::triggered, this, &MainWindow::restore_maintenance_clicked);
    connect(ui->actionMessages_inputs_2, &QAction::triggered, this, &MainWindow::restore_messages_clicked);
    connect(ui->actionForecast_inputs_2, &QAction::triggered, this, &MainWindow::restore_forecast_clicked);
    connect(ui->actionWeather_inputs_2, &QAction::triggered, this, &MainWindow::restore_weather_clicked);

    connect(ui->actionAdd_new_predefined_location, &QAction::triggered, this, &MainWindow::add_location_clicked);

    //connect on location chaned signal to slots
    connect(this, &MainWindow::newLocationAdded, ui->maintenanceUI, &MaintenanceView::location_added);
    connect(this, &MainWindow::newLocationAdded, ui->forecastUI, &ForecastView::location_added);
    connect(this, &MainWindow::newLocationAdded, ui->weatherFormWidget, &WeatherView::location_added);


    //connect maintenance and forecast to combined weather tab
    connect(ui->maintenanceUI->getController(), &MaintenanceController::weather_tab_show_observations,ui->combinedWeatherUI, &CombinedView::show_observations);
    connect(ui->forecastUI->forecastController(), &ForecastController::weather_tab_show_forecast,ui->combinedWeatherUI, &CombinedView::show_forecast);


}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_trafficButton_clicked()
{
    ui->stackedWidget->setCurrentIndex(0);
    changeButtonStyle(ui->trafficButton, 1, 1);
    changeButtonStyle(ui->weatherButton, 0, 2);
}


void MainWindow::on_weatherButton_clicked()
{
    ui->stackedWidget->setCurrentIndex(1);
    changeButtonStyle(ui->trafficButton, 0, 1);
    changeButtonStyle(ui->weatherButton, 1, 2);
}


void MainWindow::save_maintenance_clicked(bool)
{
    ui->maintenanceUI->saveUserInput();
}

void MainWindow::save_forecast_clicked(bool)
{
    ui->forecastUI->saveUserInput();
}

void MainWindow::save_weather_clicked(bool)
{
    ui->weatherFormWidget->saveUserInput();
}

void MainWindow::save_messages_clicked(bool)
{
    ui->messageBoxPlaceholder->saveUserInput();
}

void MainWindow::restore_maintenance_clicked(bool)
{
    ui->maintenanceUI->restoreUserInput();
}

void MainWindow::restore_forecast_clicked(bool)
{
    ui->forecastUI->restoreUserInput();
}

void MainWindow::restore_weather_clicked(bool)
{
    ui->weatherFormWidget->restoreUserInput();
}

void MainWindow::restore_messages_clicked(bool)
{
     ui->messageBoxPlaceholder->restoreUserInput();
}


void MainWindow::add_location_clicked(bool)
{
    LocationDialog dialog;
    int result = dialog.exec();
    if(result < 0) return;
    else emit newLocationAdded();
}


void MainWindow::changeButtonStyle(QPushButton *currentButton, int state, int buttonNumber)
{
    if(state == 1)
    {
        switch (buttonNumber) {
        case 1:
            currentButton->setStyleSheet("border-image: url(://MaterialDesignIcons/traffic-lightwhite.svg);");
            ui->trafficLabel->setStyleSheet("color: white");
            break;
        case 2:
            currentButton->setStyleSheet("border-image: url(://MaterialDesignIcons/weather_white.svg);");
            ui->weatherLabel->setStyleSheet("color: white");
            break;
        }
    }
    else if(state == 0)
    {

        switch (buttonNumber) {
        case 1:
            currentButton->setStyleSheet("border-image: url(://MaterialDesignIcons/traffic-light.svg);");
            ui->trafficLabel->setStyleSheet("color: black");
            break;
        case 2:
            currentButton->setStyleSheet("border-image: url(://MaterialDesignIcons/weather_black.svg);");
            ui->weatherLabel->setStyleSheet("color: black");
            break;
    }
    }
}


MessagesView *MainWindow::getMsgWindow(){
    return ui->messageBoxPlaceholder;
}

ForecastView *MainWindow::getForecastWindow(){
    return ui->forecastUI;
}
WeatherView *MainWindow::getWeatherWindow()
{
    return ui->weatherFormWidget;
}
