#include "weatherview.h"
#include "ui_weatherview.h"
#include "Weather/UI/weathercontroller.h"

WeatherView::WeatherView(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::WeatherView),
    newController{nullptr}
{
    ui->setupUi(this);
//    hideCharts();
    linechart = new WeatherChartHelper(this);
    ui->chartLayout->addWidget(linechart->getObservationsChartView());
    ui->chartLayout->addWidget(linechart->getForecastChartView());

    //connections
    connect(ui->weatherSaveDataButton, SIGNAL(clicked()), this, SLOT(onSaveButtonClicked()));
    connect(ui->weatherVisualizeButton, SIGNAL(clicked()), this, SLOT(onWeatherVisualizeButtonClicked()));
    connect(ui->showAvrTempButton, SIGNAL(clicked()), this, SLOT(onShowAverageButtonClicked()));
    connect(ui->weatherCompareButton, SIGNAL(clicked()), this, SLOT(onCompareToSavedDataClicked()));

    //set datetime to current
    ui->startDateTimeEdit->setDateTime(QDateTime::currentDateTime());
    ui->endDateTimeEdit->setDateTime(QDateTime::currentDateTime());

    locations = AppDatabase::getInstance().getLocationsList();
    ui->savedLocationComboBox->addItems(locations.keys());

    waitingDialog = new WaitDialog(this);

    ui->weatherSaveDataButton->setEnabled(false);
    ui->showAvrTempButton->setEnabled(false);
    ui->saveAsPngButton->hide();
    ui->dataSaveSuccessNoti->hide();
}

WeatherView::~WeatherView()
{
    delete ui;
}

/**
 * @brief WeatherView::onWeatherVisualizeButtonClicked
 * Function to start fetching the data from the API
 * and enable visualize by the controller
 */
void WeatherView::onWeatherVisualizeButtonClicked()
{

   //read start and end time from QDateTime input
   resetSidebarLabels();
   WeatherParams params;
   newStartTime = ui->startDateTimeEdit->dateTime();
   newEndTime = ui->endDateTimeEdit->dateTime();
   params.setFromTime(newStartTime);
   params.setToTime(newEndTime);
   params.setXMin(ui->xCoordTextBox->text().toInt());
   params.setXMax(ui->zCoordTextBox->text().toInt());
   params.setYMin(ui->yCoordTextBox->text().toInt());
   params.setYMax(ui->pCoordTextBox->text().toInt());
   if(!ui->weatherSaveDataButton->isEnabled())
   {
       ui->weatherSaveDataButton->setEnabled(true);
   }
   if(!ui->showAvrTempButton->isEnabled())
   {
       ui->showAvrTempButton->setEnabled(true);
   }
   if (newController != nullptr){
        newController->visualizeButtonClicked(ui->timeStepComboBox1->currentText() ,
                                              params);
   }


}
/**
 * @brief WeatherView::setController
 * set weather controller
 * @param weatherController
 */
void WeatherView::setController(WeatherController *weatherController)
{
    newController = weatherController;
}

/*******************Display data***************************/
/**
 * @brief WeatherView::displayWaitingDialog
 * Function that displays the waiting dialog
 */
void WeatherView::displayWaitingDialog()
{
    waitingDialog->showDialog();
}
/**
 * @brief WeatherView::closeWaitingDialog
 * Function that closes the waiting dialog
 */
void WeatherView::closeWaitingDialog()
{
    waitingDialog->closeDialog();
}

/**
 * @brief WeatherView::displayMaxTemperature
 * function to display maximum temperature found and the date
 * @param maximumTemperature: QPair of time and maximum temperature
 */
void WeatherView::displayMaxTemperature(QPair<QDateTime, double> maximumTemperature)
{
    QString dateTime = maximumTemperature.first.toString("yyyy-MM-dd HH:mm:ss");
    QString value =  QString::number(maximumTemperature.second);
    ui->tempLabelValue->clear();
    ui->tempLabelValue->setText("Date: "+dateTime+"\nMaximum: "+value+" ˚C");
}

/**
 * @brief WeatherView::displayMinTemperature
 * function to display minimum temeprature found
 * @param minimumTemperature: QPair of time and minimum temperature
 */
void WeatherView::displayMinTemperature(QPair<QDateTime, double> minimumTemperature)
{
    QString dateTime = minimumTemperature.first.toString("yyyy-MM-dd HH:mm:ss");
    QString value =  QString::number(minimumTemperature.second);
    ui->minTempLabel->clear();
    ui->minTempLabel->setText("Date: "+dateTime+"\nMinimum: "+value+" ˚C");
}

