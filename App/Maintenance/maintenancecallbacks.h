#ifndef MAINTENANCECALLBACKS_H
#define MAINTENANCECALLBACKS_H


#include "maintenancedata.h"
#include <functional>
using namespace std::placeholders;

#define member_func_to_ptr(ref_to_function, ptr_instance) std::bind(ref_to_function, ptr_instance, _1, _2)
//typedef void (*OnMaintenanceDataReady)(MaintenanceData taskData, bool);
typedef std::function<void(MaintenanceData taskData, bool success)> OnMaintenanceDataReady;
//typedef void (*OnMaintenanceDataStored)(void);
typedef std::function<void(void)> OnMaintenanceDataStored;
//typedef void (*OnMaintenanceTypesReady)(QList<QString> types);

#endif // MAINTENANCECALLBACKS_H
