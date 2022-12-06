#include "weathercontroller.h"
#include <algorithm>
#include <cmath>
#define DAY_IN_SECONDS 60*60*24
#define DAY_IN_MINUTES 60*24
#define MONTH_IN_SECONDS 60*60*24*28
#define MONTH_IN_MINUTES 28*60*24
#define YEAR_IN_SECONDS 60*60*24*30*360

WeatherController::WeatherController(WeatherRepository &weatherRepo, WeatherView *weatherView ,QObject *parent)
    : QObject{parent}
    , weatherView_{weatherView}
    , weatherRepo_{weatherRepo}
{
    tempMap = {};
    windMap = {};
    cloudMap = {};
    tempPredMap = {};
    winPredMap = {};

}

WeatherController::~WeatherController()
{

}

void WeatherController::visualizeButtonClicked(QString timeStep, WeatherParams params)
{

    //coords must be in the requried range
    if(params.getXMin() < 19 ||
       params.getXMin() > 32 ||
       params.getXMin()> params.getXMax()){
        weatherView_->showAlertDialog("Invalid coordinates: [xmin,xmax] must be in the range [19,32]");
        return;
    }
    if(params.getXMax() < 19 ||
       params.getXMax() > 32 )
    {
        weatherView_->showAlertDialog("Invalid coordinates: [xmin,xmax] must be in the range [19,32]");
        return;
    }
    if(params.getYMin() < 59 ||
       params.getYMin() > 72 ||
       params.getYMin()> params.getYMax()){
        weatherView_->showAlertDialog("Invalid coordinates: [ymin,ymax] must be in the range [59,72]");
        return;
    }
    if(params.getYMax() < 59 ||
       params.getYMax() > 72 )
    {
        weatherView_->showAlertDialog("Invalid coordinates: [ymin,ymax] must be in the range [59,72]");
        return;
    }

        currentTimeStep = timeStep;
        startTime_ = params.getFromTime();
        endTime_ = params.getToTime();

        //set QUERY ID based on time step
        if(timeStep == "Hourly observations")
        {
            params.setQueryID(QUERY_ID_WEATHER_HOURLY);
            params.setTimeStepInMinutes(60);

        }
        else if(timeStep == "Daily observations")
        {
            params.setQueryID(QUERY_ID_WEATHER_DAILY);
            params.setTimeStepInMinutes(DAY_IN_MINUTES);
        }
        else if(timeStep == "Monthly observations")
        {
            params.setQueryID(QUERY_ID_WEATHER_MONTHLY);
            params.setTimeStepInMinutes(MONTH_IN_MINUTES);
        }
        else if(timeStep == "Weather forecast")
        {
            params.setQueryID(QUERY_ID_FORECAST);
            params.setTimeStepInMinutes(60);
            params.setForecastParameters(true, true);
        }

        //before fetching data, check if start and end time are valid
        if (checkDateTime(startTime_, endTime_) == true) {
            weatherView_->displayWaitingDialog();
            //request observation data
            if(timeStep == "Hourly observations" || timeStep == "Daily observations" || timeStep == "Monthly observations")
            {
                params.setObservationParameters(true, true, true);
                weatherRepo_.fetchWeatherObservations(
                    params, [&](WeatherObservationData data, bool) {
                      if (data.getTemperatureObservations().empty()) {
                        weatherView_->closeWaitingDialog();
                        weatherView_->showAlertDialog(
                            "No data is available for the chosen inputs");
                      } else {
                          tempMap = data.getTemperatureObservations();
                          windMap = data.getWindObservations();
                          cloudMap = data.getCloudinessObservations();
                        weatherView_->plotFetchedObservationsData(data);
                        weatherView_->closeWaitingDialog();
                      }
                    });
             }
            //request forecast data
            if(timeStep == "Weather forecast")
            {
                weatherRepo_.fetchWeatherForecast(params,[&](WeatherForecastData data, bool){

                     if(data.getTemperatureForecast().empty())
                     {
                       weatherView_->closeWaitingDialog();
                       weatherView_->showAlertDialog(
                           "No data is available for the chosen inputs");
                     }
                    else
                     {
                         tempPredMap = data.getTemperatureForecast();
                         winPredMap = data.getWindForecast();
                         weatherView_->plotFetchedForecastData(data);
                         weatherView_->closeWaitingDialog();
                     }
                });
            }
        }
        weatherView_->showSavePngButton();
}

