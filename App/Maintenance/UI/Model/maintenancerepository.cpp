#include "maintenancerepository.h"

MaintenanceRepository::MaintenanceRepository(QObject *parent)
{
    client = new MaintenanceClient(parent);
}

void MaintenanceRepository::getSpecificTaskData(QString fileName, OnMaintenanceDataReady callback)
{
    db.fetchMaintenanceData(fileName, callback);
}

void MaintenanceRepository::getSpecificTaskData(MaintenanceParams params, OnMaintenanceDataReady callback)
{
    client->fetchTasksCount(params,callback);
}

void MaintenanceRepository::storeSpecificTaskData(QString filename, OnMaintenanceDataStored callback)
{
    db.storeMaintenanceData(filename, callback);
}

QStringList MaintenanceRepository::getStoredFilesList()
{
    return db.getStoredFilesList();
}

QList<QString> MaintenanceRepository::getMaintenanceTaskTypes()
{
    static QList<QString> taskTypes;
    if(taskTypes.isEmpty()){
        taskTypes.append("BRUSHING");
        taskTypes.append("BRUSH_CLEARING");
        taskTypes.append("CLEANSING_OF_BRIDGES");
        taskTypes.append("CLEANSING_OF_REST_AREAS");
        taskTypes.append("CLEANSING_OF_TRAFFIC_SIGNS");
        taskTypes.append("CLIENTS_QUALITY_CONTROL");
        taskTypes.append("COMPACTION_BY_ROLLING");
        taskTypes.append("CRACK_FILLING");
        taskTypes.append("DITCHING");
        taskTypes.append("DUST_BINDING_OF_GRAVEL_ROAD_SURFACE");
        taskTypes.append("FILLING_OF_GRAVEL_ROAD_SHOULDERS");
        taskTypes.append("FILLING_OF_ROAD_SHOULDERS");
        taskTypes.append("HEATING");
        taskTypes.append("LEVELLING_GRAVEL_ROAD_SURFACE");
        taskTypes.append("LEVELLING_OF_ROAD_SHOULDERS");
        taskTypes.append("LEVELLING_OF_ROAD_SURFACE");
        taskTypes.append("LINE_SANDING");
        taskTypes.append("LOWERING_OF_SNOWBANKS");
        taskTypes.append("MAINTENANCE_OF_GUIDE_SIGNS_AND_REFLECTOR_POSTS");
        taskTypes.append("MECHANICAL_CUT");
        taskTypes.append("MIXING_OR_STABILIZATION");
        taskTypes.append("PATCHING");
        taskTypes.append("PAVING");
        taskTypes.append("PLOUGHING_AND_SLUSH_REMOVAL");
        taskTypes.append("PREVENTING_MELTING_WATER_PROBLEMS");
        taskTypes.append("REMOVAL_OF_BULGE_ICE");
        taskTypes.append("RESHAPING_GRAVEL_ROAD_SURFACE");
        taskTypes.append("ROAD_INSPECTIONS");
        taskTypes.append("ROAD_MARKINGS");
        taskTypes.append("ROAD_STATE_CHECKING");
        taskTypes.append("SAFETY_EQUIPMENT");
        taskTypes.append("SALTING");
        taskTypes.append("SNOW_PLOUGHING_STICKS_AND_SNOW_FENCES");
        taskTypes.append("SPOT_SANDING");
        taskTypes.append("SPREADING_OF_CRUSH");
        taskTypes.append("TRANSFER_OF_SNOW");
        taskTypes.append("UNKNOWN");
        taskTypes.append("CLEANSING_OF_REST_AREAS");
        taskTypes.append("OTHER");
    }
    return taskTypes;
}
