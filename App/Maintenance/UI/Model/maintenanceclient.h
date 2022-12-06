#ifndef MAINTENANCECLIENT_H
#define MAINTENANCECLIENT_H

#include "Maintenance/maintenanceparams.h"
#include "Maintenance/maintenancecallbacks.h"
#include <QList>
#include <QObject>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include "Data/httpclient.h"
#include "json2maintenancedata.h"

class MaintenanceClient : public HttpClient
{
     Q_OBJECT
public:
    explicit MaintenanceClient(QObject *parent = nullptr);
    //fetch data asynchronously and callback the caller when ready
    void fetchTasksCount(MaintenanceParams params, OnMaintenanceDataReady callback);

protected:
    //internal callback for handling request response success
    void onRequestFinished(QNetworkReply* reply);
    //internal callback for handling request response failure
    void onRequestFailed(QNetworkReply::NetworkError errorCode);

private:
    OnMaintenanceDataReady readyCallback;
    QByteArray currentData;
    bool pendingRequest = false;
};

#endif // MAINTENANCECLIENT_H
