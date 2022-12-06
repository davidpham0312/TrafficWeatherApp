#include "location.h"

QJsonObject Location::toJsonObject()
{
    QJsonObject obj;
    obj["locName"] = this->locName;
    obj["xMin"]    = this->xMin;
    obj["yMin"]    = this->yMin;
    obj["xMax"]    = this->xMax;
    obj["yMax"]    = this->yMax;
    return obj;
}

Location Location::fromJson(QJsonObject json)
{
    Location loc;
    loc.locName = json["locName"].toString();
    loc.xMin = json["xMin"].toDouble();
    loc.yMin = json["yMin"].toDouble();
    loc.xMax = json["xMax"].toDouble();
    loc.yMax = json["yMax"].toDouble();
    return loc;
}
