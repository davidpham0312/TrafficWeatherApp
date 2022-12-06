#ifndef XML2WEATHERDATACONVERTER_H
#define XML2WEATHERDATACONVERTER_H

#include <QMap>
#include <QByteArray>
#include <QXmlStreamReader>

#include<QDateTime>


class Xml2WeatherDataConverter
{
private:
    QMap<QString, QList<QPair<QDateTime,double>>* > parameter2ListMapper;
public:
    Xml2WeatherDataConverter();
    bool process(QByteArray data);
private:
    bool parseData(QXmlStreamReader &xml, QList<QPair<QDateTime, double>> *list);
protected:
    virtual void populateParameter2ListMapper(QMap<QString, QList<QPair<QDateTime,double>>* > &mapper) = 0;
};


#endif // XML2WEATHERDATACONVERTER_H