/**
 * @brief WeatherView::displayMaxWind
 * function to display maximum wind found
 * @param maxWind: QPair of time and maximum wind
 */
void WeatherView::displayMaxWind(QPair<QDateTime, double> maxWind)
{
    QString dateTime = maxWind.first.toString("yyyy-MM-dd HH:mm:ss");
    QString value =  QString::number(maxWind.second);
    ui->windSpeedLabel->clear();
    ui->windSpeedLabel->setText("Date: "+dateTime+"\nMaximum: "+value+" m/s");
}

/**
 * @brief WeatherView::displayMinWind
 * function to display minimum wind found
 * @param minWind: QPair of time and minimum wind
 */
void WeatherView::displayMinWind(QPair<QDateTime, double> minWind)
{
    QString dateTime = minWind.first.toString("yyyy-MM-dd HH:mm:ss");
    QString value =  QString::number(minWind.second);
    ui->minWindLabelValue->clear();
    ui->minWindLabelValue->setText("Date: "+dateTime+"\nMinimum: "+value+" m/s");
}

/**
 * @brief WeatherView::displayMaxCloud
 * function to display maximum cloud coverage
 * @param maxCloud: QPair of time and maximum cloud coverage
 */
void WeatherView::displayMaxCloud(QPair<QDateTime, double> maxCloud)
{
    QString dateTime = maxCloud.first.toString("yyyy-MM-dd HH:mm:ss");
    QString value =  QString::number(maxCloud.second);
    ui->maxCloudinessLabel->clear();
    ui->maxCloudinessLabel->setText("Date: "+dateTime+"\nMaximum: "+value);
}

/**
 * @brief WeatherView::displayMinCloud
 * function to display the minimum cloud coverage found
 * @param minCloud: QPair of time and minimum cloud coverage
 */
void WeatherView::displayMinCloud(QPair<QDateTime, double> minCloud)
{
    QString dateTime = minCloud.first.toString("yyyy-MM-dd HH:mm:ss");
    QString value =  QString::number(minCloud.second);
    ui->minCloudLabelValue->clear();
    ui->minCloudLabelValue->setText("Date: "+dateTime+"\nMinimum: "+value);
}

/**
 * @brief WeatherView::displayAverage
 * display temperature average
 * @param average: double value
 */
void WeatherView::displayTempAverage(double average)
{
    ui->avrTempLabel->clear();
    std::stringstream ss;
    ss << std::setprecision(2) << std::fixed << average;
    double val = std::stod(ss.str());
    QString value = QString::number(val);
    ui->avrTempLabel->setText("Average: "+value+" ˚C");
}
/**
 * @brief WeatherView::displayWindAverage
 * display wind average
 * @param average: double value
 */
void WeatherView::displayWindAverage(double average)
{
    ui->avrWindLabel->clear();
    std::stringstream ss;
    ss << std::setprecision(2) << std::fixed << average;
    double val = std::stod(ss.str());
    QString value = QString::number(val);
    ui->avrWindLabel->setText("Average: "+value+" m/s");
}

/**
 * @brief WeatherView::displayCloudAverage
 * display cloudiness average
 * @param average: double value
 */
void WeatherView::displayCloudAverage(double average)
{
    ui->avrCloudLabel->clear();
    std::stringstream ss;
    ss << std::setprecision(2) << std::fixed << average;
    double val = std::stod(ss.str());
    QString value = QString::number(val);
    ui->avrCloudLabel->setText("Average: "+value);
}

void WeatherView::displayObservedTempEmpty()
{
    ui->tempLabelValue->clear();
    ui->minTempLabel->clear();
    ui->avrTempLabel->clear();
    ui->tempLabelValue->setText("No data found");
    ui->minTempLabel->setText("No data found");
    ui->avrTempLabel->setText("No data found");

}

void WeatherView::displayObservedWindEmpty()
{
    ui->windSpeedLabel->clear();
    ui->minWindLabelValue->clear();
    ui->avrWindLabel->clear();
    ui->windSpeedLabel->setText("No data found");
    ui->minWindLabelValue->setText("No data found");
    ui->avrWindLabel->setText("No data found");
}

void WeatherView::displayObservedCloudEmpty()
{
    ui->maxCloudinessLabel->clear();
    ui->minCloudLabelValue->clear();
    ui->avrCloudLabel->clear();
    ui->maxCloudinessLabel->setText("No data found");
    ui->minCloudLabelValue->setText("No data found");
    ui->avrCloudLabel->setText("No data found");
}

void WeatherView::displayPredicetedTempEmpty()
{
    ui->tempLabelValue->clear();
    ui->minTempLabel->clear();
    ui->avrTempLabel->clear();
    ui->tempLabelValue->setText("No data found");
    ui->minTempLabel->setText("No data found");
    ui->avrTempLabel->setText("No data found");
}

