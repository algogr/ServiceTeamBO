#include "originator.h"
#include "algosqltablemodel.h"
#include <QDebug>
#include <QSqlError>
#include <QSqlRecord>

Originator::Originator(QObject *parent)

{


}

QString Originator::Name() const
{
    return m_Name;
}

void Originator::setName(const QString &Name)
{
    m_Name = Name;
}

int Originator::Id() const
{
    return m_Id;
}

void Originator::setId(int Id)
{
    m_Id = Id;
}

int Originator::ErpId() const
{
    return m_ErpId;
}

void Originator::setErpId(int ErpId)
{
    m_ErpId = ErpId;
}

void Originator::persist(const QList<QAbstractItemModel *> &tableList)
{

    AlgoSqlTableModel *ol= qobject_cast<AlgoSqlTableModel*> (tableList.at(2));

    ol->setTable("Originator");
    ol->setFilter("name='"+Name()+"'");
    ol->select();
    qDebug()<<"Row with name WIND:"<<ol->rowCount();
    //TODO  Add code when ERP connection is ready
    if (ol->rowCount()==0)
    {

        ol->setFilter("");
        ol->select();

        QSqlRecord r= ol->record();
        r.setValue("name",Name());
        ol->insertRecord(-1,r);
        if(ol->submitAll()) {
            ol->database().commit();
        }
        else {
            ol->database().rollback();
                    qDebug() << "Database Write Error" <<
                         "The database reported an error: " <<
                          ol->lastError().text();

        }




    }
    else
    {
        return;

    }


}


void Originator::retrieve(const QList<QAbstractItemModel*> &tableList)
{

}

