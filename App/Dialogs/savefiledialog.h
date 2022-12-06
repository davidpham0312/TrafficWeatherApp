#ifndef SAVEFILEDIALOG_H
#define SAVEFILEDIALOG_H

#include <QDialog>
#include <QMessageBox>

namespace Ui {
class SaveFileDialog;
}

class SaveFileDialog : public QDialog
{
    Q_OBJECT

public:
    explicit SaveFileDialog(QWidget *parent = nullptr, QString defaultName="");
    ~SaveFileDialog();

private:
    Ui::SaveFileDialog *ui;
    QString filename;

public:
    int exec();
    const QString getFileName() const;

private:
  void showAlertDialog(QString message);

};

#endif // SAVEFILEDIALOG_H
