#ifndef DTMESSAGESCLIENT_H
#define DTMESSAGESCLIENT_H

#include "Messages/messagesparams.h"
#include "Messages/MessagesCallbacks.h"
#include <QList>
#include <QObject>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include "Data/httpclient.h"


class MessagesClient : public HttpClient{
    Q_OBJECT
public:
    MessagesClient(QObject* parent);
    //fetch messages asynchronously and callback the caller when ready
    void fetchMessages(MessagesParams params, OnMessagesReady callback);

protected:
    //internal callback for handling request response success
    void onRequestFinished(QNetworkReply* reply);
    //internal callback for handling request response failure
    void onRequestFailed(QNetworkReply::NetworkError errorCode);

private:
    OnMessagesReady readyCallback;
    QByteArray currentData;
    bool pendingRequest = false;
};

#endif // DTMESSAGESCLIENT_H
