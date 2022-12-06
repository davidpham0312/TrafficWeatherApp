#ifndef MESSAGESVIEW_H
#define MESSAGESVIEW_H

#include <QMessageBox>
#include <QWidget>
#include <Messages/message.h>
#include <Messages/messagesparams.h>
#include <Messages/UI/messagecardwidget.h>
#include <Dialogs/waitdialog.h>
#include <Dialogs/savefiledialog.h>
#include <Data/appdatabase.h>

namespace Ui { class MessagesView; }

class MessagesController;

class MessagesView : public QWidget
{
    Q_OBJECT

public:
    MessagesView(QWidget *parent = nullptr);
    ~MessagesView();
    void displayCurrentMessageCards(QList<Message>allMessages);
    void displayCurrentMessagesTitle(QString messagesCount);
    void displayComparingMessageCards(QList<Message>allMessages);
    void displayComparingMessagesTitle(QString messagesCount, QString situationType);
    void showSaveDataDialog();
    void showAlertDialog(QString message);
    void showWaitingDialog();
    void closeWaitingDialog();
    void enableSaveButton();
    void showDataChooserDialog(QStringList &items);
    void showSaveSuccessNoti();
    void setController(MessagesController *msgController);    
    void saveUserInput();
    void restoreUserInput();

private slots:
    void on_msgCompareButton_clicked();
    void on_msgShowButton_clicked();

    void on_msgSaveButton_clicked();

    void on_msgCloseNotiButton_clicked();

private:
    bool checkInputDifference(QString currentTitle, QString selectedHours, QString selectedType);
    void addMessageCardsToLayout();
private:
    Ui::MessagesView *ui;
    MessagesController *msgController_;
    WaitDialog* waitingDialog;
    MessagesParams currentParams;
};

#endif // MESSAGESVIEW_H
