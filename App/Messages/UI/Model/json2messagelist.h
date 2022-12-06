#ifndef JSON2MESSAGELIST_H
#define JSON2MESSAGELIST_H
#include <QList>
#include <QByteArray>
#include <QJsonValue>
#include <QJsonArray>
#include <QJsonObject>
#include <QJsonDocument>
#include <QDateTime>
#include "Messages/message.h"

class Json2MessageList
{
private:
    QList<Message> messages;


public:
    Json2MessageList();
    void process(QByteArray& json);
    QList<Message> getMessages();
    void clear();

private:
    bool jsonDocumentToFeaturesArray(QJsonDocument& json, QJsonArray& featuresArr);
    bool parseMessagesFromFeatures(QJsonArray& featuresArr, QList<Message>& messages);

    bool parseAnnouncements(QJsonObject& announcementsJson, Message& message);
    bool parseAnnouncementsFeatures(QJsonArray& contactJson, Message& message);
    bool parseAnnouncementsLocation(QJsonObject& locationJson, Message& message);
    bool parseAnnouncementsTimeAndDuration(QJsonObject& dateTimeJson, Message& message);
//    bool parseAnnouncementsWorkPhases(QJsonArray& dateTimeJson, Message& message);
//    bool parseAnnouncementsLocationDetails(QJsonObject& locationDetailJson, Message& message);

    bool parseContact(QJsonObject& contactJson, Message& message);
};

#endif // JSON2MESSAGELIST_H