void WeatherController::saveButtonClicked(QString savedDataTitle, WeatherViewState state)
{
      // choose which files to save based on whether the View state is on Observations or forecast
      if(state == OBSERVATIONS){
          //use this for observatios
           weatherRepo_.storeObservationsWeatherData(savedDataTitle, [](bool){});
      }else{
          //use this for forecast
          weatherRepo_.storeForecastWeatherData(savedDataTitle, [](bool){});
      }
      weatherView_->showWeatherSavedNoti();
}

void WeatherController::requestSavedFilesList(WeatherViewState state)
{
    // choose which files list to show based on whether the View state is on Observations or forecast
    if(state == OBSERVATIONS){
        //use this for observatios
        weatherView_->showDataChooserDialog(this->weatherRepo_.getStoredObservationsFilesList());
    }else{
        //use this for forecast
        weatherView_->showDataChooserDialog(this->weatherRepo_.getStoredForecastFilesList());
    }
}


void WeatherController::getSavedObservationData(QString savedDataTitle)
{
    //request saved observation data and display it
        weatherView_->displayWaitingDialog();
        weatherRepo_.fetchWeatherObservations(savedDataTitle,[&](WeatherObservationData data, bool){
            if(data.getTemperatureObservations().isEmpty()){
                weatherView_->showAlertDialog("No data is available for the chosen inputs");

            }else{
                tempMap = data.getTemperatureObservations();
                windMap = data.getWindObservations();
                cloudMap = data.getCloudinessObservations();
                weatherView_->plotSavedObservationsData(data);
            }
            weatherView_->closeWaitingDialog();
        });
}

void WeatherController::getSavedForcastData(QString savedDataTitle)
{
    //request forecast data and display it
    weatherView_->displayWaitingDialog();
    weatherRepo_.fetchWeatherForecast(savedDataTitle,[&](WeatherForecastData data, bool){
        if(data.getTemperatureForecast().isEmpty()){
            weatherView_->showAlertDialog("No data is available for the chosen inputs");
        }else{
            tempPredMap = data.getTemperatureForecast();
            winPredMap = data.getWindForecast();
            weatherView_->plotSavedForecastData(data);
        }
        weatherView_->closeWaitingDialog();
    });
}


void WeatherController::compareToSavedDataClicked(QString savedDataTitle,  WeatherViewState state)
{     
    if(state == OBSERVATIONS) getSavedObservationData(savedDataTitle);
    else getSavedForcastData(savedDataTitle);
    weatherView_->showSavePngButton();
}

