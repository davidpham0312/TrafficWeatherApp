#ifndef MAINTENANCECONTROLLER_H
#define MAINTENANCECONTROLLER_H

#include <QObject>
#include <Weather/weatherparams.h>
#include <Maintenance/maintenanceparams.h>
#include <Maintenance/maintenancedata.h>
#include <Maintenance/UI/Model/maintenancerepository.h>

class MaintenanceController : public QObject
{
    Q_OBJECT
private:

    MaintenanceRepository* repo;
    QStringList files;
public:
    explicit MaintenanceController(QObject* parent=nullptr);
    ~MaintenanceController();
    //request data from digitraffic
    void requestMaintenanceData(MaintenanceParams params);
    //request data from database
    void requestMaintenanceData(QString filename);
    //request saving the data to DB
    void requestStoreMaintenanceData(QString filename);
    void requestSavedFilesList();

private:
    void onDataFetchedFromServer(MaintenanceData taskData, bool success);
    void onDataLoadedFromDB(MaintenanceData taskData, bool success);

signals:
        //dialogs
        void view_showAlertDialog(QString message);
        void view_showWaitingDialog();
        void view_closeWaitingDialog();
        void view_showSaveDataDialog();
        void view_showDataChooserDialog(QStringList &items);
        //data
        void view_displayMaintenanceData(MaintenanceData data, MaintenanceDataSrc src);
        //other
        void view_enableSaveButton();
        void view_showSaveSuccessNoti();

        //signal for combined weather tab
        void weather_tab_show_observations(WeatherParams params);
};

#endif // MAINTENANCECONTROLLER_H
