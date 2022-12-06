#ifndef MESSAGESPARAMS_H
#define MESSAGESPARAMS_H

#include <QString>
class MessagesParams
{

private:
    int hoursInPast = 0;
    QString situationType = "TRAFFIC_ANNOUNCEMENT";
    const QString messagesBaseUrl = "https://tie.digitraffic.fi/api/traffic-message/v1/messages?";

public:
    MessagesParams();
    int getHoursInPast() const;
    void setHoursInPast(int newHoursInPast);
    const QString &getSituationType() const;
    void setSituationType(const QString &newSituationType);
    QString toHttpRequestUrl();

    //serialization
    const QByteArray toJsonObject();
    static MessagesParams fromJson(QByteArray &json);
};

#endif // MESSAGESPARAMS_H
