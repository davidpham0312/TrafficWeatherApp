#include "forecastcontroller.h"

ForecastController::ForecastController(ForecastView *forecastView, QObject *parent)
    : QObject{parent}, forecastView_{forecastView}
{
    forecastRepo_ = new ForecastRepository(this);
}


#include<QDateTime>
void ForecastController::visualizeButtonClicked(const double minLongitude, const double minLatitude,
                                                const double maxLongitude, const double maxLatitude, const int hourIdx){
    if(minLongitude < 19 || minLongitude > 32 || minLongitude > maxLongitude ||
       maxLongitude < 19 || maxLongitude > 32){
        forecastView_->showAlertDialog("Invalid coordinates: longitude (xMin, xMax) must be in the range [19,32]");
        return;
    }
    if(minLatitude < 59 || minLatitude > 72 || minLatitude > maxLatitude ||
        maxLatitude < 59 || maxLatitude > 72 ){
        forecastView_->showAlertDialog("Invalid coordinates: latitude (yMin, yMax) must be in the range [59,72]");
        return;
    }

    if (hourIdx == -1) {
        forecastView_->showAlertDialog("Please select forecast hours.");
        return;
    }
    forecastParams.setMinLongitude(minLongitude);
    forecastParams.setMinLatitude(minLatitude);
    forecastParams.setMaxLongitude(maxLongitude);
    forecastParams.setMaxLatitude(maxLatitude);

    forecastView_->showWaitingDialog();
    forecastRepo_->getForecastData(forecastParams,
                                  member_func_to_ptr(&ForecastController::onDataFetchedFromServer, this));
    //tell combined section to show forecast
    WeatherParams wparams;
    wparams.setFromTime(QDateTime::currentDateTime());
    wparams.setToTime(QDateTime::currentDateTime().addSecs(60*60*12)); //12 hours in future
    wparams.setTimeStepInMinutes(30);
    wparams.setQueryID(QUERY_ID_FORECAST);
    wparams.setXMin(minLongitude);
    wparams.setXMax(maxLongitude);
    wparams.setYMin(minLatitude);
    wparams.setYMax(maxLatitude);
    wparams.setForecastParameters(true,true);
    emit weather_tab_show_forecast(wparams);

}

void ForecastController::saveButtonClicked(QString filename){
    forecastRepo_->storeForecastData(filename, [](){});
    forecastView_->showSaveSuccessNoti();
}

void ForecastController::compareButtonClicked(){
    fileList = forecastRepo_->getStoredFilesList();
    forecastView_->showDataChooserDialog(fileList);
}

void ForecastController::requestComparingData(QString filename){
    forecastView_->showWaitingDialog();
    forecastRepo_->getForecastData(filename, member_func_to_ptr(&ForecastController::onDataLoadedFromDB, this));
}

void ForecastController::checkUserInputs(const double minLongitude, const double maxLongitude,
                                         const double minLatitude, const double maxLatitude)
{
    if (forecastParams.getMinLongitude() != minLongitude) {
        forecastView_->showAlertDialog("The value of minimum longitude (xMin) does not correspond to the displayed data.\n"
                                       "Change xMin to " + QString::number(forecastParams.getMinLongitude()) +
                                       " or click Visualize to load data with this input.");
        return;
    }
    else if (forecastParams.getMaxLongitude() != maxLongitude) {
        forecastView_->showAlertDialog("The value of maximum longitude (xMax) does not correspond to the displayed data.\n"
                                       "Change xMax to " + QString::number(forecastParams.getMaxLongitude()) +
                                       " or click Visualize to load data with this input.");
        return;
    }
    else if (forecastParams.getMinLatitude() != minLatitude) {
        forecastView_->showAlertDialog("The value of minimum latitude (yMin) does not correspond to the displayed data.\n"
                                       "Change yMin to " + QString::number(forecastParams.getMinLatitude()) +
                                       " or click Visualize to load data with this input.");
        return;
    }
    else if (forecastParams.getMaxLatitude() != maxLatitude) {
        forecastView_->showAlertDialog("The value of maximum latitude (yMax) does not correspond to the displayed data.\n"
                                       "Change yMax to " + QString::number(forecastParams.getMaxLatitude()) +
                                       " or click Visualize to load data with this input.");
        return;
    }
    else {
        forecastView_->showSaveDataDialog();
    }
}

void ForecastController::onDataFetchedFromServer(QList<ForecastDataSample> forecastData, bool success)
{
    forecastView_->closeWaitingDialog();
    if (success){
        forecastView_->showSaveButton();
        forecastView_->showTitle();
        forecastView_->enableButtons();
        forecastView_->enableSaveButton();
        forecastView_->displayCurrentForecastCard(forecastData);
        forecastView_->displayCurrentForecastGraphs(forecastData);
    }
    else{
        forecastView_->showAlertDialog("Fething data from server failed! "
                                       "Please check your internet connection");
    }
}

void ForecastController::onDataLoadedFromDB(QList<ForecastDataSample> forecastData, bool success)
{
    forecastView_->closeWaitingDialog();
    if (success) {
        forecastView_->showTitle();
        forecastView_->enableButtons();
        forecastView_->showSaveButton();
        forecastView_->displayComparingForecastCard(forecastData);
        forecastView_->displayComparingForecastGraphs(forecastData);
    }
    else{
        forecastView_->showAlertDialog("Failed to load data from the database! "
                                       "This could be due to bad file name");
    }
}
