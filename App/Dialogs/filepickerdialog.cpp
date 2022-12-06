#include "filepickerdialog.h"
#include "ui_filepickerdialog.h"

FilePickerDialog::FilePickerDialog(QWidget *parent, QStringList fileNames):
    QDialog(parent),
    ui(new Ui::FilePickerDialog)
{

    ui->setupUi(this);
    this->fileNames = fileNames;
    this->setWindowTitle("Load data");
    model = new QStringListModel(this);
    model->setStringList(fileNames);
    ui->listView->setModel(model);
    ui->listView->scrollToTop();
    ui->listView->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->listView->setEditTriggers(QAbstractItemView::NoEditTriggers);
    //by default scroll bar appears when needed
    //ui->listView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOn);

}

FilePickerDialog::~FilePickerDialog()
{
    delete ui;
}

QString FilePickerDialog::getSelectedFileName()
{
    return filename;
}

int FilePickerDialog::exec()
{
    int a  = QDialog::exec();

    auto indices = ui->listView->selectionModel()->selectedIndexes();

    if( a <= 0 ){
        return -1;
    }
    else if(indices.isEmpty()){
        showAlertDialog("No file selected");
        return -1;
    }
    auto index = indices.at(0);
    QString text = fileNames.at(index.row());
    filename = text;
    return 1;
}


void FilePickerDialog::showAlertDialog(QString message)
{
    QMessageBox msgBox;
    msgBox.setText("Error!");
    msgBox.setInformativeText(message);
    msgBox.setIcon(QMessageBox::Critical);
    msgBox.setStandardButtons(QMessageBox::Close);
    msgBox.exec();
}
