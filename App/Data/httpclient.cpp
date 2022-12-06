#include "httpclient.h"


HttpClient::HttpClient(QObject* parent): QObject(parent)
{
    manager = new QNetworkAccessManager(this);
    //connect onRequestFinished slot for callback when request is done
    connect(manager, &QNetworkAccessManager::finished, this, &HttpClient::onRequestFinished);

}

HttpClient::~HttpClient()
{
    delete manager;
}


void HttpClient::requestData(QString url)
{
    QNetworkRequest request;
    request.setUrl(QUrl(url));
//    request.setRawHeader("Accept","application/json;charset=UTF-8");

    QNetworkReply *reply = manager->get(request);
    connect(reply, &QNetworkReply::errorOccurred,this, &HttpClient::onRequestFailed);
}

void HttpClient::onRequestFinished(QNetworkReply *reply)
{
    qDebug() << "onRequestFinished ";
    reply->deleteLater();

}

void HttpClient::onRequestFailed(QNetworkReply::NetworkError)
{

}
#include <QDir>
#include <QJsonDocument>

void HttpClient::storeReplyContentToFile(QString dir, QString name, QByteArray &data)
{
        //create the temp directory if not already there
        QDir().mkpath(dir);

        //save the reply to a json file
        QFile file(QString("%1/%2").arg(dir,name));
        file.remove();
        if (file.open(QIODevice::ReadWrite)){
            file.write(data);
        }
        file.close();
}

