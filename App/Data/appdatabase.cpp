#include "appdatabase.h"


AppDatabase &AppDatabase::getInstance()
{
    static AppDatabase db;
    return db;
}

AppDatabase::AppDatabase()
{

}

void AppDatabase::storeLocation(Location &loc)
{
    QByteArray data;
    dbLoad(FILE_SETTINGS_LOCATIONS,data);
    QJsonDocument doc;
    QJsonObject obj;
    if(!data.isEmpty() && !data.isNull()){
        doc = QJsonDocument::fromJson(data);
        obj = doc.object();
    }
    obj[loc.locName] = loc.toJsonObject();
    doc.setObject(obj);
    dbStore(FILE_SETTINGS_LOCATIONS, doc.toJson());

}

QMap<QString, Location> AppDatabase::getLocationsList()
{
    QByteArray data;
    dbLoad(FILE_SETTINGS_LOCATIONS,data);
    QJsonObject obj;
    QMap<QString, Location> map;
    if(!data.isEmpty() && !data.isNull()){
        obj = QJsonDocument::fromJson(data).object();
        foreach (QString key, obj.keys()) {
            map.insert(key,Location::fromJson(obj.value(key).toObject()));
        }
    }
    return map;
}



void AppDatabase::storeMaintenanceSettings(MaintenanceParams &params)
{
    dbStore(FILE_SETTINGS_MAINTENANCE, params.toJsonObject());
}

void AppDatabase::storeMessagesSettings(MessagesParams &params)
{
    dbStore(FILE_SETTINGS_MESSAGES, params.toJsonObject());
}

void AppDatabase::storeWeatherSettings(WeatherParams &params)
{
    dbStore(FILE_SETTINGS_WEATHER, params.toJsonObject());
}

void AppDatabase::storeForecastSettings(ForecastParams &params)
{
    dbStore(FILE_SETTINGS_FORECAST, params.toJsonObject());

}

void AppDatabase::prefillLocations()
{
    QByteArray data;
     dbLoad(FILE_SETTINGS_LOCATIONS,data);
     QJsonDocument doc;
     QJsonObject obj;
     if(data.isEmpty()){
         obj = doc.object();
         Location loc;
         loc = {"Jomala Maarianhamina lentoasema",19,22,60,61};
         obj[loc.locName] = loc.toJsonObject();

         loc = {"Vantaa Helsinki-Vantaan lentoasema",24,25,60,61};
         obj[loc.locName] = loc.toJsonObject();

         loc = {"Pori lentoasema",25,25,61,63};
         obj[loc.locName] = loc.toJsonObject();

         loc = {"Jutsjoki",26,28,69,70};
         obj[loc.locName] = loc.toJsonObject();

         loc = {"Liperi Joensuu lentoasema",29,30,62,63};
         obj[loc.locName] = loc.toJsonObject();

         loc = {"Tampere",21,22,61,62};
         obj[loc.locName] = loc.toJsonObject();


         doc.setObject(obj);
         dbStore(FILE_SETTINGS_LOCATIONS, doc.toJson());
     }

}

MaintenanceParams AppDatabase::restoreMaintenanceSettings()
{
    QByteArray data;
    dbLoad(FILE_SETTINGS_MAINTENANCE, data);
    return MaintenanceParams::fromJson(data);
}

MessagesParams AppDatabase::restoreMessagesSettings()
{
    QByteArray data;
    dbLoad(FILE_SETTINGS_MESSAGES, data);
    return MessagesParams::fromJson(data);
}

WeatherParams AppDatabase::restoreWeatherSettings()
{
    QByteArray data;
    dbLoad(FILE_SETTINGS_WEATHER, data);
    return WeatherParams::fromJson(data);
}

ForecastParams AppDatabase::restoreForecastSettings()
{
    QByteArray data;
    dbLoad(FILE_SETTINGS_FORECAST, data);
    return ForecastParams::fromJson(data);
}



QString AppDatabase::getDbPath()
{
    return DB_PATH_SETTINGS;
}

QString AppDatabase::getTempPath()
{
    return TEMP_PATH_SETTINGS;

}

QString AppDatabase::getTempFile()
{
    return "NONE";
}