void WeatherController::averageButtonClicked(WeatherViewState state)
{
    //calculate and display averages, maximums and minimums
    weatherView_->displayWaitingDialog();
    QMessageBox messageBox;
    if(currentTimeStep == "Hourly observations" || currentTimeStep == "Daily observations"
            || currentTimeStep == "Monthly observations" || state == OBSERVATIONS)
    {
        WeatherObservationData data;
        if(!tempMap.isEmpty())
        {
            data.calculateMinMaxAvg(tempMap);
            weatherView_->displayMaxTemperature(data.getMaxTemp());
            weatherView_->displayMinTemperature(data.getMinTemp());
            weatherView_->displayTempAverage(data.getAvgTemp());
        }
        else weatherView_->displayObservedTempEmpty();
        if(!windMap.isEmpty())
        {
            data.calculateMinMaxAvg(windMap);
            weatherView_->displayMaxWind(data.getMaxWind());
            weatherView_->displayMinWind(data.getMinWind());
            weatherView_->displayWindAverage(data.getAvgWind());
        }
        else weatherView_->displayObservedWindEmpty();
        if(!cloudMap.isEmpty())
        {
            data.calculateMinMaxAvg(cloudMap);
            weatherView_->displayMaxCloud(data.getMaxCloudiness());
            weatherView_->displayMinCloud(data.getMinCloudiness());
            weatherView_->displayCloudAverage(data.getAvgCloudiness());
        }
        else weatherView_->displayObservedCloudEmpty();
        weatherView_->showLabels();
        weatherView_->closeWaitingDialog();
    }
    else if(currentTimeStep == "Weather forecast" || state == FORECAST)
    {
        WeatherForecastData forData;
        if(!tempPredMap.isEmpty())
        {
        forData.calculateMinMaxAvg(tempPredMap);
        weatherView_->displayMaxTemperature(forData.getMaxTemp());
        weatherView_->displayMinTemperature(forData.getMinTemp());
        weatherView_->displayTempAverage(forData.getAvgTemp());
        }
        else weatherView_->displayPredicetedTempEmpty();
        if(!winPredMap.isEmpty())
        {
        forData.calculateMinMaxAvg(winPredMap);
        weatherView_->displayMaxWind(forData.getMaxWind());
        weatherView_->displayMinWind(forData.getMinWind());
        weatherView_->displayWindAverage(forData.getAvgWind());
        weatherView_->hideLabels();
        weatherView_->closeWaitingDialog();
        }
        else weatherView_->displayPredictedWindEmpty();
    }
}

bool WeatherController::checkDateTime(QDateTime startTime, QDateTime endTime)
{
    QMessageBox messageBox;
    int diff = startTime.secsTo(endTime);
    QDateTime currentTime = QDateTime::currentDateTime();

    if(currentTimeStep == "Hourly observations")
    {
        if(diff > DAY_IN_SECONDS)
        {
            weatherView_->showAlertDialog("Hourly observations selected. Time should be max 24h.");
            return false;
        }
        if(diff < 60)
        {
            weatherView_->showAlertDialog("Hourly observations selected. Time difference should be more than 1 hour.");
            return false;
        }
        if(startTime > currentTime || endTime > currentTime)
        {
            weatherView_->showAlertDialog("Searching for observations. Can't be more than current time");
            return false;
        }
    }
    else if(currentTimeStep == "Daily observations")
    {
        if(diff > MONTH_IN_SECONDS )
        {
           weatherView_->showAlertDialog("Daily observations selected. Day count should be less than 28 days.");
            return false;
        }
        if(diff < DAY_IN_SECONDS)
        {
            weatherView_->showAlertDialog("Daily observations selected. Time difference should be more than 1 day.");
             return false;
        }
        if(startTime > currentTime || endTime > currentTime)
        {
            weatherView_->showAlertDialog("Searching for observations. Can't be more than current time");
            return false;
        }
    }
    else if(currentTimeStep == "Monthly observations")
    {
        if(diff > YEAR_IN_SECONDS)
        {
            weatherView_->showAlertDialog("Monthly observations selected. Day number should be less than 365. ");
            return false;
        }
        if(diff < MONTH_IN_SECONDS)
        {
            weatherView_->showAlertDialog("Monthly observations selected. Time difference should be more than 1 month.");
            return false;
        }
        if(startTime > currentTime || endTime > currentTime)
        {
            weatherView_->showAlertDialog("Searching for observations. Can't be more than current time");
            return false;
        }
    }
    else if(currentTimeStep == "Weather forecast")
    {
         if(diff > DAY_IN_SECONDS*3)
        {
             weatherView_->showAlertDialog("Weather forecast selected. Time should be less than 56. ");
            return false;
        }
         if(startTime < currentTime || endTime < currentTime)
         {
             weatherView_->showAlertDialog("Weather forecast selected. Time can't be less than current time. ");
            return false;
         }
         if(diff < 60)
         {
             weatherView_->showAlertDialog("Weather forecast selected. Time difference should be more than 1 hour.");
             return false;
         }
    }

    if(startTime > endTime)
    {
        weatherView_->showAlertDialog("Starting time can't be higher than end time!");
        return false;
    }
    return true;
}




