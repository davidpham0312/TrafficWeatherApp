#ifndef LOCATIONDIALOG_H
#define LOCATIONDIALOG_H

#include <QDialog>
#include <QMessageBox>
#include <Data/location.h>
#include <Data/appdatabase.h>

namespace Ui {
class LocationDialog;
}

class LocationDialog : public QDialog
{
    Q_OBJECT

public:
    explicit LocationDialog(QWidget *parent = nullptr);
    ~LocationDialog();

private:
    Ui::LocationDialog *ui;
    Location location;

public:
    int exec();
    const Location &geLocation() const;

private:
  void showAlertDialog(QString message);
};

#endif // LOCATIONDIALOG_H
