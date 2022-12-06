#include "maintenancecontroller.h"

#define TIME_24H_IN_SECS 24*60*60
#define TIME_1H_IN_SECS 60*60

MaintenanceController::MaintenanceController(QObject *parent) :
    QObject(parent)
{
    repo = new MaintenanceRepository(parent);
}

MaintenanceController::~MaintenanceController()
{
    delete repo;
}

void MaintenanceController::requestMaintenanceData(MaintenanceParams params)
{
    //check validity of parameters
    //did user choose a task type ?
    if(params.getTaskID().isEmpty()){
        emit view_showAlertDialog("Please choose a task type first!");
        return;
    }

    // difference between `from` and `to` time must not less than 24 hours
    if(!params.getFromTime().isValid() || !params.getToTime().isValid() || params.getFromTime() > params.getToTime()){
        emit view_showAlertDialog("Invalid date");
        return;
    }

    if(params.getFromTime().secsTo(params.getToTime()) > TIME_24H_IN_SECS) {
        emit view_showAlertDialog("Invalid interval: duration between `from time` to `to time` must be less than or equal to 24hs");
        return;
    }

    if(params.getFromTime().secsTo(params.getToTime()) < TIME_1H_IN_SECS) {
        emit view_showAlertDialog("Invalid interval: duration between `from time` to `to time` must be more than or 1 hr");
        return;
    }
    //coords must be in the requried range
    if(params.getXMin() < 19 ||
       params.getXMin() > 32 ||
       params.getXMin()> params.getXMax()){
        emit view_showAlertDialog("Invalid coordinates: [xmin,xmax] must be in the range [19,32]");
        return;
    }
    if(params.getXMax() < 19 ||
       params.getXMax() > 32 )
    {
        emit view_showAlertDialog("Invalid coordinates: [xmin,xmax] must be in the range [19,32]");
        return;
    }
    if(params.getYMin() < 59 ||
       params.getYMin() > 72 ||
       params.getYMin()> params.getYMax()){
        emit view_showAlertDialog("Invalid coordinates: [ymin,ymax] must be in the range [59,72]");
        return;
    }
    if(params.getYMax() < 59 ||
       params.getYMax() > 72 )
    {
        emit view_showAlertDialog("Invalid coordinates: [ymin,ymax] must be in the range [59,72]");
        return;
    }

    repo->getSpecificTaskData(params, member_func_to_ptr(&MaintenanceController::onDataFetchedFromServer, this));
    //show waiting dialog
    emit view_showWaitingDialog();

    //tell combined section to show observatons
    WeatherParams wparams;
    wparams.setFromTime(params.getFromTime());
    wparams.setToTime(params.getToTime());
    wparams.setTimeStepInMinutes(30);
    wparams.setQueryID(QUERY_ID_WEATHER_HOURLY);
    wparams.setXMin(params.getXMin());
    wparams.setXMax(params.getXMax());
    wparams.setYMin(params.getYMin());
    wparams.setYMax(params.getYMax());
    wparams.setObservationParameters(true,true,true);
    emit weather_tab_show_observations(wparams);
}

void MaintenanceController::onDataFetchedFromServer(MaintenanceData taskData, bool success)
{
    emit view_closeWaitingDialog();
    if(success){
        if(taskData.getTasksCount() == 0){
            emit view_showAlertDialog("No maintenance data available for this selection");
        }else{
            //enable the save button if previously disabled
            emit view_enableSaveButton();
            //show the data
            emit view_displayMaintenanceData(taskData, DIGI_TRAFFIC);
        }

    }else{
        emit view_showAlertDialog("Fething data from server failed! please check your internet connection");
    }
}

void MaintenanceController::onDataLoadedFromDB(MaintenanceData taskData, bool success)
{
    emit view_closeWaitingDialog();
    if(success){
        //enable the save button if previously disabled
        emit view_enableSaveButton();
        //show the data
        emit view_displayMaintenanceData(taskData, LOCAL_DB);
    }else{
        emit view_showAlertDialog("Failed to load data from the database ! this could be due to bad file name");
    }
}

void MaintenanceController::requestMaintenanceData(QString filename)
{

    //show waiting dialog
    emit view_showWaitingDialog();
    //request data from db
    repo->getSpecificTaskData(filename, member_func_to_ptr(&MaintenanceController::onDataLoadedFromDB, this));
}

void MaintenanceController::requestStoreMaintenanceData(QString filename)
{
    repo->storeSpecificTaskData(filename, [](){/*TODO*/});
    emit view_showSaveSuccessNoti();
}

void MaintenanceController::requestSavedFilesList()
{
    files = repo->getStoredFilesList();
    emit view_showDataChooserDialog(files);
}


