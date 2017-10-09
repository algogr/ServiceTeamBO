#ifndef ALGOLOCATION_H
#define ALGOLOCATION_H

#include <QObject>
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QSslConfiguration>

class AlgoLocation : public QObject
{
    Q_OBJECT
public:
    explicit AlgoLocation(QObject *parent = nullptr,const QString &address=QString());


    double Long() const;
    void setLong(double Long);

    double Lat() const;
    void setLat(double Lat);

    QString Address() const;
    void setAddress(const QString &Address);

    QString PostalCode() const;
    void setPostalCode(const QString &PostalCode);
    static QVariantList readResults(const QString &jsonData);

signals:

public slots:
    void replyFinished(QNetworkReply* reply);

private:
    QString m_Address,m_PostalCode;
    double m_Long,m_Lat;

    QNetworkAccessManager m_Manager;
    QNetworkRequest m_Request;
    QNetworkReply* m_Reply;

};

#endif // ALGOLOCATION_H
