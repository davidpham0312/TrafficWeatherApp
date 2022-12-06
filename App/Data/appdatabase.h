#ifndef APPDATABASE_H
#define APPDATABASE_H

#include "absdatabase.h"
#include "db_paths.h"
#include "Maintenance/maintenanceparams.h"
#include "Weather/weatherparams.h"
#include "Forecast/forecastparams.h"
#include "Messages/messagesparams.h"
#include "location.h"
#include <QMap>

// singleton app database for storing and fetching user inputs
class AppDatabase : public AbsDataBase
{
public:
    static AppDatabase& getInstance();
    AppDatabase(AppDatabase const&) = delete; //no copy constructor
    void operator=(AppDatabase const&)  = delete; //no = operator

    //STORE AND RESTORE FUNCTIONS
    void storeMaintenanceSettings(MaintenanceParams &params);
    void storeMessagesSettings(MessagesParams &params);
    void storeWeatherSettings(WeatherParams &params);
    void storeForecastSettings(ForecastParams &params);
    void prefillLocations();

    MaintenanceParams restoreMaintenanceSettings();
    MessagesParams restoreMessagesSettings();
    WeatherParams restoreWeatherSettings();
    ForecastParams restoreForecastSettings();

    //special location functions
    void storeLocation(Location &loc);
    QMap<QString,Location> getLocationsList();



  private:
    AppDatabase();
    AppDatabase(AppDatabase& other);


    // AbsDataBase interface
protected:
    QString getDbPath();
    QString getTempPath();
    QString getTempFile();
};

#endif // APPDATABASE_H
