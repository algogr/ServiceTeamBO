#ifndef CUSTOMER_H
#define CUSTOMER_H

#include <QObject>
#include <QtSql/QSqlDatabase>
#include "algosqlquerymodel.h"
#include "algosqltablemodel.h"



class Customer : public QObject
{
    Q_OBJECT
public:
    explicit Customer(QObject *parent = nullptr);

    Q_INVOKABLE QString Code() const;
    Q_INVOKABLE void setCode(const QString &Code);

    Q_INVOKABLE QString Name() const;
    Q_INVOKABLE void setName(const QString &Name);

    Q_INVOKABLE QString Location() const;
    Q_INVOKABLE void setLocation(const QString &Location);


    Q_INVOKABLE QString City() const;
    Q_INVOKABLE void setCity(const QString &City);

    Q_INVOKABLE QString County() const;
    Q_INVOKABLE void setCounty(const QString &County);

    Q_INVOKABLE QString Address() const;
    Q_INVOKABLE void setAddress(const QString &Address);

    Q_INVOKABLE QString Email() const;
    Q_INVOKABLE void setEmail(const QString &Email);

    Q_INVOKABLE QString Phone1() const;
    Q_INVOKABLE void setPhone1(const QString &Phone1);

    Q_INVOKABLE QString Phone2() const;
    Q_INVOKABLE void setPhone2(const QString &Phone2);

    Q_INVOKABLE QString PC() const;
    Q_INVOKABLE void setPC(const QString &PC);



    int Id() const;
    void setId(int Id);

    int ErpId() const;
    void setErpId(int ErpId);

    void persist(const QList<QAbstractItemModel*> &tableList);
    void retrieve(const QList<QAbstractItemModel*> &tableList);
    void createToErp(AlgoSqlTableModel* model);
    void createToLocal(AlgoSqlTableModel* model);


    QString LoopNumber() const;
    void setLoopNumber(const QString &LoopNumber);

    int OriginatorId() const;
    void setOriginatorId(int OriginatorId);

    double Longitude() const;
    void setLongitude(double Longitude);

    double Latitude() const;
    void setLatitude(double Latitude);

private:
    QString m_Code,m_Name,m_Location,m_City,m_County,m_Address,m_Email,m_Phone1,m_Phone2,m_PC,m_LoopNumber;
    int m_Id,m_ErpId,m_OriginatorId;
    double m_Longitude,m_Latitude;
    int fetchLastErpid(AlgoSqlTableModel *model);



signals:

public slots:
};

#endif // CUSTOMER_H
