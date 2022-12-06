#ifndef FILEPICKERDIALOG_H
#define FILEPICKERDIALOG_H

#include <QDialog>
#include <QStringListModel>
#include <QString>
#include <QFile>
#include <QMessageBox>

//savedNames file path for weather
#define FILE_PATH "DB/weather/savedFileList"

namespace Ui {
class FilePickerDialog;
}

class FilePickerDialog : public QDialog
{
    Q_OBJECT

public:
    explicit FilePickerDialog(QWidget *parent = nullptr, QStringList fileNames=QStringList());
    ~FilePickerDialog();

public:
    int exec();
    QString getSelectedFileName();
private:
    Ui::FilePickerDialog *ui;
    QStringListModel *model;
    QString filename;
    QStringList fileNames;

private:
  void showAlertDialog(QString message);
};

#endif // FILEPICKERDIALOG_H
