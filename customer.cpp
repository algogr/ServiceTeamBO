#include "customer.h"
#include "algosqltablemodel.h"
#include "algolocation.h"
#include <QSqlQuery>
#include <QSqlRecord>
#include <QDebug>
#include <QSqlError>
#include <QTextCodec>
#include <QThread>
#include <QDir>
#include <QMutex>
#include <QSettings>

Customer::Customer(QObject *parent):QObject(),m_Id(),m_ErpId(),m_Name(),\
  m_Location(),m_City(),m_County(),m_Address(),m_Email(),\
  m_Phone1(),m_Phone2(),m_PC()

{

}

QString Customer::Code() const
{
    return m_Code;
}

void Customer::setCode(const QString &Code)
{
    m_Code = Code;
}

QString Customer::Name() const
{
    return m_Name;
}

void Customer::setName(const QString &Name)
{
    m_Name = Name;
}

QString Customer::Location() const
{
    return m_Location;
}

void Customer::setLocation(const QString &Location)
{
    m_Location = Location;
}


QString Customer::City() const
{
    return m_City;
}

void Customer::setCity(const QString &City)
{
    m_City = City;
}

QString Customer::County() const
{
    return m_County;
}

void Customer::setCounty(const QString &County)
{
    m_County = County;
}

QString Customer::Address() const
{
    return m_Address;
}

void Customer::setAddress(const QString &Address)
{
    m_Address = Address;
}

QString Customer::Email() const
{
    return m_Email;
}

void Customer::setEmail(const QString &Email)
{
    m_Email = Email;
}

QString Customer::Phone1() const
{
    return m_Phone1;
}

void Customer::setPhone1(const QString &Phone1)
{
    m_Phone1 = Phone1;
}


QString Customer::Phone2() const
{
    return m_Phone2;
}

void Customer::setPhone2(const QString &Phone2)
{
    m_Phone2 = Phone2;
}

QString Customer::PC() const
{
    return m_PC;
}

void Customer::setPC(const QString &PC)
{
    m_PC = PC;
}

int Customer::Id() const
{
    return m_Id;
}

void Customer::setId(int Id)
{
    m_Id = Id;
}

int Customer::ErpId() const
{
    return m_ErpId;
}

void Customer::setErpId(int ErpId)
{
    m_ErpId = ErpId;
}

void Customer::persist(const QList<QAbstractItemModel*> &tableList)
{
    QMutex mutex;
    mutex.lock();
    AlgoSqlTableModel *cl= qobject_cast<AlgoSqlTableModel*> (tableList.at(0));
    AlgoSqlTableModel *ce= qobject_cast<AlgoSqlTableModel*> (tableList.at(1));
    AlgoSqlTableModel *cte= qobject_cast<AlgoSqlTableModel*> (tableList.at(6));
    //TODO What to do if exists (RETRIVE???)
    ce->setFilter("phone01='"+Phone1()+"'");
    ce->setSort(13,Qt::AscendingOrder);
    ce->select();

    if (ce->rowCount()==0)
    {

        setCode(createErpCode(ce));
        createToErp(cte);

        setErpId(fetchLastErpid(ce));
        qDebug()<<"ERPID:"<<ErpId();

        createToLocal(cl);
        mutex.unlock();
        return;
    }
    else
    {
        qDebug()<<"FFFFFFFOOOOOOUUUUUNNNFFFFFFFFFF";

        setErpId(ce->data(ce->index(0,3)).toInt());
        setCode(ce->data(ce->index(0,4)).toString());
        QVariant erpid=ErpId();

        QSqlQuery query("select distinct ccceteria from findoc where trdr="+erpid.toString()+" order by trndate desc",ce->database());

        query.exec();
        query.next();
        if (query.value(0).toInt()!=OriginatorId())
        {
            setCode(createErpCode(ce));
            createToErp(cte);
            setErpId(fetchLastErpid(ce));
            createToLocal(cl);
            mutex.unlock();
            return;
        }

        QString address1=ce->data(ce->index(0,24)).toString()+"+"+ce->data(ce->index(0,25)).toString();
        QString address2=Address()+"+"+Location()+"+"+City();
        AlgoLocation loc1(0,address1);
        AlgoLocation loc2(0,address2);
        if (loc1.Long()==loc2.Long() && loc1.Lat()==loc2.Lat())
        {
            QVariant cerpid=ErpId();
            qDebug()<<"2 Query";
            QSqlQuery query("select id from Customer where erpid= "+cerpid.toString());
            qDebug()<<"2 Query";
            query.exec();
            query.next();
            setId(query.value(0).toInt());
        }
        else
        {
            setCode(createErpCode(ce));
            createToErp(cte);
            setErpId(fetchLastErpid(ce));
            createToLocal(cl);
            mutex.unlock();
            return;
        }








    }


}


