// standard C++ header:
#include <iostream>
#include <string>
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QSslConfiguration>
#include "algogmapsapimanipulator.h"
// Qt header:
#include <QDebug>
#include <QVariantList>
#include "algolocation.h"

#include <QJsonDocument>
#include <QJsonObject>

#include <QVariantMap>
#include <QEventLoop>

using namespace std;

AlgoLocation::AlgoLocation(QObject *parent,const QString &address) : QObject(parent),m_Address(),m_PostalCode(),m_Long(0),m_Lat(0),\
  m_Manager(),m_Request(),m_Reply(NULL)
{
    m_Address=address;
    qDebug()<<"Google Request:";
    QString url="http://maps.google.com/maps/api/geocode/json?key=AIzaSyA33bC9t0jf0dCqQimRWZvA6hrEZcKYmOI&address="+m_Address;
    QSslConfiguration config = QSslConfiguration::defaultConfiguration();
    config.setProtocol(QSsl::TlsV1_2);
    m_Request.setSslConfiguration(config);
    m_Request.setUrl(QUrl(url));
    m_Request.setHeader(QNetworkRequest::ServerHeader, "application/json");

    m_Reply = m_Manager.get(m_Request);
    QEventLoop loop;
    connect(&m_Manager,SIGNAL(finished(QNetworkReply*)),this,SLOT(replyFinished(QNetworkReply*)));
    loop.exec();



}

void AlgoLocation::replyFinished(QNetworkReply *reply)
{
    qDebug()<<"Google Responese:";

        QVariantList addressDetails=readResults(reply->readAll());
        m_Long=addressDetails.at(0).toDouble();
        m_Lat=addressDetails.at(1).toDouble();
        m_PostalCode=addressDetails.at(2).toString();




}

QString AlgoLocation::PostalCode() const
{
    return m_PostalCode;
}

void AlgoLocation::setPostalCode(const QString &PostalCode)
{
    m_PostalCode = PostalCode;
}

QString AlgoLocation::Address() const
{
    return m_Address;
}

void AlgoLocation::setAddress(const QString &Address)
{
    m_Address = Address;
}

double AlgoLocation::Lat() const
{
    return m_Lat;
}

void AlgoLocation::setLat(double Lat)
{
    m_Lat = Lat;
}

double AlgoLocation::Long() const
{
    return m_Long;
}

void AlgoLocation::setLong(double Long)
{
    m_Long = Long;
}

QVariantList AlgoLocation::readResults(const QString &jsonData)
{
    QJsonDocument d = QJsonDocument::fromJson(jsonData.toUtf8());
    qDebug()<<"document:"<<d;

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


