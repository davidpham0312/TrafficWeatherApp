#ifndef MESSAGESCONTROLLER_H
#define MESSAGESCONTROLLER_H

#include <QObject>
#include <Messages/message.h>
#include <Messages/messagesparams.h>
#include <Messages/UI/Model/messagesrepository.h>
#include <Messages/UI/messagesview.h>
class MessagesController : public QObject
{
    Q_OBJECT
public:
    MessagesController(MessagesRepository &msgRepo, MessagesView *msgView, QObject *parent = nullptr);

public slots:
    void showButtonClicked(const int hoursInPast, const QString situationType);
    void saveButtonClicked(QString filename);
    void compareButtonClicked();

    void requestComparingData(QString filename);
    void checkUserInputs(const int hoursInPast, const QString situationType);
private:
    void onDataFetchedFromServer(QList<Message> messages, bool success);
    void onDataLoadedFromDB(QList<Message> messages, bool success);

    MessagesView *msgView_;
    MessagesParams msgParams;
    MessagesRepository &msgRepo_;
    QStringList fileList;
};

#endif // MESSAGESCONTROLLER_H
