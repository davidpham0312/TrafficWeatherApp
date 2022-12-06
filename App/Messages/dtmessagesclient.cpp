#include "dtmessagesclient.h"
#include "json2messagelist.h"
#include <QFile>


DtMessagesClient::DtMessagesClient(QObject*)
{
    manager = new QNetworkAccessManager(this);
    //connect onRequestFinished slot for callback when request is done
    connect(manager, &QNetworkAccessManager::finished, this, &DtMessagesClient::onRequestFinished);
}

DtMessagesClient::~DtMessagesClient()
{
    delete manager;
}



void DtMessagesClient::fetchMessages(MessagesParams params, OnMessagesReady)
{
    QString urlStr  = messagesBaseUrl;
    urlStr.append(QString("inactiveHours=%1").arg(params.getHoursInPast()));
    urlStr.append("&includeAreaGeometry=false");
    urlStr.append(QString("&situationType=%1").arg(params.getSituationType()));

    QNetworkRequest request;
    request.setUrl(QUrl(urlStr));
    request.setRawHeader("Accept","application/json;charset=UTF-8");

    QNetworkReply *reply = manager->get(request);
    connect(reply, &QNetworkReply::errorOccurred,this, &DtMessagesClient::onRequestFailed);
}

void DtMessagesClient::fetchMessageTypes(MessagesParams params, OnMessageTypesReady)
{

}

void DtMessagesClient::onRequestFinished(QNetworkReply *reply)
{
    qDebug() << "onRequestFinished ";
    QByteArray data = reply->readAll();
    Json2MessageList converter;
    converter.process(data);
    QList<Message> messages = converter.getMessages();

    qDebug() << "parsed messages size = " << messages.size();
    foreach (Message m, messages) {
        qDebug() << "-----------------------------";
        qDebug() << m.getMessageType();
        qDebug() << m.getTrafficAnnouncementType();
        qDebug() << m.getTitle();
        qDebug() << m.getComment();
        qDebug() << m.getAdditionalInformation();
        qDebug() << m.getSenderName();
        qDebug() << m.getEarlyClosing();
    }
//    QJsonDocument doc = QJsonDocument::fromJson(data);
//    qDebug() << "doc.isArray(): " << doc.isArray()
//             << "doc.isObject(): "<< doc.isObject()
//             << "doc.isEmpty(): "<< doc.isEmpty()
//             << "doc.isNull(): "<< doc.isNull();

//    QJsonObject jsonObj = doc.object();
//    //print all top level entries and see if they are an array
//    foreach(const QString& key, jsonObj.keys()) {
//           QJsonValue value = jsonObj.value(key);
//           qDebug() << "Key = " << key << ", Value = " << value.isObject();
//     }

//    // we are interested in the content of "features" entry which has an array of features
//    auto featuresValue = jsonObj.find("features").value();

//    if (!featuresValue.isNull()){
//        QJsonArray featuresArr = featuresValue.toArray();
//        //we are interested in the properties of every feature
//        foreach(auto a, featuresArr) {
//            QJsonObject featureProperties = a.toObject().value("properties").toObject();
//            QJsonObject announcements = featureProperties.value("announcements").toArray().at(0).toObject();
//            qDebug() << "language = " << announcements.value("language").toString()
//                     << "title = " << announcements.value("title").toString()
//                     << "comment = " << announcements.value("comment");
////            qDebug() << "empty ? = " << featureProperties.isEmpty()
////                     << "count = " << featureProperties.count()
////                     << ", keys = " << featureProperties.keys();
//        }
//    }

//    QVariant statuscodeVariant = reply->attribute(QNetworkRequest::HttpStatusCodeAttribute) ;
//    int statuscode = statuscodeVariant.toInt();
//    // get response from the network reply
//    currentContent = QString(data) ;

//    qDebug() << "reply content: " << QString(data) << '\n';

//    //save the reply to a json file
//    QFile file("out.json");
//    if (file.open(QIODevice::ReadWrite)){
//        file.write(data);
//    }

    reply->deleteLater();

}

void DtMessagesClient::onRequestFailed(QNetworkReply::NetworkError errorCode)
{
    QNetworkReply *reply = qobject_cast<QNetworkReply*>(sender());
    qDebug() << "Received error:" << errorCode << "for url:" << reply->url();
    reply->deleteLater();

}

