#ifndef HTTPCLIENT_H
#define HTTPCLIENT_H

#include <QList>
#include <QObject>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QFile>

class HttpClient : public QObject
{
    Q_OBJECT
public:
    explicit HttpClient(QObject* parent = nullptr);
    ~HttpClient();
    //fetch data by sending an HTTP request to a given REST API
    void requestData(QString url);


protected slots:
    // internal callback for handling request response success
    // this function should be called even if reimplemeted, this is to clear some memory allocated earler
    // otherwize reply->deleteLater() needs to be called
    virtual void onRequestFinished(QNetworkReply* reply);
    // internal callback for handling request response failure
    // this function should be called even if reimplemeted, this is to clear some memory allocated earler
    // otherwize reply->deleteLater() needs to be called
    virtual void onRequestFailed(QNetworkReply::NetworkError errorCode);

protected:
    //convinience method to store reply content to a temporary file;
    void storeReplyContentToFile(QString dir, QString name, QByteArray &data);

private:
    QNetworkAccessManager* manager;
};

#endif // HTTPCLIENT_H
