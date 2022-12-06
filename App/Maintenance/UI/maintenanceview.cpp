#include "maintenanceview.h"
#include "ui_maintenanceview.h"
#include "Maintenance/UI/Model/maintenancerepository.h"
#include "Dialogs/savefiledialog.h"


MaintenanceView::MaintenanceView(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MaintenanceView)
{
    ui->setupUi(this);
    chartHelper = new MaintenanceChartHelper(this);
    ui->chart_frame->addWidget(chartHelper->getChartView(),1);
    ui->task_type_dropdown->addItems(MaintenanceRepository::getMaintenanceTaskTypes());
    ui->save_success_noti->hide();
    ui->save_png_btn->hide();
    chartHelper->getChartView()->hide();

    //init controller
    controller = new MaintenanceController(this);
    connect(controller, &MaintenanceController::view_showAlertDialog, this,&MaintenanceView::showAlertDialog);
    connect(controller, &MaintenanceController::view_showWaitingDialog, this,&MaintenanceView::showWaitingDialog);
    connect(controller, &MaintenanceController::view_closeWaitingDialog, this,&MaintenanceView::closeWaitingDialog);
    connect(controller, &MaintenanceController::view_showSaveDataDialog, this,&MaintenanceView::showSaveDataDialog);
    connect(controller, &MaintenanceController::view_showDataChooserDialog, this,&MaintenanceView::showDataChooserDialog);
    connect(controller,&MaintenanceController::view_displayMaintenanceData, this,&MaintenanceView::displayMaintenanceData);
    connect(controller, &MaintenanceController::view_enableSaveButton, this,&MaintenanceView::enableSaveButton);
    connect(controller, &MaintenanceController::view_showSaveSuccessNoti, this,&MaintenanceView::showSaveSuccessNoti);

    //init datatime feilds to now
    ui->from_dt_edit->setDateTime(QDateTime::currentDateTime());
    ui->to_dt_edit->setDateTime(QDateTime::currentDateTime());

    //populate locations (not the best practice here, but what can we do !)
    locations = AppDatabase::getInstance().getLocationsList();
    ui->location_dropdown->addItems(locations.keys());

    waitingDialog = new WaitDialog(this);
//    initWaitingDialog()


}

MaintenanceView::~MaintenanceView()
{
    delete ui;
}

MaintenanceController *MaintenanceView::getController() const
{
    return controller;
}

void MaintenanceView::saveUserInput()
{
    currentParams.setFromTime(ui->from_dt_edit->dateTime());
    currentParams.setToTime(ui->to_dt_edit->dateTime());
    currentParams.setTaskID(ui->task_type_dropdown->currentText());
    currentParams.setXMin(ui->xmin_edit->text().toDouble());
    currentParams.setXMax(ui->xmax_edit->text().toDouble());
    currentParams.setYMin(ui->ymin_edit->text().toDouble());
    currentParams.setYMax(ui->ymax_edit->text().toDouble());
    AppDatabase::getInstance().storeMaintenanceSettings(currentParams);
}

void MaintenanceView::restoreUserInput()
{
    MaintenanceParams params = AppDatabase::getInstance().restoreMaintenanceSettings();
    ui->from_dt_edit->setDateTime(params.getFromTime());
    ui->to_dt_edit->setDateTime(params.getToTime());
    ui->xmax_edit->setText(QString("%1").arg(params.getXMax()));
    ui->xmin_edit->setText(QString("%1").arg(params.getXMin()));
    ui->ymax_edit->setText(QString("%1").arg(params.getYMax()));
    ui->ymin_edit->setText(QString("%1").arg(params.getYMin()));
    if (!params.getTaskID().isEmpty()){
        ui->task_type_dropdown->setCurrentText(params.getTaskID());
    }

}

void MaintenanceView::location_added()
{
    //populate locations (not the best practice here, but what can we do !)
    locations = AppDatabase::getInstance().getLocationsList();
    ui->location_dropdown->clear(); //dont forget to clear!
    ui->location_dropdown->addItems(locations.keys());
}


