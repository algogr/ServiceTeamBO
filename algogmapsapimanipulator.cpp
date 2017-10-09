#include "algogmapsapimanipulator.h"
#include <QDebug>
#include <QJsonDocument>
#include <QJsonObject>
#include <QVariantList>
#include <QVariantMap>

AlgoGMapsApiManipulator::AlgoGMapsApiManipulator()
{
    //Tutorial is here:http://erickveil.github.io/2016/04/06/How-To-Manipulate-JSON-With-C++-and-Qt.html

}

QString AlgoGMapsApiManipulator::readPostalCode(const QString &jsonData)
{

    QJsonDocument d = QJsonDocument::fromJson(jsonData.toUtf8());
    qDebug()<<"d:"<<d;

    QJsonObject rootObject = d.object();

    QVariantMap rootMap=rootObject.toVariantMap();

    QVariantList resultsList=rootMap["results"].toList();


    QVariantMap zeroMap=resultsList[0].toMap();

    QVariantList addressComponentList=zeroMap["address_components"].toList();
    QVariantMap fiveList=addressComponentList[5].toMap();

    QString postalCode=fiveList["long_name"].toString();

    return postalCode;
}

QVariantList AlgoGMapsApiManipulator::readLocation(const QString &jsonData)
{
    QJsonDocument d = QJsonDocument::fromJson(jsonData.toUtf8());


    QJsonObject rootObject = d.object();

    QVariantMap rootMap=rootObject.toVariantMap();

    QVariantList resultsList=rootMap["results"].toList();


    QVariantMap zeroMap=resultsList[0].toMap();

    QVariantMap geometryMap=zeroMap["geometry"].toMap();

    QVariantMap locationMap=geometryMap["location"].toMap();

    QVariantList coordinates;
    coordinates<<locationMap["lng"]<<locationMap["lat"];

    return coordinates;
}

QVariantList AlgoGMapsApiManipulator::readResults(const QString &jsonData)
{
    QJsonDocument d = QJsonDocument::fromJson(jsonData.toUtf8());
    qDebug()<<"d:"<<d;

    QJsonObject rootObject = d.object();

    QVariantMap rootMap=rootObject.toVariantMap();

    QVariantList resultsList=rootMap["results"].toList();


    QVariantMap zeroMap=resultsList[0].toMap();

    QVariantList addressComponentList=zeroMap["address_components"].toList();
    QVariantMap fiveList=addressComponentList[5].toMap();

    QString postalCode=fiveList["long_name"].toString();

    QVariantMap geometryMap=zeroMap["geometry"].toMap();

    QVariantMap locationMap=geometryMap["location"].toMap();

    QVariantList addressDetails;
    addressDetails<<locationMap["lng"]<<locationMap["lat"]<<postalCode;

    return addressDetails;



}

