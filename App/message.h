#ifndef MESSAGE_H
#define MESSAGE_H

#include <QString>
#include <QList>
#include <QDateTime>

class Message
{

private:
    //main details
    QString messageType;
    QString trafficAnnouncementType; //this is different from the one above
    QString title;
    QString additionalInformation;
    QString comment;
    QDateTime starttime; //QDateTime time = QDateTime::fromString("2019-03-12T03:24:30.282Z","yyyy-MM-ddTHH:mm:ss.zzzZ");
    QDateTime endtime; //QDateTime time = QDateTime::fromString("2019-03-12T03:24:30.282Z","yyyy-MM-ddTHH:mm:ss.zzzZ");
    QString estimatedDuration;
    QString location;
    QList<QString> features;
    // additional details (shown in a dialog window)
    QString earlyClosing;
    QString contactEmail;
    QString contactNumber;
    QString senderName;
//    QString locationDetails;
//    QString roadWorkPhases;


public:
    Message();
    const QString &getMessageType() const;
    void setMessageType(const QString &newMessageType);
    const QString &getTrafficAnnouncementType() const;
    void setTrafficAnnouncementType(const QString &newTrafficAnnouncementType);
    const QString &getTitle() const;
    void setTitle(const QString &newTitle);
    const QString &getAdditionalInformation() const;
    void setAdditionalInformation(const QString &newAdditionalInformation);
    const QString &getComment() const;
    void setComment(const QString &newComment);
    const QDateTime &getStarttime() const;
    void setStarttime(const QDateTime &newStarttime);
    const QDateTime &getEndtime() const;
    void setEndtime(const QDateTime &newEndtime);
    const QString &getEstimatedDuration() const;
    void setEstimatedDuration(const QString &newEstimatedDuration);
    const QString &getLocation() const;
    void setLocation(const QString &newLocation);
    const QList<QString> &getFeatures() const;
    void setFeatures(const QList<QString> &newFeatures);
    const QString &getEarlyClosing() const;
    void setEarlyClosing(const QString &newEarlyClosing);
    const QString &getSenderName() const;
    void setSenderName(const QString &newSenderName);
    const QString &getContactNumber() const;
    void setContactNumber(const QString &newContactNumber);
    const QString &getContactEmail() const;
    void setContactEmail(const QString &newContactEmail);
//    const QString &getLocationDetails() const;
//    void setLocationDetails(const QString &newLocationDetails);
//    const QString &getRoadWorkPhases() const;
//    void setRoadWorkPhases(const QString &newRoadWorkPhases);
};

#endif // MESSAGE_H
