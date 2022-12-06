#include "messagesparams.h"

int MessagesParams::getHoursInPast() const
{
    return hoursInPast;
}

void MessagesParams::setHoursInPast(int newHoursInPast)
{
    hoursInPast = newHoursInPast;
}

const QString &MessagesParams::getSituationType() const
{
    return situationType;
}

void MessagesParams::setSituationType(const QString &newSituationType)
{
    situationType = newSituationType;
}

// generates a HTTP get request header from the stored message parameters
QString MessagesParams::toHttpRequestUrl()
{
    QString urlStr  = messagesBaseUrl;
    urlStr.append(QString("inactiveHours=%1").arg(this->hoursInPast));
    urlStr.append("&includeAreaGeometry=false");
    urlStr.append(QString("&situationType=%1").arg(this->situationType));
    return urlStr;
}

#include <QJsonObject>
#include <QJsonDocument>

const QByteArray MessagesParams::toJsonObject()
{
    QJsonObject obj;
    obj["situationType"] = this->situationType;
    obj["hoursInPast"] = this->hoursInPast;
    QJsonDocument doc(obj);
    return doc.toJson();
}

MessagesParams MessagesParams::fromJson(QByteArray &json)
{
    QJsonDocument doc = QJsonDocument::fromJson(json);
    QJsonObject obj = doc.object();
    MessagesParams data;
    data.situationType = obj["situationType"].toString();
    data.hoursInPast = obj["hoursInPast"].toInt();
    return data;
}

MessagesParams::MessagesParams()
{

}
