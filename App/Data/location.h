#ifndef LOCATION_H
#define LOCATION_H

#include <QString>
#include <QJsonObject>

class Location{
public:
    QString locName;
    float xMin, xMax, yMin, yMax;
public:
    //serialization
    QJsonObject toJsonObject();
    static Location fromJson(QJsonObject json);
};

#endif // LOCATION_H
