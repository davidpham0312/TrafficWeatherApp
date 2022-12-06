#ifndef XML2WEATHEROBSERVATION_H
#define XML2WEATHEROBSERVATION_H

#include <QByteArray>
#include <QXmlStreamReader>
#include "weatherobservationdata.h"
#include "xml2weatherdataconverter.h"

class Xml2WeatherObservation : public Xml2WeatherDataConverter
{
private:
    WeatherObservationData observations;
public:
    Xml2WeatherObservation();
    WeatherObservationData getObservations() const;
protected:
    void populateParameter2ListMapper(QMap<QString, QList<QPair<QDateTime,double>>* > &parameter2ListMapper);
};
#endif // XML2WEATHEROBSERVATION_H
