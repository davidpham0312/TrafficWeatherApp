#include "xml2weatherdataconverter.h"

Xml2WeatherDataConverter::Xml2WeatherDataConverter()
{
}

bool Xml2WeatherDataConverter::process(QByteArray data)
{
    populateParameter2ListMapper(parameter2ListMapper);
    QXmlStreamReader xml(data);

    //finding document start element
    while (!xml.atEnd() && xml.name().toString() != "FeatureCollection" ) xml.readNextStartElement();

     //jump to first "member" element if everything is OK
    if(!xml.atEnd() && xml.name().toString() == "FeatureCollection" )
        xml.readNextStartElement();
    else
        return false; /*error: doc may be empty*/

    // go through the entire document untill location 0 data is parsed
    while (!xml.atEnd()) {

        // find the elements containing data of interest
        // needed element is <result>
        QString tempName = "debugme";
        bool tempBool;

        while (!xml.atEnd()) {
            tempName = xml.name().toString();
            tempBool = (tempName == "member") || (tempName == "PointTimeSeriesObservation");
            if(tempBool){
                xml.readNextStartElement();
            }
            else if(xml.isEndElement()){
                xml.readNextStartElement();
            }
            else if (tempName == "result"){
                break;
            }
            else {
                xml.skipCurrentElement();
            }
        }

        // double check if we are in the correct spot
        // At this point we should be in a featureOfInterest element
        if(!xml.hasError() && tempName == "result")
            xml.readNextStartElement();
        else return false; /*Error*/

        // At this point we should be in a MeasurementTimeseries element
        int locationNbr;
        QString parameter;
        tempName = xml.name().toString();


        if(!xml.hasError() && tempName == "MeasurementTimeseries")
        {
            //1- check if this is the first location
             // SF_SpatialSamplingFeature
            auto tempList = xml.attributes().at(0).value().toString().split("-");
            if(tempList.isEmpty()) return false; /*ERROR*/ ;
            int size = tempList.size();
            locationNbr = tempList.at(size-2).toInt(); //generally location nbr is brefore the last element in the list
            parameter = tempList.at(size-1); //generally parameter is last element in the list

            //exit the loop since we only care about the first location
            if (locationNbr > 1) break;

            //now we will read all time value pairs and stops at the end of MeasurementTimeseries element

            //map the parameter to a list in the subclass forecastdata or observationdata member and parse data to it
            auto list = parameter2ListMapper.value(parameter, nullptr);
            if(list != nullptr) parseData(xml, list);
        }
    }
    if (xml.hasError()) return false;
    else return true;
}


bool Xml2WeatherDataConverter::parseData(QXmlStreamReader &xml, QList<QPair<QDateTime, double> > *list)
{
    if(xml.name().toString() != "MeasurementTimeseries") return false; //must start from a result
    xml.readNextStartElement();// go to the first <Point>

    while (!xml.atEnd()) { //Now we are at "Point" element

        //qDebug() << "----------------------------------";
        QPair<QDateTime, double> dataSample;

        xml.readNextStartElement();// go to MeasurementTVP element

        xml.readNextStartElement();// go to "time" element
        QString date = xml.readElementText();
        dataSample.first = QDateTime::fromString(date, Qt::ISODate); //this also skips to end of element
        // qDebug() << "> time: " << dataSample.first;

        xml.readNextStartElement();// go to "value" element
        dataSample.second = xml.readElementText().toDouble();
        // qDebug() << "> value: " << dataSample.second;
        if(!std::isnan(dataSample.second)) list->append(dataSample);

        xml.skipCurrentElement();// go to "MeasurementTVP" end
        xml.skipCurrentElement();// go to this "Point" element end
        xml.readNextStartElement();// go to Next Point or MeasurementTimeseries if all points are read
        if(xml.name().toString() == "MeasurementTimeseries") break; //end for this data is reached

    }
    return true;
}