void MaintenanceView::on_clear_btn_clicked()
{
    chartHelper->clear();
    ui->save_btn->setEnabled(false);
    ui->clear_btn->setEnabled(false);
    ui->save_png_btn->hide();
    chartHelper->getChartView()->hide();
    ui->avg_value_label->setText("0");
    ui->avg_text_label->setText("Task count: ");
    ui->no_data_label->show();
}

//#include <QRandomGenerator>
void MaintenanceView::on_vidualize_btn_clicked()
{
    //checking the validitly of this data is done by the controller
    currentParams.setFromTime(ui->from_dt_edit->dateTime());
    currentParams.setToTime(ui->to_dt_edit->dateTime());
    currentParams.setTaskID(ui->task_type_dropdown->currentText());
    currentParams.setXMin(ui->xmin_edit->text().toDouble());
    currentParams.setXMax(ui->xmax_edit->text().toDouble());
    currentParams.setYMin(ui->ymin_edit->text().toDouble());
    currentParams.setYMax(ui->ymax_edit->text().toDouble());

    controller->requestMaintenanceData(currentParams);
}


void MaintenanceView::on_save_btn_clicked()
{
    showSaveDataDialog();
}


void MaintenanceView::on_compare_btn_clicked()
{
    controller->requestSavedFilesList();
}

void MaintenanceView::showAlertDialog(QString message)
{
    QMessageBox msgBox;
    msgBox.setText("Error!");
    msgBox.setInformativeText(message);
    msgBox.setIcon(QMessageBox::Critical);
    msgBox.setStandardButtons(QMessageBox::Close);
    msgBox.exec();
}

void MaintenanceView::showWaitingDialog()
{
    waitingDialog->showDialog();
}

void MaintenanceView::closeWaitingDialog()
{
    waitingDialog->closeDialog();
}

void MaintenanceView::showSaveDataDialog()
{
    int ok;

    SaveFileDialog dialog(this,
                          "MAINTENANCE: "+QDateTime::currentDateTime().toString());
    ok = dialog.exec();

    if (ok > 0){
        controller->requestStoreMaintenanceData(dialog.getFileName());
    }

}

#include "Dialogs/filepickerdialog.h"
void MaintenanceView::showDataChooserDialog(QStringList &items)
{
    int ok;
    FilePickerDialog dialog(this, items);
    ok = dialog.exec();
    if(ok > 0) {
        controller->requestMaintenanceData(dialog.getSelectedFileName());
    }
}

void MaintenanceView::displayMaintenanceData(MaintenanceData data, MaintenanceDataSrc src)
{
    QString str = data.getTasksID();
    if(str.isEmpty()) return;

    ui->no_data_label->hide();
    chartHelper->getChartView()->show();

    str = str.toLower().replace("_"," ");
    ui->avg_text_label->setText(QString("Count for ").append(str).append(": "));
    ui->avg_value_label->setText(QString("%1").arg(data.getTasksCount()));

    switch (src) {
    case DIGI_TRAFFIC:
        chartHelper->appendCurrentData(data.getTasksID(), data.getTasksCount());
        break;
    case LOCAL_DB:
        chartHelper->appendSavedData(data.getTasksID(), data.getTasksCount());
        break;
    }
}

void MaintenanceView::enableSaveButton()
{
    ui->save_btn->setEnabled(true);
    ui->clear_btn->setEnabled(true);
    ui->save_png_btn->show();
}

void MaintenanceView::showSaveSuccessNoti()
{
    ui->save_success_noti->show();
}



void MaintenanceView::on_location_dropdown_textActivated(const QString &arg1)
{
    Location loc = locations.value(arg1);
    ui->xmin_edit->setText(QString("%1").arg(loc.xMin));
    ui->xmax_edit->setText(QString("%1").arg(loc.xMax));
    ui->ymin_edit->setText(QString("%1").arg(loc.yMin));
    ui->ymax_edit->setText(QString("%1").arg(loc.yMax));
}

void MaintenanceView::on_save_png_btn_clicked()
{
    chartHelper->saveToPng();

}


void MaintenanceView::on_pushButton_clicked()
{
    ui->save_success_noti->hide();
}

