#include "waitdialog.h"
WaitDialog::WaitDialog(QWidget *parent) : QWidget(parent)
{
    //define wait dialog
            newDialog = new QMessageBox::QDialog(this, Qt::Window);
            newDialog->setWindowModality(Qt::ApplicationModal);
            infoLabel = new QLabel(newDialog);
            spinnerLabel = new QLabel(newDialog);
            //add spinner to label
            spinner = new QMovie("://MaterialDesignIcons/Spinner.gif");
            spinnerLabel->setMaximumSize(60, 60);
            spinnerLabel->setMovie(spinner);
            spinnerLabel->show();
            spinner->start();
            //add wait dialog widgets to layout
            QVBoxLayout *waitDialogLayout = new QVBoxLayout(newDialog);
            newDialog->setWindowTitle("Processing...");
            newDialog->resize(150, 100);
            infoLabel->setText("Please wait:");
            waitDialogLayout->addWidget(infoLabel);
            waitDialogLayout->addWidget(spinnerLabel);
            waitDialogLayout->setStretch(0, 1);
            waitDialogLayout->setStretch(1, 1);
            waitDialogLayout->setStretch(2, 1);
            waitDialogLayout->itemAt(0)->setAlignment(Qt::AlignJustify);
            waitDialogLayout->itemAt(1)->setAlignment(Qt::AlignJustify);
            newDialog->setLayout(waitDialogLayout);
//            newDialog->show();

}
WaitDialog::~WaitDialog()
{
    delete spinner;
}
//send close signal
void WaitDialog::closeDialog()
{
    newDialog->close();
}

void WaitDialog::showDialog()
{
    newDialog->show();
}
