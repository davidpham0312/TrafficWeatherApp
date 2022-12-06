#include "message.h"

const QString &Message::getMessageType() const
{
    return messageType;
}

void Message::setMessageType(const QString &newMessageType)
{
    messageType = newMessageType;
}

const QString &Message::getTrafficAnnouncementType() const
{
    return trafficAnnouncementType;
}

void Message::setTrafficAnnouncementType(const QString &newTrafficAnnouncementType)
{
    trafficAnnouncementType = newTrafficAnnouncementType;
}

const QString &Message::getTitle() const
{
    return title;
}

void Message::setTitle(const QString &newTitle)
{
    title = newTitle;
}

const QString &Message::getAdditionalInformation() const
{
    return additionalInformation;
}

void Message::setAdditionalInformation(const QString &newAdditionalInformation)
{
    additionalInformation = newAdditionalInformation;
}

const QString &Message::getComment() const
{
    return comment;
}

void Message::setComment(const QString &newComment)
{
    comment = newComment;
}

const QDateTime &Message::getStarttime() const
{
    return starttime;
}

void Message::setStarttime(const QDateTime &newStarttime)
{
    starttime = newStarttime;
}

const QDateTime &Message::getEndtime() const
{
    return endtime;
}

void Message::setEndtime(const QDateTime &newEndtime)
{
    endtime = newEndtime;
}

const QString &Message::getEstimatedDuration() const
{
    return estimatedDuration;
}

void Message::setEstimatedDuration(const QString &newEstimatedDuration)
{
    estimatedDuration = newEstimatedDuration;
}

const QString &Message::getLocation() const
{
    return location;
}

void Message::setLocation(const QString &newLocation)
{
    location = newLocation;
}


const QList<QString> &Message::getFeatures() const
{
    return features;
}

void Message::setFeatures(const QList<QString> &newFeatures)
{
    features = newFeatures;
}

const QString &Message::getEarlyClosing() const
{
    return earlyClosing;
}

void Message::setEarlyClosing(const QString &newEarlyClosing)
{
    earlyClosing = newEarlyClosing;
}

const QString &Message::getSenderName() const
{
    return senderName;
}

void Message::setSenderName(const QString &newSenderName)
{
    senderName = newSenderName;
}

const QString &Message::getContactNumber() const
{
    return contactNumber;
}

void Message::setContactNumber(const QString &newContactNumber)
{
    contactNumber = newContactNumber;
}

const QString &Message::getContactEmail() const
{
    return contactEmail;
}

void Message::setContactEmail(const QString &newContactEmail)
{
    contactEmail = newContactEmail;
}

Message::Message()
{

}
