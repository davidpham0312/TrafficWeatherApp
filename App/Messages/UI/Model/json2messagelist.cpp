#include "json2messagelist.h"

Json2MessageList::Json2MessageList()
{

}

void Json2MessageList::process(QByteArray &json)
{
    QJsonDocument doc = QJsonDocument::fromJson(json);
    QJsonArray featuresArr;
    //parse the features array from the json document if possible
    if(!jsonDocumentToFeaturesArray(doc,featuresArr)) return; //error, no "features" entry found
    //convert the list of festures to the list of messages they contain
    if(!parseMessagesFromFeatures(featuresArr,messages)) return;  //error, no messages data found

}

// return parsed messages, if no message was parsed the list will be empty
QList<Message> Json2MessageList::getMessages()
{
    return messages;
}

// this function must be called if the instance of this class needs to be reused
void Json2MessageList::clear()
{
    messages.clear();
}

// we are interested in the content of "features" entry which has an array of features
// this function looks for the "features" entry that holds an array and returns it in a QJsonArray
bool Json2MessageList::jsonDocumentToFeaturesArray(QJsonDocument &json, QJsonArray &featuresArr)
{
    //DEBUG: print all top level entries and see if they are an array
    // foreach(const QString& key, jsonObj.keys()) {
    //        QJsonValue value = jsonObj.value(key);
    //        qDebug() << "Key = " << key << ", Value = " << value.isObject();
    //  }

    if(json.isEmpty() || json.isNull()) return false;

    auto jsonObj = json.object();
    auto featuresValue = jsonObj.value("features");
    if (featuresValue.isNull()) return false; // error: no messages to parse


    featuresArr = featuresValue.toArray();
    return true;
}


//This function parses the "features" entry of the messages JSON response document
// we are interested in the content "properties" entry of every feature, properties contain message details
// this function goes through every "properties" entry and create a message from it
bool Json2MessageList::parseMessagesFromFeatures(QJsonArray &featuresArr, QList<Message> &messages)
{

   foreach(auto feature, featuresArr) {

       QJsonValue tempValue = feature.toObject().value("properties");
       if(tempValue.isUndefined() || tempValue.isNull()) continue;

       QJsonObject properties= tempValue.toObject();
       if(properties.isEmpty()) continue;

       Message message;
       message.setMessageType(properties.value("situationType").toString());
       message.setTrafficAnnouncementType(properties.value("trafficAnnouncementType").toString());

       QJsonObject contact = properties.value("contact").toObject();
       parseContact(contact,message);

       QJsonObject announcements = properties.value("announcements").toArray().at(0).toObject();
       //if no announcments parsed, message is useless, abort
       if(parseAnnouncements(announcements ,message) == true) {
           messages.append(message);
       };

   }

    return messages.isEmpty() ? false : true;
}


bool Json2MessageList::parseAnnouncements(QJsonObject &announcementsJson, Message &message)
{
    if (announcementsJson.isEmpty()) return false;
    message.setTitle(announcementsJson.value("title").toString()); //TODO: toString can be given default value to indicate no data
    message.setEarlyClosing(announcementsJson.value("earlyClosing").toString("ONTIME"));
    message.setComment(announcementsJson.value("comment").toString());
    message.setAdditionalInformation(announcementsJson.value("additionalInformation").toString());
    message.setSenderName(announcementsJson.value("sender").toString());

    QJsonArray features = announcementsJson.value("features").toArray();
    parseAnnouncementsFeatures(features,message);

    QJsonObject location = announcementsJson.value("location").toObject();
    parseAnnouncementsLocation(location, message);

    QJsonObject timeAndDuration = announcementsJson.value("timeAndDuration").toObject();
    parseAnnouncementsTimeAndDuration(timeAndDuration, message);


//    qDebug() << "is there any work phases ? : " << announcementsJson.value("roadWorkPhases").toArray();

    return true;
}

bool Json2MessageList::parseAnnouncementsFeatures(QJsonArray &featuresJson, Message &message)
{
    QList<QString> features;
    foreach(auto feature, featuresJson){
        features.append(feature.toObject().value("name").toString());
    }
    message.setFeatures(features);
    return !features.isEmpty();
}

bool Json2MessageList::parseAnnouncementsLocation(QJsonObject &locationJson, Message &message)
{
    message.setLocation(locationJson.value("description").toString("unknown location"));
    return true;
}

//bool Json2MessageList::parseAnnouncementsLocationDetails(QJsonObject &locationDetailJson, Message &message)
//{
//    //todo: maybe replace this with direction ?
//    return true;
//}

//bool Json2MessageList::parseAnnouncementsWorkPhases(QJsonArray &workPhasesJson, Message &message)
//{

//    return true;
//}

bool Json2MessageList::parseAnnouncementsTimeAndDuration(QJsonObject &dateTimeJson, Message &message)
{
    QString start = dateTimeJson.value("startTime").toString();
    if (!start.isEmpty()) message.setStarttime(QDateTime::fromString(start, Qt::ISODate));

    QString end = dateTimeJson.value("endTime").toString();
    if (!end.isEmpty()) message.setEndtime(QDateTime::fromString(end, Qt::ISODate));
    else message.setEndtime(QDateTime::fromString(start, Qt::ISODate));

    message.setEstimatedDuration(dateTimeJson.value("estimatedDuration").toObject().value("informal").toString("unspecified"));
    return true;
}


bool Json2MessageList::parseContact(QJsonObject &contactJson, Message &message)
{
    message.setContactEmail(contactJson.value("email").toString());
    message.setContactNumber(contactJson.value("phone").toString());
    return true;
}