void WeatherView::displayPredictedWindEmpty()
{
    ui->windSpeedLabel->clear();
    ui->minWindLabelValue->clear();
    ui->avrWindLabel->clear();
    ui->windSpeedLabel->setText("No data found");
    ui->minWindLabelValue->setText("No data found");
    ui->avrWindLabel->setText("No data found");
}


/**********************Save and Comapre**********************/

void WeatherView::onSaveButtonClicked()
{

    int ok;

    SaveFileDialog dialog(this,
                          "WEATHER: "+QDateTime::currentDateTime().toString());
    ok = dialog.exec();

    if (ok > 0){
        if (newController != nullptr){
            newController->saveButtonClicked(dialog.getFileName(), viewState);
        }
    }

}


void WeatherView::onCompareToSavedDataClicked()
{
    newController->requestSavedFilesList(viewState);
    if(!ui->showAvrTempButton->isEnabled())
    {
        ui->showAvrTempButton->setEnabled(true);
    }
}

void WeatherView::showDataChooserDialog(QStringList items)
{
    int ok;
    FilePickerDialog dialog(this, items);
    ok = dialog.exec();
    if(ok > 0) {
        newController->compareToSavedDataClicked(dialog.getSelectedFileName(), viewState);
    }
}


void WeatherView::onShowAverageButtonClicked()
{

    newController->averageButtonClicked(viewState);
}

void WeatherView::resetSidebarLabels()
{
    ui->tempLabelValue->clear();
    ui->tempLabelValue->setText("Maximum Observed Temperature");
    ui->windSpeedLabel->clear();
    ui->windSpeedLabel->setText("Maximum Observed Wind Speed");
    ui->maxCloudinessLabel->clear();
    ui->maxCloudinessLabel->setText("Maximum Observed Cloudiness");
    ui->minTempLabel->clear();
    ui->minTempLabel->setText("Minimum Observed Temperature");
    ui->minWindLabelValue->clear();
    ui->minWindLabelValue->setText("Minimum Observed Wind Speed");
    ui->minCloudLabelValue->clear();
    ui->minCloudLabelValue->setText("Minimum Observed Cloudiness");
    ui->avrTempLabel->clear();
    ui->avrTempLabel->setText("Average Temperature");
    ui->avrWindLabel->clear();
    ui->avrWindLabel->setText("Average Wind Speed");
    ui->avrCloudLabel->clear();
    ui->avrCloudLabel->setText("Average Cloudiness");
    showLabels();
}


void WeatherView::hideLabels()
{
    ui->cloudinessLabel->hide();
    ui->maxCloudinessLabel->hide();
    ui->cloudinessIconLabel->hide();
    ui->minCloudLabelValue->hide();
    ui->avrCloudLabel->hide();
}

void WeatherView::showLabels()
{
    if(ui->cloudinessLabel->isHidden() == true) ui->cloudinessLabel->show();
    if(ui->maxCloudinessLabel->isHidden() == true) ui->maxCloudinessLabel->show();
    if(ui->cloudinessIconLabel->isHidden() == true) ui->cloudinessIconLabel->show();
    if(ui->minCloudLabelValue->isHidden()==true)ui->minCloudLabelValue->show();
    if(ui->avrCloudLabel->isHidden() == true) ui->avrCloudLabel->show();
}

void WeatherView::location_added()
{
    locations = AppDatabase::getInstance().getLocationsList();
    ui->savedLocationComboBox->clear(); //dont forget to clear!
    ui->savedLocationComboBox->addItems(locations.keys());
}

void WeatherView::saveUserInput()
{
    if(ui->timeStepComboBox1->currentText() == "Hourly observations")
        currentParams.setQueryID(QUERY_ID_WEATHER_HOURLY);
    else if(ui->timeStepComboBox1->currentText() == "Daily observations")
        currentParams.setQueryID(QUERY_ID_WEATHER_DAILY);
    else if(ui->timeStepComboBox1->currentText() == "Monthly observations")
        currentParams.setQueryID(QUERY_ID_WEATHER_MONTHLY);
    else if(ui->timeStepComboBox1->currentText() == "Weather forecast")
        currentParams.setQueryID(QUERY_ID_FORECAST);
    currentParams.setTimeStepInMinutes(30);
    currentParams.setFromTime(ui->startDateTimeEdit->dateTime());
    currentParams.setToTime(ui->endDateTimeEdit->dateTime());
    currentParams.setXMin(ui->xCoordTextBox->text().toInt());
    currentParams.setXMax(ui->zCoordTextBox->text().toInt());
    currentParams.setYMin(ui->yCoordTextBox->text().toInt());
    currentParams.setYMax(ui->pCoordTextBox->text().toInt());
    AppDatabase::getInstance().storeWeatherSettings(currentParams);
}

