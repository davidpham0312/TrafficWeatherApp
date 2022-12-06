#include "messagescontroller.h"
#include <Messages/UI/Model/messagesrepository.h>
#include <iostream>
MessagesController::MessagesController(MessagesRepository &msgRepo, MessagesView *msgView, QObject *parent)
    : QObject{parent}
    , msgView_{msgView}
    , msgRepo_{msgRepo}
{
}

void MessagesController::showButtonClicked(const int hoursInPast, const QString situationType){
    msgParams.setHoursInPast(hoursInPast);
    msgParams.setSituationType(situationType);
    msgView_->showWaitingDialog();
    msgRepo_.getMessages(msgParams, member_func_to_ptr(&MessagesController::onDataFetchedFromServer, this));
}

void MessagesController::saveButtonClicked(QString filename){
    msgRepo_.storeMessages(filename, [](){});
    msgView_->showSaveSuccessNoti();
}

void MessagesController::compareButtonClicked(){
    fileList = msgRepo_.getStoredFilesList();
    msgView_->showDataChooserDialog(fileList);
}

void MessagesController::checkUserInputs(const int hoursInPast, const QString situationType)
{
    if (msgParams.getHoursInPast() != hoursInPast) {
        msgView_->showAlertDialog("The value of hours does not correspond to the displayed data.\n"
                                  "Change hours to " + QString::number(msgParams.getHoursInPast()) +
                                  " or click Show to load data with this input.");
        return;
    }
    else if (msgParams.getSituationType() != situationType) {
        msgView_->showAlertDialog("The value of maximum longitude (xMax) does not correspond to the displayed data.\n"
                                  "Change xMax to " + situationType + " or click Visualize to load data with this input.");
        return;
    }
    else {
        msgView_->showSaveDataDialog();
    }
}

void MessagesController::requestComparingData(QString filename){
    msgView_->showWaitingDialog();
    msgRepo_.getMessages(filename, member_func_to_ptr(&MessagesController::onDataLoadedFromDB, this));
}

void MessagesController::onDataFetchedFromServer(QList<Message> messages, bool success)
{
    msgView_->closeWaitingDialog();
    if (success){
        msgView_->enableSaveButton();
        const QString messagesCount = QString::number(messages.count());
        msgView_->displayCurrentMessagesTitle(messagesCount);
        msgView_->displayCurrentMessageCards(messages);
    }
    else{
        msgView_->showAlertDialog("Fething data from server failed! "
                                       "Please check your internet connection");
    }
}

void MessagesController::onDataLoadedFromDB(QList<Message> messages, bool success)
{
    msgView_->closeWaitingDialog();
    if (success) {
        QString messagesType = messages.at(0).getMessageType();
        msgView_->displayComparingMessagesTitle(QString::number(messages.size()), messagesType);
        msgView_->displayComparingMessageCards(messages);
    }
    else{
        msgView_->showAlertDialog("Failed to load data from the database! "
                                  "This could be due to bad file name");
    }
}
