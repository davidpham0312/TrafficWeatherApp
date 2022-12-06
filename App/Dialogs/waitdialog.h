#ifndef WAITDIALOG_H
#define WAITDIALOG_H

#include <QWidget>
#include <QDialog>
#include <QPushButton>
#include <QMessageBox>
#include <QLabel>
#include <QMovie>
#include <QVBoxLayout>

class WaitDialog : public QWidget
{
    Q_OBJECT
public:
    explicit WaitDialog(QWidget *parent = nullptr);
    ~WaitDialog();
     void closeDialog();
     void showDialog();
protected:

private:
    QMessageBox::QDialog *newDialog;
    QPushButton *cancelButton;
    QLabel *infoLabel;
    QMovie *spinner;
    QLabel *spinnerLabel;
};

#endif // WAITDIALOG_H