void WeatherView::restoreUserInput()
{
    WeatherParams params = AppDatabase::getInstance().restoreWeatherSettings();
    ui->startDateTimeEdit->setDateTime(params.getFromTime());
    ui->endDateTimeEdit->setDateTime(params.getToTime());
    ui->xCoordTextBox->setText(QString("%1").arg(params.getXMin()));
    ui->zCoordTextBox->setText(QString("%1").arg(params.getXMax()));
    ui->yCoordTextBox->setText(QString("%1").arg(params.getYMin()));
    ui->pCoordTextBox->setText(QString("%1").arg(params.getYMax()));

    if(params.getQueryID() == QUERY_ID_WEATHER_HOURLY)
        ui->timeStepComboBox1->setCurrentText("Hourly observations");
    else if(params.getQueryID() == QUERY_ID_WEATHER_DAILY)
        ui->timeStepComboBox1->setCurrentText("Daily observations");
    else if(params.getQueryID() == QUERY_ID_WEATHER_MONTHLY)
        ui->timeStepComboBox1->setCurrentText("Monthly observations");
    else if(params.getQueryID() == QUERY_ID_FORECAST)
        ui->timeStepComboBox1->setCurrentText("Weather forecast");
}


void WeatherView::on_clearPushButton_clicked()
{
    linechart->clearWeatherGraphs();
    linechart->getObservationsChartView()->hide();
    linechart->getForecastChartView()->hide();
    ui->no_data_label->show();
    ui->weatherSaveDataButton->setEnabled(false);
    ui->showAvrTempButton->setEnabled(false);
    ui->saveAsPngButton->hide();
    ui->xCoordTextBox->clear();
    ui->yCoordTextBox->clear();
    ui->zCoordTextBox->clear();
    ui->pCoordTextBox->clear();
    resetSidebarLabels();
}


void WeatherView::showAlertDialog(QString message)
{

    ui->weatherSaveDataButton->setEnabled(false);
    ui->showAvrTempButton->setEnabled(false);
    ui->saveAsPngButton->hide();
    QMessageBox msgBox;
    msgBox.setText("Error!");
    msgBox.setInformativeText(message);
    msgBox.setIcon(QMessageBox::Critical);
    msgBox.setStandardButtons(QMessageBox::Close);
    msgBox.exec();
}

void WeatherView::showWeatherSavedNoti()
{
    ui->dataSaveSuccessNoti->show();
}

void WeatherView::showSavePngButton()
{
    ui->saveAsPngButton->show();
}

void WeatherView::plotFetchedObservationsData(WeatherObservationData data)
{
    ui->no_data_label->hide();
    linechart->plotWeatherCurrObservations(data);
}

void WeatherView::plotSavedObservationsData(WeatherObservationData data)
{
    ui->no_data_label->hide();
    linechart->plotWeatherLoadedObservations(data);
}

void WeatherView::plotFetchedForecastData(WeatherForecastData data)
{
    ui->no_data_label->hide();
    linechart->plotWeatherCurrForecast(data);
}

void WeatherView::plotSavedForecastData(WeatherForecastData data)
{
    ui->no_data_label->hide();
    linechart->plotWeatherLoadedForecast(data);
}


void WeatherView::on_timeStepComboBox1_activated(int index)
{
    if(index == 3) viewState = WeatherViewState::FORECAST;
    else viewState = WeatherViewState::OBSERVATIONS;
}


void WeatherView::on_savedLocationComboBox_textActivated(const QString &arg1)
{
    Location loc = locations.value(arg1);
    ui->xCoordTextBox->setText(QString("%1").arg(loc.xMin));
    ui->zCoordTextBox->setText(QString("%1").arg(loc.xMax));
    ui->yCoordTextBox->setText(QString("%1").arg(loc.yMin));
    ui->pCoordTextBox->setText(QString("%1").arg(loc.yMax));
}


void WeatherView::on_saveAsPngButton_clicked()
{
    if(ui->timeStepComboBox1->currentText() == "Hourly observation"
            || ui->timeStepComboBox1->currentText() == "Daily observations"
            || ui->timeStepComboBox1->currentText() == "Monthly observations" )
    {
        linechart->saveObservtionToPng();
    }
    else if(ui->timeStepComboBox1->currentText() == "Weather forecast")
    {
        linechart->saveForecastToPng();
    }
}


void WeatherView::on_dataCloseNotiButton_clicked()
{
     ui->dataSaveSuccessNoti->hide();
}

