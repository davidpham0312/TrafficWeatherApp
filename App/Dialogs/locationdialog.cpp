#include "locationdialog.h"
#include "ui_locationdialog.h"

LocationDialog::LocationDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::LocationDialog)
{
    ui->setupUi(this);
    setWindowTitle("Save new location");
}

LocationDialog::~LocationDialog()
{
    delete ui;
}

const Location &LocationDialog::geLocation() const
{
    return location;
}

void LocationDialog::showAlertDialog(QString message) {
    QMessageBox msgBox;
    msgBox.setText("Error!");
    msgBox.setInformativeText(message);
    msgBox.setIcon(QMessageBox::Critical);
    msgBox.setStandardButtons(QMessageBox::Close);
    msgBox.exec();
}

int LocationDialog::exec()
{
    int a  = QDialog::exec();
    if( a <= 0 ){ //cancel clicked
        return -1;
    }

    location.locName = ui->location_edit->text();
    location.xMin = ui->xmin_edit->text().toFloat();
    location.xMax = ui->xmax_edit->text().toFloat();
    location.yMin = ui->ymim_edit->text().toFloat();
    location.yMax = ui->ymax_edit->text().toFloat();

    //check inputs correctness
    if(location.locName.isEmpty()){
        showAlertDialog("Invalid location name: name must no be empty");
        return -1;
    }
    //coords must be in the requried range
    if(location.xMin < 19 ||
       location.xMin > 32 ||
       location.xMin> location.xMax){
        showAlertDialog("Invalid coordinates: [xmin,xmax] must be in the range [19,32]");
        return -1;
    }
    if(location.xMax < 19 ||
       location.xMax > 32 )
    {
        showAlertDialog("Invalid coordinates: [xmin,xmax] must be in the range [19,32]");
        return -1;
    }
    if(location.yMin < 59 ||
       location.yMin > 72 ||
       location.yMin> location.yMax){
        showAlertDialog("Invalid coordinates: [ymin,ymax] must be in the range [59,72]");
        return -1;
    }
    if(location.yMax < 59 ||
       location.yMax > 72 )
    {
        showAlertDialog("Invalid coordinates: [ymin,ymax] must be in the range [59,72]");
        return -1;
    }
    //store location in db
    AppDatabase::getInstance().storeLocation(location);

    return a;
}
