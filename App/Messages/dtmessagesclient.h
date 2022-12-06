#ifndef DTMESSAGESCLIENT_H
#define DTMESSAGESCLIENT_H

#include "messagesparams.h"
#include "MessagesCallbacks.h"
#include <QList>
#include <QObject>
#include <QNetworkAccessManager>
#include <QNetworkReply>


class DtMessagesClient : public QObject
{
    Q_OBJECT
public:
    explicit DtMessagesClient(QObject* parent = nullptr);
    ~DtMessagesClient();
    void fetchMessages(MessagesParams params, OnMessagesReady);
    void fetchMessageTypes(MessagesParams params, OnMessageTypesReady);


private slots:
    void onRequestFinished(QNetworkReply* reply);
    void onRequestFailed(QNetworkReply::NetworkError errorCode);

private:
    QNetworkAccessManager* manager;
    QList<Message> messages;
    QString currentContent;



    QString messagesBaseUrl = "https://tie.digitraffic.fi/api/traffic-message/v1/messages?";
    QList<const QString> situationTypes;

};

#endif // DTMESSAGESCLIENT_H
