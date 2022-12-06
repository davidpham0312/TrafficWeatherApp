#include "savefiledialog.h"
#include "ui_savefiledialog.h"

SaveFileDialog::SaveFileDialog(QWidget *parent, QString defaultName) :
    QDialog(parent),
    ui(new Ui::SaveFileDialog)
{
    ui->setupUi(this);
    ui->data_label_edit->setText(defaultName);
    this->setWindowTitle("Save data");
}

SaveFileDialog::~SaveFileDialog()
{
    delete ui;
}


const QString SaveFileDialog::getFileName() const
{
    return filename;
}

void SaveFileDialog::showAlertDialog(QString message) {
    QMessageBox msgBox;
    msgBox.setText("Error!");
    msgBox.setInformativeText(message);
    msgBox.setIcon(QMessageBox::Critical);
    msgBox.setStandardButtons(QMessageBox::Close);
    msgBox.exec();
}

int SaveFileDialog::exec()
{
    int a  = QDialog::exec();
    QString text = ui->data_label_edit->text();
    if( a <= 0 ){
        return -1;
    }
    else if(text.isEmpty()){
        showAlertDialog("Label must not be empty!");
        return -1;
    }
    filename = text;
    return 1;
}
