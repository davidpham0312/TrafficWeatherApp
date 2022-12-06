#include "messagesview.h"
#include "ui_messagesview.h"
#include "Messages/UI/messagescontroller.h"

MessagesView::MessagesView(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::MessagesView)
    , msgController_{nullptr}
{
    ui->setupUi(this);
    ui->msgSaveSuccessNoti->hide();
    waitingDialog = new WaitDialog(this);
}

MessagesView::~MessagesView()
{
    delete ui;
}

void MessagesView::displayCurrentMessagesTitle(QString messagesCount){

    QString formattedSituationType = ui->msgTypeDropdown->currentText()
                                    .split("_").join(" ").toLower();
    QString hours = ui->msgHoursSpinBox->text();
    // Set label depending on number of messages and hour (add plural / keep singular form)
    ui->msgCurrentTitleLabel->setText(messagesCount + " " + formattedSituationType
                               + (messagesCount == "1"|| messagesCount == "0" ? "" : "s")
                               + " from the past " + hours
                               + (hours == "1" || hours == "0" ? " hour" : " hours"));
}

void MessagesView::displayComparingMessagesTitle(QString messagesCount, QString situationType){

    QString formattedSituationType = situationType.split("_").join(" ").toLower();

    ui->msgComparingTitleLabel->setText(messagesCount + " " + formattedSituationType
                               + (messagesCount == "1"|| messagesCount == "0" ? "" : "s"));
}

void MessagesView::showSaveDataDialog()
{
    int ok;

    SaveFileDialog dialog(this,
                          "MESSAGE: "+QDateTime::currentDateTime().toString());
    ok = dialog.exec();

    if (ok > 0){
        msgController_->saveButtonClicked(dialog.getFileName());
    }

}

void MessagesView::showAlertDialog(QString message)
{
    QMessageBox msgBox;
    msgBox.setText("Error!");
    msgBox.setInformativeText(message);
    msgBox.setIcon(QMessageBox::Critical);
    msgBox.setStandardButtons(QMessageBox::Close);
    msgBox.exec();
}

void MessagesView::showWaitingDialog()
{
    waitingDialog->showDialog();
}

void MessagesView::closeWaitingDialog()
{
    waitingDialog->closeDialog();
}

void MessagesView::enableSaveButton()
{
    ui->msgSaveButton->setEnabled(true);
}


#include "Dialogs/filepickerdialog.h"
void MessagesView::showDataChooserDialog(QStringList &items)
{
    int ok;
    FilePickerDialog dialog(this, items);
    ok = dialog.exec();
    if(ok > 0) {
        msgController_->requestComparingData(dialog.getSelectedFileName());
    }
}

void MessagesView::showSaveSuccessNoti()
{
    ui->msgSaveSuccessNoti->show();
}

void MessagesView::displayCurrentMessageCards(QList<Message>allMessages){
    ui->msgScrollWidget->hide();

    QLayoutItem* item;
    while ( (item = ui->msgCurrentBoxesLayout->layout()->takeAt(0) ) != NULL )
    {
        delete item->widget();
        delete item;
    }

    for (int i = 0; i < allMessages.size(); i++) {
        Message m = allMessages.at(i);
        MessageCardWidget *messageCard = new MessageCardWidget(
                                      m.getTitle(), m.getComment(), m.getLocation(),
                                      m.getFeatures(),m.getStarttime(), m.getEndtime(),
                                      m.getContactEmail(), m.getContactNumber());
        messageCard->addCurrentDataToCard();
        ui->msgCurrentBoxesLayout->addWidget(messageCard, 0, Qt::AlignTop);

    }
    ui->msgCurrentBoxesLayout->setAlignment(Qt::AlignTop);
    ui->msgScrollWidget->show();
}

void MessagesView::displayComparingMessageCards(QList<Message>allMessages){
    ui->msgScrollWidget->hide();

    QLayoutItem* item;
    while ( (item = ui->msgComparingBoxesLayout->layout()->takeAt(0) ) != NULL )
    {
        delete item->widget();
        delete item;
    }
    for (int i = 0; i < allMessages.size(); i++) {
        Message m = allMessages.at(i);
        MessageCardWidget *messageCard = new MessageCardWidget(
                                      m.getTitle(), m.getComment(), m.getLocation(),
                                      m.getFeatures(),m.getStarttime(), m.getEndtime(),
                                      m.getContactEmail(), m.getContactNumber());
        messageCard->addComparingDataToCard();
        ui->msgComparingBoxesLayout->addWidget(messageCard, 0, Qt::AlignTop);

    }
    ui->msgComparingBoxesLayout->setAlignment(Qt::AlignTop);
    ui->msgScrollWidget->show();
}

void MessagesView::setController(MessagesController *controller){
    msgController_ = controller;
}

void MessagesView::saveUserInput()
{
    MessagesParams params;
    params.setHoursInPast(ui->msgHoursSpinBox->value());
    params.setSituationType(ui->msgTypeDropdown->currentText());
    AppDatabase::getInstance().storeMessagesSettings(params);

}

void MessagesView::restoreUserInput()
{
    MessagesParams currentParams = AppDatabase::getInstance().restoreMessagesSettings();
    ui->msgHoursSpinBox->setValue(currentParams.getHoursInPast());
    ui->msgTypeDropdown->setCurrentText(currentParams.getSituationType());
}

bool MessagesView::checkInputDifference(QString currentTitle, QString selectedHours, QString selectedType){
    if (currentTitle.contains(" " + selectedHours + " hour") &&
            currentTitle.contains(selectedType.split("_").join(" "))){
        return false;
    }
    return true;
}


void MessagesView::on_msgShowButton_clicked()
{
    if (!checkInputDifference(ui->msgCurrentTitleLabel->text(), ui->msgHoursSpinBox->text(),
                             ui->msgTypeDropdown->currentText())){
        return;
    }
    else if (msgController_ != nullptr){
        msgController_->showButtonClicked(ui->msgHoursSpinBox->text().toInt(),
                                          ui->msgTypeDropdown->currentText());
        ui->msgCompareButton->setDisabled(false);
    }
}


void MessagesView::on_msgCompareButton_clicked()
{
    msgController_->compareButtonClicked();
}


void MessagesView::on_msgSaveButton_clicked()
{
    msgController_->checkUserInputs(ui->msgHoursSpinBox->text().toInt(),
                                    ui->msgTypeDropdown->currentText());
}


void MessagesView::on_msgCloseNotiButton_clicked()
{
    ui->msgSaveSuccessNoti->hide();
}