void Customer::retrieve(const QList<QAbstractItemModel*> &tableList)
{

}

void Customer::createToErp(AlgoSqlTableModel* model)
{
    model->setFilter("");
    model->select();
    qDebug()<<"ErpId:"<<ErpId()<<"ID:"<<Id();

    QSqlRecord r= model->record();

    r.setValue("code",Code());
    r.setValue("address",Address());
    r.setValue("city",City());
    r.setValue("cccperioxi",Location().left(30));
    r.setValue("cccnomos",County().left(30));
    r.setValue("phone01",Phone1());
    r.setValue("phone02",Phone2().left(20));
    r.setValue("cccphone02",Phone2());
    r.setValue("cccdbf",LoopNumber().left(30));
    r.setValue("name",Name());
    r.setValue("ccceteria",OriginatorId());
    r.setValue("isins",0);
    r.remove(0);
    model->insertRecord(-1,r);

    if(model->submitAll()) {

        qDebug()<<"Commit";
        model->database().commit();

        ag:QThread::msleep(2000);

        QDir::setCurrent("c:\\algo\\autoimport");
        system("AutoRunCusImport.bat");
        QThread::msleep(2000);
        QString querystr="select trdr from trdr where sodtype=13 and code='"+Code()+"'";
        qDebug()<< querystr;
        QSqlDatabase db(model->database());
        //db.open();
        QSqlQuery query(db);
        query.exec(querystr);
        if (!query.next())
            goto ag;


    }
    else {
        model->database().rollback();
                qDebug() << "Database Write Error" <<
                     "The database reported an error: " <<
                      model->lastError().text();

    }

    model->select();



}

void Customer::createToLocal(AlgoSqlTableModel* model)
{

    model->setFilter("");
    model->select();
    //TODO Problem with google maps
    /*
    AlgoLocation loc(0,Address());

    setLatitude(loc.Lat());
    setLongitude(loc.Long());
    setPC(loc.PostalCode());
    */

    QSqlRecord r= model->record();

    r.setValue("erpid",ErpId());

    r.setValue("lockid",0);
    r.setValue("name",Name());
    r.setValue("location",Location());
    r.setValue("city",City());
    r.setValue("county",County());
    r.setValue("address",Address());
    r.setValue("phone1",Phone1());
    r.setValue("phone2",Phone2());
    r.setValue("postalcode",PC());
    r.setValue("loopnumber",LoopNumber());
    r.setValue("originatorid",OriginatorId());
    r.setValue("longtitude",Longitude());
    r.setValue("latitude",Latitude());


    model->insertRecord(-1,r);
    if(model->submitAll()) {
        model->database().commit();
    }
    else {
        model->database().rollback();
                qDebug() << "Database Write Error" <<
                     "The database reported an error: " <<
                      model->lastError().text();

    }

    model->setSort(0,Qt::DescendingOrder);
    model->select();

    setId(model->data(model->index(0,0)).toInt());

}

QString Customer::createErpCode(AlgoSqlTableModel* model)
{


    QString querystr="select max(Cast(code AS INTEGER)) from trdr where sodtype=13";
    QSqlDatabase db(model->database());
    //db.open();
    QSqlQuery query(db);
    query.prepare(querystr);
    query.exec();
    query.next();
    int lastCode=query.value(0).toInt()+1;
    QVariant vCode=lastCode;
    QString code=QString("%1").arg(vCode.toInt(),6,10,QChar('0'));
    //db.close();
    qDebug()<<"ERPCODE:"<<code;
    return code;




}

QString Customer::LoopNumber() const
{
    return m_LoopNumber;
}

void Customer::setLoopNumber(const QString &LoopNumber)
{
    m_LoopNumber = LoopNumber;
}

int Customer::OriginatorId() const
{
    return m_OriginatorId;
}

void Customer::setOriginatorId(int OriginatorId)
{
    m_OriginatorId = OriginatorId;
}

double Customer::Longitude() const
{
    return m_Longitude;
}

void Customer::setLongitude(double Longitude)
{
    m_Longitude = Longitude;
}

double Customer::Latitude() const
{
    return m_Latitude;
}

void Customer::setLatitude(double Latitude)
{
    m_Latitude = Latitude;
}


int Customer::fetchLastErpid(AlgoSqlTableModel *model)
{

    QString querystr="select trdr from trdr where sodtype=13 and code='"+Code()+"'";
    qDebug()<< querystr;
    QSqlDatabase db(model->database());
    //db.open();
    QSqlQuery query(db);
    ag:query.exec(querystr);
    if (!query.next())
        goto ag;


    return query.value(0).toInt();


}


