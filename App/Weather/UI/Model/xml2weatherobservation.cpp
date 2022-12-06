#include "xml2weatherobservation.h"

Xml2WeatherObservation::Xml2WeatherObservation() : Xml2WeatherDataConverter()
{

}

WeatherObservationData Xml2WeatherObservation::getObservations() const
{
    return observations;
}


void Xml2WeatherObservation::populateParameter2ListMapper(QMap<QString, QList<QPair<QDateTime, double> > *> &mapper)
{
    mapper.insert("t2m", &observations.temperatureObservations);
    mapper.insert("ws_10min", &observations.windObservations);
    mapper.insert("n_man", &observations.cloudinessObservations);
    //new parameters and lists can be added here
}


