#ifndef MAINTENANCEVIEW_H
#define MAINTENANCEVIEW_H

#include <QWidget>
#include "Maintenance/UI/maintenancecharthelper.h"
#include "Maintenance/maintenancedata.h"
#include "Maintenance/maintenanceparams.h"
#include "Maintenance/UI/maintenancecontroller.h"
#include <QInputDialog>
#include <QMessageBox>
#include <Data/appdatabase.h>
#include <Dialogs/waitdialog.h>

namespace Ui {
class MaintenanceView;
}

class MaintenanceView : public QWidget
{
    Q_OBJECT

private:
    MaintenanceChartHelper* chartHelper;
    Ui::MaintenanceView *ui;
    MaintenanceController* controller;
//    QMessageBox waitingDialog;
    WaitDialog* waitingDialog;
    MaintenanceParams currentParams;
    QMap<QString, Location> locations;


public:
    explicit MaintenanceView(QWidget *parent = nullptr);
    ~MaintenanceView();
    void saveUserInput();
    void restoreUserInput();

    MaintenanceController *getController() const;

public slots:
    void location_added();

private:
    void initWaitingDialog();

private slots:
    void on_clear_btn_clicked();

    void on_vidualize_btn_clicked();

    void on_save_btn_clicked();

    void on_compare_btn_clicked();


    void on_location_dropdown_textActivated(const QString &arg1);


    void on_save_png_btn_clicked();

    void on_pushButton_clicked();

public slots:
    //dialogs
    void showAlertDialog(QString message);
    void showWaitingDialog();
    void closeWaitingDialog();
    void showSaveDataDialog();
    void showDataChooserDialog(QStringList &items);
    //data
    void displayMaintenanceData(MaintenanceData data, MaintenanceDataSrc src);
    //other
    void enableSaveButton();
    void showSaveSuccessNoti();
};

#endif // MAINTENANCEVIEW_H
